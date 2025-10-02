/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DatabaseError.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:01:39 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 14:15:14 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stdexcept>
#include <string>

class DatabaseError : public std::runtime_error
{
public:
    explicit DatabaseError(const std::string &msg)
        : std::runtime_error(msg) {}

    DatabaseError(const DatabaseError &) = default;
    DatabaseError &operator=(const DatabaseError &) = default;
    DatabaseError(DatabaseError &&) noexcept = default;
    DatabaseError &operator=(DatabaseError &&) noexcept = default;
    ~DatabaseError() override = default;
};