// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// angle utilities
/**
\file
\author Steven Ward
*/

#pragma once

#include "math-const.hpp"

#include <cmath>

/// milliradians per radian
constexpr int mrad_per_rad = 1'000;

/// radians per revolution
template <typename T>
requires std::is_floating_point_v<T>
constexpr T rad_per_rev = M_2_pi<T>;

/// degrees per revolution
constexpr int deg_per_rev = 360;

/// arcminutes per degree
constexpr int arcmin_per_deg = 60;

/// arcseconds per arcminute
constexpr int arcsec_per_arcmin = 60;

/// degrees per radian
template <typename T>
requires std::is_floating_point_v<T>
constexpr T deg_per_rad = 180 / M_pi<T>;

/// convert to radians from milliradians
template <typename T>
requires std::is_floating_point_v<T>
constexpr T rad_from_mrad(const T x_mrad)
{
	return x_mrad / mrad_per_rad;
}

/// convert to milliradians from radians
template <typename T>
requires std::is_floating_point_v<T>
constexpr T mrad_from_rad(const T x_rad)
{
	return mrad_per_rad * x_rad;
}

/// convert to revolutions from radians
template <typename T>
requires std::is_floating_point_v<T>
constexpr T rev_from_rad(const T x_rad)
{
	return x_rad / rad_per_rev<T>;
}

/// convert to radians from revolutions
template <typename T>
requires std::is_floating_point_v<T>
constexpr T rad_from_rev(const T x_rev)
{
	return rad_per_rev<T> * x_rev;
}

/// convert to revolutions from degrees
template <typename T>
requires std::is_floating_point_v<T>
constexpr T rev_from_deg(const T x_deg)
{
	return x_deg / deg_per_rev;
}

/// convert to degrees from revolutions
template <typename T>
requires std::is_floating_point_v<T>
constexpr T deg_from_rev(const T x_rev)
{
	return deg_per_rev * x_rev;
}

/// convert to degrees from arcminutes
template <typename T>
requires std::is_floating_point_v<T>
constexpr T deg_from_arcmin(const T x_arcmin)
{
	return x_arcmin / arcmin_per_deg;
}

/// convert to arcminutes from degrees
template <typename T>
requires std::is_floating_point_v<T>
constexpr T arcmin_from_deg(const T x_deg)
{
	return arcmin_per_deg * x_deg;
}

/// convert to arcminutes from arcseconds
template <typename T>
requires std::is_floating_point_v<T>
constexpr T arcmin_from_arcsec(const T x_arcsec)
{
	return x_arcsec / arcsec_per_arcmin;
}

/// convert to arcseconds from arcminutes
template <typename T>
requires std::is_floating_point_v<T>
constexpr T arcsec_from_arcmin(const T x_arcmin)
{
	return arcsec_per_arcmin * x_arcmin;
}

/// convert to radians from degrees
template <typename T>
requires std::is_floating_point_v<T>
constexpr T rad_from_deg(const T x_deg)
{
	return x_deg / deg_per_rad<T>;
}

/// convert to degrees from radians
template <typename T>
requires std::is_floating_point_v<T>
constexpr T deg_from_rad(const T x_rad)
{
	return deg_per_rad<T> * x_rad;
}

/// convert from degrees to degees and arcminutes
/**
\note \a arcmin will have the same sign as \a deg if the angle is not zero
\param[in] x_deg the angle (degrees)
\param[out] deg (whole number) degrees
\param[out] arcmin (decimal) arcminutes
*/
template <typename T>
requires std::is_floating_point_v<T>
constexpr void deg_to_dm(const T x_deg, T& deg, T& arcmin)
{
	T tmp = x_deg;
	deg = std::trunc(tmp);

	tmp = arcmin_from_deg(tmp - deg);
	arcmin = tmp;
}

/// convert from degrees to degees, arcminutes, and arcseconds
/**
\note \a arcmin and \a arcsec will have the same sign as \a deg if the angle is not zero
\param[in] x_deg the angle (degrees)
\param[out] deg (whole number) degrees
\param[out] arcmin (whole number) arcminutes
\param[out] arcsec (decimal) arcseconds
*/
template <typename T>
requires std::is_floating_point_v<T>
constexpr void deg_to_dms(const T x_deg, T& deg, T& arcmin, T& arcsec)
{
	T tmp = x_deg;
	deg = std::trunc(tmp);

	tmp = arcmin_from_deg(tmp - deg);
	arcmin = std::trunc(tmp);

	tmp = arcsec_from_arcmin(tmp - arcmin);
	arcsec = tmp;
}

/// convert to degrees from degrees and arcminutes
/**
\param[in] deg (whole number) degrees
\param[in] arcmin (decimal) arcminutes
\return (decimal) degrees
*/
template <typename T>
requires std::is_floating_point_v<T>
constexpr T deg_from_dm(const T deg, const T arcmin)
{
	return deg + deg_from_arcmin(arcmin);
}

/// convert to degrees from degrees, arcminutes, and arcseconds
/**
\param[in] deg (whole number) degrees
\param[in] arcmin (whole number) arcminutes
\param[in] arcsec (decimal) arcseconds
\return (decimal) degrees
*/
template <typename T>
requires std::is_floating_point_v<T>
constexpr T deg_from_dms(const T deg, const T arcmin, const T arcsec)
{
	return deg_from_dm(deg, arcmin + arcmin_from_arcsec(arcsec));
}
