// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// functions similar to those in <ctype.h> that operate on unsigned chars in the C locale
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/string/byte
*/

#pragma once

#include <array>
#include <cstdint>

namespace uctype
{

/// Character type attribute masks
/**
* All ASCII characters that are not printable are control characters.
* All visible characters that are not alpha-numeric are punctuation characters.
*/
inline constexpr uint8_t mask_cntrl  {0b0000'0001};
inline constexpr uint8_t mask_space  {0b0000'0010};
inline constexpr uint8_t mask_blank  {0b0000'0100};
inline constexpr uint8_t mask_punct  {0b0000'1000};
inline constexpr uint8_t mask_upper  {0b0001'0000};
inline constexpr uint8_t mask_lower  {0b0010'0000};
inline constexpr uint8_t mask_digit  {0b0100'0000};
inline constexpr uint8_t mask_xdigit {0b1000'0000};

inline constexpr std::array<uint8_t, 128> ascii_masks{
    /* NUL   */ mask_cntrl,
    /* SOH   */ mask_cntrl,
    /* STX   */ mask_cntrl,
    /* ETX   */ mask_cntrl,
    /* EOT   */ mask_cntrl,
    /* ENQ   */ mask_cntrl,
    /* ACK   */ mask_cntrl,
    /* BEL   */ mask_cntrl,
    /* BS    */ mask_cntrl,
    /* HT    */ mask_cntrl | mask_space | mask_blank,
    /* LF    */ mask_cntrl | mask_space,
    /* VT    */ mask_cntrl | mask_space,
    /* FF    */ mask_cntrl | mask_space,
    /* CR    */ mask_cntrl | mask_space,
    /* SO    */ mask_cntrl,
    /* SI    */ mask_cntrl,
    /* DLE   */ mask_cntrl,
    /* DC1   */ mask_cntrl,
    /* DC2   */ mask_cntrl,
    /* DC3   */ mask_cntrl,
    /* DC4   */ mask_cntrl,
    /* NAK   */ mask_cntrl,
    /* SYN   */ mask_cntrl,
    /* ETB   */ mask_cntrl,
    /* CAN   */ mask_cntrl,
    /* EM    */ mask_cntrl,
    /* SUB   */ mask_cntrl,
    /* ESC   */ mask_cntrl,
    /* FS    */ mask_cntrl,
    /* GS    */ mask_cntrl,
    /* RS    */ mask_cntrl,
    /* US    */ mask_cntrl,
    /* SPACE */ mask_space | mask_blank,
    /* !     */ mask_punct,
    /* "     */ mask_punct,
    /* #     */ mask_punct,
    /* $     */ mask_punct,
    /* %     */ mask_punct,
    /* &     */ mask_punct,
    /* '     */ mask_punct,
    /* (     */ mask_punct,
    /* )     */ mask_punct,
    /* *     */ mask_punct,
    /* +     */ mask_punct,
    /* ,     */ mask_punct,
    /* -     */ mask_punct,
    /* .     */ mask_punct,
    /* /     */ mask_punct,
    /* 0     */ mask_digit | mask_xdigit,
    /* 1     */ mask_digit | mask_xdigit,
    /* 2     */ mask_digit | mask_xdigit,
    /* 3     */ mask_digit | mask_xdigit,
    /* 4     */ mask_digit | mask_xdigit,
    /* 5     */ mask_digit | mask_xdigit,
    /* 6     */ mask_digit | mask_xdigit,
    /* 7     */ mask_digit | mask_xdigit,
    /* 8     */ mask_digit | mask_xdigit,
    /* 9     */ mask_digit | mask_xdigit,
    /* :     */ mask_punct,
    /* ;     */ mask_punct,
    /* <     */ mask_punct,
    /* =     */ mask_punct,
    /* >     */ mask_punct,
    /* ?     */ mask_punct,
    /* @     */ mask_punct,
    /* A     */ mask_upper | mask_xdigit,
    /* B     */ mask_upper | mask_xdigit,
    /* C     */ mask_upper | mask_xdigit,
    /* D     */ mask_upper | mask_xdigit,
    /* E     */ mask_upper | mask_xdigit,
    /* F     */ mask_upper | mask_xdigit,
    /* G     */ mask_upper,
    /* H     */ mask_upper,
    /* I     */ mask_upper,
    /* J     */ mask_upper,
    /* K     */ mask_upper,
    /* L     */ mask_upper,
    /* M     */ mask_upper,
    /* N     */ mask_upper,
    /* O     */ mask_upper,
    /* P     */ mask_upper,
    /* Q     */ mask_upper,
    /* R     */ mask_upper,
    /* S     */ mask_upper,
    /* T     */ mask_upper,
    /* U     */ mask_upper,
    /* V     */ mask_upper,
    /* W     */ mask_upper,
    /* X     */ mask_upper,
    /* Y     */ mask_upper,
    /* Z     */ mask_upper,
    /* [     */ mask_punct,
    /* \     */ mask_punct,
    /* ]     */ mask_punct,
    /* ^     */ mask_punct,
    /* _     */ mask_punct,
    /* `     */ mask_punct,
    /* a     */ mask_lower | mask_xdigit,
    /* b     */ mask_lower | mask_xdigit,
    /* c     */ mask_lower | mask_xdigit,
    /* d     */ mask_lower | mask_xdigit,
    /* e     */ mask_lower | mask_xdigit,
    /* f     */ mask_lower | mask_xdigit,
    /* g     */ mask_lower,
    /* h     */ mask_lower,
    /* i     */ mask_lower,
    /* j     */ mask_lower,
    /* k     */ mask_lower,
    /* l     */ mask_lower,
    /* m     */ mask_lower,
    /* n     */ mask_lower,
    /* o     */ mask_lower,
    /* p     */ mask_lower,
    /* q     */ mask_lower,
    /* r     */ mask_lower,
    /* s     */ mask_lower,
    /* t     */ mask_lower,
    /* u     */ mask_lower,
    /* v     */ mask_lower,
    /* w     */ mask_lower,
    /* x     */ mask_lower,
    /* y     */ mask_lower,
    /* z     */ mask_lower,
    /* {     */ mask_punct,
    /* |     */ mask_punct,
    /* }     */ mask_punct,
    /* ~     */ mask_punct,
    /* DEL   */ mask_cntrl,
};

inline constexpr uint8_t mask_alpha{mask_upper | mask_lower};
inline constexpr uint8_t mask_alnum{mask_alpha | mask_digit};
inline constexpr uint8_t mask_graph{mask_alnum | mask_punct};

constexpr bool
isascii(const uint8_t c)
{
    return (c & 0b1000'0000) == 0;
}

constexpr bool
isupper(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_upper) != 0;
}

constexpr bool
islower(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_lower) != 0;
}

constexpr bool
isalpha(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_alpha) != 0;
}

constexpr bool
isdigit(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_digit) != 0;
}

constexpr bool
isalnum(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_alnum) != 0;
}

constexpr bool
isxdigit(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_xdigit) != 0;
}

constexpr bool
isspace(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_space) != 0;
}

constexpr bool
isblank(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_blank) != 0;
}

constexpr bool
isgraph(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_graph) != 0;
}

constexpr bool
isprint(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_cntrl) == 0;
}

constexpr bool
iscntrl(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_cntrl) != 0;
}

constexpr bool
ispunct(const uint8_t c)
{
    return !isascii(c) ? false : (ascii_masks[c] & mask_punct) != 0;
}

constexpr uint8_t
tolower(const uint8_t c)
{
    return isupper(c) ? (c | 0b0010'0000) : c;
}

constexpr uint8_t
toupper(const uint8_t c)
{
    return islower(c) ? (c & 0b1101'1111) : c;
}

}
