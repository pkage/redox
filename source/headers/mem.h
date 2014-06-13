//
// mem.h: redox language
// created 2014-06-08 22:15:20
// created by patrick kage
//

#ifndef RD_MEMORY
#define RD_MEMORY

#include <vector>

namespace redox {
	namespace mem {
		namespace types { // there's got to be a better way of doing this.
			enum { INT, FLOAT, CHAR, STRING , typecount};
			class VarBase {
			public:
				std::string name;
				std::string get_name() {return name;}
				void set_name(std::string n) {name = n;}
				int type; // used in casting to find out the type of a variable before using it
			};
			class Int : public VarBase {
			public:
				int value;
				int read() {return value;}
				void write(int v) {value = v;}
				int get_type() {return INT;}
				void init(int v, std::string n) {name = n; value = v; type = INT;}
			};
			class Float : public VarBase {
			public:
				float value;
				float read() {return value;}
				void write(float f) {value = f;}
				int get_type() {return FLOAT;}
				void init(float v, std::string n) {name = n; value = v; type = FLOAT;}
			};
			class Char : public VarBase {
			public:
				char value;
				char read() {return value;}
				void write(char v) {value = v;}
				int get_type() {return CHAR;}
				void init(char v, std::string n) {name = n; value = v; type = CHAR;}
			};
			class String : public VarBase {
			public:
				std::string value;
				std::string read() {return value;}
				void write(std::string v) {value = v;}
				int get_type() {return STRING;}
				void init(std::string v, std::string n) {name = n; value = v; type = STRING;}
			};
		}
		class Memory {
		private:
			std::vector<void *> slots;
		public:
			bool valid(int index) {
				return (index >= 0 && index < slots.size());
			}
			void* get_ptr(int index) {
				return slots.at(index);
			}
			int get_type(int index) {
				return static_cast<types::VarBase*>(slots.at(index))->type;
			}
			int add_slot(int type) {
				if (type < 0 || type > types::typecount) {return -1;}
				void* empty; slots.push_back(empty);
				int tmp = slots.size() - 1;
				switch (type) {
					case types::INT:
						slots.at(tmp) = new types::Int;
						break;
					case types::FLOAT:
						slots.at(tmp) = new types::Float;
						break;
					case types::CHAR:
						slots.at(tmp) = new types::Char;
						break;
					case types::STRING:
						slots.at(tmp) = new types::String;
						break;
					default:
						break;
				}
				return tmp;
			}
			int search(std::string name) {
				for (int c = 0; c < slots.size(); c++) {
					if (static_cast<types::VarBase*>(get_ptr(c))->get_name() == name) {
						return c;
					}
				}
				return -1;
			}
			bool add_item(void* value, int type, std::string name) {
				int slot = add_slot(type);
				if (slot == -1) {
					return false;
				}
				switch (type) {
					case types::INT:
						static_cast<types::Int*>(slots.at(slot))->init(*(static_cast<int*>(value)), name);
						break;
					case types::FLOAT:
						static_cast<types::Float*>(slots.at(slot))->init(*(static_cast<float*>(value)), name);
						break;
					case types::CHAR:
						static_cast<types::Char*>(slots.at(slot))->init(*(static_cast<char*>(value)), name);
						break;
					case types::STRING:
						static_cast<types::String*>(slots.at(slot))->init(*(static_cast<std::string*>(value)), name);
						break;
					default:
						break;
				}
				return true;
			}
			std::string get_name(int index) {
				if (!valid(index)) {return "";}
				return static_cast<types::VarBase*>(get_ptr(index))->get_name();
			}
		};
	}
}

#endif
