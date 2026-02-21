// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Quote strings
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/io/manip/quoted
* \sa https://www.gnu.org/software/bash/manual/bash.html#Single-Quotes
*
* Note: Only \c std::string is supported.
*/

#pragma once

#include <cctype>
#include <cstdint>
#include <string>
#include <string_view>

#define C_BACKSLASH    '\\'
#define C_SINGLE_QUOTE '\''
#define C_DOUBLE_QUOTE '"'

// single quote, backslash, single quote, single quote
//#define S_SINGLE_QUOTE_ESCAPED "'\\''"
#define S_SINGLE_QUOTE_ESCAPED R"('\'')"

#define OCT_DIGITS "01234567"
#define HEX_DIGITS "0123456789ABCDEF"

/// Convert the byte to its escaped octal representation
std::string
to_oct_str(const uint8_t c)
{
    const char d1 = OCT_DIGITS[(c & 0700) >> 6];
    const char d2 = OCT_DIGITS[(c & 0070) >> 3];
    const char d3 = OCT_DIGITS[(c & 0007)     ];
    return std::string{C_BACKSLASH, d1, d2, d3};
}

/// Convert the byte to its escaped hexadecimal representation
std::string
to_hex_str(const uint8_t c)
{
    const char d1 = HEX_DIGITS[(c & 0xF0) >> 4];
    const char d2 = HEX_DIGITS[(c & 0x0F)     ];
    return std::string{C_BACKSLASH, 'x', d1, d2};
}

/// Is the character a word character?
/**
<blockquote>
A "word" character is an underscore or any character that is a letter or digit.
</blockquote>
\sa https://www.pcre.org/original/doc/html/pcrepattern.html#:~:text=A%20%22word%22%20character%20is%20an%20underscore%20or%20any%20character%20that%20is%20a%20letter%20or%20digit.
*/
constexpr bool
isword(const char c)
{
    return (c == '_') || std::isalnum(static_cast<unsigned char>(c));
}

/// Is the character special for a POSIX shell?
/**
\sa https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_02
*/
constexpr bool
is_special_char_shell(const char c)
{
    return (c == '\t') ||
           (c == '\n') ||
           (c == ' ' ) ||
           (c == '"' ) ||
           (c == '#' ) ||
           (c == '$' ) ||
           (c == '%' ) ||
           (c == '&' ) ||
           (c == '\'') ||
           (c == '(' ) ||
           (c == ')' ) ||
           (c == '*' ) ||
           (c == ';' ) ||
           (c == '<' ) ||
           (c == '=' ) ||
           (c == '>' ) ||
           (c == '?' ) ||
           (c == '[' ) ||
           (c == '\\') ||
           (c == '`' ) ||
           (c == '|' ) ||
           (c == '~' );
}

/// Does the string contain special characters for a POSIX shell?
bool
contains_special_chars_shell(const std::string& s)
{
    for (const auto c : s)
    {
        if (is_special_char_shell(c) || !std::isprint(static_cast<unsigned char>(c)))
            return true;
    }

    return false;
}

/// Escape the character for a POSIX shell
/**
\sa https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_02
*/
std::string
escape_shell(const char c)
{
    switch (c)
    {
    case '\t': return std::string{C_BACKSLASH, 't'};
    case '\n': return std::string{C_BACKSLASH, 'n'};
    case ' ' :
    case '"' :
    case '#' :
    case '$' :
    case '%' :
    case '&' :
    case '\'':
    case '(' :
    case ')' :
    case '*' :
    case ';' :
    case '<' :
    case '=' :
    case '>' :
    case '?' :
    case '[' :
    case '\\':
    case '`' :
    case '|' :
    case '~' : return std::string{C_BACKSLASH, c};
    default: break;
    }

    if (std::isprint(static_cast<unsigned char>(c)))
        return std::string{c};

    return to_hex_str(static_cast<uint8_t>(c));
}

/// Escape the string for a POSIX shell
/**
\sa https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_02
*/
std::string
escape_shell(const std::string& s)
{
    std::string result;
    result.reserve(s.size());
    for (const auto c : s)
    {
        result += escape_shell(c);
    }
    return result;
}

