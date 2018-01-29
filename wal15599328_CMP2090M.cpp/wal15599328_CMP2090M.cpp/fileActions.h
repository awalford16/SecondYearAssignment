#pragma once
#include "Image.h"

#ifndef FILEACTIONS_H
#define FILEACTIONS_H

class FileActions {
public:
	Image readPPM(const char*);
	void writePPM(const Image, const char*);
};

#endif