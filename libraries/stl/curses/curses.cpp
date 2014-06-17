//
// redox STL: terminal module
// by Patrick Kage
// created 6/14/14
//

#include <iostream>


int main() {};

extern "C" std::string __info() {
	return "sv__name vvclear vsprint vsprintln svget svget_line";
}

extern "C" std::string __name() { 
	return "terminal module : redox STL : Patrick Kage";
}

extern "C" void __init() {}

extern "C" void clear() {
	std::system("clear"); // kinda hackish
}

extern "C" void print(std::string str) {
	std::cout << str;
}

extern "C" void println(std::string str) {
	std::cout << str << '\n';
}

extern "C" std::string get() {
	std::string tmp;
	std::cin >> tmp;
	return tmp;
}

extern "C" std::string get_line() {
	std::string tmp;
	std::getline(std::cin, tmp);
	return tmp;
}
