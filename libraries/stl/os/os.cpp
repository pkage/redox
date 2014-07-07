//
// redox STL: terminal module
// by Patrick Kage
// created 6/14/14
//

#include <iostream>



int main() {};

extern "C" std::string __info() {
	return "sv__name ssgetenv vssetenv vssystem";
}

extern "C" std::string __name() { 
	return "os module : redox STL : Patrick Kage";
}

extern "C" void __init() {}

extern "C" std::string getenv(std::string env) {
	
}

