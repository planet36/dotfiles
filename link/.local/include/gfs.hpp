// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Non-cyclic permutation for Type-II generalized Feistel structure (GFS) (a.k.a. generalized Feistel network)
/**
\file
\author Steven Ward
\sa https://link.springer.com/chapter/10.1007/0-387-34805-0_42
\sa https://doi.org/10.1007/978-3-642-13858-4_2

Zheng, Y., Matsumoto, T., Imai, H. (1990). _On the Construction of Block Ciphers Provably Secure and Not Relying on Any Unproved Hypotheses_

Page 8 (468)
> Let E be a permutation consisting of 2k-1 rounds of Type-1, or k+1 rounds of
Type-2, or k+1 rounds of Type-3 transformations, each of which is chosen
randomly and independently. The following Theorems 1-3 say that no oracle
circuit with polynomially many oracle gates can distinguish between E and a
truly random function.

Page 10 (470)
> PSBC consists principally of s rounds of Generalized Type-2 transformations
where s ≥ k+2. The reason for choosing s ≥ k+2 is as follows: When s = k+1, our
block cipher PSBC is secure against chosen plaintext attack, but not secure
against chosen plaintext/ciphertext attack. When s ≥ k+2, PSBC is secure
against chosen plaintext/ciphertext attack. See Appendix C and [LR]

(PSBC = Provably Secure Block Cipher)


Suzaki, T., Minematsu, K. (2010). _Improving the Generalized Feistel_.

Page 20
> Our goal is to find block shuffles having a better diffusion than the cyclic
shift. For this purpose, we formally define a criterion for the goodness of
diffusion called the maximum diffusion round, DRmax, which tells how many
rounds are needed to achieve the full diffusion. Hence, a smaller DRmax would
imply a faster, better diffusion. Moreover, we observe that DRmax is closely
related to the security against impossible differential and saturation attacks,
and the pseudorandomness analysis. This demonstrates the usefulness of our
notion.

> In addition, we present a family of highly diffusive shuffles when _k_ is a
power of two. This is based on the de Bruijn graph, and achieves DRmax being
about 2 log₂ k. As DRmax of Type-II GFS is _k_, this means a significant
improvement for a large _k_.

Page 22
> In this section, we introduce a formal notion of the diffusion property of
GFS. What we mean by ‘diffusion’ here is the state that a sub block input
affects all of the sub blocks of output.

> Thus, for any GFSπ, any sub output block is affected by any sub input block
after DRmax(π) rounds. We call this state the _full diffusion_.

Page 37
> Table 4, 5 and 6 show the optimum shuffles found in the search and their
security evaluation. We eliminate isomorphic shuffles. Type-II and Nyberg’s GFN
are also evaluated. Shuffles based on de Bruijn graph is indicated by ∗. A
shuffle is presented in list: π = {3, 0, 1, 4, 5, 2} means that the first input
sub block is mapped to the third sub block of output, etc.

> We evaluated both π and π⁻¹.

*/

#pragma once

#include <array>
#include <bit>
#include <cstdint>

/**
* DRmax = 2k-1
* \pre \a k is even
* \pre \a k is >= 2
*/
constexpr unsigned int
gfs1_cyclic_drmax(unsigned int k)
{
	return 2 * k - 1;
}

/**
* DRmax = k+1
* \pre \a k is even
* \pre \a k is >= 2
*/
constexpr unsigned int
gfs2_cyclic_drmax(unsigned int k)
{
	return k + 1;
}

/**
* DRmax = k+1
* \pre \a k is even
* \pre \a k is >= 2
*/
constexpr unsigned int
gfs3_cyclic_drmax(unsigned int k)
{
	return k + 1;
}

/// Get the maximum diffusion round (DRmax) when using the optimal non-cyclic block shuffle permutation
/** DRmax ≅ ⌈2×log₂(k)⌉ */
template <unsigned int k>
constexpr unsigned int
gfs2_noncyclic_drmax()
{
	static_assert(k >= 6);
	static_assert(k <= 16);
	static_assert(k % 2 == 0);

	if constexpr      (k ==  6) return 6;
	else if constexpr (k ==  8) return 6;
	else if constexpr (k == 10) return 7;
	else if constexpr (k == 12) return 8;
	else if constexpr (k == 14) return 8;
	else if constexpr (k == 16) return 8;
}

/**
Python snippet to generate the arrays
\code{.py}
for k in range(2, 16+1, 2):
    l = list(range(k))
    print(l[1:] + l[:1])
\endcode
*/
template <size_t k>
constexpr std::array<uint8_t, k>
gfs_cyclic_p()
{
	static_assert(k >= 2);
	static_assert(k <= 16);
	static_assert(k % 2 == 0);

	if constexpr      (k ==  2) return {1, 0};
	else if constexpr (k ==  4) return {1, 2, 3, 0};
	else if constexpr (k ==  6) return {1, 2, 3, 4, 5, 0};
	else if constexpr (k ==  8) return {1, 2, 3, 4, 5, 6, 7, 0};
	else if constexpr (k == 10) return {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	else if constexpr (k == 12) return {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0};
	else if constexpr (k == 14) return {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0};
	else if constexpr (k == 16) return {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
}

/// Get the optimal non-cyclic block shuffle permutation (π) for \a k.
/** Permutation No. 1 is chosen for each \a k. */
template <unsigned int k>
constexpr std::array<uint8_t, k>
gfs2_noncyclic_p()
{
	static_assert(k >= 6);
	static_assert(k <= 16);
	static_assert(k % 2 == 0);

	if constexpr      (k ==  6) return {3,0,1,4,5,2};
	else if constexpr (k ==  8) return {3,0,1,4,7,2,5,6};
	else if constexpr (k == 10) return {5,0,7,2,9,6,3,8,1,4};
	else if constexpr (k == 12) return {3,0,7,2,9,4,11,8,5,10,1,6};
	else if constexpr (k == 14) return {1,2,9,4,3,6,13,8,7,10,11,12,5,0};
	else if constexpr (k == 16) return {1,2,9,4,15,6,5,8,13,10,7,14,11,12,3,0};
}

/// Get the optimal non-cyclic block shuffle permutation inverse (π⁻¹) for \a k.
/** Permutation No. 1 is chosen for each \a k. */
template <unsigned int k>
constexpr std::array<uint8_t, k>
gfs2_noncyclic_p_inv()
{
	static_assert(k >= 6);
	static_assert(k <= 16);
	static_assert(k % 2 == 0);

	if constexpr      (k ==  6) return {1,2,5,0,3,4};
	else if constexpr (k ==  8) return {1,2,5,0,3,6,7,4};
	else if constexpr (k == 10) return {1,8,3,6,9,0,5,2,7,4};
	else if constexpr (k == 12) return {1,10,3,0,5,8,11,2,7,4,9,6};
	else if constexpr (k == 14) return {13,0,1,4,3,12,5,8,7,2,9,10,11,6};
	else if constexpr (k == 16) return {15,0,1,14,3,6,5,10,7,2,9,12,13,8,11,4};
}
