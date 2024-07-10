// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// typedefs for GCC machine modes
/**
\file
\author Steven Ward
\sa https://gcc.gnu.org/onlinedocs/gccint/Machine-Modes.html
*/

// Generated by "generate-gcc-machine-modes-typedefs.py" on 2024-07-10T17:22:07+00:00
// system information: Linux-6.9.8-arch1-1-x86_64-with-glibc2.39

#pragma once

// NO bit (BI)
// YES quarter integer (QI)
#define HAVE_QI_MODE
// YES half integer (HI)
#define HAVE_HI_MODE
// NO single partial integer (PSI)
// YES single integer (SI)
#define HAVE_SI_MODE
// NO double partial integer (PDI)
// YES double integer (DI)
#define HAVE_DI_MODE
// YES tetra integer (TI)
#define HAVE_TI_MODE
// NO octa integer (OI)
// NO hexadeca integer (XI)
// NO quarter binary float (QF)
// YES half binary float (HF)
#define HAVE_HF_MODE
// NO three-quarter binary float (TQF)
// YES single binary float (SF)
#define HAVE_SF_MODE
// YES double binary float (DF)
#define HAVE_DF_MODE
// YES extended binary float (XF)
#define HAVE_XF_MODE
// YES tetra binary float (TF)
#define HAVE_TF_MODE
// YES single decimal float (SD)
#define HAVE_SD_MODE
// YES double decimal float (DD)
#define HAVE_DD_MODE
// YES tetra decimal float (TD)
#define HAVE_TD_MODE
// NO quarter signed fractional (QQ)
// NO half signed fractional (HQ)
// NO single signed fractional (SQ)
// NO double signed fractional (DQ)
// NO tetra signed fractional (TQ)
// NO quarter unsigned fractional (UQQ)
// NO half unsigned fractional (UHQ)
// NO single unsigned fractional (USQ)
// NO double unsigned fractional (UDQ)
// NO tetra unsigned fractional (UTQ)
// NO half signed accumulator (HA)
// NO single signed accumulator (SA)
// NO double signed accumulator (DA)
// NO tetra signed accumulator (TA)
// NO half unsigned accumulator (UHA)
// NO single unsigned accumulator (USA)
// NO double unsigned accumulator (UDA)
// NO tetra unsigned accumulator (UTA)
// NO quarter complex binary float (QC)
// YES half complex binary float (HC)
#define HAVE_HC_MODE
// YES single complex binary float (SC)
#define HAVE_SC_MODE
// YES double complex binary float (DC)
#define HAVE_DC_MODE
// YES extended complex binary float (XC)
#define HAVE_XC_MODE
// YES tetra complex binary float (TC)
#define HAVE_TC_MODE
// YES quarter complex integer (CQI)
#define HAVE_CQI_MODE
// YES half complex integer (CHI)
#define HAVE_CHI_MODE
// YES single complex integer (CSI)
#define HAVE_CSI_MODE
// YES double complex integer (CDI)
#define HAVE_CDI_MODE
// YES tetra complex integer (CTI)
#define HAVE_CTI_MODE
// NO octa complex integer (COI)

#ifdef HAVE_BI_MODE
// bit (BI)
using bit = int [[gnu::mode(BI)]];
#endif

#ifdef HAVE_QI_MODE
// quarter integer (QI)
using int8 = int [[gnu::mode(QI)]];
using uint8 = unsigned [[gnu::mode(QI)]];
#endif

#ifdef HAVE_HI_MODE
// half integer (HI)
using int16 = int [[gnu::mode(HI)]];
using uint16 = unsigned [[gnu::mode(HI)]];
#endif

#ifdef HAVE_PSI_MODE
// single partial integer (PSI)
using pint32 = int [[gnu::mode(PSI)]];
using puint32 = unsigned [[gnu::mode(PSI)]];
#endif

