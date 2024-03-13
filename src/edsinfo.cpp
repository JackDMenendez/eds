#include <iostream>
#include "eds.hpp"
int
main(int argc, char *argv []) {
	std::cout << EDS_DESCRIPTION << '\n'
	          << "Homepage: " << EDS_HOMEPAGE_URL << '\n'
	          << "Version: " << EDS_VERSION_MAJOR << '.'
	                         << EDS_VERSION_MINOR << '.'
				 << EDS_VERSION_CANDIDATE << '.'
				 << EDS_VERSION_BUILD << std::endl;
        return 0;
}
