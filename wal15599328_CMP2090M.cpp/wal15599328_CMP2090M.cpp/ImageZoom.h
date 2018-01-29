#pragma once
#include "Image.h"
#include <vector>

class ImageZoom : public Image {
private:
	int scaleSize;

public:
	// Expand Image size
	void zoomImage(Image *result, int w1, int h1, int w2, int h2);

	void bilinearZoom(Image *result, int w2, int h2);

	void ROI(Image *result, int xpoint, int ypoint);

	void ImageInfo(Image image);

	// Getters and Setters
	void setScaleSize(int sSize);
	int getScaleSize();


};