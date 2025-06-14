// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// character meter
/**
\file
\author Steven Ward
*/

#pragma once

#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

// https://www.unicode.org/charts/PDF/U0000.pdf

static constexpr wchar_t SPACE = 0x0020;

// https://www.unicode.org/charts/PDF/U2580.pdf

static constexpr wchar_t UPPER_HALF_BLOCK           = 0x2580;
static constexpr wchar_t LOWER_ONE_EIGHTH_BLOCK     = 0x2581;
static constexpr wchar_t LOWER_ONE_QUARTER_BLOCK    = 0x2582;
static constexpr wchar_t LOWER_THREE_EIGHTHS_BLOCK  = 0x2583;
static constexpr wchar_t LOWER_HALF_BLOCK           = 0x2584;
static constexpr wchar_t LOWER_FIVE_EIGHTHS_BLOCK   = 0x2585;
static constexpr wchar_t LOWER_THREE_QUARTERS_BLOCK = 0x2586;
static constexpr wchar_t LOWER_SEVEN_EIGHTHS_BLOCK  = 0x2587;
static constexpr wchar_t FULL_BLOCK                 = 0x2588;
static constexpr wchar_t LEFT_SEVEN_EIGHTHS_BLOCK   = 0x2589;
static constexpr wchar_t LEFT_THREE_QUARTERS_BLOCK  = 0x258A;
static constexpr wchar_t LEFT_FIVE_EIGHTHS_BLOCK    = 0x258B;
static constexpr wchar_t LEFT_HALF_BLOCK            = 0x258C;
static constexpr wchar_t LEFT_THREE_EIGHTHS_BLOCK   = 0x258D;
static constexpr wchar_t LEFT_ONE_QUARTER_BLOCK     = 0x258E;
static constexpr wchar_t LEFT_ONE_EIGHTH_BLOCK      = 0x258F;
static constexpr wchar_t RIGHT_HALF_BLOCK           = 0x2590;

static constexpr wchar_t UPPER_ONE_EIGHTH_BLOCK     = 0x2594;
static constexpr wchar_t RIGHT_ONE_EIGHTH_BLOCK     = 0x2595;

// https://www.unicode.org/charts/PDF/U1FB00.pdf

static constexpr wchar_t VERTICAL_ONE_EIGHTH_BLOCK_2   = 0x1FB70;
static constexpr wchar_t VERTICAL_ONE_EIGHTH_BLOCK_3   = 0x1FB71;
static constexpr wchar_t VERTICAL_ONE_EIGHTH_BLOCK_4   = 0x1FB72;
static constexpr wchar_t VERTICAL_ONE_EIGHTH_BLOCK_5   = 0x1FB73;
static constexpr wchar_t VERTICAL_ONE_EIGHTH_BLOCK_6   = 0x1FB74;
static constexpr wchar_t VERTICAL_ONE_EIGHTH_BLOCK_7   = 0x1FB75;
static constexpr wchar_t HORIZONTAL_ONE_EIGHTH_BLOCK_2 = 0x1FB76;
static constexpr wchar_t HORIZONTAL_ONE_EIGHTH_BLOCK_3 = 0x1FB77;
static constexpr wchar_t HORIZONTAL_ONE_EIGHTH_BLOCK_4 = 0x1FB78;
static constexpr wchar_t HORIZONTAL_ONE_EIGHTH_BLOCK_5 = 0x1FB79;
static constexpr wchar_t HORIZONTAL_ONE_EIGHTH_BLOCK_6 = 0x1FB7A;
static constexpr wchar_t HORIZONTAL_ONE_EIGHTH_BLOCK_7 = 0x1FB7B;

