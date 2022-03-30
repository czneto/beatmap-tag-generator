#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <locale>
#include <vector>

// IO FUNC

// in
template<typename type, typename char_type = char> _NODISCARD constexpr type input(std::basic_istream<char_type, std::char_traits<char_type>>& in = std::cin) noexcept
{
    std::basic_stringstream<char_type> temp_ss;
    {
        char_type temp_char;
        while (true)
        {
            if (in.get(temp_char) && temp_ss.put(temp_char))
            {

                if (temp_char == std::use_facet<std::ctype<char_type>>(std::locale()).widen('\n'))
                {
                    break; // means the end of the input
                }
                temp_char = 0;
            }
            else
            {
                in.clear();
                return type(); // in or ss got a bad fail
            }
        }
    }
    if ((temp_ss.str()).empty())
    {
        return type(); // is empty
    }
    temp_ss.seekg(-1, std::ios_base::end); // the end -1 of input sequence
    const std::streampos end = temp_ss.tellg();
    temp_ss.seekg(0);
    temp_ss.clear();
    type temp; // this may fail
    if (temp_ss >> temp)
    {
        if (temp_ss.tellg() != end)
        {
            return type(); // multiple entries is a bad input
        }
    }
    else
    {
        return type(); // is an incompatible type
    }
    return temp; // ok
}

template<typename type, typename char_type = char> _NODISCARD constexpr std::vector<type> input_many(std::basic_istream<char_type, std::char_traits<char_type>>& in = std::cin) noexcept
{
    std::vector<type> result;
    std::basic_stringstream<char_type> temp_ss;
    {
        char_type temp_char;
        while (true)
        {
            if (in.get(temp_char) && temp_ss.put(temp_char))
            {

                if (temp_char == std::use_facet<std::ctype<char_type>>(std::locale()).widen('\n'))
                {
                    break; // means the end of the input
                }
                temp_char = 0;
            }
            else
            {
                in.clear();
                return result; // in or ss got a bad fail
            }
        }
    }
    if ((temp_ss.str()).empty())
    {
        return result; // is empty
    }
    temp_ss.seekg(-1, std::ios_base::end); // the end -1 of input sequence
    const std::streampos end = temp_ss.tellg();
    temp_ss.seekg(0);
    temp_ss.clear();
    type temp = type(); // this may fail
    while (true)
    {
        if (temp_ss >> temp)
        {
            result.emplace_back(temp);
            temp = std::move(type());
        }
        else
        {
            return std::vector<type>(); // has an incompatible type
        }
        if (temp_ss.tellg() == end)
        {
            break;
        }
    }
    return result; // ok
}

// out
template<typename t, typename os = std::basic_ostream<char, std::char_traits<char>>>
inline void basic_out(const t& msg, os& out = std::cout) noexcept
{
    out << msg;
}
template<typename os = std::basic_ostream<char, std::char_traits<char>>>
inline void endl(os& out = std::cout) noexcept
{
    out << std::endl;
}
template<typename t> inline void output(const t& first) noexcept
{
    basic_out(first);
}
template<typename t, typename ...Args> inline void output(const t& first, const Args& ...args) noexcept
{
    output(first); output(args...);
}
inline void output() noexcept {}
