#pragma once

#include <string>
#include <vector>

struct VpnContext {
    std::string endpoint;
    std::vector<std::string> url_list;
    std::string socket_;
    unsigned int port;
};