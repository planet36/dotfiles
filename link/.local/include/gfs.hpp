// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Non-cyclic permutation for Type-II generalized Feistel structure (GFS) (a.k.a. generalized Feistel network)
/**
\file
\author Steven Ward
\sa https://doi.org/10.1007/978-3-642-13858-4_2

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

/// Get the maximum diffusion round (DRmax)
/** DRmax ≅ ⌈2×log₂(k)⌉ */
template <unsigned int k>
constexpr unsigned int
gfs_drmax()
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

/// Get the optimum, non-cyclic block shuffle permutation (π) for \a k.
/** Permutation No. 1 is chosen for each \a k. */
template <unsigned int k>
constexpr std::array<uint8_t, k>
gfs_noncyclic_p()
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

/// Get the optimum, non-cyclic block shuffle permutation inverse (π⁻¹) for \a k.
/** Permutation No. 1 is chosen for each \a k. */
template <unsigned int k>
constexpr std::array<uint8_t, k>
gfs_noncyclic_p_inv()
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
