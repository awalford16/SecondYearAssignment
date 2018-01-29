#include "Image.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

Image::Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }

Image::Image(const unsigned int & _w, const unsigned int & _h, const Rgb & c) : w(_w), h(_h), pixels(NULL)
{
	pixels = new Rgb[w * h];
	for (unsigned int i = 0; i < w * h; ++i)
		pixels[i] = c;
	
}

//Image::Image(const Image & im)
//{
//	w = im.w;
//	h = im.h;
//	pixels = new Rgb[im.w * im.h];
//	for (int i = 0; i < im.w * im.h; ++i)
//		pixels[i] = im.pixels[i];
//}
//
//Image & Image::operator=(const Image & other)
//{
//	w = other.w;
//	h = other.h;
//	pixels = new Rgb[other.w * other.h];
//	for (unsigned int i = 0; i < other.w * other.h; ++i)
//		pixels[i] = other.pixels[i];
//
//	return *this;
//}

const Image::Rgb & Image::operator[](const unsigned int & i) const
{
	return pixels[i];
}

Image::Rgb & Image::operator[](const unsigned int & i)
{
	return pixels[i];
}

Image::~Image()
{
	//if (pixels != NULL) delete[] pixels;
	//delete[] pixels;
}

void Image::setName(std::string n)
{
	name = n;
}

// Getters and Setters
std::string Image::getImageName()
{
	return name;
}

void Image::setColorDepth(int n)
{
	colorDepth = n;
}

int Image::getColorDepth()
{
	return colorDepth;
}

void Image::setMethod(std::string m)
{
	method = m;
}

std::string Image::getMethod()
{
	return method;
}

// Dsiplay Image information
void Image::ImageInfo(Image img)
{
	std::cout << "Image Name: " << img.name << std::endl;
	std::cout << "Image Width (Pixels): " << img.w << std::endl;
	std::cout << "Image Height (Pixels): " << img.h << std::endl;
	std::cout << "Number of Pixels: " << img.w * img.h << std::endl;
	std::cout << "Colour Depth: " << img.colorDepth << "bits" << std::endl;
	std::cout << "Method: " << img.method << std::endl;

	Image::Rgb maxValue(0,0,0);
	Image::Rgb avgValue;
	Image::Rgb minValue(1,1,1);
	Image::Rgb sum(0,0,0);

	// Finding max, min and average RGB values
	for (unsigned int x = 0; x < img.w * img.h; x++) {
		sum.r += img.pixels[x].r;
		sum.g += img.pixels[x].g;
		sum.b += img.pixels[x].b;
		if (img.pixels[x] > maxValue) {
			maxValue.r = img.pixels[x].r * 255;
			maxValue.g = img.pixels[x].g * 255;
			maxValue.b = img.pixels[x].b * 255;
		}

		if (img.pixels[x] < minValue) {
			minValue.r = img.pixels[x].r * 255;
			minValue.g = img.pixels[x].g * 255;
			minValue.b = img.pixels[x].b * 255;
		}
	}

	avgValue.r = (sum.r / (img.w * img.h)) * 255;
	avgValue.g = (sum.g / (img.w * img.h)) * 255;
	avgValue.b = (sum.b / (img.w * img.h)) * 255;

	std::cout << "Maximum Pixel RGB Value: " << maxValue << std::endl;
	std::cout << "Minimum Pixel RGB Value: " << minValue << std::endl;
	std::cout << "Average Pixel RGB Value: " << avgValue << std::endl;
}

const Image::Rgb Image::kBlack = Image::Rgb(0);
const Image::Rgb Image::kWhite = Image::Rgb(1);
const Image::Rgb Image::kRed = Image::Rgb(1, 0, 0);
const Image::Rgb Image::kGreen = Image::Rgb(0, 1, 0);
const Image::Rgb Image::kBlue = Image::Rgb(0, 0, 1);

bool Image::Rgb::operator!=(const Rgb & c) const
{
	return c.r != r || c.g != g || c.b != b;
}

Image::Rgb & Image::Rgb::operator*=(const Rgb & rgb)
{
	r *= rgb.r, g *= rgb.g, b *= rgb.b; 
	return *this;
}

Image::Rgb & Image::Rgb::operator+=(const Rgb & rgb)
{
	r += rgb.r, g += rgb.g, b += rgb.b; 
	return *this;
}

Image::Rgb & Image::Rgb::operator/(const Rgb & rgb)
{
	r / rgb.r, g / rgb.g, b / rgb.b;
	return *this;
}

Image::Rgb & Image::Rgb::operator/(const float f)
{
	r / f, g / f, b / f;
	return *this;
}

bool Image::Rgb::operator<(const Rgb & rgb)
{
	float baseRgb = (r + b + g) / 3;
	float compareRgb = (rgb.r + rgb.b + rgb.g) / 3;

	if (baseRgb < compareRgb) {
		return true;
	}
	else {
		return false;
	}
}

bool Image::Rgb::operator>(const Rgb & rgb)
{
	float baseRgb = (r + b + g) / 3;
	float compareRgb = (rgb.r + rgb.b + rgb.g) / 3;

	if (baseRgb > compareRgb) {
		return true;
	}
	else {
		return false;
	}
	
}

Image::Rgb & Image::Rgb::operator*=(int & i)
{
	r *= i, g *= i, b *= i;
	return *this;
}



