//
// linter.h: redox language
// created 2014-05-30 13:19:46
// created by patrick kage
//

#ifndef RD_LINTER
#define RD_LINTER

#include <string>
#include "core.h"

namespace redox {
	namespace prep {
		void prep_file(core::File &f) {
			for (int c = 0; c < f.raw.length(); c++) {
				std::string line;
				line = f.raw.get_line(c);
				if (line.length() == 0) continue;
				while (line.at(0) == '\t') {
					line = line.substr(1);
				}
				if (line.back() == ';') {line.pop_back();}
				f.raw.overwrite(c, line);
				std::cout << line << '\n';
			}
		}
	}
}

#endif
