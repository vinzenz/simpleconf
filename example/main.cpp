//          Copyright Vinzenz 'evilissimo' Feenstra 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#include <simpleconf/simpleconf.hpp>
#include <iostream>
#include <iomanip>

int main()
{
    simpleconf conf;
    conf.set_string("string1", "string");
    conf.set_real("real1", 123456.12345);
    conf.set_real("real2", 6.12345f);
    conf.set_int("int1", -12345);
    conf.set_uint("uint1", 12345);
    conf.set_empty("empty");
    conf.set_bool("false", false);
    conf.set_bool("true", true);
    conf.save("test.conf");

    simpleconf other("test.conf");
    std::cout << "string1(string) = "   << conf.get_string("string1") << std::endl;
    std::cout << "real1(string) = "     << conf.get_string("real1") << std::endl;
    std::cout << "real1(double) = "     << std::setprecision(11) << conf.get_real("real1") << std::endl;
    std::cout << "real2(double) = "     << std::setprecision(6) << conf.get_real("real2") << std::endl;
    std::cout << "false(bool) = "     <<  std::boolalpha << conf.get_bool("false", true) << std::endl;
    std::cout << "true(bool) = "     <<  std::boolalpha << conf.get_bool("true", false) << std::endl;
    std::cout << "non-existent(bool) = "     <<  std::showbase << std::hex << conf.get_int("non-existent", 0xdeadbeef) << std::endl;
}
