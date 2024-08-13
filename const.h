#pragma once
#include <map>
#include <memory>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "Singleton.h"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

enum ErrorCodes {
	Success = 0,
	Error_Json = 1001,
	RPCFailed = 1002
};

class ConfigMgr;
extern ConfigMgr gCfgMgr;