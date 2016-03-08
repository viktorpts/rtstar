#include "StdAfx.h"
#include "Cluster.h"

CCluster::CCluster(void)
{
	objects = new double[(int)STARCOUNT];
	for (double n=1;n<=STARCOUNT;n++) {
		objects[(int)n-1] = n;
	}
}

CCluster::~CCluster(void)
{
	delete[] objects;
}
