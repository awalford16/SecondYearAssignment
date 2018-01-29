#pragma once
//*********************************************
//Image class to hold and allow manipulation of images once read into the code
//from https://www.scratchapixel.com/
//*********************************************
#include <cstdlib> 
#include <cstdio> 
#include <string>
#ifndef IMAGE_H
#define IMAGE_H

class Image
{
protected:
	std::string name;
	int colorDepth;
	std::string method;

public:
	// Rgb structure, i.e. a pixel 
	struct Rgb
	{
		Rgb() : r(0), g(0), b(0) {}
		Rgb(float c) : r(c), g(c), b(c) {}
		Rgb(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
		bool operator != (const Rgb &c) const;
		Rgb& operator *= (const Rgb &rgb);
		Rgb& operator += (const Rgb &rgb);
		Rgb& operator / (const Rgb &rgb);
		Rgb& operator / (const float f);
		bool operator < (const Rgb &rgb);
		bool operator > (const Rgb &rgb);
		Rgb& operator *= (int &i);

		// Overload output operator for displaying RGB values
		friend std::ostream& operator<<(std::ostream& os, Rgb& rgb) {
			// Convert float values to int for display
			os << static_cast<int>(rgb.r) << ' ' << static_cast<int>(rgb.g) << ' ' << static_cast<int>(rgb.b);
			return os;
		}
		friend float& operator += (float &f, const Rgb rgb)
		{
			f += (rgb.r + rgb.g + rgb.b) / 3.f; return f;
		}
		float r, g, b;
	};

	//constructors
	Image();
	Image(const unsigned int &_w, const unsigned int &_h, const Rgb &c = kBlack); 

	// Copy constructor
	//Image(const Image &im);

	// Copy assignment operator
	//Image& operator=(const Image& other);

	const Rgb& operator [] (const unsigned int &i) const;

	Rgb& operator [] (const unsigned int &i);

	//destructor
	~Image();

	unsigned int w, h; // Image resolution 
	Rgb *pixels; // 1D array of pixels 
	static const Rgb kBlack, kWhite, kRed, kGreen, kBlue; // Preset colors 

	// Getters and Setters
	void setName(std::string n);
	std::string getImageName();
	void setColorDepth(int n);
	int getColorDepth();
	void setMethod(std::string m);
	std::string getMethod();

	virtual void ImageInfo(Image img);
};

#endif

