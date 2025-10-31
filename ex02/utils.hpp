/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:21:25 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/31 20:04:45 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

using vector = std::vector<size_t>;
using deque = std::deque<size_t>;

void print_elements(vector::iterator it, vector::iterator end, size_t element_size);
void print_elements(deque::iterator it, deque::iterator end, size_t block_size);
void print_v(vector &container, size_t block_size);
void print_info(int lvl, int total_blocks, int block_size);

size_t jacobsthal(size_t n);