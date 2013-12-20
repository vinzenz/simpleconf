//          Copyright Vinzenz 'evilissimo' Feenstra 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#include <simpleconf/simpleconf.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>

namespace detail {
    template< typename T, typename U >
    struct converter;

    template< typename T, typename U >
    typename converter<T,U>::result_type convert(U const & v)
    {
        return converter<T,U>()(v);
    }

    template<>
    struct converter<std::string, std::string>
    {
        typedef std::string result_type;
        typedef std::string const & input_type;
        result_type operator()(input_type v) const
        {
            return v;
        }
    };

    template<>
    struct converter<double, std::string>
    {
        typedef std::string input_type;
        typedef double result_type;
        result_type operator()(input_type const & i) const {
            using boost::spirit::qi::double_;
            using boost::spirit::qi::parse;
            double result = double();
            if(!parse(i.begin(), i.end(), double_, result)) {
                throw boost::bad_lexical_cast();
            }
            return result;
        }
    };

    template< typename T, typename U>
    struct converter
    {
        typedef U input_type;
        typedef T result_type;
        result_type operator()(input_type const & i) const {
            return boost::lexical_cast<result_type>(i);
        }
    };

    template< typename C, typename T >
    T get(C const & data,
          std::string const & name,
          T default_value)
    {
        auto iter = data.find(name);
        if( iter != data.end() )
        {
            return convert<T>(iter->second);
        }
        return default_value;
    }

    template< typename C, typename T >
    void set(C & data, std::string const & name, T value)
    {
        auto iter = data.find(name);
        if(iter != data.end())
            convert<std::string>(value).swap(iter->second);
        else
            data.insert({name, convert<std::string>(value)});
    }
}



simpleconf::simpleconf(std::string const & file_path)
: data_()
{
    load(file_path);
}


void simpleconf::load(std::string const & file_path)
{
    if(file_path.empty()) return;
    decltype(data_) data;
    std::ifstream ifs(file_path.c_str());
    std::string line, key, value;
    while(std::getline(ifs, line)) {
        value.clear();
        std::size_t pos = line.find_first_of('=');
        if(pos != std::string::npos) {
            key.assign(line.begin(), line.begin() + pos);
            value.assign(line.begin() + pos + 1, line.end());
        }
        else {
            key.swap(line);
        }

        detail::set(data, key, value);
    }
    data_.swap(data);
}


void simpleconf::save(std::string const & file_path) const
{
    std::ofstream ofs(file_path.c_str());
    for(auto const & i : data_) {
        ofs << i.first;
        if( !i.second.empty() ) {
            ofs << "=" << i.second;
        }
        ofs << "\n";
    }
}


bool simpleconf::exists(std::string const & name) const
{
    return data_.count(name) > 0;
}


bool simpleconf::is_empty(std::string const & name) const
{
    return exists(name) && data_.find(name)->second.empty();
}


uint64_t simpleconf::get_uint(std::string const & name, uint64_t default_value) const
{
    return detail::get(data_, name, default_value);
}


int64_t simpleconf::get_int(std::string const & name, int64_t default_value) const
{
    return detail::get(data_, name, default_value);
}


double simpleconf::get_real(std::string const & name, double default_value)
{
    return detail::get(data_, name, default_value);
}


std::string simpleconf::get_string(std::string const & name, std::string const & default_value) const
{
    return detail::get(data_, name, default_value);
}


bool simpleconf::get_bool(std::string const & name, bool default_value) const
{
    return detail::get(data_, name, default_value);
}


void simpleconf::set_bool(std::string const & name, bool value)
{
    detail::set(data_, name, value);
}


void simpleconf::set_int(std::string const & name, int value)
{
    detail::set(data_, name, value);
}


void simpleconf::set_uint(std::string const & name, uint64_t value)
{
    detail::set(data_, name, value);
}


void simpleconf::set_real(std::string const & name, double value)
{
    detail::set(data_, name, value);
}


void simpleconf::set_string(std::string const & name, std::string const & value)
{
    detail::set(data_, name, value);
}


void simpleconf::set_empty(std::string const & name)
{
    set_string(name, std::string());
}


void simpleconf::erase(std::string const & name)
{
    if( exists(name) ) {
        data_.erase(name);
    }
}

