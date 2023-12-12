/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:43:45 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/12 19:43:16 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTC_HPP
# define BTC_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <cstdlib>
# include <map>

void	trim( std::string &str );
int		dateToInt( const std::string &date );
std::map<int, double>	getData( const std::string &filename );

#endif
