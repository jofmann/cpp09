/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/23 17:03:03 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

using vector = std::vector<size_t>;

void print_elements(vector::const_iterator it,
                    vector::const_iterator end,
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

void print_v(const vector &vec, size_t block_size)
{
    for (auto it = vec.begin(); it < vec.end(); it += block_size)
    {
        print_elements(it, vec.end(), block_size);
    }
    std::cout << std::endl;
}

void print_info(int lvl, int total_blocks, int pairs_of_blocks, int block_size)
{
    std::cout << "lvl: " << lvl << " total_blocks: " << total_blocks << " pairs_of_blocks: " << pairs_of_blocks << " block_size: " << block_size << std::endl;
}

void init_main_pend(vector &main, vector &pend, const vector &vec, size_t block_size, int total_blocks)
{
    auto start = vec.begin();
    auto end = start + block_size * 2;
    main.insert(main.end(), start, end);
    start = end;
    end = start + block_size;
    // insert pairs_of_blocks in main or pend
    for (int i = 3; i <= total_blocks; i++)
    {
        if (i % 2 == 0)
            main.insert(main.end(), start, end);
        else
            pend.insert(pend.end(), start, end);
        start += block_size;
        end = start + block_size;
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

vector::iterator bi_search(vector::iterator first, vector::const_iterator last, size_t target, size_t block_size)
{
    int left = 0;
    int right = (last - first) / block_size;

    while (left < right)
    {
        int mid = left + (right - left) / 2;
        auto mid_last_elem = *(first + mid * block_size + block_size - 1);
        if (mid_last_elem <= target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return first + left * block_size;
}

// void jacobsthal_insertion(vector &main, vector &pend, int block_size)
// {
// }

// void reverse_insertion(vector &main, vector &pend, int block_size)
// {
// }

vector::const_iterator get_right_bound(const vector &vec, int steps)
{

    if (std::distance(vec.begin(), vec.end()) > steps)
        return vec.begin() + steps;
    else
        return vec.end();
}
void insert_block(vector &main, const vector &pend, size_t target_jacob, size_t block_size, size_t total_inserted)
{
    auto target_block = std::next(pend.begin(), (target_jacob - 2) * block_size);

    size_t right_bound_steps = (target_jacob + total_inserted) * block_size;
    auto right_bound = get_right_bound(main, right_bound_steps);

    size_t search_value = *(target_block + block_size - 1);
    auto b_target_pos = bi_search(main.begin(), right_bound, search_value, block_size);

    std::cout << "target_block: ";
    print_elements(target_block, pend.end(), block_size);
    std::cout << std::endl;
    std::cout << "right bound: ";
    if (right_bound != main.end())
        print_elements(right_bound, main.end(), block_size);
    else
        std::cout << "END";
    std::cout << std::endl;
    main.insert(b_target_pos, target_block, target_block + block_size);
}

void binary_insertion(vector &main, vector &pend, size_t block_size)
{
    size_t n = 3;
    size_t target_jacob = jacobsthal(n);
    size_t jacobs_insertion_amount = jacobsthal(n) - jacobsthal(n - 1);

    size_t inserted_count = 0;
    size_t total_insertions = 0;
    size_t total_pend_blocks = pend.size() / block_size;

    while (total_pend_blocks > total_insertions)
    {
        // if (target_jacob > pend.size())
        //     break;
        std::cout << "!!! " << total_insertions << " !!!" << std::endl;
        std::cout << "target_jacob: " << target_jacob << " total_pend_blocks: " << total_pend_blocks << std::endl;
        if (jacobs_insertion_amount <= inserted_count)
        {
            n++;
            target_jacob = jacobsthal(n);
            jacobs_insertion_amount = target_jacob - jacobsthal(n - 1);
            inserted_count = 0;
            if (target_jacob > pend.size())
            {
                std::cout << "####break target_jacob:" << target_jacob << " total_pend_blocks: " << total_pend_blocks << std::endl;
                break;
            }
        }
        std::cout << "jacobs_insertion_amount: " << jacobs_insertion_amount << std::endl;
        std::cout << "insertion_count: " << inserted_count << std::endl;
        std::cout << "target_jacob: " << target_jacob << std::endl;
        std::cout << "total_insertions: " << total_insertions << std::endl;

        insert_block(main, pend, target_jacob, block_size, total_insertions);
        inserted_count++;
        target_jacob--;
        total_insertions++;
        std::cout << "pend: ";
        print_v(pend, block_size);
        std::cout << "\nmain: ";
        print_v(main, block_size);
        std::cout << std::endl;
    }

    if (total_insertions < total_pend_blocks)
    {

        int end_idx = total_insertions * block_size;
        pend.erase(pend.begin(), pend.begin() + end_idx);
        // reverse insert
        total_pend_blocks = pend.size() / block_size;
        while (total_pend_blocks > 0)
        {
            std::cout << "reverse" << std::endl;
            std::cout << "!!! " << total_insertions << " !!!" << std::endl;

            std::cout << "target_jacob: " << target_jacob << " total_pend_blocks: " << total_pend_blocks << std::endl;

            std::cout << "total_insertions: " << total_insertions << std::endl;
            std::cout << "jacobs_insertion_amount: " << jacobs_insertion_amount << std::endl;
            std::cout << "jacobs_block_idx: " << target_jacob << std::endl;
            std::cout << "real block_idx: " << total_pend_blocks - total_insertions << std::endl;
            std::cout << "total_pend_blocks: " << total_pend_blocks << std::endl;

            auto last_block = pend.end() - block_size;
            auto right_bound = get_right_bound(main, (target_jacob + total_insertions) * block_size); // falsch (target_jacob + total_insertions
            auto found = bi_search(main.begin(), right_bound, *(last_block + block_size - 1), block_size);

            std::cout << "pend: ";
            print_v(pend, block_size);
            std::cout << "\nmain: ";
            print_v(main, block_size);
            std::cout << "target_block: ";
            print_elements(last_block, pend.end(), block_size);
            std::cout << std::endl;
            std::cout << "right bound: ";
            if (right_bound != main.end())
                print_elements(right_bound, main.end(), block_size);
            else
                std::cout << "END";
            std::cout << std::endl;

            main.insert(found, last_block, last_block + block_size);
            pend.erase(last_block, last_block + block_size);
            total_pend_blocks--;
            target_jacob--;
            total_insertions++;

            std::cout << "pend: ";
            print_v(pend, block_size);
            std::cout << "\nmain: ";
            print_v(main, block_size);
            std::cout << std::endl;
        }
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

void sort_pairs(vector &vec, int depth)
{

    size_t block_size = static_cast<int>(std::pow(2, depth - 1));
    if (block_size * 2 > vec.size())
        return;

    size_t total_blocks = vec.size() / block_size;
    int pairs_of_blocks = vec.size() / block_size - ((vec.size() / block_size) % 2);
    auto start = vec.begin();
    auto end = start + pairs_of_blocks * block_size;
    for (; start != end; start += block_size * 2)
    {
        size_t left_end = start[block_size - 1];
        size_t right_end = start[block_size * 2 - 1];
        if (left_end > right_end)
            std::swap_ranges(start, start + block_size, start + block_size);
    }

    sort_pairs(vec, depth + 1);
    vector main, pend;

    init_main_pend(main, pend, vec, block_size, total_blocks);

    print_info(depth, total_blocks, pairs_of_blocks, block_size);
    std::cout << "Before binary!" << std::endl;
    std::cout << "vec :";
    print_v(vec, block_size);
    std::cout << "main :";
    print_v(main, block_size);
    std::cout << "pend :";
    print_v(pend, block_size);

    if (!pend.empty())
        binary_insertion(main, pend, block_size);
    insert_rest(vec, main);
    std::cout << "after binary!" << std::endl;
    std::cout << "vec :";
    print_v(vec, block_size);
    std::cout << "main :";
    print_v(main, block_size);
    std::cout << "pend :";
    print_v(pend, block_size);
    vec = std::move(main);
    std::cout << std::endl;
}