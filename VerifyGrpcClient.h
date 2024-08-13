#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;


class VerifyGrpcClient:public Singleton<VerifyGrpcClient>
{
	friend class Singleton<VerifyGrpcClient>;// 使之能够访问私有成员
public:
	GetVarifyRsp GetVarifyCode(std::string email) {
		ClientContext context;
		GetVarifyRsp reply;
		GetVarifyReq request;

		request.set_email(email);
		Status status = stub_->GetVarifyCode(&context, request, &reply);
		if (status.ok())
		{
			return reply;
		}
		else {
			reply.set_error(ErrorCodes::RPCFailed);
			return reply;
		}
	}
private:
	VerifyGrpcClient() {//如果不写会生成公有的构造函数
		std::shared_ptr<Channel> channel = grpc::CreateChannel("0.0.0.0:50051",
			grpc::InsecureChannelCredentials()); // 相当于通信间的通道
		stub_ = VarifyService::NewStub(channel);
	}
private:
	std::unique_ptr<VarifyService::Stub> stub_;// 相当于信使，只有拥有它才能和其他人通信
};

