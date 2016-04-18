#ifndef SUBSYSTEM_HPP
#define SUBSYSTEM_HPP

#include <Poco/Util/Subsystem.h>
#include <Poco/Net/HTTPServer.h>

namespace webcpp {

	class subsystem : public Poco::Util::Subsystem {
	public:

		virtual const char *name() const;

		void initialize(Poco::Util::Application& app);

		void uninitialize();

	private:
		Poco::Net::HTTPServer *server;
	public:
		const static int DEFAULT_PORT;
		const static int DEFAULT_MAX_QUEUED;
		const static int DEFAULT_MAX_THREADS;
		const static std::string DEFAULT_SOFTWARE_VERSION;
	};
}
#endif /* SUBSYSTEM_HPP */

