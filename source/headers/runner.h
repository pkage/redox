//
// runner.h: redox language
// created 2014-05-30 17:12:05
// created by patrick kage
//

#ifndef RD_RUNNER
#define RD_RUNNER

#include <string>
#include <vector>

#include "mem.h"
#include "core.h"
#include "library.h"
#include "error.h"


namespace redox {
	namespace runner {
		namespace optypes {
			enum optypes {NONE, UNKNOWN, DECLARATION, ASSIGNMENT, CALL, RETURN, FUNCTIONDEC, LIBCALL, COMPARISON, WHILE, OPENBLOCK, CLOSEBLOCK, ELSE, IMPORT};
		}
		class Parser {
		private:
			std::vector<std::string> components;
		public:
			int optype;
			void guessoptype() {
				if (components.size() == 0) {
					optype = optypes::NONE;
					return;
				}
				if (components.at(0) == "decl") {
					optype = optypes::DECLARATION;
					return;
				} else if (components.size() > 1 && components.at(1) == "=") {
					optype = optypes::ASSIGNMENT;
					return;
				} else if (components.at(0) == "function") {
					optype = optypes::FUNCTIONDEC;
					return;
				} else if (components.at(0) == "return") {
					optype = optypes::RETURN;
					return;
				} else if (components.back().back() == ')' && components.at(0) != "if" && components.at(0) != "while" && components.at(0) != "for") { // for statement unsupported as of now
					if (components.at(0).find(".") == std::string::npos) {
						optype = optypes::CALL;
						return;
					} else {
						optype = optypes::LIBCALL;
						return;
					}
				} else if (components.at(0) == "if") {
					optype = optypes::COMPARISON;
					return;
				} else if (components.at(0) == "while") {
					optype = optypes::WHILE;
					return;
				} else if (components.at(0) == "{") {
					optype = optypes::OPENBLOCK;
					return;
				} else if (components.at(0) == "}") {
					if (components.size() == 2 && components.at(1) == "else") {optype = optypes::ELSE;return;}
					optype = optypes::CLOSEBLOCK;
					return;
				} else if (components.at(0) == "import") {
					optype = optypes::IMPORT;
					return;
				} else {
					optype = optypes::UNKNOWN;
					return;
				}
				
			}
			void parseln(std::string ln) {
				if (ln.at(ln.length() - 1) == ';') {
					ln.pop_back();
				}
				int prev = 0;
				int next = 0;
				
				while ((next = ln.find_first_of(" ", prev)) != std::string::npos) {
					if (next - prev != 0) {
						components.push_back(ln.substr(prev, next - prev));
					}
					prev = next + 1;
				}
				if (prev < ln.size()) {
					components.push_back(ln.substr(prev));
				}
				guessoptype();
			}
			void clear() {
				components.clear();
				optype = optypes::NONE;
			}
			int size() {return components.size();}
			bool valid(int addr) {return (addr >= 0 || addr < components.size());}
			std::string component(int addr) {
				if (!valid(addr)) return "";
				return components.at(addr);
			}
		};
		void execBlock(core::File &f, mem::Memory &mem, core::Block &block) {
			for (int c = 0; c < block.sb.length(); c++) {
				std::cout << "This function is in no way prepared to handle: " << block.sb.get_line(c);
			}
		}
	}
}

#endif
