/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:17:22 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/22 14:33:29 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <cstdlib>
# include <limits>
# include <algorithm>

typedef struct	s_pair
{
	int			first;
	int			second;
}				t_pair;

class PmergeMe
{
	public:

		template < typename T >
		static T	strTabToContainer( const char **strTab )
		{
			T	container;
			double		nb;
			char		*endPtr;

			while (*strTab)
			{
				nb = std::strtod(*strTab, &endPtr);

				if (nb > std::numeric_limits<int>::max() || *endPtr != '\0')
					throw (InvalidNumberException());
				else if (nb < 0)
					throw (NegativeNumberException());

				container.push_back(static_cast<int>(nb));

				strTab++;
			}

			return (container);
		};

		template < typename T, typename U >
		static void	sortContainer( T &container )
		{
			U	pair;
			int	tmp = -1;

			if (container.size() % 2 != 0)
			{
				tmp = container.back();
				container.pop_back();
			}

			pair = _pairingContainer<T, U>(container);
			_sortPair(pair);
			_mergeSortPair(pair);
			_insertFirst(container, pair, tmp);
			// _insertSecond(container, pair);
		};


		class	InvalidNumberException : public std::exception
		{
			public:

				virtual const char	*what( void ) const throw();
		};

		class	NegativeNumberException : public std::exception
		{
			public:

				virtual const char	*what( void ) const throw();
		};

	private:

		PmergeMe( void );
		PmergeMe( const PmergeMe &src );
		~PmergeMe( void );

		PmergeMe	&operator=( const PmergeMe &src );

		template < typename T, typename U >
		static U	_pairingContainer( T &container )
		{
			t_pair	pairTmp;
			U		pair;

			for (typename T::iterator it = container.begin(); it != container.end(); it++)
			{
				pairTmp.first = *(it++);
				pairTmp.second = *it;
				pair.push_back(pairTmp);
			}

			container.clear();

			return (pair);
		};

		template < typename T >
		static void	_sortPair( T &pair )
		{
			int	tmp;

			for (typename T::iterator it = pair.begin(); it != pair.end(); it++)
			{
				if (it->first < it->second)
				{
					tmp = it->first;
					it->first = it->second;
					it->second = tmp;
				}
			}
		};

		template < typename T >
		static void	_mergeSortPair( T &pair )
		{
			T	first;
			T	second;

			_splitPair(pair, first, second);

			if (first.size() > 1)
				_mergeSortPair(first);
			if (second.size() > 1)
				_mergeSortPair(second);

			_mergePair(pair, first, second);
		}

		template < typename T >
		static void	_mergePair( T &pair, T &first, T &second )
		{
			typename T::iterator	it_first = first.begin();
			typename T::iterator	it_second = second.begin();

			while (it_first != first.end() || it_second != second.end())
			{
				if (it_second == second.end() || (it_first != first.end() && it_first->first < it_second->first))
				{
					pair.push_back(*it_first);
					it_first++;
				}
				else
				{
					pair.push_back(*it_second);
					it_second++;
				}
			}
		}

		template < typename T >
		static void	_splitPair( T &pair, T &first, T &second )
		{
			int		i = pair.size() / 2;

			for (typename T::iterator it = pair.begin(); it != pair.end(); it++)
			{
				if (i-- > 0)
					first.push_back(*it);
				else
					second.push_back(*it);
			}

			pair.clear();
		}

		template < typename T, typename U >
		static void	_insertFirst( U &container, T &pair, int tmp )
		{
			container.push_back(pair.front().second);

			for (typename T::iterator it = pair.begin(); it != pair.end(); it++)
				container.push_back(it->first);

			if (tmp != -1)
			{
				t_pair	pairTmp;

				pairTmp.first = -1;
				pairTmp.second = tmp;
				pair.push_back(pairTmp);
			}
		};


};

#endif
