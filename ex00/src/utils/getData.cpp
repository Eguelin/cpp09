/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getData.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:39:08 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/13 15:21:26 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

static bool	addLineToData( std::map<int, double> &data, const std::string &line );

int	getData( std::map<int, double> &data, const std::string &filename )
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

		if (line.empty() || line == "date,exchange_rate")
			continue;

		if (!addLineToData(data, line))
		{
			std::cerr << "Error: invalid line format: " << line << std::endl;
			file.close();

			return (1);
		}
	}

	file.close();

	return (0);
}

static bool	addLineToData( std::map<int, double> &data, const std::string &line )
{
	int		date;
	double	price;
	size_t	pos;
	char	*endptr;

	pos = line.find(",");
	if (pos == std::string::npos || pos == 0 || pos == line.size() - 1)
		return (false);

	date = dateToInt(line.substr(0, pos));

	if (date == -1)
		return (false);

	price = std::strtod(line.substr(pos + 1).c_str(), &endptr);
	if (*endptr != '\0')
		return (false);

	data[date] = price;

	return (true);
}
