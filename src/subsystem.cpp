#include <Poco/Util/Application.h>
#include <Poco/ThreadPool.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>

#include <iostream>

#include "subsystem.hpp"
#include "conf.hpp"
#include "factory.hpp"

namespace webcpp {

	const int subsystem::DEFAULT_PORT = 8888;
	const int subsystem::DEFAULT_MAX_QUEUED = 100;
	const int subsystem::DEFAULT_MAX_THREADS = 50;
	const std::string subsystem::DEFAULT_SOFTWARE_VERSION = "webcppd/0.1.1";

	const char* subsystem::name() const {
		return "http::Server";
	}

	void subsystem::initialize(Poco::Util::Application& app) {
		webcpp::conf serverConf(app.config());
		unsigned short port = static_cast<unsigned short> (serverConf.getInt("port", subsystem::DEFAULT_PORT));
		int maxQueued = serverConf.getInt("maxQueued", subsystem::DEFAULT_MAX_QUEUED);
		int maxThreads = serverConf.getInt("maxThreads", subsystem::DEFAULT_MAX_THREADS);
		std::string softwareVersion = serverConf.getString("softwareVersion", subsystem::DEFAULT_SOFTWARE_VERSION);

		Poco::ThreadPool::defaultPool().addCapacity(maxThreads);

		Poco::Net::HTTPServerParams* pars = new Poco::Net::HTTPServerParams;
		pars->setMaxQueued(maxQueued);
		pars->setMaxThreads(maxThreads);
		pars->setSoftwareVersion(softwareVersion);
		this->server = new Poco::Net::HTTPServer(new webcpp::factory(serverConf), port, pars);
		this->server->start();
		
	}

	void subsystem::uninitialize() {
		this->server->stop();
		delete server;
	}




}
