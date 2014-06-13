//
// library.h: redox language
// created 2014-06-12 02:14:33
// created by patrick kage
//

#ifndef RD_LIBS
#define RD_LIBS

#include <vector>
#include <string>
#include <dlfcn.h>
#include "error.h"

namespace redox {
	namespace libs {
		namespace types {
			enum Desc {VOID_V, VOID_S, STR_V, STR_S};
			typedef void (*void_v)();
			typedef void (*void_s)(std::string);
			typedef std::string (*str_v)();
			typedef std::string (*str_s)(std::string);
		}
		class Method {
		public:
			std::string name;
			int type;
			void init(types::Desc d, std::string name) {
				this->type = d;
				this->name = name;
			}
		};
		class Lib {
		private:
			void* ptr;
			std::vector<Method> methods;
			std::string path;
			std::string name;
			bool valid;
		public:
			Lib() {valid = false;}
			~Lib() {dlclose(ptr);} // free the library when the object is destroyed.
			void init(std::string path) {
				this->path = path;
				ptr = dlopen(path.c_str(), RTLD_LAZY);
				if (!ptr) {
					error::equeue.add_error(error::LIBNOTFOUND, dlerror());
					valid = false;
					return;
				}
				types::str_v __info = (types::str_v) dlsym(ptr, "__info");
				if (!__info) {
					error::equeue.add_error(error::INVALIDLIB, "Library does not contain metadata.");
					valid = false;
					return;
				}
				// begin tokenizing
				std::string source = __info();
				std::vector<std::string> results; // tokenize the the __info return;
				
				size_t prev = 0;
				size_t next = 0;
				
				while ((next = source.find_first_of(" ", prev)) != std::string::npos) {
					if (next - prev != 0) {
						results.push_back(source.substr(prev, next - prev));
					}
					prev = next + 1;
				}
				if (prev < source.size()) {
					results.push_back(source.substr(prev));
				}
				// end tokenizing
				// initialize list
				Method tmpm;
				std::string ts1, ts2;
				for (int c = 0; c < results.size(); c++) {
					ts1 = results.at(c).substr(0,2); // get the first two characters, which are the definition
					ts2 = results.at(c).substr(2,std::string::npos);
					if (ts1 == "vv") {
						tmpm.init(types::VOID_V, ts2);
					} else if (ts1 == "vs") {
						tmpm.init(types::VOID_S, ts2);
					} else if (ts1 == "sv") {
						tmpm.init(types::STR_V, ts2);
					} else if (ts1 == "ss") {
						tmpm.init(types::STR_S, ts2);
					}
				}
				
			}
		};
	}
}

#endif
