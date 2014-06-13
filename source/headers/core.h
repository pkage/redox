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
//			bool add_scope_var(void* ptr, int type, );
		};
		class File {
		public:
			
			
			
		};
	}

}

#endif
