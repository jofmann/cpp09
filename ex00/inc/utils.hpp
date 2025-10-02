/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:51:28 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 13:13:13 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <iostream>
#include <utility>
#include <stdexcept>

float input_value_to_float(const std::string &str);
int date_to_int(const std::string &date);
std::string int_to_date(int date);

void print_map(const std::map<int, float> &map);
std::string trim_whitespaces(const std::string &str);

std::pair<int, float> get_key_value(const std::string &line, char delimeter);
