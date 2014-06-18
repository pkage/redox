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
			core::StringBundle sb; sb.clear();
			for (int c = 0; c < f.raw.length(); c++) {
				std::string line;
				line = f.raw.get_line(c);
				if (line.length() == 0) continue;
				while (line.at(0) == '\t') {
					line = line.substr(1);
				}
				while (line.back() == ' ' || line.back() == '\t') {
					line.pop_back();
				}
				if (line.back() == ';') {line.pop_back();}
				if (line.back() == '{') {
					line.pop_back();
					if (line.length() != 0) sb.add_line(line);
					sb.add_line("{");
					continue;
				}
				if (line.back() == '}') {
					line.pop_back();
					if (line.length() != 0) sb.add_line(line);
					sb.add_line("}");
					continue;
				}
				sb.add_line(line); // normal statement
			}
			f.raw.clear();
			for (int c = 0; c < sb.length(); c++) {
				f.raw.add_line(sb.get_line(c));	
			}
		}
	}
}

#endif
