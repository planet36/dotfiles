// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// non-thread-safe C circular queue
/**
\file
\author Steven Ward
*/

#pragma once

// inspired by
// https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static const unsigned long circqueue_version = 20220609UL;

typedef struct
{
	void* buf;
	size_t max_num_elems;
	size_t sizeof_elem;
	size_t head; // remove from front (head)
	size_t tail; // add to back (tail)
	bool empty; // (head == tail) && !full
	bool full;
} circqueue;

static const circqueue circqueue_default = {0};

static circqueue
circqueue_init(size_t max_num_elems, size_t sizeof_elem)
{
	return (circqueue){
		.buf = calloc(max_num_elems, sizeof_elem),
		.max_num_elems = max_num_elems,
		.sizeof_elem = sizeof_elem,
		.head = 0,
		.tail = 0,
		.empty = true,
		.full = false,
	};
}

static void
circqueue_free(circqueue* cq)
{
	(void)memset(cq->buf, 0, cq->max_num_elems * cq->sizeof_elem);
	free(cq->buf);
	cq->buf = NULL;
	cq->max_num_elems = 0;
	cq->sizeof_elem = 0;
	cq->head = 0;
	cq->tail = 0;
	cq->empty = true;
	cq->full = false;
}

// https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html
// automatically deallocate circqueue
#define circqueue(varname, max_num_elems, type)  \
	__attribute__((cleanup(circqueue_free))) \
	circqueue varname = circqueue_init(max_num_elems, sizeof(type));

static size_t
circqueue_count(const circqueue* cq)
{
	size_t ret;

	if (cq->empty)
		ret = 0;
	else if (cq->full)
		ret = cq->max_num_elems;
	else if (cq->tail > cq->head)
		ret = cq->tail - cq->head;
	else
		ret = cq->max_num_elems - (cq->head - cq->tail);

	return ret;
}

static void
circqueue_push(circqueue* cq, const void* x)
{
	// add to tail
	(void)memcpy((char*)cq->buf + cq->tail * cq->sizeof_elem,
	             x, cq->sizeof_elem);

	if (cq->full)
		if (++cq->head == cq->max_num_elems) // inc head
			cq->head = 0; // head rollover

	if (++cq->tail == cq->max_num_elems) // inc tail
		cq->tail = 0; // tail rollover

	cq->empty = false;
	cq->full = cq->head == cq->tail;
}

static bool
circqueue_pop(circqueue* cq, void* x)
{
	if (cq->empty)
		return false;

	if (x)
		(void)memcpy(x, (char*)cq->buf + cq->head * cq->sizeof_elem,
		             cq->sizeof_elem);

	// zeroize element
	(void)memset((char*)cq->buf + cq->head * cq->sizeof_elem,
	             0, cq->sizeof_elem);

	if (++cq->head == cq->max_num_elems) // inc head
		cq->head = 0; // head rollover

	cq->empty = cq->head == cq->tail;
	cq->full = false;

	return true;
}

static void
circqueue_zeroize(circqueue* cq)
{
	(void)memset(cq->buf, 0, cq->max_num_elems * cq->sizeof_elem);
	cq->head = 0;
	cq->tail = 0;
	cq->empty = true;
	cq->full = false;
}
