/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_deque.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:19:25 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/31 20:09:02 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "utils.hpp"

void init_main_pend(deque &main, deque &pend, deque &container, int block_size, int total_blocks)
{
    // first two insertion (b1, a1) into main
    auto start = container.begin();
    auto end = start + block_size * 2;
    main.insert(main.end(), start, end);
    start = end;
    end = start + block_size;

    // insert pairs_of_blocks in main or pend
    for (size_t i = 3; i <= total_blocks; i++)
    {
        if (i % 2 == 0)
            main.insert(main.end(), start, end);
        else
            pend.insert(pend.end(), start, end);
        start += block_size;
        end = start + block_size;
    }
}

int search(const deque &main, int left, int right, size_t target_value, size_t block_size)
{
    while (left < right)
    {
        size_t mid_block_idx = left + ((right - left) / (2 * block_size)) * block_size;
        mid_block_idx = std::min(mid_block_idx, right - block_size);

        if (main[mid_block_idx + block_size - 1] < target_value)
            left = mid_block_idx + block_size;
        else
            right = mid_block_idx;
    }
    return left;
}

void binary_insertion(deque &main, deque &pend, size_t block_size)
{
    int total_blocks_pend = pend.size() / block_size;
    int inserted_blocks = 0;

    for (int n = 3;; n++)
    {
        int pend_id = jacobsthal(n);
        int diff = jacobsthal(n) - jacobsthal(n - 1);
        if (diff <= 0 || diff > total_blocks_pend - inserted_blocks)
            break;

        int offset = 0;
        for (int i = 0; i < diff; i++)
        {
            int target_block_idx = (inserted_blocks + diff - 1 - i) * block_size;
            int right_bound_block_idx = std::min((pend_id + inserted_blocks - offset) * block_size, main.size());

            int found = search(main, 0, right_bound_block_idx, pend[target_block_idx + block_size - 1], block_size);
            main.insert(main.begin() + found, pend.begin() + target_block_idx, pend.begin() + target_block_idx + block_size);

            if ((found / block_size) == (pend_id + inserted_blocks))
                offset++;
        }
        inserted_blocks += diff;
    }

    int remaining_blocks = total_blocks_pend - inserted_blocks;
    for (int i = remaining_blocks - 1; i >= 0; i--)
    {
        int target_block_idx = (inserted_blocks + i) * block_size;
        int right_bound_block_idx = main.size();

        int found = search(main, 0, right_bound_block_idx, pend[target_block_idx + block_size - 1], block_size);

        main.insert(main.begin() + found, pend.begin() + target_block_idx, pend.begin() + target_block_idx + block_size);
    }
}

void sort_blocks(deque &container, int block_size)
{
    int pairs = container.size() / block_size - ((container.size() / block_size) % 2);
    auto end = container.begin() + pairs * block_size;

    for (auto it = container.begin(); it != end; std::advance(it, block_size * 2))
    {
        auto left_block_last = std::next(it, block_size - 1);
        auto right_block_last = std::next(it, block_size * 2 - 1);

        if (*right_block_last < *left_block_last)
        {
            for (int i = block_size - 1; i >= 0; i--)
            {
                std::iter_swap(left_block_last - i, right_block_last - i);
            }
        }
    }
}

void insert_rest(deque &container, deque &main)
{
    for (auto it = container.begin() + main.size(); it < container.end(); it++)
    {
        main.push_back(*it);
    }
}

void ford_johnson(deque &container, int depth)
{
    const int block_size = static_cast<int>(std::pow(2, depth - 1));

    int total_blocks = container.size() / block_size;
    if (total_blocks < 2)
        return;

    sort_blocks(container, block_size);
    ford_johnson(container, depth + 1);

    deque main, pend;
    init_main_pend(main, pend, container, block_size, total_blocks);

    bool is_odd = total_blocks % 2 == 1;
    if (!pend.empty())
        binary_insertion(main, pend, block_size);

    if (container.size() > main.size())
        insert_rest(container, main);
    container = main;
}