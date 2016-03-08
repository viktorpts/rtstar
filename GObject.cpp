#include "StdAfx.h"
#include "GObject.h"
#include <time.h>


/*
		:: NOTES ::

	- All angular parameters are universal and are not dependant on the units used
	- THIS VERSION OF THE FILE: Orbit generation is based on algorithms tailored for
		each part of the galaxy and not on subsequent modification
	- This class will become virtual; derived classes will be star and nebulae
	- Longitude, periapsis argument and true anomaly are all generated in the same
		function, to make region generation easier

	- 26.Dec.2011 - Changed brightness of starss in the galactic arms to be greater
		Number of stars in galactic arms reduced to match rest of disc

*/

//////////////////////////////////////////////////////////////////////////////////////
// Constructors

CGObject::CGObject(void)
{
	// Initialize random ID
	srand( (int) time(NULL) );
	ID = rand() % int(STARCOUNT);
	position = ID/STARCOUNT;
	mod = fmod(ID,2);
	if (mod) mod = ID;
	else mod = -ID;
	while (abs(mod) > 100) mod /= 100;
}

CGObject::CGObject(double in_ID)
{
	ID = in_ID;
	position = ID/STARCOUNT;
	mod = fmod(ID,2);
	if (mod) mod = ID;
	else mod = -ID;
	while (abs(mod) > 100) mod /= 100;
}


//////////////////////////////////////////////////////////////////////////////////////
// Initialization

void CGObject::Generate()
{
	SetSmajor();
	SetVelocity();
	SetEcc();
	SetIncl();
	SetLong();
	SetPeri();
	SetTruea();
	SetMagnitude();
	SetColor();
}

void CGObject::Generate(const double in_ID)
{
	ID = in_ID;
	SetSmajor();
	SetVelocity();
	SetEcc();
	SetIncl();
	SetLong();
	SetPeri();
	SetTruea();
	SetMagnitude();
	SetColor();
}

void CGObject::SetMagnitude()
{
	magnitude = (int) fmod(abs(ID*SEED),21.0) - 10;		// WARNING: Formula should be -10 in the release!!!

	// Halo is brighter
	if ( position > GSHALO && position <= GSHALO+GSBULGE ) {
		float mp = 2/(position/(GSHALO-GSBULGE));
		if(mp>1) mp=1;
		magnitude += int(10*mp);
	}

	// Stars in the galactic arms are younger and brighter
	if ( position > GSHALO + 0.8*GSBULGE ) {
		// Galactic arms; +0.8*GSBULGE, because the arms protrude into the bulge, for
		// smoother transition

		double angle = fmod(orbit.truea + orbit.periapsis + orbit.longitude,PI*2);
			// Make the angle change between 0<a<2*PI
		double a=0.3;	// Unknown variable; possibly rotation
		double b=0.3;	// Winding of the spiral; smaller number means more wound up spiral
		double spiral = log(orbit.smajor/a)/b;
			// Representation of a logarithmic spiral

		// Attempt correction
		spiral = fmod(spiral,PI*4);
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
		spiral+=PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
		spiral+=PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
		spiral+=PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;

		angle+=2*PI;
		spiral-=3*PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
		spiral+=PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
		spiral+=PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
		spiral+=PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;

		angle+=2*PI;
		spiral-=3*PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
		spiral+=PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
		spiral+=PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
		spiral+=PI/2;
		if(angle > spiral && angle < spiral+GARM) magnitude += 10;
	}

	/*
	if (fmod(ID,STARCOUNT/VISBAR + 1) < int(STARCOUNT/VISBAR))
		// Stars beyond the barrier are fainter
		magnitude+=10;
	//*/
}

