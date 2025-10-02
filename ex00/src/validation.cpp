/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:53:36 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 13:14:21 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.hpp"

bool is_valid_date(const std::string &date) // TODO: Add checks for logical  months days years
{
    static const std::regex pattern(R"(^\d{4}-\d{2}-\d{2}$)");
    return std::regex_match(date, pattern);
}

bool is_valid_line(const std::string &line, char delimeter)
{
    size_t pos = line.find(delimeter);
    if (pos == std::string::npos)
        return false;
    // if (line.find('|', pos + 1) != std::string::npos) // TODO: Maybe unnecessary to check again for
    //     return false;
    // if (pos == 0 || pos == line.size() - 1)
    //     return false;
    return true;
}

bool check_extension(const std::string &filename, const std::string &extension)
{
    if (extension.size() > filename.size())
        return false;

    return std::equal(extension.rbegin(), extension.rend(), filename.rbegin());
}