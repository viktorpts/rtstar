#include "StdAfx.h"
#include "CartC.h"

CCartC::CCartC(void)
{
	x = 0;
	y = 0;
	z = 0;
}

CCartC::CCartC(double in_x, double in_y, double in_z)
{
	x = in_x;
	y = in_y;
	z = in_z;
}

void CCartC::Set(double in_x, double in_y, double in_z)
{
	x = in_x;
	y = in_y;
	z = in_z;
}

void CCartC::Get(double *out_x, double *out_y, double *out_z)
{
	*out_x = x;
	*out_y = y;
	*out_z = z;
}

double CCartC::Dist(const CCartC in_coord)
{
	return sqrt(pow(in_coord.x - x,2) + pow(in_coord.y - y,2) + pow(in_coord.z - z,2));
}

double CCartC::Dist(double in_x=0, double in_y=0, double in_z=0)
{
	return sqrt(pow(in_x - x,2) + pow(in_y - y,2) + pow(in_z - z,2));
}

CCartC CCartC::operator -(const CCartC &in_coord)
{
	CCartC result(this->x - in_coord.x,this->y - in_coord.y,this->z - in_coord.z);
	return result;
}

CCartC CCartC::operator +(const CCartC &in_coord)
{
	CCartC result(this->x + in_coord.x,this->y + in_coord.y,this->z + in_coord.z);
	return result;
}

CCartC::~CCartC(void)
{
}
