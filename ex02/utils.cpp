/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/28 13:46:58 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

using vector = std::vector<size_t>;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void print_elements(vector::iterator it,
                    vector::iterator end,
                    size_t block_size)
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

bool _comp_it(const std::vector<size_t>::iterator &a,
              const std::vector<size_t>::iterator &b)
{
    return *a < *b;
}

void print_v(vector &vec, size_t block_size)
{
    for (auto it = vec.begin(); it < vec.end(); it += block_size)
    {
        print_elements(it, vec.end(), block_size);
    }
    std::cout << std::endl;
}

void print_(std::vector<vector::iterator> &vec, size_t block_size)
{
    for (auto it = vec.begin(); it < vec.end(); it++)
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

void print_info(int lvl, int total_blocks, int pairs_of_blocks, int block_size)
{
    std::cout << "lvl: " << lvl << " total_blocks: " << total_blocks << " pairs_of_blocks: " << pairs_of_blocks << " block_size: " << block_size << std::endl;
}

void init_main_pend(std::vector<vector::iterator> &main, std::vector<vector::iterator> &pend, vector &container, int block_size, int total_blocks)
{
    // first two insertion (b1, a1) into main
    auto curr = std::next(container.begin(), block_size - 1);
    auto next = std::next(container.begin(), block_size * 2 - 1);
    main.push_back(curr);
    main.push_back(next);

    // insert pairs_of_blocks in main or pend
    for (int i = 3; i <= total_blocks; i++)
    {
        curr = std::next(container.begin(), block_size * i - 1);
        if (i % 2 == 0)
            main.push_back(curr);
        else
            pend.push_back(curr);
    }
}

size_t jacobsthal(size_t n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void binary_insertion(std::vector<vector::iterator> &main, std::vector<vector::iterator> &pend, bool is_odd)
{

    int inserted_numbers = 0;
    for (int n = 3;; n++)
    {
        int pend_id = jacobsthal(n);
        size_t diff = jacobsthal(n) - jacobsthal(n - 1);
        int offset = 0;
        if (diff > pend.size())
            break;
        auto target = std::next(pend.begin(), diff - 1);
        auto right_bound = std::next(main.begin(), pend_id + inserted_numbers);
        int insertions = diff;
        while (insertions > 0)
        {
            auto found_pos = std::upper_bound(main.begin(), right_bound, *target, _comp_it);
            auto inserted_pos = main.insert(found_pos, *target);
            insertions--;
            target = pend.erase(target);
            std::advance(target, -1);
            if (static_cast<int>(std::distance(main.begin(), inserted_pos)) == (pend_id + inserted_numbers))
                offset += 1;
            right_bound = std::next(main.begin(), pend_id + inserted_numbers - offset);
        }
        inserted_numbers += diff;
        offset = 0;
    }

    for (int i = pend.size() - 1; i >= 0; i--)
    {
        auto target = std::next(pend.begin(), i);
        auto right_bound = std::next(main.begin(), main.size() - pend.size() + i + is_odd);
        auto found_pos = std::upper_bound(main.begin(), right_bound, *target, _comp_it);
        main.insert(found_pos, *target);
    }
}

void insert_rest(const vector &vec, vector &main)
{
    if (vec.size() > main.size())
    {
        auto it = vec.begin() + main.size();
        main.insert(main.end(), it, vec.end());
    }
}

void sort_blocks(vector &container, int block_size)
{
    int pairs = container.size() / block_size - ((container.size() / block_size) % 2);
    auto end = container.begin() + pairs * block_size;

    for (auto it = container.begin(); it != end; std::advance(it, block_size * 2))
    {
        auto left_block_last = std::next(it, block_size - 1);
        auto right_block_last = std::next(it, block_size * 2 - 1);

        if (_comp_it(right_block_last, left_block_last))
        {
            for (int i = block_size - 1; i >= 0; i--)
            {
                std::iter_swap(left_block_last - i, right_block_last - i);
            }
        }
    }
}

void ford_johnson(vector &container, int depth)
{
    const int block_size = static_cast<int>(std::pow(2, depth - 1));

    int total_blocks = container.size() / block_size;
    if (total_blocks < 2)
        return;

    bool is_odd = total_blocks % 2 == 1;
    sort_blocks(container, block_size);

    ford_johnson(container, depth + 1);

    std::vector<vector::iterator> main, pend;

    init_main_pend(main, pend, container, block_size, total_blocks);

    binary_insertion(main, pend, is_odd);

    vector copy;
    copy.reserve(container.size());
    for (auto it = main.begin(); it != main.end(); it++)
    {
        for (int i = block_size - 1; i >= 0; i--)
        {
            auto block_last = *it;
            auto element = std::prev(block_last, i);
            copy.push_back(*element);
        }
    }
    container = copy;
}
