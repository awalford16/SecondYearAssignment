#pragma once
#include "Image.h"
#include "fileActions.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

class Blending {

private:
	// Image Links
	std::vector<std::string> linksArray = { "Images/ImageStacker_set1/IMG_1.ppm", "Images/ImageStacker_set1/IMG_2.ppm", "Images/ImageStacker_set1/IMG_3.ppm",
		"Images/ImageStacker_set1/IMG_4.ppm", "Images/ImageStacker_set1/IMG_5.ppm", "Images/ImageStacker_set1/IMG_6.ppm", "Images/ImageStacker_set1/IMG_7.ppm",
		"Images/ImageStacker_set1/IMG_8.ppm", "Images/ImageStacker_set1/IMG_9.ppm", "Images/ImageStacker_set1/IMG_10.ppm", "Images/ImageStacker_set1/IMG_11.ppm",
		"Images/ImageStacker_set1/IMG_12.ppm", "Images/ImageStacker_set1/IMG_13.ppm" };
	std::vector<Image> images;

public:
	void loadImages(); 

	// Mean bleanding algorithm function
	void meanBlend(Image *result);

	// Median blending functions
	void medianBlend(Image *result);

	// Sigma clip belnding functions
	void sigmaClipBlend(Image *result);

	float sigmaClipRejection(std::vector<float> values); 

	bool checkReject(float value, float median, float stanDev);

	float medianFloat(std::vector<float> values);

	float meanFloat(std::vector<float> values);

	float stanDevFloat(std::vector<float> values); 
};