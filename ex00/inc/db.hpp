/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:34:01 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/01 15:20:02 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <utility>

std::map<int, float> create_db(const std::string &filepath);
std::pair<int, float> get_db_entry(const std::map<int, float> &db, int date);