#pragma once

class CCartC
{
public:
	double x,y,z;

	void Set(double in_x, double in_y, double in_z);
	void Get(double *out_x, double *out_y, double *out_z);

	double Dist(const CCartC in_coord);
	double Dist(double in_x, double in_y, double in_z);

	CCartC operator-(const CCartC&);
	CCartC operator+(const CCartC&);

	CCartC(void);
	CCartC(double in_x, double in_y, double in_z);
	~CCartC(void);
};
