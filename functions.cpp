#include <cstdio>
#include <cstdlib>

#include "functions.h"

int randNum( int low, int high )
{
	int diff = high - low;
	return low + ((int)rand() % diff);
}
