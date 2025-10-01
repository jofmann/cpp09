/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:51:08 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/01 14:02:07 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int date_to_int(const std::string &date)
{
    // Annahme: date = "YYYY-MM-DD"
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    return year * 10000 + month * 100 + day;
}

std::string int_to_date(int date)
{
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day;
    return oss.str();
}

void print_map(const std::map<int, float> &map)
{
    int i = 0;
    for (auto it = map.begin(); it != map.end(); it++)
    {
        if (i == 20)
            break;
        std::cout << int_to_date(it->first) << " | " << it->second << std::endl;
        i++;
    }
}