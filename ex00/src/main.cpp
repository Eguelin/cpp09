/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:38:38 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/13 15:06:46 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

int main( int argc, char **argv )
{
	std::map<int, double>	data;

	if (argc < 2)
	{
		std::cerr << "Error: could not open file." << std::endl;

		return (1);
	}

	if (getData(data, "./data.csv"))
		return (1);

	for (int i = 1; i < argc; i++)
		if (exeInput(data, argv[i]))
			return (1);

	return (0);
}
