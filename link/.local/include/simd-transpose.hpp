// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Transpose an array of \c __m128i, treating it as a square matrix of integers
/**
\file
\author Steven Ward
*/

#pragma once

#include "simd-array.hpp"

#include <array>
#include <immintrin.h>

inline void
transpose_2(arr_m128i<2>& x)
{
	const __m128i a0_b0 = _mm_unpacklo_epi64(x[0], x[1]);
	const __m128i a1_b1 = _mm_unpackhi_epi64(x[0], x[1]);

	x[0] = a0_b0;
	x[1] = a1_b1;
}


/**
\sa https://randombit.net/bitbashing/posts/integer_matrix_transpose_in_sse2.html
*/
void
transpose_4(arr_m128i<4>& x)
{
	const __m128i a01_b01 = _mm_unpacklo_epi32(x[0], x[1]);
	const __m128i a23_b23 = _mm_unpackhi_epi32(x[0], x[1]);
	const __m128i c01_b01 = _mm_unpacklo_epi32(x[2], x[3]);
	const __m128i c23_d23 = _mm_unpackhi_epi32(x[2], x[3]);

	x[0] = _mm_unpacklo_epi64(a01_b01, c01_b01); // a0_b0_c0_d0
	x[1] = _mm_unpackhi_epi64(a01_b01, c01_b01); // a1_b1_c1_d1
	x[2] = _mm_unpacklo_epi64(a23_b23, c23_d23); // a2_b2_c2_d2
	x[3] = _mm_unpackhi_epi64(a23_b23, c23_d23); // a3_b3_c3_d3
}


/**
\sa https://community.intel.com/t5/Intel-ISA-Extensions/4x4-matrix-transpose-using-sse2-intrinsics/m-p/785883#M353
\verbatim
Cast your __m128i variables into __m128 variables (using _mm_castsi128_ps), use the macro _MM_TRANSPOSE_PS, then cast back using _mm_castps_si128.
\endverbatim
*/
void
transpose_4_macro(arr_m128i<4>& x)
{
	__m128 a = _mm_castsi128_ps(x[0]);
	__m128 b = _mm_castsi128_ps(x[1]);
	__m128 c = _mm_castsi128_ps(x[2]);
	__m128 d = _mm_castsi128_ps(x[3]);

	_MM_TRANSPOSE4_PS(a, b, c, d);

	x[0] = _mm_castps_si128(a);
	x[1] = _mm_castps_si128(b);
	x[2] = _mm_castps_si128(c);
	x[3] = _mm_castps_si128(d);
}


/**
\sa https://stackoverflow.com/a/4951060/1892784
*/
void
transpose_8(arr_m128i<8>& x)
{
	const __m128i a03_b03 = _mm_unpacklo_epi16(x[0], x[1]);
	const __m128i a47_b47 = _mm_unpackhi_epi16(x[0], x[1]);
	const __m128i c03_d03 = _mm_unpacklo_epi16(x[2], x[3]);
	const __m128i c47_d47 = _mm_unpackhi_epi16(x[2], x[3]);
	const __m128i e03_f03 = _mm_unpacklo_epi16(x[4], x[5]);
	const __m128i e47_f47 = _mm_unpackhi_epi16(x[4], x[5]);
	const __m128i g03_h03 = _mm_unpacklo_epi16(x[6], x[7]);
	const __m128i g47_h47 = _mm_unpackhi_epi16(x[6], x[7]);

	const __m128i a01_b01_c01_d01 = _mm_unpacklo_epi32(a03_b03, c03_d03);
	const __m128i a23_b23_c23_d23 = _mm_unpackhi_epi32(a03_b03, c03_d03);
	const __m128i e01_f01_g01_h01 = _mm_unpacklo_epi32(e03_f03, g03_h03);
	const __m128i e23_f23_g23_h23 = _mm_unpackhi_epi32(e03_f03, g03_h03);
	const __m128i a45_b45_c45_d45 = _mm_unpacklo_epi32(a47_b47, c47_d47);
	const __m128i a67_b67_c67_d67 = _mm_unpackhi_epi32(a47_b47, c47_d47);
	const __m128i e45_f45_g45_h45 = _mm_unpacklo_epi32(e47_f47, g47_h47);
	const __m128i e67_f67_g67_h67 = _mm_unpackhi_epi32(e47_f47, g47_h47);

	x[0] = _mm_unpacklo_epi64(a01_b01_c01_d01, e01_f01_g01_h01); // a0_b0_c0_d0_e0_f0_g0_h0
	x[1] = _mm_unpackhi_epi64(a01_b01_c01_d01, e01_f01_g01_h01); // a1_b1_c1_d1_e1_f1_g1_h1
	x[2] = _mm_unpacklo_epi64(a23_b23_c23_d23, e23_f23_g23_h23); // a2_b2_c2_d2_e2_f2_g2_h2
	x[3] = _mm_unpackhi_epi64(a23_b23_c23_d23, e23_f23_g23_h23); // a3_b3_c3_d3_e3_f3_g3_h3
	x[4] = _mm_unpacklo_epi64(a45_b45_c45_d45, e45_f45_g45_h45); // a4_b4_c4_d4_e4_f4_g4_h4
	x[5] = _mm_unpackhi_epi64(a45_b45_c45_d45, e45_f45_g45_h45); // a5_b5_c5_d5_e5_f5_g5_h5
	x[6] = _mm_unpacklo_epi64(a67_b67_c67_d67, e67_f67_g67_h67); // a6_b6_c6_d6_e6_f6_g6_h6
	x[7] = _mm_unpackhi_epi64(a67_b67_c67_d67, e67_f67_g67_h67); // a7_b7_c7_d7_e7_f7_g7_h7
}


