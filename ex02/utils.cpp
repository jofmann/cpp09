/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/23 11:23:59 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

using vector = std::vector<size_t>;

void print_elements(vector::const_iterator it,
                    vector::const_iterator end,
                    size_t element_size)
{
    std::cout << "[";
    for (size_t i = 0; i < element_size; i++)
    {
        auto current = it + i;
        if (current >= end)
            break;

        std::cout << *current;
        if (i < element_size - 1 && current + 1 < end)
            std::cout << ",";
    }
    std::cout << "]";
}

void print_v(const vector &vec, size_t element_size)
{
    for (auto it = vec.begin(); it < vec.end(); it += element_size)
    {
        print_elements(it, vec.end(), element_size);
    }
    std::cout << std::endl;
}

void print_info(int lvl, int elements, int pairs, int element_size)
{
    std::cout << "lvl: " << lvl << " elements: " << elements << " pairs: " << pairs << " element_size: " << element_size << std::endl;
}

void init_main_pend(vector &main, vector &pend, const vector &vec, size_t element_size, int elements)
{
    auto start = vec.begin();
    auto end = start + element_size * 2;
    main.insert(main.end(), start, end);
    start = end;
    end = start + element_size;
    // insert pairs in main or pend
    for (int i = 3; i <= elements; i++)
    {
        if (i % 2 == 0)
            main.insert(main.end(), start, end);
        else
            pend.insert(pend.end(), start, end);
        start += element_size;
        end = start + element_size;
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

vector::iterator bi_search(vector::iterator first, vector::const_iterator last, size_t target, size_t element_size)
{
    int left = 0;
    int right = (last - first) / element_size;

    while (left < right)
    {
        int mid = left + (right - left) / 2;
        auto mid_last_elem = *(first + mid * element_size + element_size - 1);
        if (mid_last_elem <= target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return first + left * element_size;
}

// void jacobsthal_insertion(vector &main, vector &pend, int element_size)
// {
// }

// void reverse_insertion(vector &main, vector &pend, int element_size)
// {
// }

vector::const_iterator get_right_bound(const vector &vec, int steps)
{

    if (std::distance(vec.begin(), vec.end()) > steps)
        return vec.begin() + steps;
    else
        return vec.end();
}

void binary_insertion(vector &main, vector &pend, size_t element_size)
{
    size_t n = 3;
    size_t b_target_idx = jacobsthal(n);
    size_t insertions = jacobsthal(n) - jacobsthal(n - 1);

    size_t inserted_count = 0;
    size_t total_insertions = 0;
    size_t elements_in_pend = pend.size() / element_size;
    std::cout << "b_target_idx: " << b_target_idx << " elements_in_pend: " << elements_in_pend << std::endl;
    if (b_target_idx - 1 < elements_in_pend) // TODO: check ob diese bedingung korrekt ist. wann soll ich reverse inserten
    {
        while (elements_in_pend > total_insertions)
        {
            if (insertions <= inserted_count)
            {
                n++;
                b_target_idx = jacobsthal(n);
                if (b_target_idx > elements_in_pend)
                {
                    std::cout << "break b_target_idx:" << b_target_idx << " elements_in_pend: " << elements_in_pend << std::endl;
                    break;
                }
                insertions = b_target_idx - jacobsthal(n - 1);
                inserted_count = 0;
            }
            std::cout << "insertions: " << insertions << std::endl;
            std::cout << "insertion_count: " << inserted_count << std::endl;
            std::cout << "b_target_idx: " << b_target_idx << std::endl;
            std::cout << "total_insertions: " << total_insertions << std::endl;

            auto b_target_it = pend.begin() + (b_target_idx - 2) * element_size;

            auto right_bound = get_right_bound(main, (b_target_idx + total_insertions) * element_size);

            auto b_target_pos = bi_search(main.begin(), right_bound, *(b_target_it + element_size - 1), element_size);

            std::cout << "element: ";
            print_elements(b_target_it, pend.end(), element_size);
            std::cout << std::endl;
            std::cout << "right bound: ";
            if (right_bound != main.end())
                print_elements(right_bound, main.end(), element_size);
            else
                std::cout << "END";
            std::cout << std::endl;

            main.insert(b_target_pos, b_target_it, b_target_it + element_size);
            // pend.erase(b_target_it, b_target_it + element_size);
            inserted_count++;
            b_target_idx--;
            total_insertions++;
            std::cout << "pend: ";
            print_v(pend, element_size);
            std::cout << "\nmain: ";
            print_v(main, element_size);
            std::cout << std::endl;
        }
    }
    if (total_insertions < elements_in_pend)
    {
        int end_idx = total_insertions * element_size;
        pend.erase(pend.begin(), pend.begin() + end_idx);
        // reverse insert
        elements_in_pend = pend.size() / element_size;
        while (elements_in_pend > 0)
        {
            std::cout << "reverse" << std::endl;
            std::cout << "insertions: " << insertions << std::endl;
            std::cout << "insertion_count: " << inserted_count << std::endl;
            std::cout << "b_target_idx: " << b_target_idx << std::endl;
            std::cout << "total_insertions: " << total_insertions << std::endl;

            auto target_it = pend.end() - element_size;
            auto right_bound = get_right_bound(main, (b_target_idx + total_insertions) * element_size);
            auto found = bi_search(main.begin(), right_bound, *(target_it + element_size - 1), element_size);

            std::cout << "element: ";
            print_elements(target_it, pend.end(), element_size);
            std::cout << std::endl;
            std::cout << "right bound: ";
            if (right_bound != main.end())
                print_elements(right_bound, main.end(), element_size);
            else
                std::cout << "END";
            std::cout << std::endl;

            main.insert(found, target_it, target_it + element_size);
            pend.erase(target_it, target_it + element_size);
            elements_in_pend--;
            b_target_idx--;
            total_insertions++;

            std::cout << "pend: ";
            print_v(pend, element_size);
            std::cout << "\nmain: ";
            print_v(main, element_size);
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

    size_t element_size = static_cast<int>(std::pow(2, depth - 1));
    if (element_size * 2 > vec.size())
        return;

    int elements = vec.size() / element_size;
    int pairs = vec.size() / element_size - ((vec.size() / element_size) % 2);
    auto start = vec.begin();
    auto end = start + pairs * element_size;

    print_info(depth, elements, pairs, element_size);
    std::cout << "before pair_sort: \n";
    print_v(vec, element_size);
    for (; start != end; start += element_size * 2)
    {
        size_t left_end = start[element_size - 1];
        size_t right_end = start[element_size * 2 - 1];
        if (left_end > right_end)
            std::swap_ranges(start, start + element_size, start + element_size);
    }
    std::cout << "after pair_sort: \n";
    print_v(vec, element_size);
    sort_pairs(vec, depth + 1);

    vector main;
    vector pend;

    init_main_pend(main, pend, vec, element_size, elements);

    print_info(depth, elements, pairs, element_size);
    print_v(vec, element_size);
    std::cout << "main: ";
    print_v(main, element_size);
    std::cout << "pend: ";
    print_v(pend, element_size);
    if (pend.size() > 0)
        binary_insertion(main, pend, element_size);
    insert_rest(vec, main);
    std::cout << "main: ";
    print_v(main, element_size);
    vec = main;
    std::cout << std::endl;
}