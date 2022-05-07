/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:18:04 by nwakour           #+#    #+#             */
/*   Updated: 2022/05/07 20:51:11 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SET__H__
#define __SET__H__

#include <memory>
#include "iterator.hpp"
#include "utilities.hpp"
#include "rb_tree.hpp"
namespace ft
{
	template < typename T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class set
	{
		public:
		typedef T															key_type;
		typedef key_type													value_type;
		typedef Compare														key_compare;
		typedef key_compare													value_compare;
		typedef Allocator													allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::size_type							size_type;
		typedef typename allocator_type::difference_type					difference_type;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef ft::rb_tree<value_type, value_compare, allocator_type>		rb_tree;
		typedef typename rb_tree::node_ptr									node_ptr;
		typedef typename rb_tree::const_pointer								const_node_ptr;
		typedef ft::RB_Iterator<value_type>									iterator;
		typedef ft::const_RB_Iterator<value_type>							const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		
		private:
		rb_tree _tree;
		public:

		//! constructor
		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _tree(comp, alloc){}
	
		set (const set& x): _tree(x._tree){}
	
		template <class InputIterator>
 		set (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0): _tree(comp, alloc)
		{
			for(; first != last; ++first)
			{
				_tree.insert(*first);
			}
		}
		//! destructor
		~set()
		{
			clear();	
		}
		//! operator =
		set& operator=(const set& x)
		{
			_tree = x._tree;
			return *this;
		}

		//! Iterators
		iterator begin()
		{
			return (iterator(_tree.begin(), _tree.get__Nnull()));
		}
		const_iterator begin() const
		{
			return (const_iterator(_tree.begin(), _tree.get__Nnull()));
		}
		iterator end()
		{
			return (iterator(_tree.get__Nnull(), _tree.get__Nnull()));
		}
		const_iterator end() const
		{
			return (const_iterator(_tree.get__Nnull(), _tree.get__Nnull()));
		}
		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
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

		//! Modifiers
		pair<iterator,bool> insert (const value_type& val)
		{
			pair<node_ptr,bool> ret = _tree.insert(val);
			return (ft::make_pair(iterator(ret.first, _tree.get__Nnull()), ret.second));
		}
		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			return iterator(_tree.insert(val).first, _tree.get__Nnull());
		}
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
			_tree.erase(position._it);
		}
		size_type erase (const value_type& val)
		{
			return (_tree.erase(val));
		}
		void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				_tree.erase((first++));
			}
		}
		void swap (set& x)
		{
			_tree.swap(x._tree);
		}
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
		iterator find (const value_type& val) const
		{
			return (iterator(_tree.find(val), _tree.get__Nnull()));
		}

		size_type count (const value_type& val) const
		{
			return (_tree.count(val));
		}
		iterator upper_bound(const value_type& val) const
		{
			return (iterator(_tree.upper_bound(val), _tree.get__Nnull()));
		}
		iterator lower_bound(const value_type& val) const
		{
			return (iterator(_tree.lower_bound(val), _tree.get__Nnull()));
		}
		ft::pair<iterator,iterator> equal_range (const value_type& val) const
		{
			ft::pair<node_ptr,node_ptr> ret = _tree.equal_range(val);
			return (ft::make_pair(iterator(ret.first, _tree.get__Nnull()), iterator(ret.second, _tree.get__Nnull())));
		}
		//! Allocator
		allocator_type get_allocator() const
		{
			return (allocator_type());
		}
	};
	template <class T, class Compare, class Alloc>
	bool operator== (const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs){
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Compare, class Alloc>
	bool operator!= (const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs){
		return (!(lhs == rhs));
	}
	template <class T, class Compare, class Alloc>
	bool operator< (const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Compare, class Alloc>
	bool operator<= (const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs){
		return (!(rhs < lhs));
	}
	template <class T, class Compare, class Alloc>
	bool operator> (const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs){
		return (rhs < lhs);
	}
	template <class T, class Compare, class Alloc>
	bool operator>= (const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs){
		return (!(lhs < rhs));
	}
}

#endif