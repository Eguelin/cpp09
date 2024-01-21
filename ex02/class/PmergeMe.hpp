/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:17:22 by eguelin           #+#    #+#             */
/*   Updated: 2024/01/21 19:59:07 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <cstdlib>
# include <limits>

typedef struct	s_pair
{
	int			first;
	int			second;
}				t_pair;

class PmergeMe
{
	public:

		template < typename Container >
		static Container	strTabToContainer( const char **strTab )
		{
			Container	container;
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

		template < typename PairContainer, typename Container >
		static void	sortContainer( Container &container )
		{
			PairContainer	pair;
			int				tmp = -1;

			if (container.size() % 2 != 0)
			{
				tmp = container.back();
				container.pop_back();
			}

			pair = _pairingContainer< PairContainer, Container >(container);
			_sortPairContainer(pair);
			container.clear();
			_mergeSortPairContainer(pair);

			if (tmp != -1)
			{
				t_pair	pairTmp;

				pairTmp.first = -1;
				pairTmp.second = tmp;
				pair.push_back(pairTmp);
			}

			std::cout << "Pair: ";
			for (typename PairContainer::iterator it = pair.begin(); it != pair.end(); it++)
				std::cout << "f:" << it->first << " " << "s:" << it->second << " | ";
			std::cout << std::endl;
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

		template < typename PairContainer, typename Container >
		static PairContainer	_pairingContainer( Container &container )
		{
			t_pair			pair;
			PairContainer	pairContainer;

			for (typename Container::iterator it = container.begin(); it != container.end(); it++)
			{
				pair.first = *(it++);
				pair.second = *it;
				pairContainer.push_back(pair);
			}

			return (pairContainer);
		};

		template < typename PairContainer >
		static void	_sortPairContainer( PairContainer &pairContainer )
		{
			int	tmp;

			for (typename PairContainer::iterator it = pairContainer.begin(); it != pairContainer.end(); it++)
			{
				if (it->first < it->second)
				{
					tmp = it->first;
					it->first = it->second;
					it->second = tmp;
				}
			}
		};

		template < typename PairContainer >
		static void	_mergeSortPairContainer( PairContainer &pairContainer )
		{
			PairContainer						first;
			PairContainer						second;

			_splitContainer(pairContainer, first, second);
			pairContainer.clear();

			if (first.size() > 1)
				_mergeSortPairContainer(first);
			if (second.size() > 1)
				_mergeSortPairContainer(second);

			_mergePairContainer(pairContainer, first, second);
		}

		template < typename PairContainer >
		static void	_mergePairContainer( PairContainer &pairContainer, PairContainer &first, PairContainer &second )
		{
			typename PairContainer::iterator	it_first = first.begin();
			typename PairContainer::iterator	it_second = second.begin();

			while (it_first != first.end() || it_second != second.end())
			{
				if (it_second == second.end() || (it_first != first.end() && it_first->first < it_second->first))
				{
					pairContainer.push_back(*it_first);
					it_first++;
				}
				else
				{
					pairContainer.push_back(*it_second);
					it_second++;
				}
			}
		}

		template < typename PairContainer >
		static void	_splitContainer( PairContainer &pairContainer, PairContainer &first, PairContainer &second )
		{
			int		i = pairContainer.size() / 2;

			for (typename PairContainer::iterator it = pairContainer.begin(); it != pairContainer.end(); it++)
			{
				if (i-- > 0)
					first.push_back(*it);
				else
					second.push_back(*it);
			}
		}

};

#endif
