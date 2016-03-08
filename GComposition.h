#pragma once

class CGComposition
{
public:
	RGBTRIPLE pixel;

	void Set(char,int);

	CGComposition(void);
	CGComposition(char,int);
	~CGComposition(void);
};