#ifdef HAVE_SI_MODE
// single integer (SI)
using int32 = int [[gnu::mode(SI)]];
using uint32 = unsigned [[gnu::mode(SI)]];
#endif

#ifdef HAVE_PDI_MODE
// double partial integer (PDI)
using pint64 = int [[gnu::mode(PDI)]];
using puint64 = unsigned [[gnu::mode(PDI)]];
#endif

#ifdef HAVE_DI_MODE
// double integer (DI)
using int64 = int [[gnu::mode(DI)]];
using uint64 = unsigned [[gnu::mode(DI)]];
#endif

#ifdef HAVE_TI_MODE
// tetra integer (TI)
using int128 = int [[gnu::mode(TI)]];
using uint128 = unsigned [[gnu::mode(TI)]];
#endif

#ifdef HAVE_OI_MODE
// octa integer (OI)
using int256 = int [[gnu::mode(OI)]];
using uint256 = unsigned [[gnu::mode(OI)]];
#endif

#ifdef HAVE_XI_MODE
// hexadeca integer (XI)
using int512 = int [[gnu::mode(XI)]];
using uint512 = unsigned [[gnu::mode(XI)]];
#endif

#ifdef HAVE_QF_MODE
// quarter binary float (QF)
using bin8 = float [[gnu::mode(QF)]];
#endif

#ifdef HAVE_HF_MODE
// half binary float (HF)
using bin16 = float [[gnu::mode(HF)]];
#endif

#ifdef HAVE_TQF_MODE
// three-quarter binary float (TQF)
using bin24 = float [[gnu::mode(TQF)]];
#endif

#ifdef HAVE_SF_MODE
// single binary float (SF)
using bin32 = float [[gnu::mode(SF)]];
#endif

#ifdef HAVE_DF_MODE
// double binary float (DF)
using bin64 = float [[gnu::mode(DF)]];
#endif

#ifdef HAVE_XF_MODE
// extended binary float (XF)
using bin80 = float [[gnu::mode(XF)]];
#endif

#ifdef HAVE_TF_MODE
// tetra binary float (TF)
using bin128 = float [[gnu::mode(TF)]];
#endif

#ifdef HAVE_SD_MODE
// single decimal float (SD)
using dec32 = float [[gnu::mode(SD)]];
#endif

#ifdef HAVE_DD_MODE
// double decimal float (DD)
using dec64 = float [[gnu::mode(DD)]];
#endif

#ifdef HAVE_TD_MODE
// tetra decimal float (TD)
using dec128 = float [[gnu::mode(TD)]];
#endif

#ifdef HAVE_QQ_MODE
// quarter signed fractional (QQ)
using frac8 = int [[gnu::mode(QQ)]];
#endif

#ifdef HAVE_HQ_MODE
// half signed fractional (HQ)
using frac16 = int [[gnu::mode(HQ)]];
#endif

#ifdef HAVE_SQ_MODE
// single signed fractional (SQ)
using frac32 = int [[gnu::mode(SQ)]];
#endif

#ifdef HAVE_DQ_MODE
// double signed fractional (DQ)
using frac64 = int [[gnu::mode(DQ)]];
#endif

#ifdef HAVE_TQ_MODE
// tetra signed fractional (TQ)
using frac128 = int [[gnu::mode(TQ)]];
#endif

#ifdef HAVE_UQQ_MODE
// quarter unsigned fractional (UQQ)
using ufrac8 = unsigned [[gnu::mode(UQQ)]];
#endif

#ifdef HAVE_UHQ_MODE
// half unsigned fractional (UHQ)
using ufrac16 = unsigned [[gnu::mode(UHQ)]];
#endif

#ifdef HAVE_USQ_MODE
// single unsigned fractional (USQ)
using ufrac32 = unsigned [[gnu::mode(USQ)]];
#endif

#ifdef HAVE_UDQ_MODE
// double unsigned fractional (UDQ)
using ufrac64 = unsigned [[gnu::mode(UDQ)]];
#endif

