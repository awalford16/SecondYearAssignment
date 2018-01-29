#include "ImageZoom.h"
#include <iostream>


void ImageZoom::zoomImage(Image *result, int w1, int h1, int w2, int h2)
{
	std::cout << "Increasing Image Size ..." << std::endl;

	Image emptyImage(w2, h2);

	// Ratio for image sizing
	int x_ratio = (int)((w1 << 16) / w2) + 1;
	int y_ratio = (int)((h1 << 16) / h2) + 1;

	int x, y;
	for (int i = 0; i < h2; i++) {
		y = ((i*y_ratio) >> 16);

		for (int j = 0; j < w2; j++) {
			x = ((j * x_ratio) >> 16);
			emptyImage.pixels[(i*w2) + j] = result->pixels[(y*w1) + x];
		}
	}

	// Assign image to result
	*result = emptyImage;

	std::cout << "Done" << std::endl;
}

void ImageZoom::bilinearZoom(Image * result, int w2, int h2)
{
	
	Image output = Image(w2, h2);
	Image::Rgb a, b, c, d;
	int x, y, index;
	float x_ratio = ((float)(result->w - 1)) / w2;
	float y_ratio = ((float)(result->h - 1)) / h2;
	float x_diff, y_diff;
	int offset = 0;
	for (int i = 0; i<h2; i++) {
		for (int j = 0; j<w2; j++) {
			x = (int)(x_ratio * j);
			y = (int)(y_ratio * i);
			x_diff = (x_ratio * j) - x;
			y_diff = (y_ratio * i) - y;
			index = (y*result->w + x);
			a = result->pixels[index];
			b = result->pixels[index + 1];
			c = result->pixels[index + result->w];
			d = result->pixels[index + result->w + 1];

			// Yr = Ar(1-w)(1-h) + Br(w)(1-h) + Cr(h)(1-w) + Dr(wh)
			output.pixels[offset].r = (a.r * (1 - x_diff)*(1 - y_diff)) + (b.r * (x_diff)*(1 - y_diff)) +
				(c.r * (y_diff)*(1 - x_diff)) + (d.r * (x_diff * y_diff));

			// Yg = Ag(1-w)(1-h) + Bg(w)(1-h) + Cg(h)(1-w) + Dg(wh)
			output.pixels[offset].g = (a.g * (1 - x_diff)*(1 - y_diff)) + (b.g * (x_diff)*(1 - y_diff)) +
				(c.g * (y_diff)*(1 - x_diff)) + (d.g * (x_diff * y_diff));

			// Yb = Ab(1-w)(1-h) + Bb(w)(1-h) + Cb(h)(1-w) + Db(wh)
			output.pixels[offset].b = (a.b * (1 - x_diff)*(1 - y_diff)) + (b.b * (x_diff)*(1 - y_diff)) +
				(c.b * (y_diff)*(1 - x_diff)) + (d.b * (x_diff * y_diff));


			offset++;
		}
	}
	*result = output;

}

void ImageZoom::ROI(Image * result, int xpoint, int ypoint)
{
	std::cout << "Locating Region of Interest" << std::endl;

	// Create an empty image 1/4 size of original
	Image interestRegion = Image(result->w / 5, result->h / 5);

	int startPoint = xpoint + (ypoint * result->w);
	int c = 1;
	int n = 0;

	for (unsigned int x = 0; x < interestRegion.h * interestRegion.w; x++) {

		// If x is width display next row of pixels from full image
		if (x == interestRegion.w * c) {
			startPoint += result->w;
			c += 1;
			n = 0;
		}
		
		interestRegion.pixels[x].r = result->pixels[startPoint + n].r;
		interestRegion.pixels[x].g = result->pixels[startPoint + n].g;
		interestRegion.pixels[x].b = result->pixels[startPoint + n].b;

		n += 1;
	}

	// Assign the image to the result
	*result = interestRegion;

	std::cout << "Done" << std::endl;
}


// Polymorphism to display additional zoom info
void ImageZoom::ImageInfo(Image image)
{
	// Display Original image info
	image.ImageInfo(image);

	// Additional info regarding zoom
	std::cout << "Original Image width: " << image.w / scaleSize << std::endl;
	std::cout << "Original Image height: " << image.h / scaleSize << std::endl;
	std::cout << "Original Image pixel count: " << (image.w / scaleSize) * (image.w / scaleSize) << std::endl;
	std::cout << "Scale size: " << scaleSize << "x" << std::endl;

}

void ImageZoom::setScaleSize(int sSize)
{
	scaleSize = sSize;
}

int ImageZoom::getScaleSize()
{
	return scaleSize;
}

