//
// tools.h: redox language
// created 2014-05-30 10:10:51
// created by patrick kage
//

#ifndef RD_TOOLS
#define RD_TOOLS

#include <stdlib.h>
#include <string>

#ifndef LIB_PATH_VAR
#define LIB_PATH_VAR "RDX_LIBS"
#endif


namespace redox {
	namespace tools {
		std::string get_lib_path() {
			return std::string(getenv(LIB_PATH_VAR));
		}
		std::string translateOptypeToString(int optype) {
			std::string types = {};
		}
	}
}

#endif
