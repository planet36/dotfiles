# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=line-too-long
# pylint: disable=missing-class-docstring
# pylint: disable=missing-function-docstring
# pylint: disable=missing-module-docstring
# pylint: disable=no-else-return
# pylint: disable=too-many-arguments
# pylint: disable=too-many-instance-attributes
# pylint: disable=too-many-locals

import math

class Ellipsoid:

	def __init__(self, _a, _f_recip, _GM = 3.986004418E14, _omega = 7.292115E-5):

		# defining parameters
		a = _a # semi-major axis (equatorial radius of the earth) (meters)
		f = 1 / _f_recip # (a-b)/a # flattening factor of the earth
		GM = _GM # geocentric gravitational constant (m^3/s^2)
		omega = _omega # nominal mean angular velocity of the earth (rad/s)

		# derived geometric constants
		b = a*(1-f) # semi-minor axis (meters)
		a2 = a*a # a squared
		b2 = b*b # b squared
		fp = f/(1-f) # (a-b)/b # second flattening
		n = f/(2-f) # (a-b)/(a+b) # third flattening
		e2 = f*(2-f) # (a2-b2)/a2 # first eccentricity squared
		e = math.sqrt(e2) # first eccentricity
		ep2 = e2/(1-e2) # (a2-b2)/b2 # second eccentricity squared
		ep = math.sqrt(ep2) # second eccentricity
		epp2 = e2/(2-e2) # (a2-b2)/(a2+b2) # third eccentricity squared
		epp = math.sqrt(epp2) # third eccentricity
		c2 = a2 - b2 # linear eccentricity squared
		c = math.sqrt(c2) # linear eccentricity
		alpha = math.asin(e) # angular eccentricity # acos(b/a)

		# derived physical constants
		gamma_e = 9.7803253359 # normal gravity at the equator (on the ellipsoid) (m/s^2)
		gamma_p = 9.8321849379 # normal gravity at the poles (on the ellipsoid) (m/s^2)
		k = (1 - f) * gamma_p / gamma_e - 1 # Somigliana's Formula - normal gravity formula constant
		m = omega * omega * a2 * b / GM # normal gravity formula constant

		self.a       = a
		self.f       = f
		self.b       = b
		self.a2      = a2
		self.b2      = b2
		self.fp      = fp
		self.n       = n
		self.e2      = e2
		self.e       = e
		self.ep2     = ep2
		self.ep      = ep
		self.epp2    = epp2
		self.epp     = epp
		self.c2      = c2
		self.c       = c
		self.alpha   = alpha
		self.gamma_e = gamma_e
		self.gamma_p = gamma_p
		self.k       = k
		self.m       = m

	def get_Rn(self, sin_lat):
		d2 = 1 - self.e2 * sin_lat * sin_lat
		d = math.sqrt(d2)
		return self.a / d

	def get_R(self, sin_lat):
		return self.get_Rn(sin_lat) * math.sqrt(1 - self.e2 * sin_lat * sin_lat * (2 - self.e2))

	def get_Rm(self, sin_lat):
		d2 = 1 - self.e2 * sin_lat * sin_lat
		d = math.sqrt(d2)
		return self.a * (1 - self.e2) / (d2 * d)


def geodetic_to_ecef(ell: Ellipsoid, lat_deg: float, lon_deg: float, ht: float) -> tuple:

	lat_rad = math.radians(lat_deg)
	lon_rad = math.radians(lon_deg)

	sin_lat = math.sin(lat_rad)
	cos_lat = math.cos(lat_rad)

	sin_lon = math.sin(lon_rad)
	cos_lon = math.cos(lon_rad)

	Rn = ell.get_Rn(sin_lat)

	x = (Rn + ht) * cos_lat * cos_lon
	y = (Rn + ht) * cos_lat * sin_lon
	z = (Rn * (1 - ell.e2) + ht) * sin_lat

	return (x, y, z)


def ecef_to_geodetic(ell: Ellipsoid, x: float, y: float, z: float) -> tuple:
	'''
D. K. Olson, "Converting Earth-centered, Earth-fixed coordinates to geodetic coordinates," in IEEE Transactions on Aerospace and Electronic Systems, vol. 32, no. 1, pp. 473-476, Jan. 1996, doi: 10.1109/7.481290.
URL: https://ieeexplore.ieee.org/document/481290

Converted to Python and modified by Steven Ward.  No rights reserved.
'''

	w2 = x * x + y * y
	w = math.sqrt(w2)
	z2 = z * z
	lon_rad = math.atan2(y, x)

	a1 = ell.a * ell.e2
	a2 = a1 * a1
	a3 = a1 * ell.e2 / 2
	a4 = 2.5 * a2
	a5 = a1 + a3
	#a6 = (1 - ell.e2)

	r2 = w2 + z2
	r = math.sqrt(r2)

	s2 = z2 / r2
	c2 = w2 / r2
	u = a2 / r
	v = a3 - a4 / r

	s = 0
	c = 0
	ss = 0

	# cos(45 deg)^2 == 0.5
	if c2 > 0.5: # Equatorial
		s = (z / r) * (1 + c2 * (a1 + u + s2 * v) / r)
		lat_rad = math.asin(s)
		ss = s * s
		c = math.sqrt(1 - ss)
	else: # Polar
		c = (w / r) * (1 - s2 * (a5 - u - c2 * v) / r)
		lat_rad = math.acos(c)
		ss = 1 - c * c
		s = math.sqrt(ss)

		if z < 0:
			lat_rad = -lat_rad
			s = -s

	d2 = 1 - ell.e2 * ss
	Rn = ell.a / math.sqrt(d2)
	Rm = (1 - ell.e2) * Rn / d2
	rf = (1 - ell.e2) * Rn
	u = w - Rn * c
	v = z - rf * s
	f = c * u + s * v
	m = c * v - s * u
	p = m / (Rm + f)

	lat_rad += p

	ht = f + m * p / 2

	return (math.degrees(lat_rad), math.degrees(lon_rad), ht)


'''
Source:
NGA.STND.0036_1.0.0_WGS84 2014-07-08

Appendix C.1
Reference Ellipsoid Names and Constants
Used for Datum Transformations*

* Refer to Appendices D, E, and F.
'''
WGS84 = Ellipsoid(6_378_137.0, 298.257223563)
