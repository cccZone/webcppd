#include "conf.hpp"

namespace webcpp {

	conf::conf(Poco::Util::AbstractConfiguration &src)
	: Poco::Util::ConfigurationView("http", &src) {

	}

}


