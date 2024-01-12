/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:02:07 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/12 19:37:08 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static void	trim( std::string &str );
static bool	isValidDate( std::string &date );
static int	convertDate( const char **str, char sep, int size );
static bool	isValidDate( int year, int month, int day );
static bool	isLeapYear( int year );

/* ************************************************************************** */
/*                         Constructors & Destructors                         */
/* ************************************************************************** */

BitcoinExchange::BitcoinExchange( void )
{
}

BitcoinExchange::BitcoinExchange( const char *dataFile )
{
	this->setData(dataFile);
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange &src )
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange( void )
{
}

/* ************************************************************************** */
/*                              Operator overload                             */
/* ************************************************************************** */

BitcoinExchange	&BitcoinExchange::operator=( const BitcoinExchange &src )
{
	if (this != &src)
		this->_data = src._data;

	return (*this);
}

/* ************************************************************************** */
/*                           Public member functions                          */
/* ************************************************************************** */

void	BitcoinExchange::setData( const char *dataFile )
{
	std::string		line;
	std::ifstream	file;

	file.open(dataFile);
	if (!file.is_open())
		throw FileException();

	while (std::getline(file, line))
	{
		if (line.empty() || line == "date,exchange_rate")
			continue;

		try
		{
			this->addDateToData(line);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << line << std::endl;

			throw InvalidDatabaseException();
		}
	}
}

void	BitcoinExchange::addDateToData( const std::string &line )
{
	std::string	date;
	double	price;
	size_t	pos;
	char	*endptr;

	pos = line.find(",");
	if (pos == std::string::npos || pos == 0 || pos == line.size() - 1)
		throw InvalidDataException();

	date = line.substr(0, pos);

	if (!isValidDate(date))
		throw InvalidDataException();

	price = std::strtod(line.substr(pos + 1).c_str(), &endptr);
	if (*endptr != '\0')
		throw InvalidDataException();

	if (this->_data.find(date) != this->_data.end())
		throw DateAlreadyExistsException();

	this->_data[date] = price;
}

double	BitcoinExchange::getPrice( std::string date ) const
{
	std::map<std::string, double>::const_iterator	it;
	std::map<std::string, double>::const_iterator	lower_bound;
	std::map<std::string, double>::const_iterator	upper_bound;

	if (!isValidDate(date))
		throw InvalidDateException();

	it = this->_data.find(date);
	if (it != this->_data.end())
		return (it->second);

	if (date < this->_data.begin()->first)
		return (this->_data.begin()->second);
	else if (date > this->_data.rbegin()->first)
		return (this->_data.rbegin()->second);

	lower_bound = this->_data.upper_bound(date);
	upper_bound = lower_bound--;

	if (upper_bound->first.compare(date) < -lower_bound->first.compare(date))
		return (upper_bound->second);

	return (lower_bound->second);
}

void	BitcoinExchange::exchangeRequest( std::string &line )	const
{
	std::string	date;
	double		nb;
	size_t		pos;
	char		*endptr;

	pos = line.find("|");
	if (pos == std::string::npos || pos == 0 || pos == line.size() - 1)
	{
		std::cout << "Error: bad input => " << line << std::endl;

		return;
	}

	date = line.substr(0, pos);
	if (!isValidDate(date))
	{
		std::cout << "Error: bad input => " << line << std::endl;

		return;
	}

	nb = std::strtod(line.substr(pos + 1).c_str(), &endptr);
	if (*endptr != '\0')
		std::cout << "Error: bad input => " << line << std::endl;
	else if (nb < 0)
		std::cout << "Error: not a positive number." << std::endl;
	else if (nb > 1000)
		std::cout << "Error: too large a number." << std::endl;
	else
		std::cout << date << " => " << nb << " = " << (nb * getPrice(date)) << std::endl;
}

void	BitcoinExchange::exchangeInputFile( const char *filename ) const
{
	std::ifstream			file;
	std::string				line;

	file.open(filename);
	if (!file.is_open())
		throw FileException();

	while (std::getline(file, line))
	{
		trim(line);

		if (line.empty() || line == "date|value")
			continue;

		exchangeRequest(line);
	}

	file.close();
}

/* ************************************************************************** */
/*                            Exceptions functions                            */
/* ************************************************************************** */

const char	*BitcoinExchange::FileException::what( void ) const throw()
{
	return ("Error: could not open file: ");
}

const char	*BitcoinExchange::InvalidDataException::what( void ) const throw()
{
	return ("Error: invalid data: ");
}

const char	*BitcoinExchange::DateAlreadyExistsException::what( void ) const throw()
{
	return ("Error: date already exists: ");
}

const char	*BitcoinExchange::InvalidDatabaseException::what( void ) const throw()
{
	return ("Error: invalid database: ");
}

const char	*BitcoinExchange::InvalidDateException::what( void ) const throw()
{
	return ("Error: invalid date: ");
}

/* ************************************************************************** */
/*                             Non-member functions                           */
/* ************************************************************************** */

static void	trim( std::string &str )
{
	if (str.empty())
		return;

	size_t firstIsSpace = str.find_first_of("\t\n\v\f\r ");
	size_t firstNoSpace = str.find_first_not_of("\t\n\v\f\r ", firstIsSpace);

	while (firstIsSpace != std::string::npos)
	{
		str.erase(firstIsSpace, firstNoSpace - firstIsSpace);
		firstIsSpace = str.find_first_of("\t\n\v\f\r ");
		firstNoSpace = str.find_first_not_of("\t\n\v\f\r ", firstIsSpace);
	}
}

static bool	isValidDate( std::string &date )
{
	int			year;
	int			month;
	int			day;
	const char	*ptr = date.c_str();

	if (date.size() != 10)
		return (false);

	year = convertDate(&ptr, '-', 4);
	month = convertDate(&ptr, '-', 2);
	day = convertDate(&ptr, '\0', 2);

	if (!isValidDate(year, month, day))
		return (false);

	return (true);
}

static int	convertDate( const char **str, char sep, int size )
{
	int		nb;
	char	*endptr;

	nb = strtol (*str, &endptr, 10);
	if (endptr == *str || *endptr != sep || endptr - *str != size)
		return (-1);

	*str = ++endptr;

	return (nb);
}

static bool	isValidDate( int year, int month, int day )
{
	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);

	if (month == 2 && (day > 29 || (day > 28 && !isLeapYear(year))))
		return (false);

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);

	return (true);
}

static bool	isLeapYear( int year )
{
	return ((!(year % 4) && year % 100) || !(year % 400));
}
