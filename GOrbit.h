#pragma once

class CGOrbit
{
public:
	double eccentricity;	// Orbital eccentricity
	double smajor;			// Length of semimajor axis
	double inclination;		// Vertical tilt of the orbit
	double longitude;		// Longitude of the ascending node
	double periapsis;		// Orientation of the closest point of approach
	double truea;			// True anomaly at epoch 0, in radians
	double velocity;		// Tangential velocity at periapsis

	CGOrbit(void);
	~CGOrbit(void);
};
