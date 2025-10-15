/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:31:22 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/15 16:32:29 by phhofman         ###   ########.fr       */
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
    vector pend = {2, 5, 7, 6, 8, 0, 9, 14, 4, 1};
    vector main_chain = {3, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21};
    std::cout << "pend: ";
    print_v(pend, 1);
    std::cout << "\nmain: ";
    print_v(main_chain, 1);
    std::cout << std::endl;
    binary_insertion(main_chain, pend, 1);
}