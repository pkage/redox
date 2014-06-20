//
// core.h: redox language
// created 2014-06-02 03:15:26
// created by patrick kage
//

#ifndef RD_CORE
#define RD_CORE

#include <vector>
#include <fstream>
#include "mem.h"
#include "library.h"
#include "error.h"

namespace redox {
	namespace core {
		class StringBundle {
		private:
			std::vector<std::string> bundle;
		public:
			bool valid(int index) {
				return (index >= 0 && index < bundle.size());
			}
			std::string get_line(int index) {return ((valid(index)) ? bundle.at(index) : "");}
			void add_line(std::string str) {bundle.push_back(str);}
			void clear() {bundle.clear();}
			int length() {return bundle.size();}
			bool overwrite(int index, std::string str) {if (valid(index)) bundle.at(index) = str; return valid(index);}
		};
		class Block {
		public:
			StringBundle sb;
			bool from_block(Block &b, int start, int end) {
				if (start > end) return false;
				if (!b.sb.valid(start) || !b.sb.valid(end)) return false;
				sb.clear();
				for (int c = start; c < end; c++) {
					sb.add_line(b.sb.get_line(c));
				}
				return true;
			}
		};
		class Function {
		public:
			Block contents;
			int returntype;
			mem::Memory scope;
			bool add_scope_var(void* ptr, int type, std::string name) {
				scope.add_item(ptr, type, name);
				return false;
			}
			bool process_arg_string(std::string args) {
				return false;
			}
		};
		class File {
		public:
			StringBundle raw;
			mem::Memory globals;
			std::vector<Function> functions;
			std::vector<libs::Lib> libraries;
			
			void load_from_file(std::string path) {
				raw.clear();
				std::ifstream ifile;
				ifile.open(path.c_str());
				if (!ifile) {
					error::equeue.add_error(error::INVALIDFILE, "File \"" + path + "\" not found");
					return;
				}
				std::string ln;
				while (!ifile.eof()) {
					std::getline(ifile, ln);
					raw.add_line(ln);
				}
			}
			void initialize_libs() {
				runner::Parser ps;
				for (int c = 0; c < raw.length(); c++) {
					ps.clear();
					ps.parseln(raw.get_line(c));
					if (ps.optype == runner::optypes::IMPORT) {
						libs::Lib lib;
						if (!(ps.size() == 2 || ps.size() == 4)) {
							error::equeue.add_error(error::SYNTAXERROR, "library incorrectly specified for loading");
							return;
						}
						for (int c = 1; c < ps.size(); c++) {
							if (ps.component(c) == "") {
								error::equeue.add_error(error::SYNTAXERROR, "library incorrectly specified for loading");
								return;
							}
							
						}
						if (ps.component(2) == "as") {
							lib.init(tools::get_lib_path() + ps.component(1), ps.component(3)); // import LIB as ALIAS
						} else {
							lib.init(tools::get_lib_path() + ps.component(1), ps.component(1));
						}
						libraries.push_back(lib);
					}
				}
			}
			void DBG_printlibs() {
				for (int c = 0; c < libraries.size(); c++) {
					std::cout << "
				}
			}
		};
	}

}

#endif