static constexpr wchar_t UPPER_ONE_QUARTER_BLOCK    = 0x1FB82;
static constexpr wchar_t UPPER_THREE_EIGHTHS_BLOCK  = 0x1FB83;
static constexpr wchar_t UPPER_FIVE_EIGHTHS_BLOCK   = 0x1FB84;
static constexpr wchar_t UPPER_THREE_QUARTERS_BLOCK = 0x1FB85;
static constexpr wchar_t UPPER_SEVEN_EIGHTHS_BLOCK  = 0x1FB86;
static constexpr wchar_t RIGHT_ONE_QUARTER_BLOCK    = 0x1FB87;
static constexpr wchar_t RIGHT_THREE_EIGHTHS_BLOCK  = 0x1FB88;
static constexpr wchar_t RIGHT_FIVE_EIGHTHS_BLOCK   = 0x1FB89;
static constexpr wchar_t RIGHT_THREE_QUARTERS_BLOCK = 0x1FB8A;
static constexpr wchar_t RIGHT_SEVEN_EIGHTHS_BLOCK  = 0x1FB8B;

static constexpr wchar_t lower_blocks[] = {
    SPACE,
    LOWER_ONE_EIGHTH_BLOCK,
    LOWER_ONE_QUARTER_BLOCK,
    LOWER_THREE_EIGHTHS_BLOCK,
    LOWER_HALF_BLOCK,
    LOWER_FIVE_EIGHTHS_BLOCK,
    LOWER_THREE_QUARTERS_BLOCK,
    LOWER_SEVEN_EIGHTHS_BLOCK,
    FULL_BLOCK,
};

static constexpr size_t num_lower_blocks = LEN(lower_blocks);

static constexpr wchar_t left_blocks[] = {
    SPACE,
    LEFT_ONE_EIGHTH_BLOCK,
    LEFT_ONE_QUARTER_BLOCK,
    LEFT_THREE_EIGHTHS_BLOCK,
    LEFT_HALF_BLOCK,
    LEFT_FIVE_EIGHTHS_BLOCK,
    LEFT_THREE_QUARTERS_BLOCK,
    LEFT_SEVEN_EIGHTHS_BLOCK,
    FULL_BLOCK,
};

static constexpr size_t num_left_blocks = LEN(left_blocks);

static constexpr wchar_t ver_lines[] = {
    LEFT_ONE_EIGHTH_BLOCK,
    VERTICAL_ONE_EIGHTH_BLOCK_2,
    VERTICAL_ONE_EIGHTH_BLOCK_3,
    VERTICAL_ONE_EIGHTH_BLOCK_4,
    VERTICAL_ONE_EIGHTH_BLOCK_5,
    VERTICAL_ONE_EIGHTH_BLOCK_6,
    VERTICAL_ONE_EIGHTH_BLOCK_7,
    RIGHT_ONE_EIGHTH_BLOCK,
};

static constexpr size_t num_ver_lines = LEN(ver_lines);

static constexpr wchar_t hor_lines[] = {
    LOWER_ONE_EIGHTH_BLOCK,
    HORIZONTAL_ONE_EIGHTH_BLOCK_7,
    HORIZONTAL_ONE_EIGHTH_BLOCK_6,
    HORIZONTAL_ONE_EIGHTH_BLOCK_5,
    HORIZONTAL_ONE_EIGHTH_BLOCK_4,
    HORIZONTAL_ONE_EIGHTH_BLOCK_3,
    HORIZONTAL_ONE_EIGHTH_BLOCK_2,
    UPPER_ONE_EIGHTH_BLOCK,
};

static constexpr size_t num_hor_lines = LEN(hor_lines);

static constexpr wchar_t upper_blocks[] = {
    SPACE,
    UPPER_ONE_EIGHTH_BLOCK,
    UPPER_ONE_QUARTER_BLOCK,
    UPPER_THREE_EIGHTHS_BLOCK,
    UPPER_HALF_BLOCK,
    UPPER_FIVE_EIGHTHS_BLOCK,
    UPPER_THREE_QUARTERS_BLOCK,
    UPPER_SEVEN_EIGHTHS_BLOCK,
    FULL_BLOCK,
};

static constexpr size_t num_upper_blocks = LEN(upper_blocks);