void CGObject::SetColor()
{
	int sclass = int( fmod(ID*PRIMESEED,1e4) + 1 );
	if (sclass >= 1e4)						// 0.01%
		composition.Set('O',magnitude);
	else if (sclass >= 9.987e3)				// 0.13%
		composition.Set('B',magnitude);
	else if (sclass >= 9.94e3)				// 0.6%
		composition.Set('A',magnitude);
	else if (sclass >= 9.7e3)				// 3.0%
		composition.Set('F',magnitude);
	else if (sclass >= 9.24e3)				// 7.6%
		composition.Set('G',magnitude);
	else if (sclass >= 8.79e3)				// 12.1%
		composition.Set('K',magnitude);
	else									// 76.56%
		composition.Set('M',magnitude);
}

void CGObject::SetSmajor()
{
	double distribution = position;
	if (distribution <= GSHALO) {
		distribution /= GSHALO;
		orbit.smajor = GCORE + (GHALO-GCORE)*distribution + mod*1e48;
		//orbit.smajor = 0;	// FOR TESTING ONLY!!!
			// Stars in the halo are uniformly spread
	}
	else if (distribution <= GSHALO+GSBULGE) {
		distribution = (distribution - GSHALO) / GSBULGE;
		orbit.smajor = GCORE + (GTRANS-GCORE)*distribution + mod*1e48;
			// Stars in the galactic bulge are close together at the core
	}
	else {
		distribution = (distribution - GSHALO - GSBULGE) / GSDISK;
		orbit.smajor = GTRANS + (GRADIUS-GTRANS)*distribution + mod*1e48;
			// Uniform distribution in the disk
	}
}

void CGObject::SetEcc()
{
	orbit.eccentricity = (fmod(ID*PRIMESEED,1e4) / 1e5) * (orbit.smajor / GRADIUS);
		// Up to 0.9999%; Uniform
		// Largely irrelevant, considering the distances involved
}

void CGObject::SetIncl()
{
	double distribution = position;
	double maxelev,maxincl;
	maxincl = PI/2;		// Galactic bulge, halo
	if ( orbit.smajor > GBULGE && distribution > GSHALO ) {
		// Stars within the galactic disk and the transitional region between the bulge and
		// the disk
		if ( distribution <= GSHALO+GSBULGE ) {
			// Stars within the transitional region
			// NOTE: GBULGE only contains the stars in the bulge, GSBULGE is for both the
			// bulge AND the transitional region
			distribution = (distribution - GSHALO) / GSBULGE;
			maxelev = (GBULGE-GTHICK/2)/2*cos(orbit.smajor*PI/(GTRANS-GBULGE))+(GBULGE+GTHICK/2)/2;
				// First + Last element gives the maximal offset
				// First - Last element gives the minimal offset, in this case GTHICK/2
				// Second element angle denominator gives us the amplitude
		}
		else {
			// Stars in the disk
			distribution = (distribution - GSHALO - GSBULGE) / GSDISK;
			if (orbit.smajor >= GRADIUS)
				// Stars at the very edge, or slightly outside, due to random perturbations
				// of the orbital semi-major axis
				maxelev = 0;
			else
				// The rest of the stars cluster in the shape of a parabola
				maxelev = sqrt((GRADIUS-orbit.smajor)*GTHICK/2 * 1e-2);
				// Second nominator is 100 times the maximal offset, hence *1e-2
		}
		maxincl = asin(maxelev/orbit.smajor);
			// Convert the elevation into an angle with the galactic plane
	}
	else
		distribution /= GSHALO;
	if (maxincl < 0)
		maxincl = 0;
		// Represented by a factor from 1 to 0, decreases with distance
	orbit.inclination = ( fmod(PRIMESEED*distribution,41e-19) - 205e-20 ) / 205e-20 * PI / 2;
		// A factor up to +/-0.49999999*PI, uniformly distributed
	if (maxincl == 0)
		orbit.inclination = 0;
	else if (abs(orbit.inclination) > maxincl)
		orbit.inclination = ( (abs(orbit.inclination) - maxincl) / (PI/2) * maxincl ) * orbit.inclination / abs(orbit.inclination);
			// Proportional clustering in the target region; uniform within the region
	orbit.inclination += mod*1e-8;
}

