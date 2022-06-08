// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// non-thread-safe C circular buffer
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

static const unsigned long circbuf_version = 20210715UL;

typedef struct
{
	void* buf;
	size_t num_elems;
	size_t sizeof_elem;
	size_t head;
	size_t tail;
	bool empty; // (head == tail) && !full
	bool full;
} circbuf;

static const circbuf circbuf_default = {0};

static circbuf
circbuf_init(size_t num_elems, size_t sizeof_elem)
{
	return (circbuf){
		.buf = calloc(num_elems, sizeof_elem),
		.num_elems = num_elems,
		.sizeof_elem = sizeof_elem,
		.head = 0,
		.tail = 0,
		.empty = true,
		.full = false,
	};
}

static void
circbuf_free(circbuf* cbuf)
{
	(void)memset(cbuf->buf, 0, cbuf->num_elems * cbuf->sizeof_elem);
	free(cbuf->buf);
	cbuf->buf = NULL;
	cbuf->num_elems = 0;
	cbuf->sizeof_elem = 0;
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->empty = true;
	cbuf->full = false;
}

// https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html
// automatically deallocate circbuf
#define CIRCBUF(varname, num_elems, type)  \
	__attribute__((cleanup(circbuf_free))) \
	circbuf varname = circbuf_init(num_elems, sizeof(type));

static size_t
circbuf_count(const circbuf* cbuf)
{
	if (cbuf->empty)
		return 0;
	else if (cbuf->full)
		return cbuf->num_elems;
	else if (cbuf->head > cbuf->tail)
		return cbuf->head - cbuf->tail;
	else
		return cbuf->num_elems - (cbuf->tail - cbuf->head);
}

static void
circbuf_push(circbuf* cbuf, const void* x)
{
	// add to head
	(void)memcpy((char*)cbuf->buf + cbuf->head * cbuf->sizeof_elem,
	             x, cbuf->sizeof_elem);

	if (cbuf->full)
		if (++cbuf->tail == cbuf->num_elems) // inc tail
			cbuf->tail = 0; // tail rollover

	if (++cbuf->head == cbuf->num_elems) // inc head
		cbuf->head = 0; // head rollover

	cbuf->empty = false;
	cbuf->full = cbuf->head == cbuf->tail;
}

static int
circbuf_pop(circbuf* cbuf, void* x)
{
	if (cbuf->empty)
		return -1;

	if (x)
		(void)memcpy(x, (char*)cbuf->buf + cbuf->tail * cbuf->sizeof_elem,
		             cbuf->sizeof_elem);

	// remove from tail
	(void)memset((char*)cbuf->buf + cbuf->tail * cbuf->sizeof_elem,
	             0, cbuf->sizeof_elem);

	if (++cbuf->tail == cbuf->num_elems) // inc tail
		cbuf->tail = 0; // tail rollover

	cbuf->empty = cbuf->head == cbuf->tail;
	cbuf->full = false;

	return 0;
}
