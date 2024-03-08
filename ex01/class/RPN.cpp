/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:50:03 by eguelin           #+#    #+#             */
/*   Updated: 2024/02/17 17:59:30 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static bool	isOperator( char c );

/* ************************************************************************** */
/*                           Public member functions                          */
/* ************************************************************************** */

int		RPN::calculate( const std::string &str )
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
			continue ;
		else if (str[i] == '-' && isdigit(str[i + 1]) && (str[i + 2] == ' ' || str[i + 2] == '\0'))
			RPN::_stack.push(-1 * (str[++i] - '0'));
		else if (str[i + 1] != ' ' && str[i + 1] != '\0')
			throw std::invalid_argument("Error");
		else if (isOperator(str[i]))
			RPN::_applyOperator(str[i]);
		else if (isdigit(str[i]))
			RPN::_stack.push(str[i] - '0');
		else
			throw std::invalid_argument("Error");
	}

	if (RPN::_stack.size() != 1)
		throw std::invalid_argument("Error");

	return (RPN::_stack.top());
}

/* ************************************************************************** */
/*                     Private constructors & destructors                     */
/* ************************************************************************** */

RPN::RPN( void )
{
}

RPN::RPN( const RPN &src )
{
	*this = src;
}

RPN::~RPN( void )
{
}

/* ************************************************************************** */
/*                         Private operator overload                          */
/* ************************************************************************** */

RPN	&RPN::operator=( const RPN &src )
{
	(void)src;

	return (*this);
}

/* ************************************************************************** */
/*                          Private member functions                          */
/* ************************************************************************** */

void	RPN::_applyOperator( char c )
{
	int		a;
	int		b;

	if (RPN::_stack.size() < 2)
		throw std::invalid_argument("Error");

	a = RPN::_stack.top();
	RPN::_stack.pop();
	b = RPN::_stack.top();
	RPN::_stack.pop();

	switch (c)
	{
		case '+':
			RPN::_stack.push(b + a);
			break;
		case '-':
			RPN::_stack.push(b - a);
			break;
		case '*':
			RPN::_stack.push(b * a);
			break;
		case '/':
			if (a == 0)
				throw std::invalid_argument("Error");
			RPN::_stack.push(b / a);
			break;
		default:
			throw std::invalid_argument("Error");
	}
}

/* ************************************************************************** */
/*                              Static functions                              */
/* ************************************************************************** */

static bool	isOperator( char c )
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

/* ************************************************************************** */
/*                      Static attributes initialization                      */
/* ************************************************************************** */

std::stack< int, std::list<int> >	RPN::_stack;
