/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:41:06 by phhofman          #+#    #+#             */
/*   Updated: 2025/09/19 17:37:58 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>
#include "db.hpp"

bool check_extension(const std::string &filename, const std::string &extension)
{
    if (extension.size() > filename.size())
        return false;

    return std::equal(extension.rbegin(), extension.rend(), filename.rbegin());
}

void printMap(const std::map<std::string, std::string> &m)
{
    int i = 0;
    for (const auto &[key, value] : m)
    {
        if (i == 20)
            break;
        std::cout << key << " : " << value << std::endl;
        i++;
    }
}

int main(int argc, char **argv)
{

    // if (argc != 2)
    // {
    //     std::cerr << "Error: Invalid number of arguments" << std::endl;
    //     std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    //     return 1;
    // }
    // const std::string filename = argv[1];
    // if (!check_extension(filename, ".csv"))
    // {
    //     std::cerr << "Error: Filename <" << filename << "> has wrong extension." << std::endl;
    //     std::cerr << "Extension must be .csv" << std::endl;
    //     return 1;
    // }
    (void)argc;
    (void)argv;
    try
    {
        auto db = create_db("./db/data.csv");
        printMap(db);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}