void CGObject::SetLong()
{
	if (orbit.inclination == 0 || orbit.inclination == PI)
		orbit.longitude = 0;
			// If the inclination is zero or 180 degrees, the longitude has no effect on
			// the orbit
	else {
		orbit.longitude = fmod(PRIMESEED*position,37e-23) * 37e23 * PI * 2 + mod*1e-8;
			// Uniform distribution
	}
}

void CGObject::SetPeri()
{
	orbit.periapsis = fmod(PRIMESEED*position,31e-29) * 31e29 * PI * 2 + mod*1e-7;
		// Uniform distribution
}

void CGObject::SetTruea()
{
		// SUGGESTION: If one of either longitude, periapsis argument or true anomaly is
		// distributed in a sunisuidal form, there'll be no need to check for galactic arm
		// concentration here. However, such a method anywhere else than at the true anomaly
		// is also going to concentrate orbital elements too; e.g. stars in the arms are 
		// going to have relatively similar elements/
	orbit.truea = fmod(PRIMESEED*position,367e-83) * 367e83 * PI * 2;
		// Uniform distribution
	if ( position > GSHALO && position <= GSHALO + GSBULGE ) {
		// Reserved for possible later use; galactic bar at the bulge could be implemented here
	}
	if ( position > GSHALO + 0.8*GSBULGE && false) {
		// Galactic arms; +0.8*GSBULGE, because the arms protrude into the bulge, for
		// smoother transition
		double arm_alpha_start = 0;
		double arm_alpha = arm_alpha_start + GARM;
		double arm_beta_start = PI/2;
		double arm_beta = arm_beta_start + GARM;
		double arm_gamma_start = PI;
		double arm_gamma = arm_gamma_start + GARM;
		double arm_delta_start = 3*PI/2;
		double arm_delta = arm_delta_start + GARM;

		double angle = fmod(orbit.truea + orbit.periapsis + orbit.longitude,2*PI);
			// Make the angle change between 0<a<2*PI
		double a=0.3;	// Unknown variable; possibly rotation
		double b=0.3;	// Winding of the spiral; smaller number means more wound up spiral
		double correction = log(orbit.smajor/a)/b;
			// Representation of a logarithmic spiral
		if (angle >= arm_delta_start )	// Check the quadrant in which the star is located
			correction += arm_delta;
		else if (angle >= arm_gamma_start )
			correction += arm_gamma;
		else if (angle >= arm_beta_start )
			correction += arm_beta;
		else
			correction += arm_alpha;

		angle = fmod(angle,PI/2) - PI/4;
			// The angle is only relevant with the offset inside it's quadrant
		angle *= sqrt(abs(angle) / PI * 4);
			// Make it change from 1 to 0 then apply concentration
		angle += correction;
			// Bring the angle back up to 2*PI, so we get 4 arms distributed in a circle
		orbit.truea = angle - orbit.periapsis - orbit.longitude;
			// In the galactic disk, the inclination is mostly irrelevant to the final angle,
			// hence it is represented as a sum of the three orbital elements
	}
	orbit.truea += mod*1e-9;
}


void CGObject::SetVelocity()
{
	orbit.velocity = 7.33841e-4;	// Expressed in n times the speed of light
}

void CGObject::SetAnomaly(const double in_time)	// Currently, the only method to set star advancement along an orbit; perhaps a new internal method should be invented
{
	orbit.truea -= orbit.velocity/orbit.smajor*in_time;
		// NOTE: The formula used here is (velocity/perimeter)*time,
		// which gives us the advancement as a factor of the perimeter.
		// In order to get an angle we have to multiply that by 2*PI,
		// but the perimeter is found as radius*2*PI, so we have the
		// aforeused formula as a result (velocity/radius*time)
}


//////////////////////////////////////////////////////////////////////////////////////
// Get info

RGBTRIPLE CGObject::GetColor()	// Temporary construct for apparent color
{
	return composition.pixel;
}

