// example C++ redox extension

#include <string>
#include <iostream>

using namespace std;

int main() { // placate your compiler by providing an entry point
	cout << "This is a dynamic library, not an executable. Fuck off.";
	return 1;
}

extern "C" std::string __info() { // required by library loader, declares available functions
	return "vvhello vsecho ssreverse";
}

extern "C" std::string __name() { // required by library loader, makes library name available
	return "example library v1.0 by Patrick Kage";
}

extern "C" void hello() {
	cout << "Hello world!";	// say hello!
}

extern "C" void echo(std::string s) {
	cout << s; // echo the string
}

extern "C" std::string reverse(std::string s) {
	return std::string(s.rbegin(), s.rend()); // reverse the string
}
