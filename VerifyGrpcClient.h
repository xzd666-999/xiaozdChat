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
	friend class Singleton<VerifyGrpcClient>;// ʹ֮�ܹ�����˽�г�Ա
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
	VerifyGrpcClient() {//�����д�����ɹ��еĹ��캯��
		std::shared_ptr<Channel> channel = grpc::CreateChannel("0.0.0.0:50051",
			grpc::InsecureChannelCredentials()); // �൱��ͨ�ż��ͨ��
		stub_ = VarifyService::NewStub(channel);
	}
private:
	std::unique_ptr<VarifyService::Stub> stub_;// �൱����ʹ��ֻ��ӵ�������ܺ�������ͨ��
};

