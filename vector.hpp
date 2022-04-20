/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tenshi <tenshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:04:22 by nwakour           #+#    #+#             */
/*   Updated: 2022/03/29 22:38:23 by tenshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <memory>
#include "iterator.hpp"
#include "pair.hpp"
// #include <stack>

namespace ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
		typedef T															value_type; 
		typedef Allocator 													allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::size_type							size_type;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef ft::random_access_iterator<T>								iterator;
		typedef typename std::ptrdiff_t										difference_type;
		typedef ft::random_access_iterator<const T>							const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		
		//! Member functions !//
		
		explicit vector (const allocator_type& alloc = allocator_type())
			: _start(NULL), _size(0), _capacity(0), _end(NULL),  _alloc(alloc){
		}
		
		explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			:_start(NULL), _size(0), _capacity(0), _end(NULL),  _alloc(alloc)
		{
			pointer tmp = NULL;
			try
			{
				tmp = myalloc(n);
				myfill_strong(tmp,n, val);
			}
			catch(...)
			{
				_alloc.deallocate(tmp, n);
				throw;
			}
			_start = tmp;
			_size = n;
			_end = _start + n;
			_capacity = n;
		}
		
		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<ft::is_input_iterator<typename InputIterator::iterator_category>::value>::type* = 0)
			:_start(NULL), _size(0), _capacity(0), _end(NULL),  _alloc(alloc){

			for(; first != last; ++first)
			{
				this->push_back(*first);
			}
		}
		template <class ForwardIterator>
		vector (ForwardIterator first, ForwardIterator last,
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<ForwardIterator>::value, ForwardIterator>::type* = 0)
			:_start(NULL), _size(0), _capacity(0), _end(NULL),  _alloc(alloc){

			difference_type diff =  std::distance(first, last);
			pointer tmp = NULL;
			try
			{
				tmp = myalloc(diff);
				mycopy_strong(first, last, tmp);
			}
			catch(...)
			{
				_alloc.deallocate(tmp, diff);
				throw;
			}
			_start = tmp;
			_size = diff;
			_end = _start + diff;
			_capacity = diff;
		}

		vector (const vector& x) : _start(NULL), _size(0), _capacity(0), _end(NULL), _alloc(allocator_type())
		{
			*this = x;
		}

		~vector(){
			clear();
			_alloc.deallocate(_start, _capacity);
		}

		//! Capacity !//

		size_type size() const{
			return (_size);
		}

		size_type max_size() const{
			return(_alloc.max_size());
		}
		
		void resize(size_type n, value_type val = value_type())
		{
			if (n > _size)
			{
				if (n > _capacity)
				{
					pointer tmp;
					size_type tmp_cap;
					if (n > _capacity * 2)
						tmp_cap = n;
					else 
						tmp_cap = _capacity * 2;
					tmp = myalloc(tmp_cap);
					try
					{
						mycopy_strong(_start, _end, tmp);
						myfill_strong(tmp + _size, n - _size, val);
					}
					catch(...)
					{
						for (size_type i = 0; i < _size; ++i)
						{
							_alloc.destroy(tmp + i);
						}
						_alloc.deallocate(tmp, tmp_cap);
						throw;
					}
					use_new_stack(tmp, n, tmp_cap);
				}
				else
				{
					_end = myfill_strong(_end, n - _size, val);
					_size = n;
				}
			}
			else
			{
				while (_size > n)
				{
					--_size;
					_alloc.destroy(--_end);
				}
			}
		}
		
		size_type capacity() const{
			return (_capacity);
		}
		bool empty() const{
			return (_end == _start);
		}
		void reserve(size_type size){
			if (size > _capacity)
			{
				pointer tmp = myalloc(size);
				try{mycopy_strong(_start, _end, tmp);}
				catch(...)
				{
					_alloc.deallocate(tmp, size);
					throw;
				}
				use_new_stack(tmp, _size, size);
			}
		}
		//! Element access !//

		reference operator[] (size_type n){
			return (*(_start + n));
		}
		const_reference operator[] (size_type n) const{
			return (*(_start + n));
		}
		
		reference at (size_type n) {
			if (n < _size)
				return(*(_start + n));
			else
				throw std::out_of_range("vector");
		}
		const_reference at (size_type n) const {
			if (n < _size)
				return(*(_start + n));
			else
				throw std::out_of_range("vector");
		}

		reference front(){
			return(*_start);
		}
		const_reference front() const{
			return(*_start);
		}

		reference back(){
			return(*(_end - 1));
		}
		const_reference back() const{
			return(*(_end - 1));
		}
		
		//! Modifiers !//
		
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
			typename ft::enable_if<ft::is_input_iterator<typename InputIterator::iterator_category>::value>::type* = 0)
		{
			clear();
			for(; first != last; ++first)
			{
				push_back(*first);
			}
		}
		
		template <class ForwardIterator>
		void assign (ForwardIterator first, ForwardIterator last,
		typename ft::enable_if<!ft::is_integral<ForwardIterator>::value>::type* = 0) //! keep adding until throw (Basic guarantee)
		{
			difference_type diff = std::distance(first, last);
			clear();
			if ((size_type)diff > _capacity)
			{
				_alloc.deallocate(_start, _capacity);
				_start = myalloc(diff);
				_end = _start;
				_capacity = diff;
			}
			try
			{
				for (;first != last; ++_end, ++first, ++_size)
				{
					_alloc.construct(_end, *first);			
				}
			}
			catch(...)
			{
				throw;
			}
		}
		
		void assign (size_type n, const value_type& val) //! keep adding until throw (Basic guarantee)
		{
			clear();
			if (n > _capacity)
			{
				_alloc.deallocate(_start, _capacity);
				_start = myalloc(n);
				_end = _start;
				_capacity = n;
			}
			try
			{
				for(; _size < n; ++_size, ++_end)
				{
					_alloc.construct(_end, val);
				}
			}
			catch(...)
			{
				throw;
			}
		}

		void push_back(const value_type& val)
		{
			if (_size == _capacity)
			{
				size_type cap_tmp = 1;
				pointer tmp;
				if (_size)
					cap_tmp = _capacity * 2;
				try
				{
					tmp = myalloc(cap_tmp);
					mycopy_strong(_start, _end, tmp);
					_alloc.construct(tmp + _size, val);
				}
				catch(...)
				{
					_alloc.deallocate(tmp, cap_tmp);
					throw;
				}
				use_new_stack(tmp, _size + 1, cap_tmp);
			}
			else
			{
				try{_alloc.construct(_end, val);}
				catch(...){throw;}
				++_end;
				++_size;
			}
		}

		void pop_back()
		{
			_alloc.destroy(--_end);
			--_size;
		}

		iterator erase(iterator position)
		{
			difference_type diff = std::distance(iterator(_start), position);
			std::copy(_start + diff + 1, _end, _start + diff);
			_alloc.destroy(--_end);
			--_size;
			return (_start + diff);
		}

		iterator erase(iterator first, iterator last)
		{
			difference_type size = std::distance(first, last);
			difference_type diff = std::distance(iterator(_start), first);

			std::copy(_start + diff + size, _end, _start + diff);
			for (; size > 0; --size)
			{
				_alloc.destroy(--_end);
				--_size;
			}
			return (_start + diff);
		}

		iterator insert(iterator position, const value_type& val)
		{
			difference_type diff = std::distance(iterator(_start), position);
			if (_size == _capacity)
			{
				size_type tmp_cap = 1;
				pointer tmp = NULL;
				if (_size)
					tmp_cap = _capacity * 2;
				try
				{
					tmp = myalloc(tmp_cap);
					_alloc.construct(tmp + diff, val);
					for (difference_type i = diff - 1; i >= 0; --i)
					{
						_alloc.construct(tmp + i, *(_start + i));
					}
					for (size_type i = diff; i < _size; ++i)
					{
						_alloc.construct(tmp + i + 1, *(_start + i));
					}
				}
				catch(...)
				{
					if (tmp != NULL)
					{
						for (size_type i = 0; i < tmp_cap; ++i)
						{
							_alloc.destroy(tmp + i);
						}
						_alloc.deallocate(tmp, tmp_cap);
					}
					throw;
				}
				use_new_stack(tmp, _size + 1, tmp_cap);
			}
			else
			{
				if (!_size)
					_alloc.construct(_end, val);
				else
				{
					_alloc.construct(_end, *(_end - 1));
					for (pointer dist = _end - 1, src = _end - 1; dist != _start + diff; --dist)
					{
						*dist = *(--src);
					}
					*(_start + diff) = val;
				}
				++_size;
				++_end;
			}
			return (_start + diff);
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			difference_type diff = std::distance(iterator(_start), position);
			if (!n)
				return ;
			if (_size + n > _capacity)
			{
				size_type tmp_cap = _capacity * 2;
				pointer tmp = NULL;
				if (_size + n > tmp_cap)
					tmp_cap = _size + n;
				try
				{
					tmp = myalloc(tmp_cap);
					for (size_type i = 0; i < n; ++i)
					{
						_alloc.construct(tmp + diff + i, val);
					}
					for (difference_type i = diff - 1; i >= 0; --i)
					{
						_alloc.construct(tmp + i, *(_start + i));
					}
					for (size_type i = diff; i < _size; ++i)
					{
						_alloc.construct(tmp + n + i, *(_start + i));
					}
				}
				catch(...)
				{
					if (tmp != NULL)
					{
						for (size_type i = 0; i < tmp_cap; ++i)
						{
							_alloc.destroy(tmp + i);
						}
						_alloc.deallocate(tmp, tmp_cap);
					}
					throw;
				}
				use_new_stack(tmp, _size + n, tmp_cap);
			}
			else
			{
				size_type basic_len = 0;
				try
				{
					if (!_size)
						myfill_basic(_start, n, val, basic_len);
					else
					{
						if (n + diff < _size)
						{
							mycopy_basic(_end - n, _end, _end, basic_len);
							myassign_basic_back(_end - (n + 1) , _start + (diff - 1), _end - 1, basic_len);
							myfill_basic(_start + diff, n, val, basic_len);
						}
						else
						{
							myfill_basic(_end, n - (_size - diff), val, basic_len);
							mycopy_basic(_start + diff, _end, _end + n - (_size - diff), basic_len);
							myfill_basic(_start + diff, _size - diff, val, basic_len);
						}
					}
				}
				catch(...)
				{
					_size += basic_len;
					_end += basic_len;
					throw;
				}
				_size += n;
				_end += n;
			}
		}
		template <class ForwardIterator>
		void insert (iterator position, ForwardIterator first, ForwardIterator last,
			typename ft::enable_if<!ft::is_integral<ForwardIterator>::value>::type* = 0)
		{
			difference_type diff = std::distance(iterator(_start), position);
			difference_type lsize = std::distance(first, last);
			if (_size + lsize > _capacity)
			{
				size_type tmp_cap = _capacity * 2;
				pointer tmp = NULL;
				if (_size + lsize > tmp_cap)
					tmp_cap = _size + lsize;
				
				try
				{
					tmp = myalloc(tmp_cap);
					mycopy_strong(first, last, tmp + diff);
					for (difference_type i = diff - 1; i >= 0; --i)
					{
						_alloc.construct(tmp + i, *(_start + i));
					}
					for (size_type i = diff; i < _size; ++i)
					{
						_alloc.construct(tmp + lsize + i, *(_start + i));
					}
				}
				catch(...)
				{
					if (tmp != NULL)
					{
						for (size_type i = 0; i < tmp_cap; ++i)
						{
							_alloc.destroy(tmp + i);
						}
						_alloc.deallocate(tmp, tmp_cap);
					}
					throw;
				}
				use_new_stack(tmp, _size + lsize, tmp_cap);
			}
			else
			{
				size_type basic_len = 0;
				try
				{
					if (!_size)
						mycopy_basic(first, last, _start, basic_len);
					else
					{
						if ((size_type)(lsize + diff) < _size)
						{
							mycopy_basic(_end - lsize, _end, _end, basic_len);
							myassign_basic_back(_end - (lsize + 1) , _start + (diff - 1), _end - 1, basic_len);
							myassign_basic_front(first, last, _start + diff, basic_len);
						}
						else
						{
							mycopy_basic(last - (lsize - (_size - diff)), last, _end, basic_len);
							mycopy_basic(_start + diff, _end, _end + lsize - (_size - diff), basic_len);
							myassign_basic_front(first, first + (_size - diff), _start + diff, basic_len);
						}
					}
				}
				catch(...)
				{
					_size += basic_len;
					_end += basic_len;
					throw;
				}
				_size += lsize;
				_end += lsize;
			}
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<ft::is_input_iterator<typename InputIterator::iterator_category>::value>::type* = 0)
		{

			if (first != last)
				position = this->insert(position, *(first++));
			for(; first != last; ++first)
			{
				position  = this->insert(position + 1, *first);
			}
		}

		void clear(){
			while (_start != _end)
				_alloc.destroy(--_end);
			_size = 0;
		}
		iterator begin(){
			return(iterator(_start));
		}
		iterator end(){
			return(iterator(_end));
		}
		const_iterator begin() const{
			return(const_iterator(_start));
		}
		const_iterator end() const{
			return(const_iterator(_end));
		}

		reverse_iterator rbegin(){
			return(reverse_iterator(this->end()));
		}
		reverse_iterator rend(){
			return(reverse_iterator(this->begin()));
		}
		const_reverse_iterator rbegin() const{
			return(const_reverse_iterator(this->end()));
		}
		const_reverse_iterator rend() const{
			return(const_reverse_iterator(this->begin()));
		}
		allocator_type get_allocator() const
		{
			return (_alloc);
		}
		vector &operator=(const vector& copy)
		{
			assign(copy.begin(), copy.end());
			return (*this);
		}
		void swap(vector& v)
		{
			std::swap(_start, v._start);
			std::swap(_end, v._end);
			std::swap(_size, v._size);
			std::swap(_capacity, v._capacity);
			std::swap(_alloc, v._alloc);
		}
		private:
			pointer				_start;
			size_type			_size;
			size_type			_capacity;
			pointer				_end;
			allocator_type		_alloc;
		protected:
        pointer myalloc(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("vector");
			return(_alloc.allocate(n));
		}
		template<typename InputIterator>
        pointer mycopy_strong(InputIterator first, InputIterator last, pointer p)
		{
			size_type i = 0;
			try
			{
				for(; first != last; ++i, ++first, ++p)
				{
					_alloc.construct(p, *first);
				}
				return (p);
			}
			catch(...)
			{
				for(; i > 0; --i)
				{
					_alloc.destroy(--p);
				}
				throw;
			}
		}
		template<typename InputIterator>
        void mycopy_basic(InputIterator first, InputIterator last, pointer p, size_type &ret)
		{
			for(; first != last; ++first, ++p)
			{
				_alloc.construct(p, *first);
				if (p >= _end)
					++ret;
			}
		}
		template<typename InputIterator>
        void myassign_basic_front(InputIterator first, InputIterator last, pointer p, size_type &ret)
		{
			for(; first != last; ++first, ++p)
			{
				*p = *first;
				if (p >= _end)
					++ret;
			}
		}
		template<typename InputIterator>
        void myassign_basic_back(InputIterator first, InputIterator last, pointer p, size_type &ret)
		{
			for(; first != last; --first, --p)
			{
				*p = *first;
				if (p >= _end)
					++ret;
			}
		}
		pointer myfill_strong(pointer p, size_type n, const value_type &val)
		{
			size_type i = 0;
			try
			{
				for(; i < n; ++i, ++p)
				{
					_alloc.construct(p, val);
				}
				return (p);
			}
			catch(...)
			{
				for(; i > 0; --i)
				{
					_alloc.destroy(--p);
				}
				throw;
			}
		}
		void myfill_basic(pointer p, size_type n, const value_type &val, size_type &ret)
		{
			for(size_type i = 0; i < n; ++i, ++p)
			{
				_alloc.construct(p, val);
				if (p >= _end)
					++ret;
			}
		}
		void use_new_stack(pointer p, size_type size, size_type capacity)
		{
			while(_end != _start)
				_alloc.destroy(--_end);
			_alloc.deallocate(_start, _capacity);
			_start = p;
			_end = _start + size;
			_size = size;
			_capacity = capacity;
		}
	};
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (!(rhs < lhs));
	}
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (!(lhs < rhs));
	}
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& v1, vector<T,Alloc>& v2){
		v1.swap(v2);
	}
}

#endif