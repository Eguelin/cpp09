/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:50:03 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/26 14:07:10 by eguelin          ###   ########.fr       */
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

		static float	calculate( const std::string &str );

	private:

		RPN( void );
		RPN( const RPN &src );
		~RPN( void );

		RPN	&operator=( const RPN &src );

		static void	_applyOperator( char c , std::stack<float , std::list<float> > &stack );
};

#endif
