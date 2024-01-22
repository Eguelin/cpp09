/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:38:38 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/22 15:22:00 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>
#include <deque>

int main( int argc, const char **argv )
{
	std::vector<int>	vect;
	std::deque<int>		deque;

	(void)argc;
	try
	{
		vect = PmergeMe::strTabToContainer< std::vector<int> >(argv + 1);
		deque = PmergeMe::strTabToContainer< std::deque<int> >(argv + 1);

		std::cout << "Size: " << vect.size() << std::endl;

		std::cout << "Before:";
		for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;

		PmergeMe::sortContainer< std::vector<int>, std::vector<t_pair> >(vect);
		PmergeMe::sortContainer< std::deque<int>, std::deque<t_pair> >(deque);

		std::cout << "After:";
		for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return (1);
	}

	return (0);
}
