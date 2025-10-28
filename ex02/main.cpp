/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:31:22 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/28 13:25:49 by phhofman         ###   ########.fr       */
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
    if (argc < 3)
    {
        std::cerr << "Error: need at least two positive integers as arguments." << std::endl;
        return 1;
    }
    try
    {
        PmergeMe pm(argv + 1);
        std::cout << "before: " << std::endl;
        print_v(pm._vec, pm._vec.size());
        int size = pm._vec.size();
        pm.sort();
        std::cout << "after: " << std::endl;
        std::cout << "old size: " << size << " new size: " << pm._vec.size() << std::endl;
        if (std::is_sorted(pm._vec.begin(), pm._vec.end()))
        {
            std::cout << "sorted !" << std::endl;
        }
        else
        {
            std::cout << " not sorted !" << std::endl;
        }
        print_v(pm._vec, pm._vec.size());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}