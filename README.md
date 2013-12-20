simpleconf
==========

A simple configuration file library for C++

This library provides an absolute simplistic implementation
for configuration files.

The library is using a simple key/value pair store format.

Each line is one entry, everything before the first occurrence of an
equal sign `=` is the key, everything after the `=` is the value until the end
of the line.

    KEY=VALUE\n

Concepts:

The library supports empty values, and everything is a string.

Empty values will be represented by the save by omitting the = sign.

Empty values can be used, for example, as flags.

Conversion for the following types is provided:

`uint64_t`, `int64_t`, `bool`, `double` and `std::string`

Building the library will require the boost library to be installed
on your system, however it will only require headers.

In detail it is using boost::spirit for the double parser and
boost::lexical_cast for the other conversions.
