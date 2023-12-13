/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeInput.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:20:32 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/13 15:28:56 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

static void		exeLine( const std::map<int, double> &data, const std::string &line );
static double	getPrice( const std::map<int, double> &data, int date );

int	exeInput( const std::map<int, double> &data, const std::string &filename )
{
	std::ifstream			file;
	std::string				line;

	file.open(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file " << filename << std::endl;

		return (1);
	}

	while (std::getline(file, line))
	{
		trim(line);

		if (line.empty() || line == "date|value")
			continue;

		exeLine(data, line);
	}

	file.close();

	return (0);
}

static void	exeLine( const std::map<int, double> &data, const std::string &line )
{
	std::string	strDate;
	int			date;
	double		nb;
	size_t		pos;
	char		*endptr;

	pos = line.find("|");
	if (pos == std::string::npos || pos == 0 || pos == line.size() - 1)
	{
		std::cerr << "Error: bad input => " << line << std::endl;

		return;
	}

	strDate = line.substr(0, pos);
	date = dateToInt(strDate);
	if (date == -1)
	{
		std::cerr << "Error: bad input => " << line << std::endl;

		return;
	}

	nb = std::strtod(line.substr(pos + 1).c_str(), &endptr);
	if (*endptr != '\0')
		std::cerr << "Error: bad input => " << line << std::endl;
	else if (nb < 0)
		std::cerr << "Error: not a positive number." << std::endl;
	else if (nb == 0)
		std::cout << strDate << " => " << nb << " = " << 0 << std::endl;
	else if (nb > 1000)
		std::cerr << "Error: too large a number." << std::endl;
	else
		std::cout << strDate << " => " << nb << " = " << (nb * getPrice(data, date)) << std::endl;
}

static double	getPrice( const std::map<int, double> &data, int date )
{
	std::map<int, double>::const_iterator	it;
	std::map<int, double>::const_iterator	lower_bound;
	std::map<int, double>::const_iterator	upper_bound;

	it = data.find(date);
	if (it != data.end())
		return (it->second);

	if (date < data.begin()->first)
		return (data.begin()->second);
	else if (date > data.rbegin()->first)
		return (data.rbegin()->second);

	lower_bound = data.lower_bound(date);
	upper_bound = data.upper_bound(date);

	if (upper_bound->first - date < date - lower_bound->first)
		return (upper_bound->second);

	return (lower_bound->second);
}
