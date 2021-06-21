# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=missing-class-docstring
# pylint: disable=missing-function-docstring
# pylint: disable=missing-module-docstring
# pylint: disable=too-many-instance-attributes
# pylint: disable=too-many-locals

from math import sqrt, asin

class Ellipsoid:

	def __init__(self, _a, _f_recip):

		a = _a ## semi-major axis (equatorial radius of the earth) (meters)
		f = 1 / _f_recip ## (a-b)/a ## flattening factor of the earth
		b = a*(1-f) ## semi-minor axis (meters)
		a2 = a*a ## a squared
		b2 = b*b ## b squared
		fp = f/(1-f) ## (a-b)/b ## second flattening
		n = f/(2-f) ## (a-b)/(a+b) ## third flattening
		e2 = f*(2-f) ## (a2-b2)/a2 ## first eccentricity squared
		e = sqrt(e2) ## first eccentricity
		ep2 = e2/(1-e2) ## (a2-b2)/b2 ## second eccentricity squared
		ep = sqrt(ep2) ## second eccentricity
		epp2 = e2/(2-e2) ## (a2-b2)/(a2+b2) ## third eccentricity squared
		epp = sqrt(epp2) ## third eccentricity
		c2 = a2 - b2 ## linear eccentricity squared
		c = sqrt(c2) ## linear eccentricity
		alpha = asin(e) ## angular eccentricity ## acos(b/a)

		self.a     = a
		self.f     = f
		self.b     = b
		self.a2    = a2
		self.b2    = b2
		self.fp    = fp
		self.n     = n
		self.e2    = e2
		self.e     = e
		self.ep2   = ep2
		self.ep    = ep
		self.epp2  = epp2
		self.epp   = epp
		self.c2    = c2
		self.c     = c
		self.alpha = alpha

	def get_Rn(self, sin_lat):
		d2 = 1 - self.e2 * sin_lat * sin_lat
		d = sqrt(d2)
		return self.a / d

	def get_R(self, sin_lat):
		return self.get_Rn(sin_lat) * sqrt(1 - self.e2 * sin_lat * sin_lat * (2 - self.e2))

	def get_Rm(self, sin_lat):
		d2 = 1 - self.e2 * sin_lat * sin_lat
		d = sqrt(d2)
		return self.a * (1 - self.e2) / (d2 * d)

'''
Source:
NGA.STND.0036_1.0.0_WGS84 2014-07-08

Appendix C.1
Reference Ellipsoid Names and Constants
Used for Datum Transformations*

* Refer to Appendices D, E, and F.
'''
WGS84 = Ellipsoid(6_378_137.0, 298.257223563)
