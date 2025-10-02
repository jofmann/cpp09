/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:53:36 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 14:36:10 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.hpp"

bool is_valid_date(const std::string &date)
{
    static const std::regex pattern(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!std::regex_match(date, pattern))
        return false;

    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    if (month < 1 || month > 12)
        return false;

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (leap)
        days_in_month[1] = 29;

    if (day < 1 || day > days_in_month[month - 1])
        return false;
    return true;
}

bool is_valid_line(const std::string &line, char delimeter)
{
    size_t pos = line.find(delimeter);
    if (pos == std::string::npos)
        return false;
    return true;
}

bool check_extension(const std::string &filename, const std::string &extension)
{
    if (extension.size() > filename.size())
        return false;

    return std::equal(extension.rbegin(), extension.rend(), filename.rbegin());
}