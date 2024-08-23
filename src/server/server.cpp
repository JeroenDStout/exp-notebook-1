#include "server/server.h"

#include "server/uwebsockets.h"
#include "version/git_version.h"

int main() {
	std::cout
	  << "Notebook Experiment 1" << gaos::version::get_git_essential_version() << std::endl << std::endl
	  << gaos::version::get_compile_stamp() << std::endl << std::endl
	  << gaos::version::get_git_history() << std::endl << std::endl
    ;

	struct per_socket_data {
        std::string topic;
	};

    /* Overly simple hello world app */
	uWS::SSLApp *app = new uWS::SSLApp({
	  .key_file_name  = "misc/key.pem",
	  .cert_file_name = "misc/cert.pem",
	  .passphrase     = "1234"
	});

	app->ws<per_socket_data>("/*", {
        // Settings
        .compression              = uWS::DISABLED,
        .maxPayloadLength         = 16 * 1024 * 1024,
        .idleTimeout              = 60,
        .maxBackpressure          = 16 * 1024 * 1024,
        .closeOnBackpressureLimit = false,
        .resetIdleTimeoutOnSend   = true,
        .sendPingsAutomatically   = false,

        // Handlers
        .upgrade = nullptr,
        .open = [](auto *ws) {
            std::cout << "Open" << std::endl;
            
            per_socket_data *ps_data = (per_socket_data *) ws->getUserData();
            ps_data->topic = std::to_string((uintptr_t)ws);
            ws->subscribe(ps_data->topic);
        },
        .message = [&app](auto *ws, std::string_view message, uWS::OpCode opCode) {
            std::cout << "Message: " << message << std::endl;

            per_socket_data *ps_data = (per_socket_data *) ws->getUserData();
            app->publish(ps_data->topic, message, opCode);
        },
        .drain = [](auto*) {
            std::cout << "Drain" << std::endl;
        },
        .ping = [](auto*, std::string_view) {
            std::cout << "Ping" << std::endl;
        },
        .pong = [](auto*, std::string_view) {
            std::cout << "Pong" << std::endl;
        },
        .close = [](auto*, int, std::string_view) {
            std::cout << "Close" << std::endl;
        }
    }).listen(9001, [](auto *listen_s) {
        if (listen_s) {
            std::cout << "Listening on port " << 9001 << std::endl;
        }
    });
    
    app->run();

    delete app;

    uWS::Loop::get()->free();
}