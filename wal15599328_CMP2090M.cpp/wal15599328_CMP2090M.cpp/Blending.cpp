#include "Blending.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>

void Blending::loadImages()
{
	std::cout << "Loading Images" << std::endl;
	FileActions *f = new FileActions();
	for (unsigned int i = 0; i < 13; i++) {
		Image img;
		// Convert file names to char arrays
		char *fileName = (char*)linksArray[i].c_str();

		img = f->readPPM(fileName);

		// Add image to vector
		images.push_back(img);

	}

	// Memory Management
	delete f;
	std::cout << "Images Loaded" << std::endl;
}

void Blending::meanBlend(Image * result)
{
	int counter = 0;

	std::cout << "Blending Images..." << std::endl;

	while (counter < 13) {
		//Add RGB Values to the empty image
		for (unsigned int x = 0; x < images[counter].w * images[counter].h; x++) {
			result->pixels[x] += images[counter].pixels[x];
		}
		counter += 1;
	}

	// Divide accumulated values by number of images
	for (unsigned int x = 0; x < result->w * result->h; x++) {
		result->pixels[x].r = result->pixels[x].r / 13;
		result->pixels[x].g = result->pixels[x].g / 13;
		result->pixels[x].b = result->pixels[x].b / 13;

	}

	std::cout << "Images Blended" << std::endl;
}

void Blending::medianBlend(Image * result)
{
	std::vector<float> rValues;
	std::vector<float> gValues;
	std::vector<float> bValues;

	std::cout << "Blending Images..." << std::endl;
	int counter = 0;
	// Loop through each pixel
	for (unsigned int x = 0; x < images[counter].w * images[counter].h; x++) {

		for (int i = 0; i < 13; i++) {
			// Add rgb values for each image to vector
			rValues.push_back(images[i].pixels[x].r);
			gValues.push_back(images[i].pixels[x].g);
			bValues.push_back(images[i].pixels[x].b);
		}

		// Sort each array of r, g and b values
		std::sort(rValues.begin(), rValues.end());
		std::sort(gValues.begin(), gValues.end());
		std::sort(bValues.begin(), bValues.end());

		// Set pixel values for resultant image (pixel value equivilent to value in middle of array)
		result->pixels[x].r = rValues[6];
		result->pixels[x].g = gValues[6];
		result->pixels[x].b = bValues[6];

		// Clear vector for next pixel
		rValues.clear();
		gValues.clear();
		bValues.clear();

		if (counter == 12) {
			counter = 0;
		}
		else {
			counter += 1;
		}
	}

	std::cout << "Images Blended" << std::endl;
}

void Blending::sigmaClipBlend(Image * result)
{
	std::vector<float> rValues;
	std::vector<float> gValues;
	std::vector<float> bValues;

	std::cout << "Blending images ..." << std::endl;
	for (unsigned int x = 0; x < result->w * result->h; x++) {

		// Add each pixel value to vector
		for (unsigned int i = 0; i < images.size(); i++) {
			rValues.push_back(images[i].pixels[x].r);
			gValues.push_back(images[i].pixels[x].g);
			bValues.push_back(images[i].pixels[x].b);
		}

		// Evaluate pixel values
		result->pixels[x].r = sigmaClipRejection(rValues);
		result->pixels[x].g = sigmaClipRejection(gValues);
		result->pixels[x].b = sigmaClipRejection(bValues);

		// Clear vector for next pixel
		rValues.clear();
		gValues.clear();
		bValues.clear();
	}

	std::cout << "Images Blended" << std::endl;
}

float Blending::sigmaClipRejection(std::vector<float> values)
{
	float median = 0.f;
	float sDev = 0.f;
	float oldSDev = 0.f;

	// Set a limited number of iterations
	for (unsigned int i = 0; i < 4; i++) {

		for (int x = 0; x < values.size(); x++) {

			median = medianFloat(values);
			sDev = stanDevFloat(values);

			if (checkReject(values.at(x), median, sDev)) {
				// Erase value from vector that is outside of range
				values.erase(values.begin() + x);
			}

			// Exit criteria check (Check Standard Deviation Tolerance)
			if (oldSDev != 0.0) {
				if (sDev >= oldSDev - ((oldSDev - sDev) / sDev) && sDev <= oldSDev + ((oldSDev - sDev) / sDev)) {
					break;
				}
			}

			if (values.size() == 1) return values[0];

			// Assign most recent standard deviation to old
			oldSDev = sDev;
		}

	}

	// Return average of values within range
	return meanFloat(values);
}

bool Blending::checkReject(float value, float median, float stanDev)
{
	bool min = value < median - (stanDev * 0.3f);
	bool max = value > median + (stanDev * 0.3f);

	if (min || max) {
		return true;
	}
	else {
		return false;
	}
}

float Blending::medianFloat(std::vector<float> values)
{
	std::sort(values.begin(), values.end());

	// Check for even amount of values
	if (values.size() % 2 == 0) {
		return values[(values.size() / 2) - 1] + values[values.size() / 2] / 2;
	}
	else {
		return values[values.size() / 2];
	}

}

float Blending::meanFloat(std::vector<float> values)
{
	float sum = 0;

	for (unsigned int x = 0; x < values.size(); x++) {
		sum += values[x];
	}

	return sum / values.size();
}

float Blending::stanDevFloat(std::vector<float> values)
{
	float meanValue = meanFloat(values);

	float stanDev = 0;
	float variance = 0;

	for (unsigned int x = 0; x < values.size(); x++) {

		// Square difference of mean and pixel value
		variance += pow(meanValue - values[x], 2);

	}

	// Square root value
	stanDev = sqrt(variance / values.size());

	return stanDev;
}
