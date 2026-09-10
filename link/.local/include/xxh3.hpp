// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Simple wrapper for XXH3
/**
* \file
* \author Steven Ward
* \sa https://xxhash.com/
* \sa https://github.com/Cyan4973/xxHash
*/

#pragma once

#if defined(DEBUG)
#include <cassert>
#endif
#include <new>
#include <stdexcept>
#include <xxhash.h>

class simple_xxh3_64
{
private:
    XXH3_state_t* state_ptr;

public:
    simple_xxh3_64() : state_ptr(XXH3_createState())
    {
        if (state_ptr == nullptr)
            throw std::bad_alloc();

        [[maybe_unused]] const XXH_errorcode err = XXH3_64bits_reset(state_ptr);
#if defined(DEBUG)
        assert(err == XXH_OK);
#endif
    }

    explicit simple_xxh3_64(XXH64_hash_t seed) : state_ptr(XXH3_createState())
    {
        if (state_ptr == nullptr)
            throw std::bad_alloc();

        [[maybe_unused]] const XXH_errorcode err = XXH3_64bits_reset_withSeed(state_ptr, seed);
#if defined(DEBUG)
        assert(err == XXH_OK);
#endif
    }

    /// Construct with the secret \a secret, of \a secretSize bytes
    /**
    * \exception std::bad_alloc the state could not be allocated
    * \exception std::invalid_argument \a secretSize is less than \c XXH3_SECRET_SIZE_MIN
    */
    simple_xxh3_64(const void* secret, size_t secretSize) : state_ptr(XXH3_createState())
    {
        if (state_ptr == nullptr)
            throw std::bad_alloc();

        if (secretSize < XXH3_SECRET_SIZE_MIN ||
            XXH3_64bits_reset_withSecret(state_ptr, secret, secretSize) != XXH_OK)
        {
            XXH3_freeState(state_ptr);
            throw std::invalid_argument("XXH3_64bits_reset_withSecret");
        }
    }

#if 0
    /// Construct with the secret \a secret, of \a secretSize bytes, and the seed \a seed
    /**
    * \exception std::bad_alloc the state could not be allocated
    * \exception std::invalid_argument \a secretSize is less than \c XXH3_SECRET_SIZE_MIN
    */
    simple_xxh3_64(const void* secret, size_t secretSize, XXH64_hash_t seed) : state_ptr(XXH3_createState())
    {
        if (state_ptr == nullptr)
            throw std::bad_alloc();

        if (secretSize < XXH3_SECRET_SIZE_MIN ||
            XXH3_64bits_reset_withSecretandSeed(state_ptr, secret, secretSize, seed) != XXH_OK)
        {
            XXH3_freeState(state_ptr);
            throw std::invalid_argument("XXH3_64bits_reset_withSecretandSeed");
        }
    }
#endif

    simple_xxh3_64(const simple_xxh3_64&) = delete;
    simple_xxh3_64& operator=(const simple_xxh3_64&) = delete;

    simple_xxh3_64(simple_xxh3_64&&) = delete;
    simple_xxh3_64& operator=(simple_xxh3_64&&) = delete;

    ~simple_xxh3_64()
    {
        [[maybe_unused]] const XXH_errorcode err = XXH3_freeState(state_ptr);
#if defined(DEBUG)
        assert(err == XXH_OK);
#endif
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void update(const void* input, size_t len)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        [[maybe_unused]] const XXH_errorcode err = XXH3_64bits_update(state_ptr, input, len);
#if defined(DEBUG)
        assert(err == XXH_OK);
#endif
    }

    [[nodiscard]] XXH64_hash_t digest() const { return XXH3_64bits_digest(state_ptr); }
};

class simple_xxh3_128
{
private:
    XXH3_state_t* state_ptr;

public:
    simple_xxh3_128() : state_ptr(XXH3_createState())
    {
        if (state_ptr == nullptr)
            throw std::bad_alloc();

        [[maybe_unused]] const XXH_errorcode err = XXH3_128bits_reset(state_ptr);
#if defined(DEBUG)
        assert(err == XXH_OK);
#endif
    }

    explicit simple_xxh3_128(XXH64_hash_t seed) : state_ptr(XXH3_createState())
    {
        if (state_ptr == nullptr)
            throw std::bad_alloc();

        [[maybe_unused]] const XXH_errorcode err = XXH3_128bits_reset_withSeed(state_ptr, seed);
#if defined(DEBUG)
        assert(err == XXH_OK);
#endif
    }

    /// Construct with the secret \a secret, of \a secretSize bytes
    /**
    * \exception std::bad_alloc the state could not be allocated
    * \exception std::invalid_argument \a secretSize is less than \c XXH3_SECRET_SIZE_MIN
    */
    simple_xxh3_128(const void* secret, size_t secretSize) : state_ptr(XXH3_createState())
    {
        if (state_ptr == nullptr)
            throw std::bad_alloc();

        if (secretSize < XXH3_SECRET_SIZE_MIN ||
            XXH3_128bits_reset_withSecret(state_ptr, secret, secretSize) != XXH_OK)
        {
            XXH3_freeState(state_ptr);
            throw std::invalid_argument("XXH3_128bits_reset_withSecret");
        }
    }

#if 0
    /// Construct with the secret \a secret, of \a secretSize bytes, and the seed \a seed
    /**
    * \exception std::bad_alloc the state could not be allocated
    * \exception std::invalid_argument \a secretSize is less than \c XXH3_SECRET_SIZE_MIN
    */
    simple_xxh3_128(const void* secret, size_t secretSize, XXH64_hash_t seed) : state_ptr(XXH3_createState())
    {
        if (state_ptr == nullptr)
            throw std::bad_alloc();

        if (secretSize < XXH3_SECRET_SIZE_MIN ||
            XXH3_128bits_reset_withSecretandSeed(state_ptr, secret, secretSize, seed) != XXH_OK)
        {
            XXH3_freeState(state_ptr);
            throw std::invalid_argument("XXH3_128bits_reset_withSecretandSeed");
        }
    }
#endif

    simple_xxh3_128(const simple_xxh3_128&) = delete;
    simple_xxh3_128& operator=(const simple_xxh3_128&) = delete;

    simple_xxh3_128(simple_xxh3_128&&) = delete;
    simple_xxh3_128& operator=(simple_xxh3_128&&) = delete;

    ~simple_xxh3_128()
    {
        [[maybe_unused]] const XXH_errorcode err = XXH3_freeState(state_ptr);
#if defined(DEBUG)
        assert(err == XXH_OK);
#endif
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void update(const void* input, size_t len)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        [[maybe_unused]] const XXH_errorcode err = XXH3_128bits_update(state_ptr, input, len);
#if defined(DEBUG)
        assert(err == XXH_OK);
#endif
    }

    [[nodiscard]] XXH128_hash_t digest() const { return XXH3_128bits_digest(state_ptr); }
};
