//          Copyright Vinzenz 'evilissimo' Feenstra 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#ifndef GUARD_SIMPLECONF_SIMPLECONF_HPP_INCLUDED
#define GUARD_SIMPLECONF_SIMPLECONF_HPP_INCLUDED

#include <cstdint>
#include <string>
#include <unordered_map>

class simpleconf {
    std::unordered_map<std::string, std::string> data_;
public:
    simpleconf(std::string const & file_path = std::string());

    void load(std::string const & file_path);

    void save(std::string const & file_path) const;

    bool exists(std::string const & name) const;

    bool is_empty(std::string const & name) const;

    uint64_t get_uint(std::string const & name, uint64_t default_value = uint64_t()) const;

    int64_t get_int(std::string const & name, int64_t default_value = int64_t()) const;

    double get_real(std::string const & name, double default_value = double());

    std::string get_string(std::string const & name, std::string const & default_value = std::string()) const;

    bool get_bool(std::string const & name, bool default_value) const;

    void set_bool(std::string const & name, bool value);

    void set_int(std::string const & name, int value);

    void set_uint(std::string const & name, uint64_t value);

    void set_real(std::string const & name, double value);

    void set_string(std::string const & name, std::string const & value);

    void set_empty(std::string const & name);

    void erase(std::string const & name);
};

#endif // GUARD_SIMPLECONF_SIMPLECONF_HPP_INCLUDED

