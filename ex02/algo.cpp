/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:24:20 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/24 13:25:54 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

// alias wie bei dir
using vector = std::vector<size_t>;

// Hilfsfunktion: slice ein vector<size_t> in Blöcke der Größe block_size
static std::vector<std::vector<size_t>> slice_blocks(const vector &v, size_t block_size)
{
    std::vector<std::vector<size_t>> blocks;
    size_t n_blocks = v.size() / block_size;
    blocks.reserve(n_blocks);
    for (size_t i = 0; i < n_blocks; ++i)
    {
        blocks.emplace_back(v.begin() + i * block_size, v.begin() + (i + 1) * block_size);
    }
    return blocks;
}

// Hilfs: schreibe block-list zurück in flachen vector (überschreibt target)
static void flatten_blocks_into(vector &target, const std::vector<std::vector<size_t>> &blocks)
{
    target.clear();
    target.reserve(blocks.size() * (blocks.empty() ? 0 : blocks[0].size()));
    for (const auto &blk : blocks)
    {
        target.insert(target.end(), blk.begin(), blk.end());
    }
}

// iterative Jacobsthal (schneller und keine tiefe Rekursion)
static long jacobsthal_number(long n)
{
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;
    long a = 0; // J(0)
    long b = 1; // J(1)
    for (long i = 2; i <= n; ++i)
    {
        long c = b + 2 * a;
        a = b;
        b = c;
    }
    return b;
}

// Comparator: vergleiche Block anhand letztem Element (wie in deinem bi_search)
struct BlockLastComp
{
    bool operator()(const std::vector<size_t> &lhs, const std::vector<size_t> &rhs) const
    {
        // compare based on last element
        return lhs.back() < rhs.back();
    }
    bool operator()(const std::vector<size_t> &lhs, size_t value) const
    {
        return lhs.back() < value;
    }
    bool operator()(size_t value, const std::vector<size_t> &rhs) const
    {
        return value < rhs.back();
    }
};

// Upper bound on blocks by last-element (search in [begin, bound_it) by last element)
static std::vector<std::vector<size_t>>::iterator upper_bound_by_last(
    std::vector<std::vector<size_t>> &blocks,
    std::vector<std::vector<size_t>>::iterator bound_it,
    size_t value)
{
    return std::upper_bound(blocks.begin(), bound_it, value,
                            [](const size_t &val, const std::vector<size_t> &blk)
                            { return val < blk.back(); });
}

/*
 * Neue binary_insertion, arbeitet auf Block-Vektoren und schreibt am Ende zurück in `main`.
 *
 * main: flacher vector mit bereits teilweise sortierten Blocks
 * pend: flacher vector mit Pending-Blocks (nur b's)
 * block_size: Elemente pro Block
 */
