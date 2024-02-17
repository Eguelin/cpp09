/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:38:38 by eguelin           #+#    #+#             */
/*   Updated: 2024/02/17 18:34:46 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main( int argc, char **argv )
{
	const char	*dataFile = "data.csv";

	(void)argv;
	if (argc != 2)
	{
		std::cout << "Error: wrong number of arguments" << std::endl;

		return (1);
	}

	try
	{
		BitcoinExchange bitcoinExchange(dataFile);

		bitcoinExchange.exchangeInputFile(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;

		return (1);
	}

	return (0);
}
