/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:17:12 by nwakour           #+#    #+#             */
/*   Updated: 2022/05/07 20:40:58 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <memory>
#include <functional>
#include "utilities.hpp"
#include "iterator.hpp"
#include <iostream>
namespace ft
{
	template <typename T, class Compare, class Allocator>
	class rb_tree
	{
	public:
		typedef T															value_type;
		typedef Compare														value_compare;
		typedef Allocator													allocator_type;
		typedef ft::node<value_type> 										node_type;
		typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
		typedef typename node_allocator::pointer							node_ptr;
		typedef typename node_allocator::size_type							size_type;
		typedef typename node_allocator::const_pointer						const_pointer;
		// typedef ft::RB_Iterator<value_type>									iterator;
		// typedef ft::const_RB_Iterator<value_type>							const_iterator;
		// typedef ft::reverse_iterator<iterator>								reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

	private:
		value_compare _comp;
		node_allocator _node_alloc;
		node_ptr _Nnull;
		node_ptr _root;
		size_type _size;

	public:
		explicit rb_tree(const value_compare &comp = value_compare(), const allocator_type &alloc = allocator_type()):
			_comp(comp), _node_alloc(alloc), _Nnull(NULL), _root(NULL),  _size(0)
		{
			_Nnull = make_Nnull();
			_root = _Nnull;
		}

		node_ptr get__Nnull()
		{
			return _Nnull;
		}

		const_pointer get__Nnull() const
		{
			return _Nnull;
		}

		node_ptr make_Nnull()
		{
			node_ptr Nnull;
			if (1 > this->max_size())
				throw std::length_error("RB_tree");
			Nnull = _node_alloc.allocate(1);
			Nnull->black();
			Nnull->parent = Nnull;
			Nnull->left = Nnull->right = Nnull;
			return (Nnull);
		}
		node_ptr dup_node(node_ptr x)
		{
			if (1 > this->max_size())
				throw std::length_error("RB_tree");
			node_ptr y = _node_alloc.allocate(1);
			try
			{
				_node_alloc.construct(y, x->val);
			}
			catch(...)
			{
				_node_alloc.deallocate(y, 1);
				throw;
			}
			y->parent = y->left = y->right = _Nnull;
			return y;
		}

		node_ptr dup_rb_tree(const node_ptr x, const node_ptr par,const node_ptr old_null)
		{
			if (x == old_null)
				return _Nnull;
			node_ptr y = dup_node(x);
			y->parent = par;
			if (x->left != old_null)
				y->left = dup_rb_tree(x->left, y,old_null);
			if (x->right != old_null)
				y->right = dup_rb_tree(x->right, y,old_null);
			return y;
		}
		rb_tree(const rb_tree &x) : _comp(x._comp), _node_alloc(x._node_alloc), _Nnull(make_Nnull()), _root(dup_rb_tree(x._root, _Nnull,x._Nnull)), _size(x._size)
		{
			_Nnull->right = _root->max_node(_Nnull);
		}
		rb_tree &operator=(const rb_tree &x)
		{
			clear();
			_comp = x._comp;
			_node_alloc = x._node_alloc;
			_root = dup_rb_tree(x._root, _Nnull, x._Nnull);
			_Nnull->right = _root->max_node(_Nnull);
			_size = x._size;
			return *this;
		}
		~rb_tree()
		{
			clear();
			_node_alloc.deallocate(_Nnull, 1);
		}
		template<typename key>
		size_type count (const key& val) const
		{
			node_ptr x = _root;
			while (x != _Nnull)
			{
				if (_comp(val, x->val))
					x = x->left;
				else if (_comp(x->val, val))
					x = x->right;
				else
					return 1;
			}
			return 0;
		}
		size_type size() const{
			return _size;
		}
		size_type max_size() const{
			return(_node_alloc.max_size());
		}
		bool empty() const{
			return (_size == 0);
		}
		void clear_node(node_ptr del)
		{
			_node_alloc.destroy(del);
			_node_alloc.deallocate(del, 1);
		}
		void clear_rb_tree(node_ptr del)
		{
			if (del != _Nnull)
			{
				clear_rb_tree(del->left);
				clear_rb_tree(del->right);
				clear_node(del);
				--_size;
			}
		}
		void clear()
		{
			clear_rb_tree(_root);
			_root = _Nnull;
			_Nnull->parent = _Nnull->right = _Nnull->left = _Nnull;
		}
		
		node_ptr new_node(const value_type& val)
		{
			if (1 > this->max_size())
				throw std::length_error("RB_tree");
			node_ptr n = _node_alloc.allocate(1);
			try
			{
				_node_alloc.construct(n, val);
			}
			catch(...)
			{
				_node_alloc.deallocate(n, 1);
				throw;
			}
			n->parent = n->right = n->left = _Nnull;
			return (n);
		}
		
		void rotate_left(node_ptr x)
		{
			node_ptr y = x->right;
			x->right = y->left;
			if (y->left != _Nnull)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == _Nnull)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		void rotate_right(node_ptr x)
		{
			node_ptr y = x->left;
			x->left = y->right;
			if (y->right != _Nnull)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == _Nnull)
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		template<typename key>
		node_ptr find(const key& val)
		{
			node_ptr x = _root;
			while (x != _Nnull)
			{
				if (_comp(val, x->val))
					x = x->left;
				else if (_comp(x->val, val))
					x = x->right;
				else
					return (x);
			}
			return (_Nnull);
		}
		
		node_ptr find(const value_type& val) const
		{
			node_ptr x = _root;
			while (x != _Nnull)
			{
				if (_comp(val, x->val))
					x = x->left;
				else if (_comp(x->val, val))
					x = x->right;
				else
					return (x);
			}
			return (_Nnull);
		}
		
		template<typename key>
		const_pointer find(const key& val) const
		{
			const_pointer x = _root;
			while (x != _Nnull)
			{
				if (_comp(val, x->val))
					x = x->left;
				else if (_comp(x->val, val))
					x = x->right;
				else
					return (x);
			}
			return (_Nnull);
		}

		template <typename key_type>
		node_ptr at (const key_type& k)
		{
			node_ptr x = _root;
			node_ptr y = _Nnull;
			
			while (x != _Nnull)
			{
				y = x;
				if (_comp(k, x->val))
					x = x->left;
				else if (_comp(x->val, k))
					x = x->right;
				else
					return x;
			}
			throw std::out_of_range("map");
		}


		template <typename key_type>
		const_pointer at (const key_type& k) const
		{
			const_pointer x = _root;
			const_pointer y = _Nnull;
			
			while (x != _Nnull)
			{
				y = x;
				if (_comp(k, x->val))
					x = x->left;
				else if (_comp(x->val, k))
					x = x->right;
				else
					return x;
			}
			throw std::out_of_range("map");
		}

		template <typename key_type>
		node_ptr operator[] (const key_type& k)
		{
			node_ptr x = _root;
			node_ptr y = _Nnull;
			
			while (x != _Nnull)
			{
				y = x;
				if (_comp(k, x->val))
					x = x->left;
				else if (_comp(x->val, k))
					x = x->right;
				else
					return x;
			}
			node_ptr newnode = new_node(ft::make_pair(k,value_type().second));
			newnode->parent = y;
			if (y == _Nnull)
				_root = newnode;
			else if (_comp(newnode->val, y->val))
				y->left = newnode;
			else
				y->right = newnode;
			++_size;
			if (newnode->parent == _Nnull)
				newnode->black();
			else if(newnode->parent->parent == _Nnull)
				;
			else
				balance_insert(newnode);
			if (_Nnull->right == _Nnull)
				_Nnull->right = _root->max_node(_Nnull);
			else
				_Nnull->right = _Nnull->right->max_node(_Nnull);
			return newnode;
		}
		
		ft::pair<node_ptr,bool> insert(node_ptr newnode)
		{
			node_ptr x = _root;
			node_ptr y = _Nnull;
			
			while (x != _Nnull)
			{
				y = x;
				if (_comp(newnode->val, x->val))
					x = x->left;
				else if (_comp(x->val, newnode->val))
					x = x->right;
				else
					return ft::make_pair(x,false);
			}
			newnode->parent = y;
			if (y == _Nnull)
				_root = newnode;
			else if (_comp(newnode->val, y->val))
				y->left = newnode;
			else
				y->right = newnode;
			++_size;
			if (newnode->parent == _Nnull)
				newnode->black();
			else if(newnode->parent->parent == _Nnull)
				;
			else
				balance_insert(newnode);
			if (_Nnull->right == _Nnull)
				_Nnull->right = _root->max_node(_Nnull);
			else
				_Nnull->right = _Nnull->right->max_node(_Nnull);
			return ft::make_pair(newnode,true);
		}
		void balance_insert(node_ptr newnode)
		{
			// printTree();
			// std::cout << "\n";
			while (newnode->parent != _Nnull && !newnode->parent->is_black)
			{
				node_ptr x = _Nnull;
				if (newnode->parent == newnode->parent->parent->right)
				{
					x = newnode->parent->parent->left;
					if (!x->is_black)
					{
						x->black();
						newnode->parent->black();
						newnode->parent->parent->red();
						newnode = newnode->parent->parent;
					}
					else
					{
						if(newnode == newnode->parent->left)
						{
							newnode = newnode->parent;
							rotate_right(newnode);
						}
						newnode->parent->black();
						newnode->parent->parent->red();
						rotate_left(newnode->parent->parent);
					}
				}
				else
				{
					x = newnode->parent->parent->right;
					if(!x->is_black)
					{
						x->black();
						newnode->parent->black();
						newnode->parent->parent->red();
						newnode = newnode->parent->parent;
					}
					else
					{
						if(newnode == newnode->parent->right)
						{
							newnode = newnode->parent;
							rotate_left(newnode);
						}
						newnode->parent->black();
						newnode->parent->parent->red();
						rotate_right(newnode->parent->parent);
					}
				}
			}
			_root->black();
		}
		
		ft::pair<node_ptr,bool> insert(const value_type &val)
		{
			node_ptr newnode = new_node(val);
			ft::pair<node_ptr,bool> ret = insert(newnode);
			if (ret.second == false)
				clear_node(newnode);
			return ret;
		}

		void replace_node(node_ptr x, node_ptr y)
		{
			if (x == _root)
				_root = y;
			else if(x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->parent = x->parent;
		}
		// void erase(iterator it)
		// {
		// 	erase(it._it);
		// }
		void erase(node_ptr del)
		{
			node_ptr x;
			node_ptr y = del;
			bool iblack = del->is_black;
			if (del == _Nnull->right)
			{
				if (_size == 1)
					_Nnull->right = _Nnull;
				else 
					_Nnull->right = del->Rb_tree_decrement(_Nnull);
			}
			if (del->left == _Nnull)
			{
				x = del->right;
				replace_node(del, del->right);
			}
			else if (del->right == _Nnull)
			{
				x = del->left;
				replace_node(del, del->left);
			}
			else
			{
				y = del->right->min_node(_Nnull);
				iblack = y->is_black;
				x = y->right;
				if (y->parent == del)
					x->parent = y;
				else
				{
					replace_node(y, y->right);
					y->right = del->right;
					y->right->parent = y;
				}
				replace_node(del, y);
				y->left = del->left;
				y->left->parent = y;
				y->is_black = del->is_black;
			}
			clear_node(del);
			--_size;
			if (iblack)
				balance_erase(x);
			_Nnull->parent = _Nnull->left = _Nnull;
		}
		void balance_erase(node_ptr x)
		{
			while (x != _root && x->is_black)
			{
				if (x == x->parent->left)
				{
					node_ptr w = x->parent->right;
					if (!w->is_black)
					{
						w->black();
						x->parent->red();
						rotate_left(x->parent);
						w = x->parent->right;
					}
					if (w->left->is_black && w->right->is_black)
					{
						w->red();
						x = x->parent;
					}
					else
					{
						if (w->right->is_black)
						{
							w->left->black();
							w->red();
							rotate_right(w);
							w = x->parent->right;
						}
						w->is_black = x->parent->is_black;
						x->parent->black();
						w->right->black();
						rotate_left(x->parent);
						x = _root;
					}
				}
				else
				{
					node_ptr w = x->parent->left;
					if (!w->is_black)
					{
						w->black();
						x->parent->red();
						rotate_right(x->parent);
						w = x->parent->left;
					}
					if (w->left->is_black && w->right->is_black)
					{
						w->red();
						x = x->parent;
					}
					else
					{
						if (w->left->is_black)
						{
							w->right->black();
							w->red();
							rotate_left(w);
							w = x->parent->left;
						}
						w->is_black = x->parent->is_black;
						x->parent->black();
						w->left->black();
						rotate_right(x->parent);
						x = _root;
					}
				}
			}
			x->is_black = 1;
			// printTree();
			// std::cout << "\n";
		}
		
		template<typename Key>
		bool erase(const Key& val)
		{
			node_ptr x = find(val);
			if (x == _Nnull)
				return false;
			erase(x);
			return true;
		}

		template<typename Key>
		node_ptr lower_bound(const Key& val)
		{
			node_ptr x = _root;
			node_ptr y = _Nnull;
			while (x != _Nnull)
			{
				if (!_comp(x->val , val))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return y;
		}

		node_ptr lower_bound(const value_type& val) const
		{
			node_ptr x = _root;
			node_ptr y = _Nnull;
			while (x != _Nnull)
			{
				if (!_comp(x->val , val))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return y;
		}

		template<typename Key>
		const_pointer lower_bound(const Key& val) const
		{
			const_pointer x = _root;
			const_pointer y = _Nnull;
			while (x != _Nnull)
			{
				if (!_comp(x->val , val))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return y;
		}

		node_ptr upper_bound(const value_type& val) const
		{
			node_ptr x = _root;
			node_ptr y = _Nnull;
			while (x != _Nnull)
			{
				if (_comp(val, x->val))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return y;
		}
		
		template<typename Key>
		node_ptr upper_bound(const Key& val)
		{
			node_ptr x = _root;
			node_ptr y = _Nnull;
			while (x != _Nnull)
			{
				if (_comp(val, x->val))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return y;
		}

		template<typename Key>
		const_pointer upper_bound(const Key& val) const
		{
			const_pointer x = _root;
			const_pointer y = _Nnull;
			while (x != _Nnull)
			{
				if (_comp(val, x->val))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return y;
		}

		template<typename Key>
		ft::pair<node_ptr,node_ptr> equal_range(const Key& val)
		{
			node_ptr x = _root;
			node_ptr y = _Nnull;
			while (x != _Nnull)
			{
				if (_comp(x->val, val))
				{
					x = x->right;
				}
				else if (_comp(val, x->val))
				{
					y = x;
					x = x->left;
				}
				else
					return (ft::make_pair(x, x->Rb_tree_increment(_Nnull)));
			}
			return (ft::make_pair(y, y));
		}

		ft::pair<node_ptr,node_ptr> equal_range(const value_type& val) const
		{
			node_ptr x = _root;
			node_ptr y = _Nnull;
			while (x != _Nnull)
			{
				if (_comp(x->val, val))
				{
					x = x->right;
				}
				else if (_comp(val, x->val))
				{
					y = x;
					x = x->left;
				}
				else
					return (ft::make_pair(x, x->Rb_tree_increment(_Nnull)));
			}
			return (ft::make_pair(y, y));
		}
	
		template<typename Key>
		ft::pair<const_pointer,const_pointer> equal_range(const Key& val) const
		{
			const_pointer x = _root;
			const_pointer y = _Nnull;
			while (x != _Nnull)
			{
				if (_comp(x->val, val))
				{
					x = x->right;
				}
				else if (_comp(val, x->val))
				{
					y = x;
					x = x->left;
				}
				else
					return (ft::make_pair(x, x->Rb_tree_increment(_Nnull)));
			}
			return (ft::make_pair(y, y));
		}

		node_ptr begin()
		{
			if (_root == _Nnull)
				return _Nnull;
			return _root->min_node(_Nnull);
		}
		const_pointer begin() const
		{
			if (_root == _Nnull)
				return _Nnull;
			return _root->min_node(_Nnull);
		}
		// reverse_iterator rbegin()
		// {
		// 	return reverse_iterator(end());
		// }
		// const_reverse_iterator rbegin() const
		// {
		// 	return const_reverse_iterator(end());
		// }
		node_ptr end()
		{
			return _Nnull;
		}
		const_pointer end() const
		{
			return _Nnull;
		}
		// reverse_iterator rend()
		// {
		// 	return reverse_iterator(begin());
		// }
		// const_reverse_iterator rend() const
		// {
		// 	return const_reverse_iterator(begin());
		// }

	
		// void printHelper(node_ptr root, std::string indent, bool last) const
		// {
		// 	if (root != _Nnull)
		// 	{
		// 		std::cout << indent;
		// 		if (last) {
		// 			std::cout << "R----";
		// 			indent += "   ";
		// 		} else {
		// 			std::cout << "L----";
		// 			indent += "|  ";
		// 		}

		// 		std::string sColor = root->is_black ? "BLACK" : "RED";
		// 		std::cout << root->val << "(" << sColor << ")" << std::endl;
		// 		printHelper(root->left, indent, false);
		// 		printHelper(root->right, indent, true);
		// 	}
  		// }
		void swap(rb_tree &s)
		{
			std::swap(_root, s._root);
			std::swap(_Nnull, s._Nnull);
			std::swap(_comp, s._comp);
			std::swap(_size, s._size);
		}
		// void printTree() const
		// {
		// 	if (_root != _Nnull)
		// 	{
		// 		printHelper(_root, "", true);
		// 	}
		// }
	};
}
#endif