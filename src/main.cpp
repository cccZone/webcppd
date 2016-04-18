#include "server.hpp"

int main(int argc, char** argv) {
	webcpp::server server;
	return server.run(argc, argv);
}

