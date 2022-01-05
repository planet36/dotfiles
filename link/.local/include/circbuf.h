// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// circular buffer
/**
\file
\author Steven Ward
*/

# pragma once

// inspired by
// https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const unsigned long circbuf_version = 20210715UL;

typedef struct
{
	void* buf;
	uint32_t num_elems;
	uint32_t sizeof_elem;
	uint32_t head;
	uint32_t tail;
	bool full;
} circbuf;

static const circbuf circbuf_default = {0};

static circbuf
circbuf_init(uint32_t num_elems, uint32_t sizeof_elem)
{
	return (circbuf){
		.buf = calloc(num_elems, sizeof_elem),
		.num_elems = num_elems,
		.sizeof_elem = sizeof_elem,
		.head = 0,
		.tail = 0,
		.full = false
	};
}

static void
circbuf_free(circbuf* cbuf)
{
	(void)memset(cbuf->buf, 0, (size_t)cbuf->num_elems * cbuf->sizeof_elem);
	free(cbuf->buf);
	cbuf->buf = NULL;
	cbuf->num_elems = 0;
	cbuf->sizeof_elem = 0;
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->full = false;
}

// https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html
// automatically deallocate circbuf
#define CIRCBUF(varname, num_elems, type) \
__attribute__((cleanup(circbuf_free))) \
circbuf varname = circbuf_init(num_elems, sizeof(type));

static bool
circbuf_empty(const circbuf* cbuf)
{
	return (cbuf->head == cbuf->tail) && !cbuf->full;
}

static uint32_t
circbuf_count(const circbuf* cbuf)
{
	if (circbuf_empty(cbuf))
		return 0;
	else if (cbuf->full)
		return cbuf->num_elems;
	else
		if (cbuf->head > cbuf->tail)
			return cbuf->head - cbuf->tail;
		else
			return cbuf->num_elems - (cbuf->tail - cbuf->head);
}

static void
circbuf_add(circbuf* cbuf, const void* x)
{
	// add to head
	(void)memcpy((char*)cbuf->buf + (size_t)cbuf->head * cbuf->sizeof_elem,
	             x, cbuf->sizeof_elem);

	if (cbuf->full)
		if (++cbuf->tail == cbuf->num_elems) // inc tail
			cbuf->tail = 0; // tail rollover

	if (++cbuf->head == cbuf->num_elems) // inc head
		cbuf->head = 0; // head rollover

	cbuf->full = cbuf->head == cbuf->tail;
}

static int
circbuf_del(circbuf* cbuf, void* x)
{
	if (circbuf_empty(cbuf))
		return -1;

	if (x)
		(void)memcpy(x, (char*)cbuf->buf + (size_t)cbuf->tail * cbuf->sizeof_elem,
		             cbuf->sizeof_elem);

	// remove from tail
	(void)memset((char*)cbuf->buf + (size_t)cbuf->tail * cbuf->sizeof_elem,
	             0, cbuf->sizeof_elem);

	if (++cbuf->tail == cbuf->num_elems) // inc tail
		cbuf->tail = 0; // tail rollover

	cbuf->full = false;

	return 0;
}
