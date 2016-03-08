#include "StdAfx.h"
#include "visual.h"
#include <math.h>


void RotatePoint(double* x, double* y, double* z, double rx, double ry, double rz)
{
	// Initialize the rotation matrix
	double rot_matrix[4][4];
	rot_matrix[0][0] = 1;
	rot_matrix[0][1] = 0;
	rot_matrix[0][2] = 0;
	rot_matrix[0][3] = 0;
	rot_matrix[1][0] = 0;
	rot_matrix[1][1] = cos(rx);
	rot_matrix[1][2] = -sin(rx);
	rot_matrix[1][3] = 0;
	rot_matrix[2][0] = 0;
	rot_matrix[2][1] = sin(rx);
	rot_matrix[2][2] = cos(rx);
	rot_matrix[2][3] = 0;
	rot_matrix[3][0] = 0;
	rot_matrix[3][1] = 0;
	rot_matrix[3][2] = 0;
	rot_matrix[3][3] = 1;

	// Rotated coordinates

	double x_rotated = rot_matrix[0][0] * *x + rot_matrix[1][0] * *y + rot_matrix[2][0] * *z + rot_matrix[3][0];
	double y_rotated = rot_matrix[0][1] * *x + rot_matrix[1][1] * *y + rot_matrix[2][1] * *z + rot_matrix[3][1];
	double z_rotated = rot_matrix[0][2] * *x + rot_matrix[1][2] * *y + rot_matrix[2][2] * *z + rot_matrix[3][2];
	*x = x_rotated;
	*y = y_rotated;
	*z = z_rotated;
}

void RotatePointX(double* x, double* y, double* z, double rx)
{
	// Initialize the rotation matrix
	double rot_matrix[4][4];
	rot_matrix[0][0] = 1;
	rot_matrix[0][1] = 0;
	rot_matrix[0][2] = 0;
	rot_matrix[0][3] = 0;
	rot_matrix[1][0] = 0;
	rot_matrix[1][1] = cos(rx);
	rot_matrix[1][2] = -sin(rx);
	rot_matrix[1][3] = 0;
	rot_matrix[2][0] = 0;
	rot_matrix[2][1] = sin(rx);
	rot_matrix[2][2] = cos(rx);
	rot_matrix[2][3] = 0;
	rot_matrix[3][0] = 0;
	rot_matrix[3][1] = 0;
	rot_matrix[3][2] = 0;
	rot_matrix[3][3] = 1;

	// Rotated coordinates

	double x_rotated = rot_matrix[0][0] * *x + rot_matrix[1][0] * *y + rot_matrix[2][0] * *z + rot_matrix[3][0];
	double y_rotated = rot_matrix[0][1] * *x + rot_matrix[1][1] * *y + rot_matrix[2][1] * *z + rot_matrix[3][1];
	double z_rotated = rot_matrix[0][2] * *x + rot_matrix[1][2] * *y + rot_matrix[2][2] * *z + rot_matrix[3][2];
	*x = x_rotated;
	*y = y_rotated;
	*z = z_rotated;
}

COLORREF AdjustColor(COLORREF color, RGBTRIPLE add, float ratio) {
	BYTE red, green, blue;
	int c1, c2;

	// Red
	c1 = GetRValue(color);
	c2 = int(add.rgbtRed * ratio);
	if((c1+c2) > 255) red = 255;
	else red = BYTE(c1+c2);

	// Green
	c1 = GetGValue(color);
	c2 = int(add.rgbtGreen * ratio);
	if((c1+c2) > 255) green = 255;
	else green = BYTE(c1+c2);

	// Blue
	c1 = GetBValue(color);
	c2 = int(add.rgbtBlue * ratio);
	if((c1+c2) > 255) blue = 255;
	else blue = BYTE(c1+c2);
	
	return RGB(red,green,blue);
}