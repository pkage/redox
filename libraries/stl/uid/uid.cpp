//
// redox STL: terminal module
// by Patrick Kage
// created 6/14/14
//

#include <iostream>
#include <ctime>

#ifdef __APPLE__
#include <ranlib.h>
#else
#include <random>
#endif

int main() {};

extern "C" std::string __info() {
	return "sv__name svgenerate";
}

extern "C" std::string __name() { 
	return "uid module : redox STL : Patrick Kage";
}

extern "C" void __init() {
	srand(time(0));
}

extern "C" std::string generate() {
	std::string valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // valid characters
	std::string out = "";
	for (int c = 0; c < 32; c++) {
		out += valid[rand()%valid.length()];
	}
	return out;
}
