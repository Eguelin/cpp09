/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:02:08 by eguelin           #+#    #+#             */
/*   Updated: 2024/02/17 20:02:43 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <map>
# include <algorithm>

class BitcoinExchange
{
	public:

		BitcoinExchange( const char *dataFile );
		~BitcoinExchange( void );

		void	exchangeInputFile( const char *filename );
		void	exchangeRequest( const std::string &line );

		class FileException: public std::exception
		{
			public:
				FileException( const std::string &msg );
				~FileException( void ) throw();
				virtual const char	*what( void ) const throw();
			private:
				std::string	_msg;
		};

		class InvalidInputException: public std::exception
		{
			public:
				InvalidInputException( const std::string &msg );
				~InvalidInputException( void ) throw();
				virtual const char	*what( void ) const throw();
			private:
				std::string	_msg;
		};

	private:

		std::map<std::string, double>	_data;

		BitcoinExchange( void );
		BitcoinExchange( const BitcoinExchange &src );

		BitcoinExchange	&operator=( const BitcoinExchange &src );

		void	_addDateToData( const std::string &line );
		double	_getNumber( const std::string &str );
		double	_getPrice( const std::string &date );
		void	_getData( const std::string &line, const std::string &sep, std::string &date, double &nbr );
};

#endif
