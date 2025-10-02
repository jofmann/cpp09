/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:34:01 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 16:31:15 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"
#include "validation.hpp"

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <stdexcept>
#include <utility>

class BitcoinExchange
{
private:
    std::map<int, float> _db;

public:
    class BitcoinExchangeException;

    BitcoinExchange(const std::string &filepath);
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    std::pair<int, float> get_entry(int date) const;
};
