/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/31 20:05:04 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

size_t jacobsthal(size_t n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void print_elements(vector::iterator it, vector::iterator end, size_t block_size)
{
    std::cout << "[";
    for (size_t i = 0; i < block_size; i++)
    {
        auto current = it + i;
        if (current >= end)
            break;

        std::cout << *current;
        if (i < block_size - 1 && current + 1 < end)
            std::cout << ",";
    }
    std::cout << "]";
}

void print_v(vector &container, size_t block_size)
{
    for (auto it = container.begin(); it < container.end(); it += block_size)
    {
        print_elements(it, container.end(), block_size);
    }
    std::cout << std::endl;
}

void print_info(int lvl, int total_blocks, int block_size)
{
    std::cout << "lvl: " << lvl << " total_blocks: " << total_blocks << " block_size: " << block_size << std::endl;
}