void
transpose_16(arr_m128i<16>& x)
{
	const __m128i a07_b07 = _mm_unpacklo_epi8(x[0x0], x[0x1]);
	const __m128i a8f_b8f = _mm_unpackhi_epi8(x[0x0], x[0x1]);
	const __m128i c07_d07 = _mm_unpacklo_epi8(x[0x2], x[0x3]);
	const __m128i c8f_d8f = _mm_unpackhi_epi8(x[0x2], x[0x3]);
	const __m128i e07_f07 = _mm_unpacklo_epi8(x[0x4], x[0x5]);
	const __m128i e8f_f8f = _mm_unpackhi_epi8(x[0x4], x[0x5]);
	const __m128i g07_h07 = _mm_unpacklo_epi8(x[0x6], x[0x7]);
	const __m128i g8f_h8f = _mm_unpackhi_epi8(x[0x6], x[0x7]);
	const __m128i i07_j07 = _mm_unpacklo_epi8(x[0x8], x[0x9]);
	const __m128i i8f_j8f = _mm_unpackhi_epi8(x[0x8], x[0x9]);
	const __m128i k07_l07 = _mm_unpacklo_epi8(x[0xa], x[0xb]);
	const __m128i k8f_l8f = _mm_unpackhi_epi8(x[0xa], x[0xb]);
	const __m128i m07_n07 = _mm_unpacklo_epi8(x[0xc], x[0xd]);
	const __m128i m8f_n8f = _mm_unpackhi_epi8(x[0xc], x[0xd]);
	const __m128i o07_p07 = _mm_unpacklo_epi8(x[0xe], x[0xf]);
	const __m128i o8f_p8f = _mm_unpackhi_epi8(x[0xe], x[0xf]);

	const __m128i a03_b03_c03_d03 = _mm_unpacklo_epi16(a07_b07, c07_d07);
	const __m128i a47_b47_c47_d47 = _mm_unpackhi_epi16(a07_b07, c07_d07);
	const __m128i a8b_b8b_c8b_d8b = _mm_unpacklo_epi16(a8f_b8f, c8f_d8f);
	const __m128i acf_bcf_ccf_dcf = _mm_unpackhi_epi16(a8f_b8f, c8f_d8f);
	const __m128i e03_f03_g03_h03 = _mm_unpacklo_epi16(e07_f07, g07_h07);
	const __m128i e47_f47_g47_h47 = _mm_unpackhi_epi16(e07_f07, g07_h07);
	const __m128i e8b_f8b_g8b_h8b = _mm_unpacklo_epi16(e8f_f8f, g8f_h8f);
	const __m128i ecf_fcf_gcf_hcf = _mm_unpackhi_epi16(e8f_f8f, g8f_h8f);
	const __m128i i03_j03_k03_l03 = _mm_unpacklo_epi16(i07_j07, k07_l07);
	const __m128i i47_j47_k47_l47 = _mm_unpackhi_epi16(i07_j07, k07_l07);
	const __m128i i8b_j8b_k8b_l8b = _mm_unpacklo_epi16(i8f_j8f, k8f_l8f);
	const __m128i icf_jcf_kcf_lcf = _mm_unpackhi_epi16(i8f_j8f, k8f_l8f);
	const __m128i m03_n03_o03_p03 = _mm_unpacklo_epi16(m07_n07, o07_p07);
	const __m128i m47_n47_o47_p47 = _mm_unpackhi_epi16(m07_n07, o07_p07);
	const __m128i m8b_n8b_o8b_p8b = _mm_unpacklo_epi16(m8f_n8f, o8f_p8f);
	const __m128i mcf_ncf_ocf_pcf = _mm_unpackhi_epi16(m8f_n8f, o8f_p8f);

	const __m128i a01_b01_c01_d01_e01_f01_g01_h01 = _mm_unpacklo_epi32(a03_b03_c03_d03, e03_f03_g03_h03);
	const __m128i a23_b23_c23_d23_e23_f23_g23_h23 = _mm_unpackhi_epi32(a03_b03_c03_d03, e03_f03_g03_h03);
	const __m128i i01_j01_k01_l01_m01_n01_o01_p01 = _mm_unpacklo_epi32(i03_j03_k03_l03, m03_n03_o03_p03);
	const __m128i i23_j23_k23_l23_m23_n23_o23_p23 = _mm_unpackhi_epi32(i03_j03_k03_l03, m03_n03_o03_p03);
	const __m128i a45_b45_c45_d45_e45_f45_g45_h45 = _mm_unpacklo_epi32(a47_b47_c47_d47, e47_f47_g47_h47);
	const __m128i a67_b67_c67_d67_e67_f67_g67_h67 = _mm_unpackhi_epi32(a47_b47_c47_d47, e47_f47_g47_h47);
	const __m128i i45_j45_k45_l45_m45_n45_o45_p45 = _mm_unpacklo_epi32(i47_j47_k47_l47, m47_n47_o47_p47);
	const __m128i i67_j67_k67_l67_m67_n67_o67_p67 = _mm_unpackhi_epi32(i47_j47_k47_l47, m47_n47_o47_p47);
	const __m128i a89_b89_c89_d89_e89_f89_g89_h89 = _mm_unpacklo_epi32(a8b_b8b_c8b_d8b, e8b_f8b_g8b_h8b);
	const __m128i aab_bab_cab_dab_eab_fab_gab_hab = _mm_unpackhi_epi32(a8b_b8b_c8b_d8b, e8b_f8b_g8b_h8b);
	const __m128i i89_j89_k89_l89_m89_n89_o89_p89 = _mm_unpacklo_epi32(i8b_j8b_k8b_l8b, m8b_n8b_o8b_p8b);
	const __m128i iab_jab_kab_lab_mab_nab_oab_pab = _mm_unpackhi_epi32(i8b_j8b_k8b_l8b, m8b_n8b_o8b_p8b);
	const __m128i acd_bcd_ccd_dcd_ecd_fcd_gcd_hcd = _mm_unpacklo_epi32(acf_bcf_ccf_dcf, ecf_fcf_gcf_hcf);
	const __m128i aef_bef_cef_def_eef_fef_gef_hef = _mm_unpackhi_epi32(acf_bcf_ccf_dcf, ecf_fcf_gcf_hcf);
	const __m128i icd_jcd_kcd_lcd_mcd_ncd_ocd_pcd = _mm_unpacklo_epi32(icf_jcf_kcf_lcf, mcf_ncf_ocf_pcf);
	const __m128i ief_jef_kef_lef_mef_nef_oef_pef = _mm_unpackhi_epi32(icf_jcf_kcf_lcf, mcf_ncf_ocf_pcf);

	x[0x0] = _mm_unpacklo_epi64(a01_b01_c01_d01_e01_f01_g01_h01, i01_j01_k01_l01_m01_n01_o01_p01); // a0_b0_c0_d0_e0_f0_g0_h0_i0_j0_k0_l0_m0_n0_o0_p0
	x[0x1] = _mm_unpackhi_epi64(a01_b01_c01_d01_e01_f01_g01_h01, i01_j01_k01_l01_m01_n01_o01_p01); // a1_b1_c1_d1_e1_f1_g1_h1_i1_j1_k1_l1_m1_n1_o1_p1
	x[0x2] = _mm_unpacklo_epi64(a23_b23_c23_d23_e23_f23_g23_h23, i23_j23_k23_l23_m23_n23_o23_p23); // a2_b2_c2_d2_e2_f2_g2_h2_i2_j2_k2_l2_m2_n2_o2_p2
	x[0x3] = _mm_unpackhi_epi64(a23_b23_c23_d23_e23_f23_g23_h23, i23_j23_k23_l23_m23_n23_o23_p23); // a3_b3_c3_d3_e3_f3_g3_h3_i3_j3_k3_l3_m3_n3_o3_p3
	x[0x4] = _mm_unpacklo_epi64(a45_b45_c45_d45_e45_f45_g45_h45, i45_j45_k45_l45_m45_n45_o45_p45); // a4_b4_c4_d4_e4_f4_g4_h4_i4_j4_k4_l4_m4_n4_o4_p4
	x[0x5] = _mm_unpackhi_epi64(a45_b45_c45_d45_e45_f45_g45_h45, i45_j45_k45_l45_m45_n45_o45_p45); // a5_b5_c5_d5_e5_f5_g5_h5_i5_j5_k5_l5_m5_n5_o5_p5
	x[0x6] = _mm_unpacklo_epi64(a67_b67_c67_d67_e67_f67_g67_h67, i67_j67_k67_l67_m67_n67_o67_p67); // a6_b6_c6_d6_e6_f6_g6_h6_i6_j6_k6_l6_m6_n6_o6_p6
	x[0x7] = _mm_unpackhi_epi64(a67_b67_c67_d67_e67_f67_g67_h67, i67_j67_k67_l67_m67_n67_o67_p67); // a7_b7_c7_d7_e7_f7_g7_h7_i7_j7_k7_l7_m7_n7_o7_p7
	x[0x8] = _mm_unpacklo_epi64(a89_b89_c89_d89_e89_f89_g89_h89, i89_j89_k89_l89_m89_n89_o89_p89); // a8_b8_c8_d8_e8_f8_g8_h8_i8_j8_k8_l8_m8_n8_o8_p8
	x[0x9] = _mm_unpackhi_epi64(a89_b89_c89_d89_e89_f89_g89_h89, i89_j89_k89_l89_m89_n89_o89_p89); // a9_b9_c9_d9_e9_f9_g9_h9_i9_j9_k9_l9_m9_n9_o9_p9
	x[0xa] = _mm_unpacklo_epi64(aab_bab_cab_dab_eab_fab_gab_hab, iab_jab_kab_lab_mab_nab_oab_pab); // aa_ba_ca_da_ea_fa_ga_ha_ia_ja_ka_la_ma_na_oa_pa
	x[0xb] = _mm_unpackhi_epi64(aab_bab_cab_dab_eab_fab_gab_hab, iab_jab_kab_lab_mab_nab_oab_pab); // ab_bb_cb_db_eb_fb_gb_hb_ib_jb_kb_lb_mb_nb_ob_pb
	x[0xc] = _mm_unpacklo_epi64(acd_bcd_ccd_dcd_ecd_fcd_gcd_hcd, icd_jcd_kcd_lcd_mcd_ncd_ocd_pcd); // ac_bc_cc_dc_ec_fc_gc_hc_ic_jc_kc_lc_mc_nc_oc_pc
	x[0xd] = _mm_unpackhi_epi64(acd_bcd_ccd_dcd_ecd_fcd_gcd_hcd, icd_jcd_kcd_lcd_mcd_ncd_ocd_pcd); // ad_bd_cd_dd_ed_fd_gd_hd_id_jd_kd_ld_md_nd_od_pd
	x[0xe] = _mm_unpacklo_epi64(aef_bef_cef_def_eef_fef_gef_hef, ief_jef_kef_lef_mef_nef_oef_pef); // ae_be_ce_de_ee_fe_ge_he_ie_je_ke_le_me_ne_oe_pe
	x[0xf] = _mm_unpackhi_epi64(aef_bef_cef_def_eef_fef_gef_hef, ief_jef_kef_lef_mef_nef_oef_pef); // af_bf_cf_df_ef_ff_gf_hf_if_jf_kf_lf_mf_nf_of_pf
}


template <size_t N>
inline void
transpose(arr_m128i<N>& x)
{
	static_assert(
			(N == 1) ||
			(N == 2) ||
			(N == 4) ||
			(N == 8) ||
			(N == 16)
			);

	if constexpr (N == 1)
		return; // No-op
	else if constexpr (N == 2)
		transpose_2(x);
	else if constexpr (N == 4)
		transpose_4(x);
	else if constexpr (N == 8)
		transpose_8(x);
	else if constexpr (N == 16)
		transpose_16(x);
}
