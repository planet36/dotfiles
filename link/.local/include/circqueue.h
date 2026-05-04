// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// non-thread-safe C circular queue
/**
* \file
* \author Steven Ward
* \sa https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-cleanup
*/

#pragma once

// inspired by
// https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct
{
    void* buf;
    size_t max_num_elems;
    size_t sizeof_elem;
    size_t head; // remove from front (head)
    size_t tail; // add to back (tail)
    size_t num_elems;
} circqueue;

static bool
circqueue_is_empty(const circqueue* cq)
{
    return cq->num_elems == 0;
}

static bool
circqueue_is_full(const circqueue* cq)
{
    return cq->num_elems == cq->max_num_elems;
}

static const circqueue circqueue_default = {
    .buf = nullptr,
    .max_num_elems = 0,
    .sizeof_elem = 0,
    .head = 0,
    .tail = 0,
    .num_elems = 0,
};

static circqueue
circqueue_init(size_t max_num_elems, size_t sizeof_elem)
{
    return (circqueue){
        .buf = calloc(max_num_elems, sizeof_elem),
        .max_num_elems = max_num_elems,
        .sizeof_elem = sizeof_elem,
        .head = 0,
        .tail = 0,
        .num_elems = 0,
    };
}

static void
circqueue_free(circqueue* cq)
{
    (void)memset(cq->buf, 0, cq->max_num_elems * cq->sizeof_elem);
    free(cq->buf);
    cq->buf = nullptr;
    cq->max_num_elems = 0;
    cq->sizeof_elem = 0;
    cq->head = 0;
    cq->tail = 0;
    cq->num_elems = 0;
}

// automatically deallocate circqueue
#define circqueue(varname, max_num_elems, type)          \
    circqueue varname [[gnu::cleanup(circqueue_free)]] = \
        circqueue_init(max_num_elems, sizeof(type));

static bool
circqueue_push_overwrite_if_full(circqueue* cq, const void* x)
{
    // add to tail
    (void)memcpy((char*)cq->buf + cq->tail * cq->sizeof_elem, x, cq->sizeof_elem);

    if (circqueue_is_full(cq))
    {
        if (++cq->head == cq->max_num_elems) // inc head
            cq->head = 0;                    // head rollover
    }
    else
    {
        // was not full
        ++cq->num_elems;
    }

    if (++cq->tail == cq->max_num_elems) // inc tail
        cq->tail = 0;                    // tail rollover

    return true;
}

static bool
circqueue_push(circqueue* cq, const void* x)
{
    if (circqueue_is_full(cq))
        return false;

    return circqueue_push_overwrite_if_full(cq, x);
}

static bool
circqueue_pop(circqueue* cq, void* x)
{
    if (circqueue_is_empty(cq))
        return false;

    if (x)
        (void)memcpy(x, (char*)cq->buf + cq->head * cq->sizeof_elem, cq->sizeof_elem);

    // reset element
    (void)memset((char*)cq->buf + cq->head * cq->sizeof_elem, 0, cq->sizeof_elem);

    // was not empty
    --cq->num_elems;

    if (++cq->head == cq->max_num_elems) // inc head
        cq->head = 0;                    // head rollover

    return true;
}

static void
circqueue_reset(circqueue* cq)
{
    (void)memset(cq->buf, 0, cq->max_num_elems * cq->sizeof_elem);
    cq->head = 0;
    cq->tail = 0;
    cq->num_elems = 0;
}

#if defined(__cplusplus)
} // extern "C"
#endif
