/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:38:38 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/21 20:11:21 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>
#include <list>

int main( int argc, const char **argv )
{
	std::vector<int>	vect;
	std::list<int>		list;

	(void)argc;
	try
	{
		vect = PmergeMe::strTabToContainer< std::vector<int> >(argv + 1);
		list = PmergeMe::strTabToContainer< std::list<int> >(argv + 1);

		std::cout << "Vector: ";
		for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;

		std::cout << "List: ";
		for (std::list<int>::iterator it = list.begin(); it != list.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;

		PmergeMe::sortContainer< std::vector<t_pair>, std::vector<int> >(vect);
		PmergeMe::sortContainer< std::list<t_pair>, std::list<int> >(list);
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return (1);
	}

	return (0);
}
