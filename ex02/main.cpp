/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:31:22 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/07 16:11:40 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <stdexcept>
#include <cstring>

bool is_valid_seq(char **argv)
{
    for (int i = 0; argv[i] != NULL; i++)
    {
        try
        {
            size_t pos;
            int num = std::stoi(argv[i], &pos);
            if (pos != std::strlen(argv[i]))
            {
                std::cerr << "Error: not valid number => " << argv[i] << std::endl;
                return false;
            }
            if (num < 0)
            {
                std::cerr << "Error: must be positive number => " << argv[i] << std::endl;
                return false;
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: not valid number => " << argv[i] << std::endl;
            return false;
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Error: number out of range =>" << std::endl;
            return false;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Error: need at least two positive integers as arguments." << std::endl;
        return 1;
    }
    if (!is_valid_seq(argv + 1))
        return 1;
}