/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:14:59 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/31 20:06:31 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <chrono>
#include "utils.hpp"

using vector = std::vector<size_t>;
using deque = std::deque<size_t>;

class PmergeMe
{
private:
    vector _vec;
    deque _deque;

public:
    class PmergeMe_exception;
    class PmergeMe_invalid_arg;
    class PmergeMe_out_of_range;
    class PmergeMe_not_sorted;

    PmergeMe(char **seq);
    ~PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);

    void print_vector(size_t limit);
    void print_deque(size_t limit);
    void sort_vector();
    void sort_deque();

    vector get_vector();
    deque get_deque();
};

void ford_johnson(vector &container, int depth);

void ford_johnson(deque &container, int depth);