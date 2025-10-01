/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:11:37 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/01 10:18:01 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <regex>
#include <iostream>

// db
bool is_valid_db_exchange_rate(const std::string &exchange_rate);
bool is_valid_db_date(const std::string &date);
bool is_valid_db_line(const std::string &line);

// input
bool is_valid_input_value(const std::string &exchange_rate);