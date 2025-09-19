/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:19:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/09/19 17:39:06 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>

std::map<std::string, std::string> create_db(const std::string &filename)
{
    std::ifstream db(filename);
    std::map<std::string, std::string> db_map;
    if (!db.is_open())
    {
        std::cerr << "Error: db open" << std::endl;
        throw std::runtime_error(" Error: db open ");
    }
    std::string line;
    while (std::getline(db, line))
    {
        int idx = line.find(',');
        auto [it, succes] = db_map.insert({line.substr(0, idx), line.substr(idx + 1)});
        if (!succes)
        {
            std::cerr << "Key already exists";
            throw std::runtime_error(" Key already exists ");
        }
    }
    return db_map;
}