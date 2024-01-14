/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:02:07 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/14 15:46:08 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static int	convertDate( const std::string &date );
static int	convertDatePart( const char **str, char sep, int size );
static bool	isValidDate( int year, int month, int day );
static bool	isLeapYear( int year );

/* ************************************************************************** */
/*                           Public static functions                          */
/* ************************************************************************** */

void	BitcoinExchange::addData( const char *dataFile )
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
			BitcoinExchange::addDateToData(line);
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
	int		date;
	double	price;
	size_t	pos;
	char	*endptr;

	pos = line.find(",");
	if (pos == std::string::npos || pos == 0 || pos == line.size() - 1)
		throw InvalidDataException();

	date = convertDate(line.substr(0, pos));
	if (date == -1)
		throw InvalidDataException();

	price = std::strtod(line.substr(pos + 1).c_str(), &endptr);
	if (*endptr != '\0')
		throw InvalidDataException();

	if (BitcoinExchange::_data.find(date) != BitcoinExchange::_data.end())
		throw DateAlreadyExistsException();

	BitcoinExchange::_data[date] = price;
}

void	BitcoinExchange::exchangeInputFile( const char *filename )
{
	std::ifstream			file;
	std::string				line;

	file.open(filename);
	if (!file.is_open())
		throw FileException();

	while (std::getline(file, line))
	{
		if (line.empty() || line == "date | value")
			continue;

		exchangeRequest(line);
	}

	file.close();
}

void	BitcoinExchange::exchangeRequest( const std::string &line )
{
	int			date;
	std::string	dateStr;
	double		nb;
	size_t		pos;
	char		*endptr;

	pos = line.find(" | ");
	if (pos == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;

		return;
	}

	dateStr = line.substr(0, pos);
	date = convertDate(dateStr);
	if (date == -1)
	{
		std::cout << "Error: bad input => " << line << std::endl;

		return;
	}

	pos = pos + 3;
	if (!isdigit(line[pos]))
	{
		std::cout << "Error: bad input => " << line << std::endl;

		return;
	}

	nb = std::strtod(line.substr(pos).c_str(), &endptr);
	if (*endptr != '\0')
		std::cout << "Error: bad input => " << line << std::endl;
	else if (nb < 0)
		std::cout << "Error: not a positive number." << std::endl;
	else if (nb > 1000)
		std::cout << "Error: too large a number." << std::endl;
	else
		std::cout << dateStr << " => " << nb << " = " << (nb * getPrice(date)) << std::endl;
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

/* ************************************************************************** */
/*                      Private constructor & destructor                      */
/* ************************************************************************** */

BitcoinExchange::BitcoinExchange( void )
{
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange &src )
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange( void )
{
}

/* ************************************************************************** */
/*                         Private operator overload                          */
/* ************************************************************************** */

BitcoinExchange	&BitcoinExchange::operator=( const BitcoinExchange &src )
{
	if (this != &src)
		BitcoinExchange::_data = src._data;

	return (*this);
}

/* ************************************************************************** */
/*                          Private static functions                          */
/* ************************************************************************** */

double	BitcoinExchange::getPrice( int date )
{
	std::map<int, double>::const_iterator	it;
	std::map<int, double>::const_iterator	lower_bound;
	std::map<int, double>::const_iterator	upper_bound;

	it = BitcoinExchange::_data.find(date);
	if (it != BitcoinExchange::_data.end())
		return (it->second);

	if (date < BitcoinExchange::_data.begin()->first)
		return (BitcoinExchange::_data.begin()->second);
	else if (date > BitcoinExchange::_data.rbegin()->first)
		return (BitcoinExchange::_data.rbegin()->second);

	lower_bound = BitcoinExchange::_data.upper_bound(date);
	upper_bound = lower_bound--;

	if (upper_bound->first - date < date - lower_bound->first)
		return (upper_bound->second);

	return (lower_bound->second);
}

/* ************************************************************************** */
/*                      Static attributes initialization                      */
/* ************************************************************************** */

std::map<int, double>	BitcoinExchange::_data;

/* ************************************************************************** */
/*                             Non-member functions                           */
/* ************************************************************************** */

static int	convertDate( const std::string &date )
{
	int			year;
	int			month;
	int			day;
	const char	*ptr = date.c_str();

	if (date.size() != 10)
		return (-1);

	year = convertDatePart(&ptr, '-', 4);
	month = convertDatePart(&ptr, '-', 2);
	day = convertDatePart(&ptr, '\0', 2);

	if (!isValidDate(year, month, day))
		return (false);

	return (year * 10000 + month * 100 + day);
}

static int	convertDatePart( const char **str, char sep, int size )
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
