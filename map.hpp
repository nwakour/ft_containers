/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:32:45 by nwakour           #+#    #+#             */
/*   Updated: 2022/04/06 22:29:33 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP__H__
#define __MAP__H__

#include <memory>
#include "iterator.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"


namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
		typedef Key 														key_type;
		typedef T															mapped_type;
		typedef pair<const key_type, mapped_type>							value_type;
		typedef Compare														key_compare;
		typedef	class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map; //?
			protected:
				Compare comp;
  				value_compare (Compare c) : comp(c) {}
			public:
				bool operator() (const value_type& x, const value_type& y) const{
					return comp(x.first, y.first);
  				}
		} value_compare;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::size_type							size_type;
		typedef typename allocator_type::difference_type					difference_type;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef ft::rb_tree<value_type, value_compare, allocator_type>		rb_tree;
		typedef typename rb_tree::iterator									iterator;
		typedef typename rb_tree::const_iterator							const_iterator;
		typedef typename rb_tree::reverse_iterator							reverse_iterator;
		typedef typename rb_tree::const_reverse_iterator					const_reverse_iterator;
		
		
		
		private:
			rb_tree _tree;
		public:
	
		//! constructor
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

		template <class InputIterator>
  		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0): _tree(comp, alloc)
		{
			  for(; first != last; ++first)
			{
				_tree.insert(*first);
			}
		}

		map (const map& x) : _tree(x._tree) {}
		
		//! destructor
		~map(){
			_tree.clear();
		}
		map& operator=(const map& x)
		{
			_tree = x._tree;
			return *this;
		}

		//! Iterators
		iterator begin()
		{
			return (_tree.begin());
		}
		const_iterator begin() const
		{
			return (_tree.begin());
		}
		iterator end()
		{
			return (_tree.end());
		}
		const_iterator end() const
		{
			return (_tree.end());
		}
		reverse_iterator rbegin()
		{
			return (_tree.rbegin());
		}
		const_reverse_iterator rbegin() const
		{
			return (_tree.rbegin());
		}
		reverse_iterator rend()
		{
			return (_tree.rend());
		}
		const_reverse_iterator rend() const
		{
			return (_tree.rend());
		}

		//! Capacity
		
		size_type max_size() const{
			return _tree.max_size();
		}
		size_type size() const{
			return _tree.size();
		}
		bool empty() const{
			return _tree.empty();
		}
		//! Element access
		// mapped_type& operator[] (const key_type& k);
		//! Modifiers
		pair<iterator,bool> insert (const value_type& val)
		{
			return (_tree.insert(val));
		}
		//iterator insert (iterator position, const value_type& val);
		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last,
		  	typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)	
		{
			for(; first != last; ++first)
			{
				_tree.insert(*first);
			}
		}
		
		void erase (iterator position)
		{
			_tree.erase(*position);
		}
		size_type erase (const key_type& val)
		{
			return (_tree.erase(val));
		}
		void erase (iterator first, iterator last)
		{
			for(; first != last; ++first)
			{
				_tree.erase(*first);
			}
		}
		// void swap (map& x);
		void clear()
		{
			_tree.clear();
		}

		//! Observers
		key_compare key_comp() const
		{
			return (key_compare());
		}
		value_compare value_comp() const
		{
			return (value_compare());
		}
		
		//! Operations
		iterator find(const key_type& val)
		{
			return (_tree.find(val));
		}
		const_iterator find(const key_type& val) const
		{
			return (_tree.find(val));
		}
		size_type count(const key_type& val) const
		{
			return (_tree.count(val));
		}
		iterator upper_bound(const key_type& val)
		{
			return (_tree.upper_bound(val));
		}
		const_iterator upper_bound(const key_type& val) const
		{
			return (_tree.upper_bound(val));
		}
		iterator lower_bound(const key_type& val)
		{
			return (_tree.lower_bound(val));
		}
		const_iterator lower_bound(const key_type& val) const
		{
			return (_tree.lower_bound(val));
		}
		ft::pair<iterator,iterator> equal_range(const key_type& val)
		{
			return (_tree.equal_range(val));
		}
		pair<const_iterator,const_iterator> equal_range(const key_type& val) const
		{
			return (_tree.equal_range(val));
		}
		//! Allocator
		allocator_type get_allocator() const
		{
			return (allocator_type());
		}
	};
	template <class T, class Compare, class Alloc>
	bool operator== (const map<T,Compare,Alloc>& lhs, const map<T,Compare,Alloc>& rhs){
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Compare, class Alloc>
	bool operator!= (const map<T,Compare,Alloc>& lhs, const map<T,Compare,Alloc>& rhs){
		return (!(lhs == rhs));
	}
	template <class T, class Compare, class Alloc>
	bool operator< (const map<T,Compare,Alloc>& lhs, const map<T,Compare,Alloc>& rhs){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Compare, class Alloc>
	bool operator<= (const map<T,Compare,Alloc>& lhs, const map<T,Compare,Alloc>& rhs){
		return (!(rhs < lhs));
	}
	template <class T, class Compare, class Alloc>
	bool operator> (const map<T,Compare,Alloc>& lhs, const map<T,Compare,Alloc>& rhs){
		return (rhs < lhs);
	}
	template <class T, class Compare, class Alloc>
	bool operator>= (const map<T,Compare,Alloc>& lhs, const map<T,Compare,Alloc>& rhs){
		return (!(lhs < rhs));
	}
}

#endif