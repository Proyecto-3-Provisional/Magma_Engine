#pragma once

#include <string>

#define NUM_P_CMPS 6

//incluir .lua detras del nombre que se inserte
int luaMain(std::string filename);

const std::string possibleCmps[NUM_P_CMPS] = {
	"Transform",
	"Mesh",
	"Rigidbody",
	"Image",
	"Text",
	"Button"
	//AudioSource
};