/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dateToInt.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:02:47 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/12 19:43:44 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

static int	convertDate( const char **str, char sep, int size );
static bool	isValidDate( int year, int month, int day );
static bool	isLeapYear( int year );

int	dateToInt( const std::string &date )
{
	int			year;
	int			month;
	int			day;
	const char	*ptr = date.c_str();

	if (date.size() != 10)
		return (-1);

	year = convertDate(&ptr, '-', 4);
	month = convertDate(&ptr, '-', 2);
	day = convertDate(&ptr, '\0', 2);

	if (!isValidDate(year, month, day))
		return (-1);

	return (year * 10000 + month * 100 + day);
}

static int	convertDate( const char **str, char sep, int size )
{
	int		nb;
	char	*endptr;

	nb = strtod (*str, &endptr);
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
