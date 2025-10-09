/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:31:22 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/09 16:58:24 by phhofman         ###   ########.fr       */
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
        pm.print_vector();
        pm.sort();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}