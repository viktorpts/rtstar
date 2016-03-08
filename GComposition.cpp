#include "StdAfx.h"
#include "GComposition.h"


//////////////////////////////////////////////////////////////////////////////////////
// Class <-> Color correspondence
//
// O - Blue					155,176,255
// B - Blue-white			170,191,255
// A - White to blue-white	202,215,255
// F - White				248,247,255
// G - Yellow white			255,244,234
// K - Yellow orange		255,210,161
// M - Orange red			255,204,111

CGComposition::CGComposition(void)
{
	pixel.rgbtRed = 255;
	pixel.rgbtGreen = 204;
	pixel.rgbtBlue = 111;
}

CGComposition::CGComposition(char in_class,int in_mag)
{
	int tRed, tGreen, tBlue;
	float brightness = float(11 - in_mag) / 31;	// Expressed as a factor from 0.0323 to 1
	switch (in_class) {
		case 'O':
			tRed = 155;
			tGreen = 176;
			tBlue = 255;
			break;
		case 'B':
			tRed = 170;
			tGreen = 191;
			tBlue = 255;
			break;
		case 'A':
			tRed = 202;
			tGreen = 215;
			tBlue = 255;
			break;
		case 'F':
			tRed = 248;
			tGreen = 247;
			tBlue = 255;
			break;
		case 'G':
			tRed = 255;
			tGreen = 244;
			tBlue = 234;
			break;
		case 'K':
			tRed = 255;
			tGreen = 210;
			tBlue = 161;
			break;
		case 'M':
			tRed = 255;
			tGreen = 204;
			tBlue = 111;
			break;
		default:
			tRed = 255;
			tGreen = 204;
			tBlue = 111;
	}
	pixel.rgbtRed = int(tRed * brightness);
	pixel.rgbtGreen = int(tGreen * brightness);
	pixel.rgbtBlue = int(tBlue * brightness);
}

void CGComposition::Set(char in_class,int in_mag)
{
	int tRed, tGreen, tBlue;
	float brightness = float(11 - in_mag) / 31;	// Expressed as a factor from 0.0323 to 1
	switch (in_class) {
		case 'O':
			tRed = 155;
			tGreen = 176;
			tBlue = 255;
			break;
		case 'B':
			tRed = 170;
			tGreen = 191;
			tBlue = 255;
			break;
		case 'A':
			tRed = 202;
			tGreen = 215;
			tBlue = 255;
			break;
		case 'F':
			tRed = 248;
			tGreen = 247;
			tBlue = 255;
			break;
		case 'G':
			tRed = 255;
			tGreen = 244;
			tBlue = 234;
			break;
		case 'K':
			tRed = 255;
			tGreen = 210;
			tBlue = 161;
			break;
		case 'M':
			tRed = 255;
			tGreen = 204;
			tBlue = 111;
			break;
		default:
			tRed = 255;
			tGreen = 204;
			tBlue = 111;
	}
	pixel.rgbtRed = int(tRed * brightness);
	pixel.rgbtGreen = int(tGreen * brightness);
	pixel.rgbtBlue = int(tBlue * brightness);
}

CGComposition::~CGComposition(void)
{
}
