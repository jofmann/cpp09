/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:01:01 by phhofman          #+#    #+#             */
/*   Updated: 2025/09/19 17:14:02 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

bool validate_db(const std::string &filename)
{
    std::ifstream db_file(filename);

    if (!db_file.is_open())
    {
        std::cerr << "Error: Can not open <" << filename << ">" << std::endl;
        return false;
    }

    std::string line;
    std::size_t i = 0;
    while (std::getline(db_file, line))
    {
        if (line.empty())
        {
            std::cerr << "Error: Empty entry on line: " << i << std::endl;
            return false;
        }
        i++;
    }
}