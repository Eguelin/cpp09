/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:43:45 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/12 19:38:07 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

void	trim( std::string &str )
{
	if (str.empty())
		return;

	size_t firstIsSpace = str.find_first_of("\t\n\v\f\r ");
	size_t firstNoSpace = str.find_first_not_of("\t\n\v\f\r ", firstIsSpace);

	while (firstIsSpace != std::string::npos)
	{
		str.erase(firstIsSpace, firstNoSpace - firstIsSpace);
		firstIsSpace = str.find_first_of("\t\n\v\f\r ");
		firstNoSpace = str.find_first_not_of("\t\n\v\f\r ", firstIsSpace);
	}
}
