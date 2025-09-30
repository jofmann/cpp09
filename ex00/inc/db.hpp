/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:34:01 by phhofman          #+#    #+#             */
/*   Updated: 2025/09/30 16:17:41 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>

// db
std::map<std::string, float> create_db(const std::string &filename);

// validation
bool is_valid_date(const std::string &date);
bool is_valid_exchange_rate(const std::string &exchange_rate);
bool is_valid_line(const std::string &line);