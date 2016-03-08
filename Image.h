#pragma once

// Default resolution, keep shit tidy and don't move it to another file
#define HRES 600
#define VRES 600

class CImage
{
	int hres, vres;
	int resolution;
	RGBTRIPLE *canvas;
public:
	

	CImage(void);
	CImage(int in_hres, int in_vres);
	~CImage(void);
};