#include <iostream>
#include "server.hpp"
#include "subsystem.hpp"

namespace webcpp {

	server::server() : helpRequested(false) {
		this->addSubsystem(new webcpp::subsystem);
	}

	server::~server() {

	}

	void server::initialize(Poco::Util::Application& self) {
		if (this->confFile.empty()) {
			this->loadConfiguration();
		} else {
			this->loadConfiguration(this->confFile);
		}
		Poco::Util::ServerApplication::initialize(self);
	}

	void server::uninitialize() {
		Poco::Util::ServerApplication::uninitialize();
	}

	void server::defineOptions(Poco::Util::OptionSet& options) {
		Poco::Util::ServerApplication::defineOptions(options);
		options.addOption(
				Poco::Util::Option("help", "h",
				"display help information on command line arguments")
				.required(false)
				.repeatable(false));
		options.addOption(
				Poco::Util::Option("conf", "c",
				"configuration file")
				.required(false)
				.repeatable(false)
				.argument("filename"));
	}

	void server::handleOption(const std::string& name, const std::string& value) {
		Poco::Util::ServerApplication::handleOption(name, value);
		if (name == "help") {
			this->helpRequested = true;
			this->stopOptionsProcessing();
		} else if (name == "conf") {
			this->confFile = value;
		}
	}

	void server::displayHelp() {
		Poco::Util::HelpFormatter hf(this->options());
		hf.setCommand(commandName());
		hf.setUsage("OPTIONS");
		hf.setHeader("A web server, based on POCO C++ library.");
		hf.format(std::cout);
	}

	int server::main(const std::vector<std::string>& args) {
		if (helpRequested) {
			this->displayHelp();
		} else {
			// wait for CTRL-C or kill
			this->waitForTerminationRequest();
		}
		return Poco::Util::Application::EXIT_OK;
	}

}