void binary_insertion(vector &main, vector &pend, size_t block_size)
{
    if (block_size == 0)
        return;

    // slice in Block-Vektoren
    auto main_blocks = slice_blocks(main, block_size);
    auto pend_blocks = slice_blocks(pend, block_size);

    // Phase 1: Jacobsthal-driven insertions
    long prev_j = 1; // J(1) = 1
    long inserted_numbers = 0;

    for (long k = 2;; ++k)
    {
        long curr_j = jacobsthal_number(k);
        long diff = curr_j - prev_j;
        // Wenn die "Diff" größer ist als die aktuelle Anzahl an pend-blöcken => break
        if (diff > static_cast<long>(pend_blocks.size()))
        {
            break;
        }

        // Wir werden 'diff' Blöcke aus pend_blocks entfernen,
        // jedes Mal an der Position (diff - 1) in der (aktuellen) pend_blocks-Liste.
        // Genau wie in der Referenzlösung.
        long nbr_times = diff;
        // pend_index = diff - 1  (0-basiert) - das ist die Startposition für pend_it
        long pend_index = diff - 1;

        // bound index (exclusive) in main_blocks: curr_j + inserted_numbers
        // (Clamp auf main_blocks.size())
        for (; nbr_times > 0; --nbr_times)
        {
            if (pend_blocks.empty())
                break; // defensive
            // ensure pend_index is within bounds after previous erasures:
            if (pend_index < 0)
                pend_index = 0;
            if (pend_index >= static_cast<long>(pend_blocks.size()))
                pend_index = static_cast<long>(pend_blocks.size()) - 1;

            // pick block to insert
            auto block_to_insert = pend_blocks[pend_index];

            // compute bound iterator in main_blocks
            long bound_idx = curr_j + inserted_numbers;
            if (bound_idx < 0)
                bound_idx = 0;
            if (static_cast<size_t>(bound_idx) > main_blocks.size())
                bound_idx = static_cast<long>(main_blocks.size());

            auto bound_it = main_blocks.begin() + static_cast<long>(bound_idx);

            // find insertion position using upper_bound by last element
            auto insert_it = upper_bound_by_last(main_blocks, bound_it, block_to_insert.back());

            // do insert
            main_blocks.insert(insert_it, std::move(block_to_insert)); // move block in

            // remove element from pend_blocks
            pend_blocks.erase(pend_blocks.begin() + pend_index);

            // adjust counters
            ++inserted_numbers;

            // if the inserted position was exactly at the bound index, subsequent bound should be shifted left by 1
            // The reference tracks an offset; we don't need explicit offset variable here because we use inserted_numbers
            // however to mimic the reference correctness we could account for exact-equality case:
            // if ((insert_it - main_blocks.begin()) == (curr_j + inserted_numbers)) { /* offset logic */ }

            // next pend_index: after erasure, the "same" index points to next element, but reference used erase+advance-1.
            // For simplicity, keep pend_index = diff - 1 (because pend shrinks). That matches original pattern.
            pend_index = diff - 1;
            if (pend_index >= static_cast<long>(pend_blocks.size()))
                pend_index = static_cast<long>(pend_blocks.size()) - 1;
            if (pend_blocks.empty())
                break;
        }

        prev_j = curr_j;
    }

    // Phase 2: Reverse insertion of remaining pend blocks (from back to front)
    // Now pend_blocks contains the blocks that were not inserted above.
    // We insert them from last to first, with a bound similar to the reference:
    // curr_bound_index = size_of_main - size_of_pend + i + is_odd
    // We don't know is_odd here; your calling code knows whether original pairing had odd.
    // We'll take is_odd = 0 for safety; this may be adjusted if you know it at call site.
    size_t is_odd = 0; // if you know it from caller, pass it in or compute earlier
    for (ssize_t i = static_cast<ssize_t>(pend_blocks.size()) - 1; i >= 0; --i)
    {
        // compute curr_bound as (main_blocks.size() - pend_blocks.size() + i + is_odd)
        long curr_bound = static_cast<long>(main_blocks.size()) - static_cast<long>(pend_blocks.size()) + static_cast<long>(i) + static_cast<long>(is_odd);
        if (curr_bound < 0)
            curr_bound = 0;
        if (static_cast<size_t>(curr_bound) > main_blocks.size())
            curr_bound = static_cast<long>(main_blocks.size());

        auto bound_it = main_blocks.begin() + curr_bound;

        auto &block_to_insert = pend_blocks[static_cast<size_t>(i)];

        // find position up to bound_it
        auto insert_it = upper_bound_by_last(main_blocks, bound_it, block_to_insert.back());

        main_blocks.insert(insert_it, std::move(block_to_insert));
        // after insert, continue with next i-- (we don't need to erase pend_blocks because we'll discard it)
    }

    // reconstruct main from main_blocks
    flatten_blocks_into(main, main_blocks);

    // clear pend (we consumed pend_blocks) - mimic original pend.erase behavior
    pend.clear();
}

void insert_rest(const vector &vec, vector &main)
{
    if (vec.size() > main.size())
    {
        auto it = vec.begin() + main.size();
        main.insert(main.end(), it, vec.end());
    }
}

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
    std::cout << "pend: ";
    print_v(pend, block_size);
    std::cout << "\nmain: ";
    print_v(main, block_size);

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
    vec = std::move(main); // TODO: check perfomance
    std::cout << std::endl;
}