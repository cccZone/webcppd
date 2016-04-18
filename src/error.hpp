#ifndef ERROR_HPP
#define ERROR_HPP

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <iostream>
#include <string>

namespace webcpp {

	class error : public Poco::Net::HTTPRequestHandler {
	public:
		error(Poco::Net::HTTPServerResponse::HTTPStatus status,const std::string& message="");
		void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res);
	private:
		const Poco::Net::HTTPServerResponse::HTTPStatus resStatus;
		std::string message;
	};

}

#endif /* ERROR_HPP */

