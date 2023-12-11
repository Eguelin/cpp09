/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:43:45 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/11 20:02:50 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string		fileToString( std::string filename )
{
	std::ifstream		file;
	std::stringstream	buffer;

	file.open( filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file " << filename << std::endl;
		return ("");
	}

	buffer << file.rdbuf();

	file.close();

	return (buffer.str());
}

void	trim( std::string &str )
{
	std::string::iterator	it = str.begin();

	if (str.empty())
		return ;

	while (it != str.end() && std::isspace(*it))
		it++;
	str.erase(str.begin(), it);

	if (str.empty())
		return ;

	it = str.end();
	while (it != str.begin() && std::isspace(*(it - 1)))
		it--;
	str.erase(it, str.end());
}

bool	isValidDate( std::string date )
{
	int	year;
	int		month;
	int		day;
	char	*ptr = date.c_str();

	if (std::sidigit(date.begin()))
		return (false);

	year = convertDate(&ptr, '-');
	if (year < 0)
		return (false);
	month = convertDate(&ptr, '-');
	if (month < 0 || month > 12)
		return (false);
	day = convertDate(&ptr, '\0');
	if (!isValidDay(month, day))
		return (false);

	return (true);
}

int	convertDate( char **str, char sep )
{
	int		nb;
	char	*endptr;

	nb = strtod (*str, &endptr);
	if (endptr == *str || *endptr != sep || \
	nb < std::numeric_limits<int>::min() || nb > std::numeric_limits<int>::max())
		return (-1);

	*str = ++endptr;

	return (nb);
}

