/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:14:59 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/28 13:25:31 by phhofman         ###   ########.fr       */
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
public: // TODO: change to private
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

void print_elements(vector::iterator it, vector::iterator end, size_t element_size);
void print_v(vector &vec, size_t block_size);

void ford_johnson(vector &container, int depth);