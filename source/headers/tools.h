//
// tools.h: redox language
// created 2014-05-30 10:10:51
// created by patrick kage
//

#ifndef RD_TOOLS
#define RD_TOOLS

#include <stdlib.h>
#include <string>
#include <ctime>

#ifdef __APPLE___
#include <ranlib.h>
#else
#include <random>
#endif

#ifndef RDX_LIB_PATH
#error redox kernel compilation requires the RDX_LIB_PATH variable to be set
#define RDX_LIB_PATH "/usr/local/rdx/lib/"
#endif

#ifndef UID_LENGTH
#define UID_LENGTH 32
#endif


namespace redox {
	namespace tools {
		std::string get_lib_path() {
			return std::string(getenv(RDX_LIB_PATH));
		}
		std::string optype_to_string_fp(int optype) {
			std::string types[] = {"NONE", "UNKNOWN", "DECLARATION", "ASSIGNMENT", "CALL\t", "RETURN\t", "FUNCTIONDEC", "LIBCALL\t", "COMPARISON", "WHILE\t", "OPENBLOCK", "CLOSEBLOCK", "ELSE\t", "IMPORT\t"};
			return types[optype];
		}
		std::string optype_to_string(int optype) {
			std::string tmp = optype_to_string_fp(optype);
			if (tmp.back() == '\t') tmp.pop_back();
			return tmp;
		}
		void init_rand() {
			srand(time(0));
		}
		std::string gen_UID() {
			std::string valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefhijklmnopqrstuvwxyz0123456789"; // Valid base 62 number IDs
			std::string final = "";
			for (int c = 0; c < UID_LENGTH; c++) {
				final += valid[rand()%valid.length()];
			}
			return final; // This is actually a called a duosexagesimal number
		}
	}
}

#endif
