/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:02:07 by eguelin           #+#    #+#             */
/*   Updated: 2024/02/17 20:29:09 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static bool	checkDate( const std::string &date );
static int	convertDatePart( const char **str, const char sep, const int size );
static bool	isValidDate( const int year, const int month, const int day );
static bool	isLeapYear( const int year );

/* ************************************************************************** */
/*                          Constructor & Destructor                          */
/* ************************************************************************** */

BitcoinExchange::BitcoinExchange( const char *dataFile )
{
	std::string		line;
	std::ifstream	file;

	file.open(dataFile);
	if (!file.is_open())
		throw FileException("cannot open file: " + std::string(dataFile));
	else if (file.peek() == EOF)
		throw FileException("empty file: " + std::string(dataFile));

	while (std::getline(file, line))
	{
		if (line.empty() || line == "date,exchange_rate")
			continue;

		this->_addDateToData(line);
	}

	file.close();
}

BitcoinExchange::~BitcoinExchange( void )
{
}

/* ************************************************************************** */
/*                           Public static functions                          */
/* ************************************************************************** */

void	BitcoinExchange::exchangeInputFile( const char *filename )
{
	std::ifstream			file;
	std::string				line;

	file.open(filename);
	if (!file.is_open())
		throw FileException("cannot open file" + std::string(filename));
	else if (file.peek() == EOF)
		throw FileException("empty file: " + std::string(filename));

	while (std::getline(file, line))
	{
		if (line.empty() || line == "date | value")
			continue;

		try
		{
			this->exchangeRequest(line);
		}
		catch(const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	file.close();
}

void	BitcoinExchange::exchangeRequest( const std::string &line )
{
	std::string	date;
	double		nb;

	this->_getData(line, "|", date, nb);

	if (nb < 0)
		throw InvalidInputException("not a positive number");
	else if (nb > 1000)
		throw InvalidInputException("too big number");
	else if (date < BitcoinExchange::_data.begin()->first)
		throw InvalidInputException("date too early.");
	else
		std::cout << date << " => " << nb << " = " << (nb * _getPrice(date)) << std::endl;
}

/* ************************************************************************** */
/*                            Exceptions functions                            */
/* ************************************************************************** */

BitcoinExchange::FileException::FileException( const std::string &msg ) : _msg(msg)
{
}

BitcoinExchange::FileException::~FileException( void ) throw()
{
}

const char	*BitcoinExchange::FileException::what( void ) const throw()
{
	return (this->_msg.c_str());
}

BitcoinExchange::InvalidInputException::InvalidInputException( const std::string &msg ) : _msg(msg)
{
}

BitcoinExchange::InvalidInputException::~InvalidInputException( void ) throw()
{
}

const char	*BitcoinExchange::InvalidInputException::what( void ) const throw()
{
	return (this->_msg.c_str());
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

void	BitcoinExchange::_addDateToData( const std::string &line )
{
	std::string	date;
	double		nbr;

	this->_getData(line, ",", date, nbr);

	if (BitcoinExchange::_data.find(date) != BitcoinExchange::_data.end())
		throw InvalidInputException("duplicate date => " + line);

	this->_data[date] = nbr;
}

void	BitcoinExchange::_getData( const std::string &line, const std::string &sep, std::string &date, double &nbr )
{
	size_t		pos;

	pos = line.find(sep);
	if (pos == std::string::npos || pos == 0 || pos == line.size() - 1)
		throw InvalidInputException("bad input => " + line);

	date = line.substr(0, pos);
	if (!checkDate(date))
		throw InvalidInputException("bad input => " + line);

	nbr = this->_getNumber(line.substr(pos + sep.size()));
}

double	BitcoinExchange::_getNumber( const std::string &str )
{
	double	nbr;
	char	*endptr;

	nbr = strtod(str.c_str(), &endptr);
	if (*endptr != '\0')
		throw InvalidInputException("bad input => " + str);

	return (nbr);
}

double	BitcoinExchange::_getPrice( const std::string &date )
{
	std::map<std::string, double>::iterator	it;

	it = BitcoinExchange::_data.find(date);
	if (it != BitcoinExchange::_data.end())
		return (it->second);

	if (date > BitcoinExchange::_data.rbegin()->first)
		return (BitcoinExchange::_data.rbegin()->second);

	it = BitcoinExchange::_data.lower_bound(date);
	it--;

	return (it->second);
}

/* ************************************************************************** */
/*                             Non-member functions                           */
/* ************************************************************************** */

static bool	checkDate( const std::string &date )
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

	return (true);
}

static int	convertDatePart( const char **str, const char sep, const int size )
{
	int		nb;
	char	*endptr;

	nb = strtol (*str, &endptr, 10);
	if (endptr == *str || *endptr != sep || endptr - *str != size)
		return (-1);

	*str = ++endptr;

	return (nb);
}

static bool	isValidDate( const int year, const int month, const int day )
{
	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);

	if (month == 2 && (day > 29 || (day > 28 && !isLeapYear(year))))
		return (false);

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);

	return (true);
}

static bool	isLeapYear( const int year )
{
	return ((!(year % 4) && year % 100) || !(year % 400));
}
