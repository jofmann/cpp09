/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:11:37 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 13:14:31 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <regex>
#include <iostream>

bool check_extension(const std::string &filename, const std::string &extension);
bool is_valid_date(const std::string &date);
bool is_valid_line(const std::string &line, char delimeter);