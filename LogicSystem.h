#pragma once
#include "const.h"
class HttpConnection;

typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem() {};
	bool HandleGet(std::string , std::shared_ptr<HttpConnection>);
	void RegGet(std::string ,HttpHandler handler);
private:
	LogicSystem();
	// 处理post请求的集合
	std::map<std::string, HttpHandler> _post_handlers;
	// 处理get请求的集合
	std::map<std::string, HttpHandler> _get_handlers;
};