/// Quote the string for a POSIX shell
/**
\sa https://www.gnu.org/software/bash/manual/bash.html#Single-Quotes
<blockquote>
Enclosing characters in single quotes (‘'’) preserves the literal value of each
character within the quotes. A single quote may not occur between single
quotes, even when preceded by a backslash.
</blockquote>
*/
std::string
quote_shell_always(const std::string& s)
{
    static constexpr char delim = C_SINGLE_QUOTE;
    static constexpr std::string_view delim_escaped{S_SINGLE_QUOTE_ESCAPED};
    std::string result;
    result.reserve(s.size() + 2);
    result.push_back(delim);
    for (const auto c : s)
    {
        if (c == delim)
            result += delim_escaped;
        else
            result.push_back(c);
    }
    result.push_back(delim);
    return result;
}

/// Conditionally quote the string for a POSIX shell
std::string
quote_shell(const std::string& s)
{
    if (s.empty() || contains_special_chars_shell(s))
        return quote_shell_always(s);
    else
        return s;
}

/// Escape the character for a C character literal
/**
\sa https://en.cppreference.com/w/c/language/escape
\sa https://en.cppreference.com/w/cpp/language/escape
\sa https://eel.is/c++draft/lex.ccon#:simple-escape-sequence-char
*/
std::string
escape_c(const char c)
{
    // simple escape sequence
    switch (c)
    {
    case '\a': return std::string{C_BACKSLASH, 'a'};
    case '\b': return std::string{C_BACKSLASH, 'b'};
    case '\t': return std::string{C_BACKSLASH, 't'};
    case '\n': return std::string{C_BACKSLASH, 'n'};
    case '\v': return std::string{C_BACKSLASH, 'v'};
    case '\f': return std::string{C_BACKSLASH, 'f'};
    case '\r': return std::string{C_BACKSLASH, 'r'};
    case '\"':
    //case '\'':
    //case '\?':
    case '\\': return std::string{C_BACKSLASH, c};
    default: break;
    }

    if (std::isprint(static_cast<unsigned char>(c)))
        return std::string{c};

    return to_hex_str(static_cast<uint8_t>(c));
}

/// Quote the character for a C character literal
std::string
quote_c(const char c)
{
    static constexpr char delim = C_SINGLE_QUOTE;
    std::string result;
    result.reserve(4 + 2);
    result.push_back(delim);
    result += escape_c(c);
    result.push_back(delim);
    return result;
}

/// Quote the string for a C string literal
std::string
quote_c(const std::string& s)
{
    static constexpr char delim = C_DOUBLE_QUOTE;
    std::string result;
    result.reserve(s.size() + 2);
    result.push_back(delim);
    for (const auto c : s)
    {
        result += escape_c(c);
    }
    result.push_back(delim);
    return result;
}

/// Escape the character for a Perl Compatible Regular Expression (PCRE)
/**
\sa https://perldoc.perl.org/perlre#Escape-sequences
\sa https://www.pcre.org/original/doc/html/pcrepattern.html
\sa https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Regular_Expressions#escaping
*/
std::string
escape_pcre(const char c)
{
    if (isword(c))
        return std::string{c};

    switch (c)
    {
    case '\t': return std::string{C_BACKSLASH, 't'};
    case '\n': return std::string{C_BACKSLASH, 'n'};
    case '\r': return std::string{C_BACKSLASH, 'r'};
    case '\f': return std::string{C_BACKSLASH, 'f'};
    case '\a': return std::string{C_BACKSLASH, 'a'};
    case 0x1b: return std::string{C_BACKSLASH, 'e'}; // '\e'
    default: break;
    }

    if (std::isprint(static_cast<unsigned char>(c)))
        return std::string{C_BACKSLASH, c};

    return to_hex_str(static_cast<uint8_t>(c));
}

/// Escape the string for a Perl Compatible Regular Expression (PCRE)
std::string
escape_pcre(const std::string& s)
{
    std::string result;
    result.reserve(s.size());
    for (const auto c : s)
    {
        result += escape_pcre(c);
    }
    return result;
}

inline std::string
quote(const std::string& s)
{
    return quote_shell_always(s);
}

/// Quote the string similar to \c std::quoted
/**
\sa https://en.cppreference.com/w/cpp/io/manip/quoted
*/
std::string
quote_simple(const std::string& s,
             const char delim = C_DOUBLE_QUOTE,
             const char escape = C_BACKSLASH)
{
    std::string result;
    result.reserve(s.size() + 2);
    result.push_back(delim);
    for (const auto c : s)
    {
        if (c == delim || c == escape)
            result.push_back(escape);
        result.push_back(c);
    }
    result.push_back(delim);
    return result;
}

#undef C_BACKSLASH
#undef C_SINGLE_QUOTE
#undef C_DOUBLE_QUOTE
#undef S_SINGLE_QUOTE_ESCAPED
#undef OCT_DIGITS
#undef HEX_DIGITS
