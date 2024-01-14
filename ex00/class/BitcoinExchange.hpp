/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:02:08 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/14 15:45:47 by eguelin          ###   ########lyon.fr   */
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


		static void		addData( const char *dataFile );
		static void		addDateToData( const std::string &line );
		static void		exchangeInputFile( const char *filename );
		static void		exchangeRequest( const std::string &line );

		class FileException: public std::exception
		{
			public:
				virtual const char	*what( void ) const throw();
		};

		class InvalidDataException: public std::exception
		{
			public:
				virtual const char	*what( void ) const throw();
		};

		class DateAlreadyExistsException: public std::exception
		{
			public:
				virtual const char	*what( void ) const throw();
		};

		class InvalidDatabaseException: public std::exception
		{
			public:
				virtual const char	*what( void ) const throw();
		};

		class InvalidDateException: public std::exception
		{
			public:
				virtual const char	*what( void ) const throw();
		};

	private:

		static std::map<int, double>	_data;

		BitcoinExchange( void );
		BitcoinExchange( const BitcoinExchange &src );
		~BitcoinExchange( void );

		BitcoinExchange	&operator=( const BitcoinExchange &src );

		static double	getPrice( int date );
};

#endif
