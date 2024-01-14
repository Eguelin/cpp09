/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:50:03 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/13 08:03:02 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>

class RPN
{
	public:

		static int	calculate( const std::string &str );

	private:

		static std::stack<int>		_stack;

		RPN( void );
		RPN( const RPN &src );
		~RPN( void );

		RPN	&operator=( const RPN &src );

		static void	_applyOperator( char c );
};

#endif
