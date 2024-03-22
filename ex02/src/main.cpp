/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:38:38 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/22 17:09:44 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>
#include <deque>
#include <ctime>

int main( int argc, const char **argv )
{
	std::vector<int>	vect;
	std::deque<int>		deque;
	clock_t				startTime;
	clock_t				endTime;

	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " [int1] [int2] [int3] ..." << std::endl;

		return (1);
	}

	try
	{
		vect = PmergeMe::strTabToContainer< std::vector<int> >(argv + 1);

		std::cout << "Before:";
		for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;

		startTime = clock();
		vect = PmergeMe::strTabToContainer< std::vector<int> >(argv + 1);
		PmergeMe::sortContainer< std::vector<int>, std::vector<std::pair<int, int> > >(vect);
		endTime = clock();

		std::cout << "After:";
		for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;

		std::cout << "Time to process a range of " << vect.size();
		std::cout << " elements with std::vector : ";
		std::cout << static_cast<double>(endTime - startTime);
		std::cout << "us" << std::endl;

		startTime = clock();
		deque = PmergeMe::strTabToContainer< std::deque<int> >(argv + 1);
		PmergeMe::sortContainer< std::deque<int>, std::deque<std::pair<int, int> > >(deque);
		endTime = clock();

		std::cout << "Time to process a range of " << vect.size();
		std::cout << " elements with std::deque : ";
		std::cout << static_cast<double>(endTime - startTime);
		std::cout << "us" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;

		return (1);
	}

	return (0);
}
