#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/SharedLibrary.h>
#include <Poco/StringTokenizer.h>
#include <Poco/URI.h>
#include <Poco/File.h>
#include "factory.hpp"
#include "error.hpp"

namespace webcpp {

	factory::factory(webcpp::conf& conf) :
	libHandlerDir(conf.getString("libHandlerDir", "/usr/bin")) {
	}

	Poco::Net::HTTPRequestHandler* factory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
		std::string uri = Poco::URI(request.getURI()).getPath();
		uri.erase(0, 1);
		if (uri.back() == '/') {
			uri.pop_back();
		}
		Poco::StringTokenizer tokenizer(uri, "/");
		int n = tokenizer.count();
		std::string libName("libhome"), funcName("indexImpl");
		switch (n) {
			case 0:
				break;
			case 1:
				libName = "lib" + tokenizer[0];
				break;
			default:
				libName = "lib" + tokenizer[0];
				funcName = tokenizer[1] + "Impl";
		}

		std::string libPath(this->libHandlerDir + "/" + libName + Poco::SharedLibrary::suffix());
		if (!Poco::File(libPath).exists()) {
			return new webcpp::error(Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND, libName + " is not found.");
		}
		Poco::SharedLibrary libLoader;
		libLoader.load(libPath);
		if (!libLoader.isLoaded()) {
			return new webcpp::error(Poco::Net::HTTPServerResponse::HTTP_SERVICE_UNAVAILABLE, libName + " is not loaded.");
		}


		if (!libLoader.hasSymbol(funcName)) {
			return new webcpp::error(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED, funcName + " is not found.");
		}

		typedef Poco::Net::HTTPRequestHandler * (*IMPL)();
		IMPL impl = (IMPL) libLoader.getSymbol(funcName);
		Poco::Net::HTTPRequestHandler *handler = 0;
		handler = impl();
		if (!handler) {
			handler = new webcpp::error(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED, funcName + " is not running.");
		}
		return handler;
	}

}