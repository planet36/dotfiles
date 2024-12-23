// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Simple wrapper for XXH3
/**
\file
\author Steven Ward
\sa https://xxhash.com/
\sa https://github.com/Cyan4973/xxHash
*/

#pragma once

#include <cassert>
#include <xxhash.h>

class simple_xxh3_64
{
private:
	XXH3_state_t* state_ptr;

public:
	simple_xxh3_64()
	{
		assert((state_ptr = XXH3_createState()) != nullptr);
		assert(XXH3_64bits_reset(state_ptr) == XXH_OK);
	}

	simple_xxh3_64(XXH64_hash_t seed)
	{
		assert((state_ptr = XXH3_createState()) != nullptr);
		assert(XXH3_64bits_reset_withSeed(state_ptr, seed) == XXH_OK);
	}

	simple_xxh3_64(const void* secret, size_t secretSize)
	{
		assert((state_ptr = XXH3_createState()) != nullptr);
		assert(XXH3_64bits_reset_withSecret(state_ptr, secret, secretSize) == XXH_OK);
	}

#if 0
	simple_xxh3_64(const void* secret, size_t secretSize, XXH64_hash_t seed)
	{
		assert((state_ptr = XXH3_createState()) != nullptr);
		assert(XXH3_64bits_reset_withSecretandSeed(state_ptr, secret, secretSize, seed) == XXH_OK);
	}
#endif

	simple_xxh3_64(const simple_xxh3_64&) = delete;
	simple_xxh3_64& operator=(const simple_xxh3_64&) = delete;

	~simple_xxh3_64()
	{
		assert(XXH3_freeState(state_ptr) == XXH_OK);
	}

	void update(const void* input, size_t len)
	{
		assert(XXH3_64bits_update(state_ptr, input, len) == XXH_OK);
	}

	XXH64_hash_t digest() const
	{
		return XXH3_64bits_digest(state_ptr);
	}
};

class simple_xxh3_128
{
private:
	XXH3_state_t* state_ptr;

public:
	simple_xxh3_128()
	{
		assert((state_ptr = XXH3_createState()) != nullptr);
		assert(XXH3_128bits_reset(state_ptr) == XXH_OK);
	}

	simple_xxh3_128(XXH64_hash_t seed)
	{
		assert((state_ptr = XXH3_createState()) != nullptr);
		assert(XXH3_128bits_reset_withSeed(state_ptr, seed) == XXH_OK);
	}

	simple_xxh3_128(const void* secret, size_t secretSize)
	{
		assert((state_ptr = XXH3_createState()) != nullptr);
		assert(XXH3_128bits_reset_withSecret(state_ptr, secret, secretSize) == XXH_OK);
	}

#if 0
	simple_xxh3_128(const void* secret, size_t secretSize, XXH64_hash_t seed)
	{
		assert((state_ptr = XXH3_createState()) != nullptr);
		assert(XXH3_128bits_reset_withSecretandSeed(state_ptr, secret, secretSize, seed) == XXH_OK);
	}
#endif

	simple_xxh3_128(const simple_xxh3_128&) = delete;
	simple_xxh3_128& operator=(const simple_xxh3_128&) = delete;

	~simple_xxh3_128()
	{
		assert(XXH3_freeState(state_ptr) == XXH_OK);
	}

	void update(const void* input, size_t len)
	{
		assert(XXH3_128bits_update(state_ptr, input, len) == XXH_OK);
	}

	XXH128_hash_t digest() const
	{
		return XXH3_128bits_digest(state_ptr);
	}
};
