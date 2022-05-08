/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:22:49 by nwakour           #+#    #+#             */
/*   Updated: 2022/05/07 19:40:21 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR__H__
#define __ITERATOR__H__
#include <stddef.h>
#include <iterator>
#include "node.hpp"

namespace ft
{

template <typename Category, typename T, typename Distance = std::ptrdiff_t,
			typename Pointer = T*, typename Reference = T&>
	class iterator 
	{
		public :
			typedef T						value_type;
			typedef Distance				difference_type;
			typedef Pointer					pointer;
			typedef Reference				reference;
			typedef Category 				iterator_category;
	};

	template <class Iterator>
	struct iterator_traits
	{
		public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template< class T >
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t 						difference_type;
		typedef T									value_type;
		typedef T* 									pointer;
		typedef T& 									reference;
		typedef	std::random_access_iterator_tag 	iterator_category;
	};

	template< class T >
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

template <class T>
class const_RB_Iterator
{
	public:
			typedef iterator<std::bidirectional_iterator_tag, T> 				iterator_type;
			typedef	typename iterator_traits<iterator_type>::value_type			value_type;
			typedef	typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef	const T&													reference;
			typedef const T*													pointer;
			typedef ft::node<T>													node_type;
			typedef typename node_type::const_node_ptr 							node_pointer;
			
			node_pointer _it;
	private:
		node_pointer _Nnull;
		
		
	public:
		const_RB_Iterator() : _it(NULL), _Nnull(NULL){}
		const_RB_Iterator(const node_pointer& it, const node_pointer& Nnull) : _it(it), _Nnull(Nnull){}

		const_RB_Iterator(const const_RB_Iterator& copy): _it(copy._it), _Nnull(copy._Nnull){}

		~const_RB_Iterator(){};
		const_RB_Iterator &operator=(const const_RB_Iterator& copy){
			_it = copy._it;
			_Nnull = copy._Nnull;
			return *this;
		}
		reference operator*() const{
			return (_it->val);
		}
		
		pointer operator->() const{
			return (&this->_it->val);
		}

		const_RB_Iterator& operator++() {
			_it = _it->Rb_tree_increment(_Nnull);
			return *this;
		}
		
		const_RB_Iterator operator++(int) 
		{
			const_RB_Iterator tmp = *this;
			_it = _it->Rb_tree_increment(_Nnull);
			return tmp;
		}

		const_RB_Iterator& operator--() {
			_it = _it->Rb_tree_decrement(_Nnull);
			return *this;
		}

		const_RB_Iterator operator--(int) 
		{
			const_RB_Iterator tmp = *this;
			_it = _it->Rb_tree_decrement(_Nnull);
			return tmp;
		}
		
		bool operator== (const const_RB_Iterator& a){
			return _it == a._it;
		}
		bool operator!= (const const_RB_Iterator& a){
			return _it != a._it;
		}
};

template <class T>
class RB_Iterator
{
	public:
			typedef iterator<std::bidirectional_iterator_tag, T> 				iterator_type;
			typedef	typename iterator_traits<iterator_type>::value_type			value_type;
			typedef	typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef	typename iterator_traits<iterator_type>::reference			reference;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef ft::node<T>													node_type;
			typedef node_type* 													node_pointer;
			typedef ft::const_RB_Iterator<T>									const_iterator;
			node_pointer _it;
	private:
		
		node_pointer _Nnull;
	public:
		RB_Iterator() : _it(NULL), _Nnull(NULL){}
		RB_Iterator(const node_pointer& it, const node_pointer& Nnull) : _it(it), _Nnull(Nnull){}

		RB_Iterator(const RB_Iterator& copy){
			*this = copy;
		}
		~RB_Iterator(){};
		operator const_iterator() const{
			return const_iterator(_it, _Nnull);
		}
		RB_Iterator &operator=(const RB_Iterator& copy){
			_it = copy._it;
			_Nnull = copy._Nnull;
			return *this;
		}
		reference operator*() const{
			return (_it->val);
		}
		
		pointer operator->() const{
			return (&this->_it->val);
		}

		RB_Iterator& operator++() {
			_it = _it->Rb_tree_increment(_Nnull);
			return *this;
		}
		
		RB_Iterator operator++(int) 
		{
			RB_Iterator tmp = *this;
			_it = _it->Rb_tree_increment(_Nnull);
			return tmp;
		}

		RB_Iterator& operator--() {
			_it = _it->Rb_tree_decrement(_Nnull);
			return *this;
		}

		RB_Iterator operator--(int) 
		{
			RB_Iterator tmp = *this;
			_it = _it->Rb_tree_decrement(_Nnull);
			return tmp;
		}
		
		bool operator== (const RB_Iterator& a){
			return _it == a._it;
		}
		bool operator!= (const RB_Iterator& a){
			return _it != a._it;
		}
};

	template <typename T>
	class random_access_iterator
	{
		public:
		typedef iterator<std::random_access_iterator_tag, T> 	iterator_type;
		typedef typename iterator_type::iterator_category	iterator_category;
		typedef typename iterator_type::value_type			value_type;
		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::pointer						pointer;
		typedef typename iterator_type::reference					reference;
		typedef random_access_iterator<const T>						const_iterator;

		// private:
		pointer _it;
		public:
		random_access_iterator() : _it(NULL){}
		random_access_iterator(const pointer& it) : _it(it) {}

		random_access_iterator(const random_access_iterator& copy){
			*this = copy;
		}

		~random_access_iterator(){};

		operator const_iterator() const
		{
			return(const_iterator(_it));
		}

		random_access_iterator &operator=(const random_access_iterator& copy){
			_it = copy._it;
			return *this;
		}

		pointer base() const{
			return(_it);
		}
			
		reference operator*() const {
			return *_it;
		}
		pointer operator->() { 
			return &(operator*());
		}

		random_access_iterator& operator++() { 
			++_it;
			return *this;
		}

		random_access_iterator operator++(int) 
		{
			random_access_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		

		random_access_iterator& operator--() { 
			--_it;
			return *this;
		}

		random_access_iterator operator--(int) 
		{
			random_access_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		random_access_iterator operator+=(difference_type n) {
			_it += n;
			return (*this);
		}
		
		random_access_iterator operator-=(difference_type n) {
			_it -= n;
			return (*this);
		}
		reference& operator[](const difference_type &n) { 
			return *(_it + n);
		}

		difference_type operator- (const random_access_iterator& rit) { 
			return (this->_it - rit._it); }
		
		difference_type operator- (const const_iterator& rit) const { 
			return (this->_it - rit._it); }
		
		random_access_iterator operator+ (difference_type n) const{
			return (random_access_iterator(_it + n)); }
			
		random_access_iterator operator- (difference_type n) const {
			return (random_access_iterator(_it - n)); }
		
		friend bool operator==(const random_access_iterator &lhs,const random_access_iterator &rhs){
			return (lhs.base() == rhs.base()); }
		
		friend bool operator!=(const random_access_iterator &lhs,const random_access_iterator &rhs){
			return (!(lhs.base() == rhs.base())); }

		friend bool operator<(const random_access_iterator &lhs,const random_access_iterator &rhs){
			return (lhs.base() < rhs.base()); }

		friend bool operator<=(const random_access_iterator &lhs,const random_access_iterator &rhs){
			return (lhs.base() <= rhs.base()); }

		friend bool operator>(const random_access_iterator &lhs,const random_access_iterator &rhs){
			return (lhs.base() > rhs.base()); }

		friend bool operator>=(const random_access_iterator &lhs,const random_access_iterator &rhs){
			return (lhs.base() >= rhs.base()); }

		friend random_access_iterator operator+ (difference_type n,const random_access_iterator& rit) { 
			return random_access_iterator(rit._it + n); }
	};	

template <class Iterator> 
	class reverse_iterator
	{
		public :

			typedef Iterator													iterator_type;
			typedef	typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef	typename iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename iterator_traits<iterator_type>::pointer				pointer;
			typedef typename iterator_traits<iterator_type>::reference			reference;
			iterator_type	_it;
		public:
		
		reverse_iterator() : _it(iterator_type()){}

		~reverse_iterator(){};

		explicit reverse_iterator( const iterator_type &x ) : _it(x){}
	
		template <class Iter>
  		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it._it){}


		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other )
		{
			_it = other.base();
			return (*this);
		}

		iterator_type base() const{
			return(_it);
		}
		
		reference operator*() const{
			iterator_type	tmp = _it;
			return *--tmp;
		}

		pointer operator->() const{
			return &(operator*());
		}

		reverse_iterator operator+ (difference_type n) const{
			return (reverse_iterator(_it - n));
		}

		reverse_iterator& operator++(){
			--_it;
			return (*this);
		}

		reverse_iterator operator++(int){
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}
		
		reverse_iterator& operator--(){
			++_it;
			return *this;
		}

		reverse_iterator operator--(int) {
  			reverse_iterator tmp = *this;
  			--(*this);
  			return tmp;
		}

		reverse_iterator operator- (difference_type n) const{
			return(reverse_iterator(_it + n));
		}

		reverse_iterator& operator+= (difference_type n){
			_it -= n;
			return *this;
		}

		reverse_iterator& operator-= (difference_type n){
			_it += n;
			return *this;
		}

		reference& operator[](const difference_type &n) { 
			return *(_it - n - 1);
		}

		difference_type operator- (const reverse_iterator& rit) { 
			return (rit._it - this->_it); }
	};

	template< class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template< class Iter >
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
	{
		return (it + n);
	}
}
#endif