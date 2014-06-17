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
	cout << "I/O with mem::Memory wrappers\n";
	cout << "Writing \"C++ FTW\" to a string using a add_item cast with name testStr\n";
	bmem.add_item(new string("C++ FTW"), redox::mem::types::STRING, "testStr");
	cout << "Reading string back...\n";
	cout << "Value: " << static_cast<redox::mem::types::String*>(bmem.get_ptr(bmem.search("testStr")))->read() << '\n';
	cout << "Name: " << bmem.get_name(bmem.search("testStr")) << '\n';
	cout << "\nLIBRARY TEST\n";
	cout << "Creating lib object...\n";
	redox::libs::Lib lib;
	cout << "Initializing with \"exl\" as target...\n";
	lib.init("exl");
	cout << "Checking equeue... ";
	if (error::equeue.are_errors()) {
		cout << "Errors detected! Aborting...\nTrace: \n" << error::equeue.generate_report() << "\n";
		error::equeue.clear();
	} else {
		cout << "empty.\n";
		cout << "Method declarations in \"exl\": " << lib.methodl << "\n";
		cout << "getting library name: " << lib.runfcn("__name", "") << "\n";
		if (error::equeue.responder("getting library name with __name()")) return 1;
	}
	cout << "\nSTL TEST\n";
	libs::Lib term;
	cout << "Loading stl::term...\n";
	term.init("term");
	if (error::equeue.responder("loading \"term\" library")) return 1;
	cout << "Method list: " << term.methodl << "\n";
	cout << "Printing term.__name with term.println...\n";
	term.runfcn("println", term.runfcn("__name",""));
	if (error::equeue.responder("accessing functions in \"term\" stl library")) return 1;
	cout << "Getting input and echoing...\n";
	term.runfcn("print", "name: ");
	term.runfcn("println", term.runfcn("get_line",""));
	if (error::equeue.responder("accessing functions in \"term\" stl library")) return 1;
	cout << "echoing complete.\n";
	
	return 0;
}

void writeMem(redox::mem::Memory &bm) {
	static_cast<redox::mem::types::Int*>(bm.get_ptr(bm.add_slot(redox::mem::types::INT)))->init(10, "int1");
}
