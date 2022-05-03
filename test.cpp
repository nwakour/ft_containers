/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:45:42 by nwakour           #+#    #+#             */
/*   Updated: 2022/05/03 18:46:01 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "iterator.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"
#include "set.hpp"
#include <memory>
#include <set>
#include <map>
class B {
public:
	char *l;
	int i;
	B():l(NULL), i(1) {
	}
	B(const int &ex) {
		this->i = ex;
		std::cout << "constuct " << i << "\n";
		this->l = new char('a');
	}
	virtual ~B() {
		std::cout << "destroy " << i << "\n";
		delete this->l;
		this->l = NULL;
	}
	B (const B& x)
	{
		this->i = x.i;
		this->l = new char('a');
		std::cout << "copy " << i << "\n";
	}
	B &operator=(const B& copy)
	{
		this->i = copy.i;
		this->l = new char('a');
		std::cout << "assignement " << i << "\n";
		return (*this);
	}
	friend bool operator== (const B& a, const B& b){
			return a.i == b.i;
	}
	friend bool operator!= (const B& a, const B& b){
			return a.i != b.i;
	}
	friend bool operator< (const B& a, const B& b){
			return a.i < b.i;
	}
};

int main()
{
	std::set<B> s;
	std::map<int,B> m;
	
	s.find(B(1));
	m.find(1);
	// std::set<int, std::plus<int> > mp;
	// mp.insert(mp.begin(),1);
	// ft::set<int, std::plus<int> > p;
	// mp.insert(16);
	// mp.insert(8);
	// mp.insert(23);
	// mp.insert(7);
	// mp.insert(19);
	// mp.insert(29);
	// mp.insert(41);
	// mp.insert(4);
	// mp.insert(11);

	// p.insert(16);
	// p.insert(8);
	// p.insert(23);
	// p.insert(7);
	// p.insert(19);
	// p.insert(29);
	// p.insert(41);
	// p.insert(4);
	// p.insert(11);


	// for (std::set<int>::iterator it = mp.begin(); it != mp.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// for (ft::set<int>::iterator it = p.begin(); it != p.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	
	// for (std::set<int>::iterator it = --mp.end(); it != mp.begin(); --it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// for (ft::set<int>::iterator it = --p.end(); it != p.begin(); --it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// mp.erase(41);
	// p.erase(41);
	// for (std::set<int>::iterator it = mp.begin(); it != mp.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// for (ft::set<int>::iterator it = p.begin(); it != p.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// mp.erase(29);
	// p.erase(29);
	// for (std::set<int>::iterator it = mp.begin(); it != mp.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// for (ft::set<int>::iterator it = p.begin(); it != p.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// mp.insert(3);
	// p.insert(3);
	// for (std::set<int>::iterator it = mp.begin(); it != mp.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// for (ft::set<int>::iterator it = p.begin(); it != p.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// mp.erase(3);
	// p.erase(3);
	// for (std::set<int>::iterator it = mp.begin(); it != mp.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// for (ft::set<int>::iterator it = p.begin(); it != p.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// ft::pair<ft::set<int>::iterator, bool> p = s.insert(5);
	// std::cout << "pair.first: " << *(p.first) << std::endl;
	// std::cout << "pair.second: " << (p.second) << std::endl;
	// for (int i = 0; i < 10; i++)
	// {
	// 	// s.insert(i * 10);
	// 	ss.insert(B(i * 10));
	// }
	// std::cout << "start\n";
	// ss.erase(ss.begin(), --ss.end());
	// for (int i = 0; i < 100; i++)
	// {
	// 	std::cout << i << " \n";
	// 	std::cout << *(s.lower_bound(i)) << " ";
	// 	std::cout << *(ss.lower_bound(i)) << "\n";
	// }
	// ss.erase(ss.begin(), ++ss.begin());
	// std::cout << *(s.lower_bound(91)) << "\n";
	// std::cout << "done\n";

	// ft::set<int>::iterator it = s.begin();
	// std::cout << *it << "\n";
	// std::cout << *(++it) << "\n";
	// std::cout << *(++it) << "\n";
	// std::cout << *(++it) << "\n";
	// std::cout << *(++it) << "\n";
	// std::cout << *(++it) << "\n";

	// std::cout << "pair.first: " << *(p.first) << std::endl;
	// std::cout << "pair.second: " << (p.second) << std::endl;
	// for (ft::set<int>::iterator it = s.begin(); it != s.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// ss = s;
	// for (ft::set<int>::iterator it = ss.begin(); it != ss.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	// std::vector<B> vv;
	// B cp(15);
	// size_t tests = 10;
	// for (size_t i = 0; i < tests; ++i)
	// {
	// 	vv.push_back(B(i + tests));
	// }
	
	// for (size_t size = 0; size < tests; ++size)
	// {
	// 	for (size_t diff = 0; diff < size; ++diff)
	// 	{
	// 		for (size_t n = 0; n < vv.size(); ++n)
	// 		{
	// 			for (size_t nn = 0; nn < vv.size(); ++nn)
	// 			{
	// 				if (n >= nn)
	// 					continue;
	// 				for (size_t cap = 0; cap < tests; ++cap)
	// 				{
	// 					ft::vector<B> v1;
	// 					v1.reserve(cap);
	// 					for (size_t i = 0; i < size; ++i)
	// 					{
	// 						v1.push_back(B(i));
	// 					}
	// 					v1.insert(v1.begin() + diff, vv.begin() + n, vv.begin() + nn);
						// ft::vector<B> v2;
						// v2.reserve(cap);
						// for (size_t i = 0; i < size; ++i)
						// {
						// 	v2.push_back(B(i));
						// }
						// v2.insert(v2.begin() + diff, vv.begin() + n, vv.begin() + nn);
						// if (v1.size() != v2.size() || v1.capacity() != v2.capacity())
						// {
						// 	std::cout << "cap/size" << std::endl;
						// 	std::cout << cap << " "<< size << " " << diff << " " << n << " " << nn << std::endl;
						// 	return (0);
						// }
						// for (size_t i = 0; i < v1.size(); i++)
						// {
						// 	if (v1[i].i != v2[i].i)
						// 	{
						// 		std::cout << cap << " "<< size << " " << diff << " " << n << " " << nn << std::endl;
						// 		return (0);
						// 	}	
						// }
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	// for (size_t size = 0; size < tests; ++size)
	// {
	// 	for (size_t diff = 0; diff < size; ++diff)
	// 	{
	// 		for (size_t n = 0; n < tests; ++n)
	// 		{
	// 				for (size_t cap = 0; cap < tests; ++cap)
	// 				{
	// 					ft::vector<B> v1;
	// 					v1.reserve(cap);
	// 					for (size_t i = 0; i < size; ++i)
	// 					{
	// 						v1.push_back(B(i));
	// 					}
	// 					v1.insert(v1.begin() + diff, n, cp);
						// ft::vector<B> v2;
						// v2.reserve(cap);
						// for (size_t i = 0; i < size; ++i)
						// {
						// 	v2.push_back(B(i));
						// }
						// v2.insert(v2.begin() + diff, n, cp);
						// if (v1.size() != v2.size() || v1.capacity() != v2.capacity())
						// {
						// 	std::cout << "cap/size" << std::endl;
						// 	std::cout << cap << " "<< size << " " << diff << " " << n  << std::endl;
						// 	return (0);
						// }
						// for (size_t i = 0; i < v1.size(); i++)
						// {
						// 	if (v1[i].i != v2[i].i)
						// 	{
						// 		std::cout << cap << " "<< size << " " << diff << " " << n << std::endl;
						// 		return (0);
						// 	}
							
						// }
					// }
	// 		}
	// 	}
	// }
	
	// for (size_t size = 0; size < tests; ++size)
	// {
	// 	for (size_t diff = 0; diff < size; ++diff)
	// 	{
	// 				for (size_t cap = 0; cap < tests; ++cap)
	// 				{
	// 					std::vector<B> v1;
	// 					v1.reserve(cap);
	// 					for (size_t i = 0; i < size; ++i)
	// 					{
	// 						v1.push_back(B(i));
	// 					}
	// 					v1.insert(v1.begin() + diff, cp);
	// 					ft::vector<B> v2;
	// 					v2.reserve(cap);
	// 					for (size_t i = 0; i < size; ++i)
	// 					{
	// 						v2.push_back(B(i));
	// 					}
	// 					v2.insert(v2.begin() + diff, cp);
	// 					if (v1.size() != v2.size() || v1.capacity() != v2.capacity())
	// 					{
	// 						std::cout << "cap/size" << std::endl;
	// 						std::cout << cap << " "<< size << " " << diff << " "  << std::endl;
	// 						return (0);
	// 					}
	// 					for (size_t i = 0; i < v1.size(); i++)
	// 					{
	// 						if (v1[i].i != v2[i].i)
	// 						{
	// 							std::cout << cap << " "<< size << " " << diff << " " << std::endl;
	// 							return (0);
	// 						}
							
	// 					}
	// 				}
	// 	}
	// }
	// ft::vector<B> v1;
	// v1.reserve(30);
	// for (size_t i = 0; i < 1; ++i)
	// {
	// 	v1.push_back(B(i));
	// }
	// std::cout << "************" << std::endl;

	// v1.insert(v1.begin(), 1, cp);
	// std::cout << "************" << std::endl;
	// for (size_t i = 0; i < v1.size(); ++i)
	// {
	// 	std::cout << v1[i].i << " ";
		
	// }
	// std::cout << "\n";
	return(0);
}

//   template<typename _Key, typename _Val, typename _KeyOfValue,
// 	   typename _Compare, typename _Alloc>
//     pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
// 			   _Compare, _Alloc>::_Base_ptr,
// 	 typename _Rb_tree<_Key, _Val, _KeyOfValue,
// 			   _Compare, _Alloc>::_Base_ptr>
//     _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
//     _M_get_insert_hint_unique_pos(const_iterator __position,
// 				  const key_type& __k)
//     {
//       iterator __pos = __position._M_const_cast();
//       typedef pair<_Base_ptr, _Base_ptr> _Res;

//       // end()
//       if (__pos._M_node == _M_end())
// 	{
// 	  if (size() > 0
// 	      && _M_impl._M_key_compare(_S_key(_M_rightmost()), __k))
// 	    return _Res(0, _M_rightmost());
// 	  else
// 	    return _M_get_insert_unique_pos(__k);
// 	}
//       else if (_M_impl._M_key_compare(__k, _S_key(__pos._M_node)))
// 	{
// 	  // First, try before...
// 	  iterator __before = __pos;
// 	  if (__pos._M_node == _M_leftmost()) // begin()
// 	    return _Res(_M_leftmost(), _M_leftmost());
// 	  else if (_M_impl._M_key_compare(_S_key((--__before)._M_node), __k))
// 	    {
// 	      if (_S_right(__before._M_node) == 0)
// 		return _Res(0, __before._M_node);
// 	      else
// 		return _Res(__pos._M_node, __pos._M_node);
// 	    }
// 	  else
// 	    return _M_get_insert_unique_pos(__k);
// 	}
//       else if (_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
// 	{
// 	  // ... then try after.
// 	  iterator __after = __pos;
// 	  if (__pos._M_node == _M_rightmost())
// 	    return _Res(0, _M_rightmost());
// 	  else if (_M_impl._M_key_compare(__k, _S_key((++__after)._M_node)))
// 	    {
// 	      if (_S_right(__pos._M_node) == 0)
// 		return _Res(0, __pos._M_node);
// 	      else
// 		return _Res(__after._M_node, __after._M_node);
// 	    }
// 	  else
// 	    return _M_get_insert_unique_pos(__k);
// 	}
//       else
// 	// Equivalent keys.
// 	return _Res(__pos._M_node, 0);
//     }