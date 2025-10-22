/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:31:22 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/16 17:17:20 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <stdexcept>
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    // if (argc < 3)
    // {
    //     std::cerr << "Error: need at least two positive integers as arguments." << std::endl;
    //     return 1;
    // }
    // try
    // {
    //     PmergeMe pm(argv + 1);
    //     pm.print_vector();
    //     pm.sort();
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    // vector pend = {2, 5, 7, 6, 8, 0, 9, 14, 4, 1};
    // vector main_chain = {3, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21};
    // std::cout << "pend: ";
    // print_v(pend, 1);
    // std::cout << "\nmain: ";
    // print_v(main_chain, 1);
    // std::cout << std::endl;
    // binary_insertion(main_chain, pend, 1);
    // vector s = {11, 2, 17, 0, 16,55 8, 6, 15, 10, 50, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 7, 100, 45}; // double free
    vector s = {11, 3, 45, 1, 4, 5, 6, 0, 2, 3333, 4566, 9, 10, 7, 9, 5444, 17};
    std::cout << "before: " << std::endl;
    print_v(s, s.size());
    sort_pairs(s, 1);
    std::cout << "after: " << std::endl;
    print_v(s, s.size());
}