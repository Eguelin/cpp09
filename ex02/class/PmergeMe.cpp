/* ************************************************************************** */
/*                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:17:22 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/20 17:03:36 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/* ************************************************************************** */
/*                                 Exceptions                                 */
/* ************************************************************************** */

const char	*PmergeMe::InvalidNumberException::what( void ) const throw()
{
	return ("Invalid number");
}

const char	*PmergeMe::NegativeNumberException::what( void ) const throw()
{
	return ("Negative number");
}

/* ************************************************************************** */
/*                     Private constructors & destructors                     */
/* ************************************************************************** */

PmergeMe::PmergeMe( void )
{
}

PmergeMe::PmergeMe( const PmergeMe &src )
{
	*this = src;
}

PmergeMe::~PmergeMe( void )
{
}

/* ************************************************************************** */
/*                          Private operator overload                         */
/* ************************************************************************** */

PmergeMe	&PmergeMe::operator=( const PmergeMe &src )
{
	(void)src;

	return (*this);
}
