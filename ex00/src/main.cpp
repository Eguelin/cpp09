/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:38:38 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/14 15:33:55 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main( int argc, char **argv )
{
	const char	*dataFile = "data.csv";

	(void)argv;
	if (argc != 2)
	{
		std::cerr << "Error: wrong number of arguments" << std::endl;

		return (1);
	}

	try
	{
		BitcoinExchange::addData(dataFile);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << dataFile << std::endl;

		return (1);
	}

	try
	{
		BitcoinExchange::exchangeInputFile(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << argv[1] << std::endl;

		return (1);
	}

	return (0);
}
