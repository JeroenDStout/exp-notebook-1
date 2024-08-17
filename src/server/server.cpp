#include "server/server.h"

#include "server/uwebsockets.h"
#include "version/git_version.h"

int main() {
	std::cout
	  << "Notebook Experiment 1" << gaos::version::get_git_essential_version() << std::endl << std::endl
	  << gaos::version::get_compile_stamp() << std::endl << std::endl
	  << gaos::version::get_git_history() << std::endl << std::endl
    ;

    /* Overly simple hello world app */
	uWS::SSLApp({
	  .key_file_name = "misc/key.pem",
	  .cert_file_name = "misc/cert.pem",
	  .passphrase = "1234"
	}).get("/*", [](auto *res, auto */*req*/) {
	    res->end("Hello world!");
	}).listen(3000, [](auto *listen_socket) {
	    if (listen_socket) {
			std::cout << "Listening on port " << 3000 << std::endl;
	    }
	}).run();
}