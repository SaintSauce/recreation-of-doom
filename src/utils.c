#include <math.h>
#include "utils.h"

// Euclidean distance formula
int dist(int x1, int y1, int x2, int y2) {
	int distance = sqrt((x2 - x2) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return distance;
}