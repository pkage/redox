#include <iostream>

#include "headers/all.h"

using namespace std;
using namespace redox;

void writeMem(redox::mem::Memory &bm);

int main() {
	cout << "MEMORY TEST\n";
	redox::mem::Memory bmem;
	writeMem(bmem);
	cout << "Wrote memory slot 0\n";
	cout << "Begin read...\n";
	cout << "Name: " << static_cast<redox::mem::types::Int*>(bmem.get_ptr(0))->get_name() << "\n";
	cout << "Value: " << static_cast<redox::mem::types::Int*>(bmem.get_ptr(0))->read() << "\n";
	cout << "Reading name with VarBase cast (!):\n";
	cout << "Name: " << static_cast<redox::mem::types::VarBase*>(bmem.get_ptr(0))->get_name() << "\n";
	cout << "Type: " << bmem.get_type(bmem.search("int1")) << "\n";
	return 0;
}

void writeMem(redox::mem::Memory &bm) {
	static_cast<redox::mem::types::Int*>(bm.get_ptr(bm.add_slot(redox::mem::types::INT)))->init(10, "int1");
}
