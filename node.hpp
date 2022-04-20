/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:02:57 by tenshi            #+#    #+#             */
/*   Updated: 2022/04/06 21:41:51 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __NODE_H__
#define __NODE_H__

namespace ft
{
    template <typename T>
	class node
	{
		public:
		typedef T		value_type;
		typedef node<T>*	node_ptr;
		typedef const node<T>*	const_node_ptr;

		node_ptr parent;
		node_ptr left;
		node_ptr right;
		value_type val;
		bool is_black;

		node(const value_type& value):
		parent(NULL), left(NULL), right(NULL), val(value), is_black(false){}
		~node(){
			// parent = left = right = NULL;
		}
		node(const node &cm){
			*this = cm;
		}
		
		node &operator=(const node &cm)
		{
			parent = cm.parent;
			left = cm.left;
			right = cm.right;
			val = cm.val;
			is_black = cm.is_black;
			return (*this);
		}
		void red()
		{
			is_black = false;
		}
		void black()
		{
			is_black = true;
		}
		node_ptr Rb_tree_increment(node_ptr Nnull)
		{
			node_ptr x = this;
			if (x == Nnull)
				return (Nnull->right);
			if (x->right != Nnull)
			{
				x = x->right;
				while (x->left != Nnull)
					x = x->left;
			}
			else
			{
				node_ptr y = x->parent;
				while (x == y->right)
				{
					x = y;
					y = y->parent;
				}
				if (x->right != y)
					x = y;
			}
			return x;
		}
		const_node_ptr Rb_tree_increment(const_node_ptr Nnull) const
		{
			const_node_ptr x = this;
			if (x == Nnull)
				return (Nnull->right);
			if (x->right != Nnull)
			{
				x = x->right;
				while (x->left != Nnull)
					x = x->left;
			}
			else
			{
				const_node_ptr y = x->parent;
				while (x == y->right)
				{
					x = y;
					y = y->parent;
				}
				if (x->right != y)
					x = y;
			}
			return x;
		}
		node_ptr Rb_tree_decrement(node_ptr Nnull)
		{
			node_ptr x = this;
			if (x == Nnull)
				return (x->right);
			if (!x->is_black && x->parent->parent == x)
				x = x->right;
			else if (x->left != Nnull)
			{
				node_ptr y = x->left;
				while (y->right != Nnull)
					y = y->right;
				x = y;
			}
			else
			{
				node_ptr y = x->parent;
				while (x == y->left)
				{
					x = y;
					y = y->parent;
				}
				x = y;
			}
			return x;
		}
		const_node_ptr Rb_tree_decrement(const_node_ptr Nnull) const
		{
			const_node_ptr x = this;
			if (x == Nnull)
				return (x->right);
			if (!x->is_black && x->parent->parent == x)
				x = x->right;
			else if (x->left != Nnull)
			{
				const_node_ptr y = x->left;
				while (y->right != Nnull)
					y = y->right;
				x = y;
			}
			else
			{
				const_node_ptr y = x->parent;
				while (x == y->left)
				{
					x = y;
					y = y->parent;
				}
				x = y;
			}
			return x;
		}
		node_ptr min_node(node_ptr Nnull)
		{
			node_ptr x = this;
			while (x->left != Nnull)
				x = x->left;
			return (x);	
		}
		const_node_ptr min_node(const_node_ptr Nnull) const
		{
			const_node_ptr x = this;
			while (x->left != Nnull)
				x = x->left;
			return (x);	
		}
		node_ptr max_node(node_ptr Nnull)
		{
			node_ptr x = this;
			while (x->right != Nnull)
				x = x->right;
			return (x);
		}
		const_node_ptr max_node(const_node_ptr Nnull) const
		{
			const_node_ptr x = this;
			while (x->right != Nnull)
				x = x->right;
			return (x);
		}
	};
}
#endif