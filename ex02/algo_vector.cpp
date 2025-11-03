/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:04:40 by phhofman          #+#    #+#             */
/*   Updated: 2025/11/03 13:53:27 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "utils.hpp"

void init_main_pend(vector &main, vector &pend, vector &container, const size_t block_size, const size_t total_blocks)
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

int binary_idx_search(const vector &main, int left, int right, const size_t target_value, const size_t block_size)
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

void binary_insertion(vector &main, vector &pend, const size_t block_size)
{
    size_t total_blocks_pend = pend.size() / block_size;
    size_t inserted_blocks = 0;

    for (size_t n = 3;; n++)
    {
        size_t pend_id = jacobsthal(n);
        size_t diff = jacobsthal(n) - jacobsthal(n - 1);
        if (diff <= 0 || diff > total_blocks_pend - inserted_blocks)
            break;

        int offset = 0;
        for (size_t i = 0; i < diff; i++)
        {
            int target_block_idx = (inserted_blocks + diff - 1 - i) * block_size;
            int right_bound_block_idx = std::min((pend_id + inserted_blocks - offset) * block_size, main.size());

            int found_idx = binary_idx_search(main, 0, right_bound_block_idx, pend[target_block_idx + block_size - 1], block_size);
            main.insert(main.begin() + found_idx, pend.begin() + target_block_idx, pend.begin() + target_block_idx + block_size);

            if ((found_idx / block_size) == (pend_id + inserted_blocks))
                offset++;
        }
        inserted_blocks += diff;
    }

    int remaining_blocks = total_blocks_pend - inserted_blocks;
    for (int i = remaining_blocks - 1; i >= 0; i--)
    {
        int target_block_idx = (inserted_blocks + i) * block_size;
        int right_bound_block_idx = main.size();

        int found_idx = binary_idx_search(main, 0, right_bound_block_idx, pend[target_block_idx + block_size - 1], block_size);

        main.insert(main.begin() + found_idx, pend.begin() + target_block_idx, pend.begin() + target_block_idx + block_size);
    }
}

void sort_blocks(vector &container, const size_t block_size)
{
    size_t pairs = container.size() / block_size - ((container.size() / block_size) % 2);
    size_t end = pairs * block_size;

    for (size_t i = 0; i < end; i += block_size * 2)
    {
        size_t left_block_last = i + block_size - 1;
        size_t right_block_last = i + block_size * 2 - 1;

        if (container[right_block_last] < container[left_block_last])
        {
            for (size_t j = 0; j < block_size; j++)
            {
                std::swap(container[i + j], container[i + block_size + j]);
            }
        }
    }
}

void insert_rest(vector &container, vector &main)
{
    for (auto it = container.begin() + main.size(); it < container.end(); it++)
    {
        main.push_back(*it);
    }
}

void ford_johnson(vector &container, int depth)
{
    const size_t block_size = static_cast<size_t>(std::pow(2, depth - 1));

    const size_t total_blocks = container.size() / block_size;
    if (total_blocks < 2)
        return;

    sort_blocks(container, block_size);
    ford_johnson(container, depth + 1);

    vector main, pend;

    init_main_pend(main, pend, container, block_size, total_blocks);

    if (!pend.empty())
        binary_insertion(main, pend, block_size);

    if (container.size() > main.size())
        insert_rest(container, main);

    container = std::move(main);
}