static constexpr wchar_t right_blocks[] = {
    SPACE,
    RIGHT_ONE_EIGHTH_BLOCK,
    RIGHT_ONE_QUARTER_BLOCK,
    RIGHT_THREE_EIGHTHS_BLOCK,
    RIGHT_HALF_BLOCK,
    RIGHT_FIVE_EIGHTHS_BLOCK,
    RIGHT_THREE_QUARTERS_BLOCK,
    RIGHT_SEVEN_EIGHTHS_BLOCK,
    FULL_BLOCK,
};

static constexpr size_t num_right_blocks = LEN(right_blocks);

static void
clamp(double* x)
{
    if (*x < 0)
        *x = 0;
    else if (*x > 1)
        *x = 1;
}

/** Map the real number \a x within the interval <code>[0, 1]</code> to an
* integer within the interval <code>[0, b)</code>.
*
* \pre \a b is at least \c 1.
*/
static size_t
map_to_uint(double x, size_t b)
{
    clamp(&x);

    // round to nearest int
    return (size_t)(x * (double)(b - 1U) + 0.5);
}

/** Calculate values of the meter segments.
*
* \pre \a x is within the interval <code>[0, 1]</code>.
*
* \pre \a blocks_len is at least \c 1.
*
* \a meter_width does not include the terminating null character.
*
* \a blocks_len is the length of the wide character array used for the meter.
*/
static void
calc_meter_segments(double x,
                    size_t meter_width,
                    size_t blocks_len,
                    size_t* left_width,
                    size_t* blocks_index,
                    size_t* right_width)
{
    *left_width = 0;
    *blocks_index = (size_t)-1;
    *right_width = 0;

    if (meter_width == 0 || blocks_len == 0)
        return;

    clamp(&x);

    // truncate
    *left_width = (size_t)(x * (double)meter_width);

    if (*left_width == meter_width)
        return;

    const double frac = x * (double)meter_width - (double)((size_t)(x * (double)meter_width));
    // This produces a preferred distribution at the ends of the meter.
    // round to nearest int
    *blocks_index = (size_t)(frac * (double)(blocks_len - 1U) + 0.5);
    // Use this to get an alternative distribution.
    // truncate
    //*blocks_index = (size_t)(frac * blocks_len);

    *right_width = meter_width - *left_width - 1U;
}

/** Return a Unicode lower block character (whose height is proportional to \a
* x).
*
* \pre \a x is within the interval <code>[0, 1]</code>.
*/
static wchar_t
lower_blocks_1(double x)
{
    return lower_blocks[map_to_uint(x, num_lower_blocks)];
}

/** Return a Unicode horizontal 1/8 block character (whose height is
* proportional to \a x).
*
* \pre \a x is within the interval <code>[0, 1]</code>.
*/
static wchar_t
hor_lines_1(double x)
{
    return hor_lines[map_to_uint(x, num_hor_lines)];
}

/** Return a Unicode upper block character (whose height is proportional to \a
* x).
*
* \pre \a x is within the interval <code>[0, 1]</code>.
*/
static wchar_t
upper_blocks_1(double x)
{
    return upper_blocks[map_to_uint(x, num_upper_blocks)];
}

/** Fill a meter with Unicode left block characters.
*
* The filled region is proportional to \a x, starting at the left.
*
* \pre \a x is within the interval [0, 1].
*
* \pre \a meter is a buffer capable of holding \a meter_width wide characters
* (not including the terminating null character).
*
* It is the caller's responsibility to null-terminate the \a meter buffer.
*/
static void
left_blocks_meter(double x, wchar_t* meter, size_t meter_width)
{
    size_t left_width, blocks_index, right_width, i;

    if (meter_width == 0)
        return;

    calc_meter_segments(x, meter_width, num_left_blocks, &left_width, &blocks_index,
                        &right_width);

    for (i = 0; i < left_width; ++i)
    {
        *meter++ = FULL_BLOCK;
    }

    if (blocks_index != (size_t)-1)
        *meter++ = left_blocks[blocks_index];

    for (i = 0; i < right_width; ++i)
    {
        *meter++ = SPACE;
    }
}

