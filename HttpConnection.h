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
	void WriteResponse();// Ӧ������
	void HandleReq();	 // ��������
	void PreParseGetParam();
	boost::asio::ip::tcp::socket _socket;
	beast::flat_buffer _buffer{8192}; // 8k�����ڽ���http���������ݵĻ�����
	http::request<http::dynamic_body> _requst;
	http::response<http::dynamic_body> _response;
	net::steady_timer deadline_{  
		_socket.get_executor(),std::chrono::seconds(60)
	}; // ��ʱ�����ڵײ���¼�ѭ��
	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
};

