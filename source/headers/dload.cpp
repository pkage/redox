#include <iostream>
#include <dlfcn.h>

using namespace std;

#include "common.h"

typedef void (*inc_t)();
int main() {
	void *payload_handle;
	payload_handle = dlopen( "./payload.o", RTLD_LAZY );
	if (!payload_handle) {
		cout << "failed to open payload [" << dlerror() << "]\n";
		dlclose(payload_handle);
		return 1;
	}

	inc_t inc = (inc_t) dlsym(payload_handle, "inc");
	if (!inc) {
		cout << "failed to find inc() [" << dlerror() << "]\n";
		dlclose(payload_handle);
		return 1;
	}
	typedef int (*get_val_t)();
	get_val_t get_val = (get_val_t) dlsym(payload_handle, "get_val");
	if (!get_val) {
		cout << "failed to find get_val() [" << dlerror() << "]\n";
		dlclose(payload_handle);
		return 1;
	}
	typedef void (*info_t)();
	info_t info = (info_t) dlsym(payload_handle, "info");
	if (!info) {
		cout << "failed to find info() [" << dlerror() << "]\n";
		dlclose(payload_handle);
		return 1;
	}
	typedef void (*echo_t)(std::string);
	echo_t echo = (echo_t) dlsym(payload_handle, "echo");
	if (!echo) {
		cout << "something done fucked up [" << dlerror() << "]\n";
		dlclose(payload_handle);
		return 1;
	}
	typedef void (*cpass_t)(common);
	cpass_t cpass = (cpass_t) dlsym(payload_handle, "cpass");
	if (!echo) {
		cout << "something done fucked up [" << dlerror() << "]\n";
		dlclose(payload_handle);
		return 1;
	}
	info();
	cout << get_val();
	inc();
	cout << get_val();
	echo("this is a test");
	dlclose(payload_handle);
	common temp; temp.payload = "common class payload";
	cpass(temp);
	cout << "\n";
	return 0;
}
