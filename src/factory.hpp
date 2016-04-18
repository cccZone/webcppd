#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include "conf.hpp"

namespace webcpp {

	class factory : public Poco::Net::HTTPRequestHandlerFactory {
	public:
		factory(webcpp::conf& conf);
		Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
	private:
		const std::string libHandlerDir;
	};
}
#endif /* FACTORY_HPP */

