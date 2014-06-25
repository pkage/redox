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
		void execBlock(core::File &f, mem::Memory &mem, core::Block &block) {
			for (int c = 0; c < block.sb.length(); c++) {
				std::cout << "This function is in no way prepared to handle: " << block.sb.get_line(c);
			}
		}
	}
}

#endif
