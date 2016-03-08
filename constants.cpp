#include "stdafx.h"
#include "constants.h"
#include <math.h>

// IMPORTANT!! Expressed in universal units, each of these constants equals 1
// The following figures are for conversion purposes only


inline double ucc()
{
	return 299792458;
}

inline double ucc(int power)
{
	return 299792458 * pow(10.0,power);
}

inline double ucG()
{
	return 6.67428e-11;
}

inline double ucG(int power)
{
	return 6.67428e-11 * pow(10.0,power);
}

inline double uch()
{
	return 6.62606896e-34;
}

inline double uch(int power)
{
	return 6.62606896e-34 * pow(10.0,power);
}

inline double ucm()
{
	return 1.256637061e-6;
}

inline double ucm(int power)
{
	return 1.256637061e-6 * pow(10.0,power);
}

inline double uce()
{
	return 1.602176487e-19;
}

inline double uce(int power)
{
	return 1.602176487e-19 * pow(10.0,power);
}

// Conversion of SI units to universal units

double LYtoL(double LY)
{
	return LY * ucc() * 31557600 / sqrt(ucG() * uch() / pow(ucc(),3.0));
}

double LtoLY(double L)
{
	return L / (ucc() * 31557600) * sqrt(ucG() * uch() / pow(ucc(),3.0));
}