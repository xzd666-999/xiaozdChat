#pragma once
#include "const.h"

class HttpConnection :public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class  LogicSystem;
	HttpConnection(tcp::socket socket);
	void Start();
private:
	void CheckDeadline();
	void WriteResponse();// 应答连接
	void HandleReq();	 // 处理请求
	void PreParseGetParam();
	boost::asio::ip::tcp::socket _socket;
	beast::flat_buffer _buffer{8192}; // 8k的用于接收http请求报文内容的缓冲区
	http::request<http::dynamic_body> _requst;
	http::response<http::dynamic_body> _response;
	net::steady_timer deadline_{  
		_socket.get_executor(),std::chrono::seconds(60)
	}; // 定时器放在底层的事件循环
	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
};

