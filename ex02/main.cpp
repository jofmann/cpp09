/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:31:22 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/28 15:24:52 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <stdexcept>
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Error: need at least two positive integers as arguments." << std::endl;
        return 1;
    }
    try
    {
        PmergeMe pm(argv + 1);
        pm.sort_vector();
        pm.sort_deq();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}