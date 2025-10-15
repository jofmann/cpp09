/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/15 16:53:17 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

using vector = std::vector<unsigned int>;

void print_elements(vector::const_iterator it, int element_size)
{
    std::cout << "[";
    for (int i = 0; i < element_size; i++)
    {
        if (i < element_size - 1)
            std::cout << *(it + i) << ",";
        else
            std::cout << *(it + i);
    }
    std::cout << "]";
}

void print_v(const vector &vec, int element_size)
{
    for (auto it = vec.begin(); it != vec.end(); it += element_size)
    {
        print_elements(it, element_size);
    }
    std::cout << std::endl;
}

void print_info(int lvl, int elements, int pairs, int element_size)
{
    std::cout << "lvl: " << lvl << " elements: " << elements << " pairs: " << pairs << " element_size: " << element_size << std::endl;
}

void init_main_pend(vector &main_chain, vector &pend, const vector &vec, size_t element_size, int elements)
{
    auto start = vec.begin();
    auto end = start + element_size * 2;
    main_chain.insert(main_chain.end(), start, end);
    start = end;
    end = start + element_size;
    // insert pairs in main or pend
    for (int i = 3; i <= elements; i++)
    {
        if (i % 2 == 0)
            main_chain.insert(main_chain.end(), start, end);
        else
            pend.insert(pend.end(), start, end);
        start += element_size;
        end = start + element_size;
    }
}

unsigned int jacobsthal(unsigned int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

vector::iterator bi_search(vector::iterator first, vector::iterator last, unsigned int target, int element_size)
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

void binary_insertion(vector &main_chain, vector &pend, int element_size)
{
    unsigned int n = 3;
    unsigned int b_target = jacobsthal(n);
    unsigned int insertions = jacobsthal(n) - jacobsthal(n - 1);

    unsigned int inserted_count = 0;
    unsigned int total_insertions = 0;
    unsigned int elements_left = pend.size() / element_size;
    while (elements_left > total_insertions)
    {
        if (insertions <= inserted_count)
        {
            n++;
            b_target = jacobsthal(n);
            if (b_target > elements_left)
                break;
            insertions = b_target - jacobsthal(n - 1);
            inserted_count = 0;
        }
        std::cout << "insertions: " << insertions << std::endl;
        std::cout << "insertion_count: " << inserted_count << std::endl;
        std::cout << "b_target: " << b_target << std::endl;
        std::cout << "total_insertions: " << total_insertions << std::endl;

        auto target_el_it = pend.begin() + (b_target - 2) * element_size;
        auto right_bound = main_chain.begin() + (b_target + total_insertions) * element_size;
        auto found = bi_search(main_chain.begin(), right_bound, *(target_el_it + element_size - 1), element_size);

        std::cout << "element: ";
        print_elements(target_el_it, element_size);
        std::cout << std::endl;
        std::cout << "right bound: ";
        print_elements(right_bound, element_size);
        std::cout << std::endl;

        main_chain.insert(found, target_el_it, target_el_it + element_size);
        // pend.erase(target_el_it, target_el_it + element_size);
        inserted_count++;
        b_target--;
        total_insertions++;
        std::cout << "pend: ";
        print_v(pend, element_size);
        std::cout << "\nmain: ";
        print_v(main_chain, element_size);
        std::cout << std::endl;
    }
    if (total_insertions < elements_left)
    {
        int end_idx = total_insertions * element_size;
        pend.erase(pend.begin(), pend.begin() + end_idx);
        std::cout << "pend: ";
        print_v(pend, element_size);
        // reverse insert
        elements_left = pend.size() / element_size;
        while (elements_left > 0)
        {
            auto target_it = pend.end() - element_size;
            auto right_bound = main_chain.begin() + (b_target + total_insertions) * element_size;
            auto found = bi_search(main_chain.begin(), right_bound, *(target_it + element_size - 1), element_size);

            std::cout << "element: ";
            print_elements(target_it, element_size);
            std::cout << std::endl;
            std::cout << "right bound: ";
            print_elements(right_bound, element_size);
            std::cout << std::endl;

            main_chain.insert(found, target_it, target_it + element_size);
            pend.erase(target_it, target_it + element_size);
            elements_left = pend.size() / element_size;
            b_target--;
            total_insertions++;

            std::cout << "pend: ";
            print_v(pend, element_size);
            std::cout << "\nmain: ";
            print_v(main_chain, element_size);
            std::cout << std::endl;
        }
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

    for (; start != end; start += element_size * 2)
    {
        unsigned int left_end = start[element_size - 1];
        unsigned int right_end = start[element_size * 2 - 1];
        if (left_end > right_end)
            std::swap_ranges(start, start + element_size, start + element_size);
    }
    sort_pairs(vec, depth + 1);
    vector main_chain;
    vector pend;
    print_info(depth, elements, pairs, element_size);

    init_main_pend(main_chain, pend, vec, element_size, elements);
    std::cout << "main: ";
    print_v(main_chain, element_size);
    std::cout << "pend: ";
    print_v(pend, element_size);
    std::cout << std::endl;
}