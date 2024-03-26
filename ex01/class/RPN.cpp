/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:50:03 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/26 14:07:56 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static bool	isOperator( char c );

/* ************************************************************************** */
/*                           Public member functions                          */
/* ************************************************************************** */

float	RPN::calculate( const std::string &str )
{
	std::stack<float , std::list<float> >	stack;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
			continue ;
		else if (str[i] == '-' && isdigit(str[i + 1]) && (str[i + 2] == ' ' || str[i + 2] == '\0'))
			stack.push(-1 * (str[++i] - '0'));
		else if (str[i + 1] != ' ' && str[i + 1] != '\0')
			throw std::invalid_argument("Error");
		else if (isOperator(str[i]))
			RPN::_applyOperator(str[i] , stack);
		else if (isdigit(str[i]))
			stack.push(str[i] - '0');
		else
			throw std::invalid_argument("Error");
	}

	if (stack.size() != 1)
		throw std::invalid_argument("Error");

	return (stack.top());
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

void	RPN::_applyOperator( char c , std::stack<float , std::list<float> > &stack )
{
	float	a;
	float	b;

	if (stack.size() < 2)
		throw std::invalid_argument("Error");

	a = stack.top();
	stack.pop();
	b = stack.top();
	stack.pop();

	switch (c)
	{
		case '+':
			stack.push(b + a);
			break;
		case '-':
			stack.push(b - a);
			break;
		case '*':
			stack.push(b * a);
			break;
		case '/':
			if (a == 0)
				throw std::invalid_argument("Error");
			stack.push(b / a);
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
