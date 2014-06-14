// example C++ redox extension

#include <string>
#include <iostream>

using namespace std;

int main() { // placate your compiler by providing an entry point
	cout << "This is a dynamic library, not an executable. Fuck off.\n";
	return 1;
}

extern "C" std::string __info() { // required by library loader, declares available functions
	return "vvhello vsecho ssreverse sv__name";
}

extern "C" std::string __name() { // should be there so user can find the libaries name
	return "example library v1.0 by Patrick Kage";
}

extern "C" void __init() { // required by library loader, is simply executed.
	// do nothing
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
