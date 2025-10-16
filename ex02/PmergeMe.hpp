/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:14:59 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/15 17:18:34 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

class PmergeMe
{
private:
    std::vector<unsigned int> _vec;
    std::list<unsigned int> _list;

public:
    class PmergeMe_exception;
    class PmergeMe_invalid_arg;
    class PmergeMe_out_of_range;

    PmergeMe(char **seq);
    ~PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);

    void print_vector();
    void print_list();
    void sort();
};

using vector = std::vector<unsigned int>;

void print_elements(vector::const_iterator it, int element_size);
void print_v(const vector &vec, int element_size);
unsigned int jacobsthal(unsigned int n);
vector::iterator bi_search(vector::iterator first, vector::iterator last, unsigned int target, int element_size);
void binary_insertion(vector &main_chain, vector &pend, int element_size);
void sort_pairs(vector &vec, int depth);