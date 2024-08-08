#include "HttpConnection.h"
#include "LogicSystem.h"
HttpConnection::HttpConnection(tcp::socket socket):
	_socket(std::move(socket))
{
}

void HttpConnection::Start()
{
	auto self = shared_from_this();
	http::async_read(_socket, _buffer, _requst, [self](beast::error_code ec, std::size_t bytes_transferred) {
		try {
			if (ec)
			{
				std::cout << "http read err is : " << ec.what() << std::endl;
				return;
			}
			boost::ignore_unused(bytes_transferred);
			self->HandleReq();
			self->CheckDeadline();
		}
		catch (std::exception &exp)
		{
			std::cout << "exception" << exp.what() << std::endl;
		}
	});
}

void HttpConnection::CheckDeadline()
{
	auto self = shared_from_this();
	deadline_.async_wait([self](beast::error_code ec) {
		if(!ec)
		{ 
			// ��ʱ��û����
			self->_socket.close(ec);
		}
	});
}

void HttpConnection::WriteResponse()
{
	auto self = shared_from_this();
	// ���ð���ĳ��Ȳ��ܱ���ճ��
	_response.content_length(_response.body().size());
	http::async_write(_socket, _response, [self](beast::error_code ec, std::size_t bytes_transferred) {
		self->_socket.shutdown(tcp::socket::shutdown_send, ec);
		self->deadline_.cancel();// ȡ����ʱ��
	});
}

void HttpConnection::HandleReq()
{
	// ���ð汾
	_response.version(_requst.version());
	// ���ö�����
	_response.keep_alive(false);
	if (_requst.method() == http::verb::get)
	{
		// ����get���� 
		bool sucess = LogicSystem::GetInstance()->HandleGet(_requst.target(),shared_from_this());
		if (!sucess)
		{
			_response.result(http::status::not_found);
			_response.set(http::field::content_type,"text/plain");
			beast::ostream(_response.body()) << "url not found\r\n";
			WriteResponse();// ��Ӧ
			return;
		}
		_response.result(http::status::ok);
		_response.set(http::field::server, "GateServer");
		WriteResponse();// ��Ӧ
		return;
	}
}
