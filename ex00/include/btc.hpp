/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:43:45 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/13 18:37:17 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTC_HPP
# define BTC_HPP

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <map>

/* ************************************************************************** */
/*                                   utils                                    */
/* ************************************************************************** */

void	trim( std::string &str );
int		dateToInt( const std::string &date );
int		getData( std::map<int, double> &data, const std::string &filename );
int		exeInput( const std::map<int, double> &data, const std::string &filename );

#endif
