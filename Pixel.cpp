#include <Pixel.hpp>

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b)noexcept:
	rgba_{ 0 } {

	rgba_.r = r;
	rgba_.g = g;
	rgba_.b = b;

}

Pixel::Pixel()noexcept:
	Pixel{ 0, 0, 0 } {

}