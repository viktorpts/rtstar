#include "StdAfx.h"
#include "Image.h"
#include <math.h>

CImage::CImage(void)
{
	// Initialize canvas with default resolution
	hres = HRES;
	vres = VRES;
	resolution = hres * vres;
	canvas = new RGBTRIPLE[resolution];
	// Fill canvas with black
	for (int i=0;i<resolution;i++) {
		canvas[i].rgbtRed = 0;
		canvas[i].rgbtGreen = 0;
		canvas[i].rgbtBlue = 0;
	}
}

CImage::CImage(int in_hres, int in_vres)
{
	// Initialize canvas with inputted resolution
	hres = in_hres;
	vres = in_vres;
	resolution = hres * vres;
	canvas = new RGBTRIPLE[resolution];
	// Fill canvas with black
	for (int i=0;i<resolution;i++) {
		canvas[i].rgbtRed = 0;
		canvas[i].rgbtGreen = 0;
		canvas[i].rgbtBlue = 0;
	}
}

CImage::~CImage(void)
{
	for (int i=0;i<resolution;i++) {
		delete [] canvas;
	}
}