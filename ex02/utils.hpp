/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:21:25 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/28 16:37:01 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

using vector = std::vector<size_t>;
using deque = std::deque<size_t>;

void print_elements(vector::iterator it, vector::iterator end, size_t element_size);
void print_elements(deque::iterator it, deque::iterator end, size_t block_size);
void print_v(vector &container, size_t block_size);
void print_d(deque &container, size_t block_size);
void print_main(std::vector<vector::iterator> &main, size_t block_size);
void print_main(std::deque<deque::iterator> &main, size_t block_size);
void print_info(int lvl, int total_blocks, int pairs_of_blocks, int block_size);

bool _comp_it_vector(const std::vector<size_t>::iterator &a, const std::vector<size_t>::iterator &b);
bool _comp_it_deque(const std::deque<size_t>::iterator &a, const std::deque<size_t>::iterator &b);

size_t jacobsthal(size_t n);