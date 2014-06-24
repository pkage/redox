//
// flags.h: redox language
// created 2014-06-18 19:35:44
// created by patrick kage
//

// ugly code within

// abandon all hope ye who enter here

#ifndef RD_FLAGS
#define RD_FLAGS

#include <iostream>
#include <string>

namespace redox {
	namespace config { // shits messy
		enum {INTERACTIVE, SILENT, VERBOSE, FUCKIT, OVERRIDDEN_LIBPATH, NEWCFGDIR, CONTINUELOAD, MAX};
		bool flags[] = {0,0,0,0,0,0,0};
		std::string filetoprocess, ovrliblocation, newcfgdir;
		bool process_main(int argc, char** argv) {
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
						flags[NEWCFGDIR] = true;
					newcfgdir = argv[c + 1];
				} else if (tmp == "-v" || tmp == "--verbose") {
					print_usage();
				} else if (tmp == "-h" || tmp == "--help") {
					print_usage();
				} else {
					return false;
				}
			}
		}

		void print_usage() {
			std::cout << "usage:\n\n\trdx file [options]\n\n\tOptions:\n\t[-i][--interactive]\n\t\tRun the interpreter in interactive mode.\n\t[-s][--silent]\n\t\tRun the interpreter, silently failing on an error.\n\t[-v][--verbose]\n\t\tPrint loads of information about everything\n\t[-f][--fuck-it]\n\t\tIgnores all errors, and plows right through.\n\t[-L][--lib-path] path/to/files\n\t\tSpecify another path for libraries\n\t[-C][--cfg-path] path/to/cfg\n\t\tSpecify another path from which to load the interpreter config file\n\t[-V][--version]\n\t\tprint version information and exit\n\t[-h][--help] print this message and exit";
		}
	}
}

#endif
