#ifndef CONF_HPP
#define CONF_HPP

#include <Poco/Util/ConfigurationView.h>
namespace webcpp {

	class conf : public Poco::Util::ConfigurationView {
	public:
		conf()=delete;
		conf(Poco::Util::AbstractConfiguration &src);
		virtual ~conf()=default;
	private:

	};

}

#endif /* CONF_HPP */