CCartC CGObject::GetCartesian(void)		// Cartesian position at current time
{
	double r = (orbit.smajor * (1 - pow(orbit.eccentricity,2))) / (1 + orbit.eccentricity * cos(orbit.truea));
	double x = r * (cos(orbit.longitude) * cos(orbit.periapsis + orbit.truea) - sin(orbit.longitude) * sin(orbit.periapsis + orbit.truea) * cos(orbit.inclination));
	double y = r * (sin(orbit.longitude) * cos(orbit.periapsis + orbit.truea) + cos(orbit.longitude) * sin(orbit.periapsis + orbit.truea) * cos(orbit.inclination));
	double z = r * (sin(orbit.inclination) * sin(orbit.periapsis + orbit.truea));

	CCartC result(x,y,z);
	return result;
}

CCartC CGObject::GetCartesian(const double in_time)		// Cartesian coords at a momments before or after the current time
{
	double new_truea = orbit.truea - orbit.velocity/orbit.smajor*in_time;	// We modify a copy of the current true anomally, so we don't change the actual position
	double r = (orbit.smajor * (1 - pow(orbit.eccentricity,2))) / (1 + orbit.eccentricity * cos(new_truea));
	double x = r * (cos(orbit.longitude) * cos(orbit.periapsis + new_truea) - sin(orbit.longitude) * sin(orbit.periapsis + new_truea) * cos(orbit.inclination));
	double y = r * (sin(orbit.longitude) * cos(orbit.periapsis + new_truea) + cos(orbit.longitude) * sin(orbit.periapsis + new_truea) * cos(orbit.inclination));
	double z = r * (sin(orbit.inclination) * sin(orbit.periapsis + new_truea));

	CCartC result(x,y,z);
	return result;
}

CGOrbit CGObject::GetElements()	// Orbital elements at the current momment
{
	return orbit;
}

CGOrbit CGObject::GetElements(const double in_time)		// Orbital elements at given times, before or after the current momment
{
	CGOrbit new_orbit = orbit;
	new_orbit.truea -= orbit.velocity/orbit.smajor*in_time;		// Same notes as in the true anomally formula
	return new_orbit;
}

void CGObject::NearRadii(double range, double *min_ID, double *max_ID, double *min_HID, double *max_HID)
{
	double rad_min = orbit.smajor - range;
	double rad_max = orbit.smajor + range;
	*min_HID = ceil( (rad_min - GCORE) / (GHALO-GCORE) * (STARCOUNT * GSHALO) );
	*max_HID = ceil( (rad_max - GCORE) / (GHALO-GCORE) * (STARCOUNT * GSHALO) );
	if ( rad_min >= GRADIUS ) {
		// The galactic disk is outside the drawing distance
		// Only draw the halo
		*min_ID = 0;
		*max_ID = 0;
	}
	else if ( rad_max <= GTRANS ) {
		// The galactic disk is outside the drawing distance
		// Only draw the bulge
		*min_ID = ceil( (rad_min - GCORE) / (GTRANS - GCORE) * (STARCOUNT * GSBULGE) + STARCOUNT * GSHALO );
		*max_ID = ceil( (rad_max - GCORE) / (GTRANS - GCORE) * (STARCOUNT * GSBULGE) + STARCOUNT * GSHALO );
	}
	else if ( rad_min >= GTRANS ) {
		// The galactic bulge is outside the drawing distance
		// Only draw the disk and halo
		*min_ID = ceil( (rad_min - GTRANS) / (GRADIUS - GTRANS) * (STARCOUNT * GSDISK) + STARCOUNT * (GSBULGE + GSHALO) );
		*max_ID = ceil( (rad_max - GTRANS) / (GRADIUS - GTRANS) * (STARCOUNT * GSDISK) + STARCOUNT * (GSBULGE + GSHALO) );
	}
	else {
		// Handle mixed case - render all elements
		*min_ID = ceil( (rad_min - GCORE) / (GTRANS - GCORE) * (STARCOUNT * GSBULGE) + STARCOUNT * GSHALO );
		*max_ID = ceil( (rad_max - GTRANS) / (GRADIUS - GTRANS) * (STARCOUNT * GSDISK) + STARCOUNT * (GSBULGE + GSHALO) );
	}
}
