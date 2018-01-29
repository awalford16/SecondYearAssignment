//main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Image.h"
#include "fileActions.h"
#include "Blending.h"
#include "ImageZoom.h"

using namespace std;
   
int main()
{
	cout << "************************************" << endl;
	cout << "Image Stacker / Image Scaler" << endl;
	cout << "************************************" << endl;

	bool valid = true;

	// Object for final image
	Image result = Image(3264, 2448);
	Blending b;
	// Read and add images to a vector
	b.loadImages();

	do {
		cout << "--------------------------" << endl;
		cout << "      Image Stacking      " << endl;
		cout << "--------------------------" << endl;

		// Select blending function for images
		int bChoice;
		cout << "Enter 1, 2 or 3 regarding how you would like the images to be blended: " << endl;
		cout << "1. Mean Blending" << endl;
		cout << "2. Median Blending" << endl;
		cout << "3. Sigma Clip Blending" << endl;
		cin >> bChoice;

		valid = true;

		switch (bChoice) {
		case 1:
			b.meanBlend(&result);
			result.setMethod("Mean Blending");
			break;
		case 2:
			b.medianBlend(&result);
			result.setMethod("Median Blending");
			break;
		case 3:
			b.sigmaClipBlend(&result);
			result.setMethod("Sigma Clip Blending");
			break;
		default:
			system("cls");
			cout << "Sorry, we did not understand your input, please enter 1, 2 or 3." << endl;
			valid = false;		// Set answer invalid
			break;
		}

		if (cin.fail()) {
			cout << "Incorrect Input, please enter 1, 2 or 3." << endl;
			valid = false;
			cin.clear();
			cin.ignore();
		}

	} while (valid == false);

	FileActions *file = new FileActions();

	// Set image values and display information
	result.setName("BlendedImage.ppm");
	result.setColorDepth(8);
	cout << "\nInfo reagrding blended image: " << endl;
	result.ImageInfo(result);

	//Output the image data to a file for viewing
	file->writePPM(result, "BlendedImage.ppm");

	// Delete file object while it is not being used
	delete file;
		
	// Clear screen for zooming stage
	system("pause");
	system("cls");

	// Image Zooming
	
	ImageZoom * zoom = new ImageZoom();
	Image zImage = file->readPPM("Images/Zoom/zIMG_1.ppm");


	// Loop through menu process until a valid input is entered
	do {
		cout << "--------------------------" << endl;
		cout << "      Image Scaling       " << endl;
		cout << "--------------------------" << endl;
		cout << "Loading small image ..." << endl;

		cout << endl << "Select zoom method and scale for image: " << endl << "1. Nearest Neighbour 2x" << endl << "2. Nearest Neighbour 4x" << endl
			<< "3. Bilinear Interpolation 2x" << endl << "4. Bilinear Interpolation 4x" << endl << "5. Region of Interest 2x" << endl << "6. Region of Interest 4x" << endl;
		
		// User input
		int zChoice;
		std::cin >> zChoice;

		valid = true;

		switch (zChoice) {
		case 1:
			zoom->zoomImage(&zImage, zImage.w, zImage.h, zImage.w * 2, zImage.h * 2);
			zoom->setScaleSize(2);
			zImage.setMethod("Nearest Neighbour");
			break;
		case 2:
			zoom->zoomImage(&zImage, zImage.w, zImage.h, zImage.w * 4, zImage.h * 4);
			zoom->setScaleSize(4);
			zImage.setMethod("Nearest Neighbour");
			break;
		case 3:
			zoom->bilinearZoom(&zImage, zImage.w * 2, zImage.h * 2);
			zoom->setScaleSize(2);
			zImage.setMethod("Bilinear Interpolation");
			break;
		case 4:
			zoom->bilinearZoom(&zImage, zImage.w * 4, zImage.h * 4);
			zoom->setScaleSize(4);
			zImage.setMethod("Bilinear Interpolation");
			break;
		case 5:
			zoom->ROI(&zImage, 270, 270);
			zoom->bilinearZoom(&zImage, zImage.w * 2, zImage.h * 2);
			zoom->setScaleSize(2);
			zImage.setMethod("ROI - Bilinear Zoom");
			break;
		case 6:
			zoom->ROI(&zImage, 270, 270);
			zoom->bilinearZoom(&zImage, zImage.w * 4, zImage.h * 4);
			zoom->setScaleSize(4);
			zImage.setMethod("ROI - Bilinear Zoom");
			break;
		default:
			system("cls");
			cout << "Sorry, we did not understand your input, please enter a number between 1 and 6." << endl;
			valid = false;		// Set answer invalid
			break;
		}

		if (cin.fail()) {
			cout << "Incorrect Input." << endl;
			valid = false;
			cin.clear();
			cin.ignore();
		}

	} while (valid != true);

	FileActions * zoomFile = new FileActions();
	// Set image values and display information
	zImage.setName("zoomedImage.ppm");
	zImage.setColorDepth(8);
	cout << "\nZoomed image info: " << endl;
	zoom->ImageInfo(zImage);


	file->writePPM(zImage, "zoomedImage.ppm");

	// Delete pointer objects to avoid memory leaks
	delete zoomFile, zoom;

	
	system("pause");
	return 0;
}

//Read ppm files into the code
//They need to be in 'binary' format (P6) with no comments in the header
//The first line is the 'P'number - P6 indicates it is a binary file, then the image dimensions and finally the colour range
//This header is then followed by the pixel colour data
//eg:	P6
//		3264 2448
//		255
//Open a .ppm file in notepad++ to see this header (caution: they are large files!)
