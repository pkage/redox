//
// error.h: redox language
// created 2014-06-11 15:15:13
// created by patrick kage
//

#ifndef RD_ERROR
#define RD_ERROR

#include <vector>

namespace redox {
	namespace error {
		enum Etype {
			FILENOTFOUND,
			INVALIDFILE,
			SYNTAXERROR,
			PARSEERROR,
			MISMATCHEDBLOCKS,
			LIBNOTFOUND,
			INVALIDLIB,
			LIBMETHODNOTFOUND,
			INTERNAL,
			UNKERROR
		};	
		class Error {
		public:
			std::string error, error_type, origin;
			bool fatal, catchable;
			void init(std::string error, std::string type, std::string origin, bool fatal, bool catchable) {
				this->error = error;
				this->error_type = type;
				this->origin = origin;
				this->fatal = fatal;
				this->catchable = catchable;
			}
			void factory(Etype et, std::string origin) {
				switch (et) {
					case FILENOTFOUND:
						init("FileNotFound", "File", origin, true, true);
						break;
					case INVALIDFILE:
						init("InvalidFile", "File", origin, true, true);
						break;
					case SYNTAXERROR:
						init("SyntaxError", "Syntax", origin, true, false);
						break;
					case PARSEERROR:
						init("ParseError", "Syntax", origin, true, false);
						break;
					case MISMATCHEDBLOCKS:
						init("MismatchedBlocks", "Syntax", origin, true, false);
						break;
					case LIBNOTFOUND:
						init("LibraryNotFound", "File", origin, true, false);
						break;
					case INVALIDLIB:
						init("InvalidLibraryError", "Library", origin, true, false);
						break;
					case LIBMETHODNOTFOUND:
						init("LibraryMethodNotFoundError", "Library", origin, true, true);
					case INTERNAL:
						init("InternalError", "Internal", origin, true, false);
						break;
					case UNKERROR:
					default:
						init("UnknownError", "Unknown", origin, true, false);
						break;
				}
			}
		};
		class ErrorQueue {
		private:
			std::vector<Error> queue;
		public:
			int get_length() {return queue.size();}
			Error get_error(int n) {
				if (n >= get_length() || n < 0) {
					Error e;e.factory(INTERNAL, "Invalid error list access");
					return e;
				}
				return queue.at(n);
			}
			void add_error(Etype et, std::string origin) {
				Error tmp; tmp.factory(et, origin);
				queue.push_back(tmp);
			}
			void clear() {
				queue.clear();
			}
			bool are_errors() {return (get_length() > 0);}
			std::string generate_report() {
				if (get_length() == 0) return "no errors.";
				std::string out = "";
				for (int c = 0; c < get_length(); c++) {
					out += "Error: " + queue.at(c).error + "\n\tType: " + queue.at(c).error_type + "\n\tOrigin: " + queue.at(c).origin + "\n";
				}
				return out;
			}
			bool responder(std::string conditions) {
				if (!are_errors()) return false;
				std::cout << "An error occurred!\nHere's what we know:\n" << generate_report();
				return true;
			}
		};
		ErrorQueue equeue;
	}
}

#endif
