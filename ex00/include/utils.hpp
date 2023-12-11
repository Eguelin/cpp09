/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:43:45 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/11 19:58:11 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <cstdlib>
# include <climits>

std::string					fileToString( std::string &filename );
map<std::string, double>	getData( std::string &filename );
bool						isValidDate( std::string &date );

#endif
