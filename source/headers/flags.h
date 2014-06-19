//
// flags.h: redox language
// created 2014-06-18 19:35:44
// created by patrick kage
//

// ugly code within

// abandon all hope ye who enter here

#ifndef RD_FLAGS
#define RD_FLAGS

namespace redox {
	namespace config {
		void print_usage() {
		enum {INTERACTIVE, SILENT, VERBOSE, FUCKIT, OVERRIDDEN_LIBPATH, NEWCFGDIR, MAX};
		bool flags[] = {0,0,0,0,0,0};
		std::string filetoprocess, ovrliblocation, newcfgdir;
		void process_main(int argc, char** argv) {
			std::string tmp;
			for (int c = 0; c < MAX; c++) {flags[c] = false;}
			if (argc == 1) {
				flags[INTERACTIVE] = true;
				return;
			}
			for (int c = 1; c < argc; c++) { // start at one to skip invocation
				if (c == 1) {filetoprocess = argv[1];continue;}
				tmp = argv[c];
				if (tmp == "-i" || tmp == "--interactive") {
					flags[INTERACTIVE] = true;
				} else if (tmp == "-s" || tmp == "--silent") {
					flags[SILENT] = true;
				} else if (tmp == "-v" || tmp == "--verbose") {
					flags[VERBOSE] = true;
				} else if (tmp == "-f" || tmp == "--fuck-it") {
					flags[FUCKIT] = true;
				} else if (tmp == "-L" || tmp == "--lib-path") {
					if (c + 1 != argc) 
						flags[OVERRIDDEN_LIBPATH] = true;
					ovrliblocation = argv[c + 1]; c++; continue;
				} else if (tmp == "-C" || tmp == "--cfg-path") {
					if (c + 1 != argc)
						flags[OVERRIDDEN_LIBPATH] = true;
					newcfgdir = argv + 1;
				} else {
					return false;
				}
			}
		}
	}
}

#endif
