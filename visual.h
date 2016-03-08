#include "Image.h"

#pragma once


void RotatePoint(double* x, double* y, double* z, double rx, double ry, double rz);
void RotatePointX(double* x, double* y, double* z, double rx);
COLORREF AdjustColor(COLORREF color, RGBTRIPLE add, float ratio);