#include "error.hpp"

namespace webcpp {

	error::error(Poco::Net::HTTPServerResponse::HTTPStatus status, const std::string& message) : resStatus(status), message(message) {

	}

	void error::handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res) {
		res.setChunkedTransferEncoding(true);
		res.setStatusAndReason(this->resStatus);
		res.setContentType("text/html");
		std::ostream& os = res.send();
		os << "<html><head><title>"
				<< static_cast<int> (res.getStatus())
				<< " "
				<< res.getReason()
				<< "</title><body bgcolor=\"white\"><center><h1>"
				<< static_cast<int> (res.getStatus())
				<< " "
				<< res.getReason()
				<< "</h1></center><hr/>"
				<< this->message
				<< "</body></html>";
	}


}