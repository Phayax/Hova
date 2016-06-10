#include <iostream>
#include <complex>

float radToDeg(float rad)
{
	return rad * 180.0f / M_PI;
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
	std::complex<float> test = std::polar(10.0f, 45.0f * static_cast<float>(M_PI) / 180.0f);
	std::cout << "testing STL polar coordinate reverse conversion" << std::endl;
	std::cout << abs(test) << " - " << real(test) << " - " << imag(test) << std::endl;
	std::cout << radToDeg(arg(test)) << std::endl;
	std::cout << "";
	// std::cout << "atan(1/1) -> " << atanDeg(1,1) << std::endl;
	// std::cout << "atan(-1/1) -> " << atanDeg(-1,1) << std::endl;
	// std::cout << "atan(1/-1) -> " << atanDeg(1,-1) << std::endl;
	// std::cout << "atan(-1/-1) -> " << atanDeg(-1,-1) << std::endl;

	return 0;
}