#ifdef HAVE_UTQ_MODE
// tetra unsigned fractional (UTQ)
using ufrac128 = unsigned [[gnu::mode(UTQ)]];
#endif

#ifdef HAVE_HA_MODE
// half signed accumulator (HA)
using accum16 = int [[gnu::mode(HA)]];
#endif

#ifdef HAVE_SA_MODE
// single signed accumulator (SA)
using accum32 = int [[gnu::mode(SA)]];
#endif

#ifdef HAVE_DA_MODE
// double signed accumulator (DA)
using accum64 = int [[gnu::mode(DA)]];
#endif

#ifdef HAVE_TA_MODE
// tetra signed accumulator (TA)
using accum128 = int [[gnu::mode(TA)]];
#endif

#ifdef HAVE_UHA_MODE
// half unsigned accumulator (UHA)
using uaccum16 = unsigned [[gnu::mode(UHA)]];
#endif

#ifdef HAVE_USA_MODE
// single unsigned accumulator (USA)
using uaccum32 = unsigned [[gnu::mode(USA)]];
#endif

#ifdef HAVE_UDA_MODE
// double unsigned accumulator (UDA)
using uaccum64 = unsigned [[gnu::mode(UDA)]];
#endif

#ifdef HAVE_UTA_MODE
// tetra unsigned accumulator (UTA)
using uaccum128 = unsigned [[gnu::mode(UTA)]];
#endif

#ifdef HAVE_QC_MODE
// quarter complex binary float (QC)
using cmplx_bin8 = _Complex float [[gnu::mode(QC)]];
#endif

#ifdef HAVE_HC_MODE
// half complex binary float (HC)
using cmplx_bin16 = _Complex float [[gnu::mode(HC)]];
#endif

#ifdef HAVE_SC_MODE
// single complex binary float (SC)
using cmplx_bin32 = _Complex float [[gnu::mode(SC)]];
#endif

#ifdef HAVE_DC_MODE
// double complex binary float (DC)
using cmplx_bin64 = _Complex float [[gnu::mode(DC)]];
#endif

#ifdef HAVE_XC_MODE
// extended complex binary float (XC)
using cmplx_bin80 = _Complex float [[gnu::mode(XC)]];
#endif

#ifdef HAVE_TC_MODE
// tetra complex binary float (TC)
using cmplx_bin128 = _Complex float [[gnu::mode(TC)]];
#endif

#ifdef HAVE_CQI_MODE
// quarter complex integer (CQI)
using cmplx_int8 = _Complex int [[gnu::mode(CQI)]];
using cmplx_uint8 = _Complex unsigned [[gnu::mode(CQI)]];
#endif

#ifdef HAVE_CHI_MODE
// half complex integer (CHI)
using cmplx_int16 = _Complex int [[gnu::mode(CHI)]];
using cmplx_uint16 = _Complex unsigned [[gnu::mode(CHI)]];
#endif

#ifdef HAVE_CSI_MODE
// single complex integer (CSI)
using cmplx_int32 = _Complex int [[gnu::mode(CSI)]];
using cmplx_uint32 = _Complex unsigned [[gnu::mode(CSI)]];
#endif

#ifdef HAVE_CDI_MODE
// double complex integer (CDI)
using cmplx_int64 = _Complex int [[gnu::mode(CDI)]];
using cmplx_uint64 = _Complex unsigned [[gnu::mode(CDI)]];
#endif

#ifdef HAVE_CTI_MODE
// tetra complex integer (CTI)
using cmplx_int128 = _Complex int [[gnu::mode(CTI)]];
using cmplx_uint128 = _Complex unsigned [[gnu::mode(CTI)]];
#endif

#ifdef HAVE_COI_MODE
// octa complex integer (COI)
using cmplx_int256 = _Complex int [[gnu::mode(COI)]];
using cmplx_uint256 = _Complex unsigned [[gnu::mode(COI)]];
#endif
