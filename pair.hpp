/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tenshi <tenshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:48:53 by nwakour           #+#    #+#             */
/*   Updated: 2022/03/29 23:06:36 by tenshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR__H__
#define __PAIR__H__

#include <type_traits>
#include "iterator.hpp"

namespace ft
{
	template<typename T1, typename T2>
	class pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;
			
			first_type first;
			second_type second;

			pair() : first(), second(){
			}

			template<class U, class V>
			pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {
			}
			
			pair (const first_type& a, const second_type& b) : first(a), second(b){
			}

			pair& operator= (const pair& pr)
			{
				first = pr.first;
				second = pr.second;
				return (*this);
			}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y));
	}


	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T>
	{typedef T type;};


	template<typename T>
	struct is_input_iterator{static const bool value = false;};
	
	template<>
	struct is_input_iterator<std::input_iterator_tag> {static const bool value = true;};

	template<typename T>
	struct is_integral{static const bool value = false;};

	template<>
	struct is_integral<bool> {static const bool value = true;};
	template<>
	struct is_integral<char> {static const bool value = true;};
	// template<>
	// struct is_integral<char16_t> {static const bool value = true;};
	// template<>
	// struct is_integral<char32_t> {static const bool value = true;};
	template<>
	struct is_integral<wchar_t> {static const bool value = true;};
	template<>
	struct is_integral<signed char> {static const bool value = true;};
	template<>
	struct is_integral<int> {static const bool value = true;};
	template<>
	struct is_integral<long int> {static const bool value = true;};
	template<>
	struct is_integral<long long int> {static const bool value = true;};
	template<>
	struct is_integral<unsigned char> {static const bool value = true;};
	template<>
	struct is_integral<unsigned short int> {static const bool value = true;};
	template<>
	struct is_integral<unsigned int> {static const bool value = true;};
	template<>
	struct is_integral<unsigned long int> {static const bool value = true;};
	template<>
	struct is_integral<unsigned long long int> {static const bool value = true;};

	template <class InputIterator1, class InputIterator2, class Compare>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2,
								Compare comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
			++first1;
			++first2;
		}
		return first1 == last1 && first2 != last2;
	}
	
	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
			++first1;
			++first2;
		}
		return first1 == last1 && first2 != last2;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  	bool equal (InputIterator1 first1, InputIterator1 last1,
			  InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;  
	}

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return true;
	};

}
#endif