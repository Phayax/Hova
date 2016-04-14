#include <iostream>
#include <math.h>

float radToDeg(float rad)
{
	return rad / (2 * M_PI) * 360.0f;
}

float atanDeg(const float x, const float y)
{
	float rangle{0.0f};
	float angle{0.0f};
	rangle = atan(y / x);
	if (x < 0) {
		// atan(1) = π/4
		rangle += atan(1) * 4;
	}

	// change to degrees:
	angle = rangle * 360.0f / (2 * atan(1) * 4);

	while (angle < 0.0f)
		angle += 360.0f;
	return angle;
}


int main()
{
	std::cout << "atan(1/1) ->" << atanDeg(1,1) << std::endl;
	std::cout << "atan(-1/1) ->" << atanDeg(-1,1) << std::endl;
	std::cout << "atan(1/-1) ->" << atanDeg(1,-1) << std::endl;
	std::cout << "atan(-1/-1) ->" << atanDeg(-1,-1) << std::endl;

	return 0;
}