/** Fill a meter with a Unicode vertical 1/8 block character.
*
* The position of the filled character is proportional to \a x, starting at the
* left.
*
* \pre \a x is within the interval [0, 1].
*
* \pre \a meter is a buffer capable of holding \a meter_width wide characters
* (not including the terminating null character).
*
* It is the caller's responsibility to null-terminate the \a meter buffer.
*/
static void
ver_lines_meter(double x, wchar_t* meter, size_t meter_width)
{
    size_t left_width, blocks_index, right_width, i;

    if (meter_width == 0)
        return;

    calc_meter_segments(x, meter_width, num_ver_lines, &left_width, &blocks_index,
                        &right_width);

    if (left_width == meter_width)
    {
        // Special case when the vertical line will be at the right end

        for (i = 1; i < left_width; ++i)
        {
            *meter++ = SPACE;
        }

        *meter++ = RIGHT_ONE_EIGHTH_BLOCK;
    }
    else
    {
        for (i = 0; i < left_width; ++i)
        {
            *meter++ = SPACE;
        }

        if (blocks_index != (size_t)-1)
            *meter++ = ver_lines[blocks_index];

        for (i = 0; i < right_width; ++i)
        {
            *meter++ = SPACE;
        }
    }
}

/** Fill a meter with Unicode right block characters.
*
* The filled region is proportional to \a x, starting at the right.
*
* \pre \a x is within the interval [0, 1].
*
* \pre \a meter is a buffer capable of holding \a meter_width wide characters
* (not including the terminating null character).
*
* It is the caller's responsibility to null-terminate the \a meter buffer.
*/
static void
right_blocks_meter(double x, wchar_t* meter, size_t meter_width)
{
    size_t left_width, blocks_index, right_width, i;

    if (meter_width == 0)
        return;

    calc_meter_segments(x, meter_width, num_right_blocks, &left_width, &blocks_index,
                        &right_width);

    // left_width and right_width are swapped

    for (i = 0; i < right_width; ++i)
    {
        *meter++ = SPACE;
    }

    if (blocks_index != (size_t)-1)
        *meter++ = right_blocks[blocks_index];

    for (i = 0; i < left_width; ++i)
    {
        *meter++ = FULL_BLOCK;
    }
}

/** Fill a meter with ASCII characters.
*
* The filled region is proportional to \a x, starting at the left.
*
* \pre \a x is within the interval <code>[0, 1]</code>.
*
* \pre meter is a buffer capable of holding \a meter_width characters
* (not including the terminating null character).
*
* It is the caller's responsibility to null-terminate the \a meter buffer.
*/
static void
left_char_meter(double x, char* meter, size_t meter_width, char fill, char unfill)
{
    size_t i;

    if (meter_width == 0)
        return;

    clamp(&x);

    // round to nearest int
    const size_t num_filled = (size_t)(x * (double)meter_width + 0.5);
    [[maybe_unused]] const size_t num_unfilled = meter_width - num_filled;

    for (i = 0; i < num_filled; ++i)
    {
        meter[i] = fill;
    }
    for (; i < meter_width; ++i)
    {
        meter[i] = unfill;
    }
}

/** Fill a meter with ASCII characters.
*
* The filled region is proportional to \a x, starting at the right.
*
* \pre \a x is within the interval <code>[0, 1]</code>.
*
* \pre meter is a buffer capable of holding \a meter_width characters
* (not including the terminating null character).
*
* It is the caller's responsibility to null-terminate the \a meter buffer.
*/
static void
right_char_meter(double x, char* meter, size_t meter_width, char fill, char unfill)
{
    size_t i;

    if (meter_width == 0)
        return;

    clamp(&x);

    // round to nearest int
    const size_t num_filled = (size_t)(x * (double)meter_width + 0.5);
    const size_t num_unfilled = meter_width - num_filled;

    for (i = 0; i < num_unfilled; ++i)
    {
        meter[i] = unfill;
    }
    for (; i < meter_width; ++i)
    {
        meter[i] = fill;
    }
}

#ifdef __cplusplus
} // extern "C"
#endif
