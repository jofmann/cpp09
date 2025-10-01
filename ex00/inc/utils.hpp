/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:51:28 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/01 14:02:35 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <iostream>

int date_to_int(const std::string &date);
std::string int_to_date(int date);
void print_map(const std::map<int, float> &map);