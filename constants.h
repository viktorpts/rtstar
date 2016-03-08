#define PRIMESEED 982451653e0
#define SEED 165367
#define PI acos(-1.0)
#define STARCOUNT 10e4
#define VISBAR 6000
#define VISDIST 4.6704e53
#define SIMSTART 0
#define SIMTIME 200		// 4.6705248e57 = 20 million years expressed in universal cycles

#define GRADIUS 1.1676e55
#define GTHICK 2.33521e53
#define GBULGE 1.1676e54
#define GTRANS 1.7514e54
#define GHALO 1.51789e55
#define GCORE 2.33521e53
#define GARM PI/4
#define GSPIN 4

#define GSHALO 0.2
#define GSDISK 0.7
#define GSBULGE 0.1

// Universal constants, expressed in SI units

inline double ucc();
inline double ucG();
inline double uch();
inline double ucm();
inline double uce();
inline double ucc(int power);
inline double ucG(int power);
inline double uch(int power);
inline double ucm(int power);
inline double uce(int power);

// Conversion of SI units to universal units

double LYtoL(double LY);
double LtoLY(double L);