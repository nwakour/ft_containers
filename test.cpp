/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:45:42 by nwakour           #+#    #+#             */
/*   Updated: 2022/05/07 19:22:29 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "iterator.hpp"
#include "vector.hpp"
#include "utilities.hpp"
#include "rb_tree.hpp"
#include "set.hpp"
#include "map.hpp"
#include <memory>
#include <set>
#include <map>
#include <list>


int main(void)
{
	// const int cut = 3;
	// ft::vector<int> vct(2);
	// vct.insert(vct.end(), 42);
	// // for (ft::vector<int>::iterator it = vct.begin(); it != vct.end(); ++it)
	// // {
	// // 	std::cout << *it << std::endl;
	// // }
	// vct.insert(vct.end(), 42);
	// vct.insert(vct.end(), 42);
	// for (ft::vector<int>::iterator it = vct.begin(); it != vct.end(); ++it)
	// {
	// 	std::cout << *it << std::endl;
	// }
	ft::vector<int> vct;
	ft::vector<int>::iterator it = vct.begin();
	ft::vector<int>::const_iterator ite = vct.begin();
	ft::vector<int>::reverse_iterator rit(it);
	ft::vector<int>::const_reverse_iterator crit(rit);
	ft::vector<int>::const_reverse_iterator crit_(it);
	ft::vector<int>::const_reverse_iterator crit_2(ite);
	return (0);
}
