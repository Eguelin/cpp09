/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:02:08 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/12 19:35:59 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <map>

class BitcoinExchange
{
	public:

		BitcoinExchange( void );
		BitcoinExchange( const char *dataFile );
		BitcoinExchange( const BitcoinExchange &src );
		~BitcoinExchange( void );

		BitcoinExchange	&operator=( const BitcoinExchange &src );

		void	setData( const char *dataFile );
		void	addDateToData( const std::string &line );
		double	getPrice( std::string date ) const;
		void 	exchangeRequest( std::string &line ) const;
		void 	exchangeInputFile( const char *filename ) const;

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

		std::map<std::string, double>	_data;
};

#endif
