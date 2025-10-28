/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/28 17:04:31 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

bool _comp_it_vector(const std::vector<size_t>::iterator &a, const std::vector<size_t>::iterator &b)
{
    return *a < *b;
}
bool _comp_it_deque(const std::deque<size_t>::iterator &a, const std::deque<size_t>::iterator &b)
{
    return *a < *b;
}

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

void print_elements(deque::iterator it, deque::iterator end, size_t block_size)
{
    std::cout << "[";
    for (size_t i = 0; i < block_size; i++)
    {
        auto current = std::next(it, i);
        if (current == end)
            break;

        std::cout << *current;
        auto next_it = std::next(current);
        if (i < block_size - 1 && next_it != end)
            std::cout << ",";
    }
    std::cout << "]";
}

void print_v(vector &container, size_t block_size)
{
    for (auto it = container.begin(); it != container.end(); it += block_size)
    {
        print_elements(it, container.end(), block_size);
    }
    std::cout << std::endl;
}

void print_d(deque &container, size_t block_size)
{
    for (auto it = container.begin(); it != container.end(); it += block_size)
    {
        print_elements(it, container.end(), block_size);
    }
    std::cout << std::endl;
}

void print_main(std::vector<vector::iterator> &main, size_t block_size)
{
    for (auto it = main.begin(); it != main.end(); it++)
    {
        std::cout << "[";
        for (size_t i = 0; i < block_size; i++)
        {
            std::cout << *(*it + i);
            if (i < block_size - 1)
                std::cout << ",";
        }
        std::cout << "]";
    }
    std::cout << std::endl;
}
void print_main(std::deque<deque::iterator> &main, size_t block_size)
{
    for (auto it = main.begin(); it != main.end(); it++)
    {
        std::cout << "[";
        for (size_t i = 0; i < block_size; i++)
        {
            auto current = std::next(*it, i);
            std::cout << *current;
            if (i < block_size - 1)
                std::cout << ",";
        }
        std::cout << "]";
    }
    std::cout << std::endl;
}

void print_info(int lvl, int total_blocks, int pairs_of_blocks, int block_size)
{
    std::cout << "lvl: " << lvl << " total_blocks: " << total_blocks << " pairs_of_blocks: " << pairs_of_blocks << " block_size: " << block_size << std::endl;
}
