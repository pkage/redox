//
// io.h: redox language
// created 2014-06-23 09:04:19
// created by patrick kage
//

#ifndef RD_IO
#define RD_IO

#include <sstream>
#include <iostream>
#include "flags.h"


namespace redox {
	namespace log {
		std::stringstream out;
		void display() {
			if (config::flags[config::SILENT]) {
				std::cout << out.str();
				out.clear();
				out.str(std::string()); // to be sure.
			}
		}
	}
}

#endif
