/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:14:59 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/22 13:01:29 by phhofman         ###   ########.fr       */
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
    std::vector<size_t> _vec;
    std::list<size_t> _list;

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

using vector = std::vector<size_t>;

void print_elements(vector::const_iterator it, vector::const_iterator end, size_t element_size);
void print_v(const vector &vec, size_t element_size);
size_t jacobsthal(size_t n);
vector::iterator bi_search(vector::iterator first, vector::iterator last, size_t target, size_t element_size);
void binary_insertion(vector &main_chain, vector &pend, size_t element_size);
void sort_pairs(vector &vec, int depth);