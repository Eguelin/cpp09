/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:50:03 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/22 11:34:38 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <list>

class RPN
{
	public:

		static int	calculate( const std::string &str );

	private:

		static std::stack< int, std::list<int> >	_stack;

		RPN( void );
		RPN( const RPN &src );
		~RPN( void );

		RPN	&operator=( const RPN &src );

		static void	_applyOperator( char c );
};

#endif
