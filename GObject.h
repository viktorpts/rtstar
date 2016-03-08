#include "data.h"

#pragma once


class CGObject
{
	double ID;
	int magnitude;
	double position;
	double mod;
	CGComposition composition;			// *** Subject to change! ***	
							// Object brightness and apparent color; will later be replaced
							// by a set of parameters, defining mass and composition

	/* Main orbital elements :: Replaced by it's own class for easier transfer */

	CGOrbit orbit;

	/* Functions to define orbital elements */

	void SetMagnitude();	// *** Subject to change! ***
	void SetColor();		// *** Subject to change! ***

	void SetEcc();
	void SetSmajor();
	void SetIncl();
	void SetLong();
	void SetPeri();
	void SetTruea();
	void SetVelocity();

public:
	void SetAnomaly(const double);
	void Generate();
	void Generate(const double in_ID);

	RGBTRIPLE GetColor();					// Returns an RGB triple
	CGOrbit GetElements();					// Get orbital elements at epoch 0
	CGOrbit GetElements(const double in_time);		// Orbital elements at given epoch
	CCartC GetCartesian(void);					// Current position
	CCartC GetCartesian(const double in_time);	// Position at given time

	void NearRadii(double range, double *min_ID, double *max_ID, double *min_HID, double *max_HID);
	//void NearInclination(double range, double *min_incl, double *max_incl);

	CGObject(void);
	CGObject(double in_ID);
	~CGObject(void);
};
