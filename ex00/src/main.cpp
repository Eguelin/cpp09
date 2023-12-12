/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:38:38 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/12 19:27:43 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

int main( int argc, char **argv )
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	std::map<int, double>	data = getData("./data.csv");

	std::cout << "data.size() = " << data.size() << std::endl;
	std::cout << data.begin()->first << " -> " << data.begin()->second << std::endl;
	std::cout << data.rbegin()->first << " -> " << data.rbegin()->second << std::endl;

	return (0);
}
