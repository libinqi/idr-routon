#include "RoutonRead.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <windows.h>

using namespace v8;

Persistent<Function> RoutonRead::constructor;

RoutonRead::RoutonRead()
{
	doExecute = execute;
}

RoutonRead::~RoutonRead()
{
}

static std::string GBKToUTF8(const std::string &strGBK)
{
	static std::string strOutUTF8 = "";
	WCHAR *str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char *str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[] str1;
	str1 = NULL;
	delete[] str2;
	str2 = NULL;
	return strOutUTF8;
}

void RoutonRead::Init(Handle<Object> exports)
{
	Isolate *isolate = Isolate::GetCurrent();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "RoutonRead"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "InitComm", DR_InitComm);
	NODE_SET_PROTOTYPE_METHOD(tpl, "CloseComm", DR_CloseComm);
	NODE_SET_PROTOTYPE_METHOD(tpl, "Authenticate", DR_Authenticate);
	NODE_SET_PROTOTYPE_METHOD(tpl, "ReadBaseInfos", DR_ReadBaseInfos);
	NODE_SET_PROTOTYPE_METHOD(tpl, "ICReadCardSN", DR_IC_ReadCardSN);

	NODE_SET_PROTOTYPE_METHOD(tpl, "OpenRealReadCard", DR_Open_RealReadCard);
	NODE_SET_PROTOTYPE_METHOD(tpl, "StartRealReadCard", DR_Start_RealReadCard);
	NODE_SET_PROTOTYPE_METHOD(tpl, "StopRealReadCard", DR_Stop_RealReadCard);

	NODE_SET_PROTOTYPE_METHOD(tpl, "ShutDownAntenna", DR_Routon_ShutDownAntenna);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "RoutonRead"),
				 tpl->GetFunction());
}

void RoutonRead::New(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.IsConstructCall())
	{
		// Invoked as constructor: `new MyObject(...)`

		RoutonRead *obj = new RoutonRead();
		obj->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	}
	else
	{
		// Invoked as plain function `MyObject(...)`, turn into construct call.
		const int argc = 1;
		Local<Value> argv[argc] = {args[0]};
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> result =
			cons->NewInstance(context, argc, argv).ToLocalChecked();
		args.GetReturnValue().Set(result);
	}
}

void RoutonRead::DR_InitComm(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int iPort = args[0]->Int32Value();
	int result = InitComm(iPort);
	args.GetReturnValue().Set(Number::New(isolate, result));
}

void RoutonRead::DR_CloseComm(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int result = CloseComm();
	args.GetReturnValue().Set(Number::New(isolate, result));
}

void RoutonRead::DR_Routon_ShutDownAntenna(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int result = Routon_ShutDownAntenna();
	args.GetReturnValue().Set(Number::New(isolate, result));
}

void RoutonRead::DR_Authenticate(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int result = Authenticate();
	args.GetReturnValue().Set(Number::New(isolate, result));
}

void RoutonRead::DR_ReadBaseInfos(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	char *name = new char[31];		 //姓名
	char *gender = new char[3];		 //性别
	char *folk = new char[10];		 //民族
	char *birthDay = new char[9];	//生日
	char *code = new char[19];		 //身份证号码
	char *address = new char[71];	//地址
	char *agency = new char[31];	 //签证机关
	char *expireStart = new char[9]; //有效期起始日期
	char *expireEnd = new char[9];   //有效期截至日期

	int result = Authenticate();
	if (result)
	{
		result = ReadBaseInfos(name, gender, folk, birthDay, code, address, agency, expireStart, expireEnd);
		if (result)
		{
			Local<Object> readInfo = Object::New(isolate);
			readInfo->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, GBKToUTF8(name).c_str()));
			readInfo->Set(String::NewFromUtf8(isolate, "gender"), String::NewFromUtf8(isolate, GBKToUTF8(gender).c_str()));
			readInfo->Set(String::NewFromUtf8(isolate, "folk"), String::NewFromUtf8(isolate, GBKToUTF8(folk).c_str()));
			readInfo->Set(String::NewFromUtf8(isolate, "birthDay"), String::NewFromUtf8(isolate, birthDay));
			readInfo->Set(String::NewFromUtf8(isolate, "code"), String::NewFromUtf8(isolate, code));
			readInfo->Set(String::NewFromUtf8(isolate, "address"), String::NewFromUtf8(isolate, GBKToUTF8(address).c_str()));
			readInfo->Set(String::NewFromUtf8(isolate, "agency"), String::NewFromUtf8(isolate, GBKToUTF8(agency).c_str()));
			readInfo->Set(String::NewFromUtf8(isolate, "expireStart"), String::NewFromUtf8(isolate, expireStart));
			readInfo->Set(String::NewFromUtf8(isolate, "expireEnd"), String::NewFromUtf8(isolate, expireEnd));

			delete[] name;
			delete[] gender;
			delete[] folk;
			delete[] birthDay;
			delete[] code;
			delete[] address;
			delete[] agency;
			delete[] expireStart;
			delete[] expireEnd;
			args.GetReturnValue().Set(readInfo);
		}
		else
		{
			args.GetReturnValue().Set(Number::New(isolate, 0));
		}
	}
	else
	{
		args.GetReturnValue().Set(Number::New(isolate, 0));
	}
}

void RoutonRead::DR_IC_ReadCardSN(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	char *code = new char[16]; //IC A卡卡号

	int result = Routon_IC_FindCard();
	if (result)
	{
		result = Routon_IC_HL_ReadCardSN(code);
		if (result)
		{
			std::string cardIdStr = code;
			cardIdStr = cardIdStr.substr(0, 2) + cardIdStr.substr(2, 2) + cardIdStr.substr(4, 2) + cardIdStr.substr(6, 2);
			//int cardId = strtol(cardIdStr.c_str(), NULL, 16);
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, cardIdStr.c_str()));
			delete[] code;
		}
		else
		{
			args.GetReturnValue().Set(Number::New(isolate, 0));
		}
	}
	else
	{
		args.GetReturnValue().Set(Number::New(isolate, 0));
	}
}

void RoutonRead::DR_Open_RealReadCard(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int iPort = args[0]->Int32Value();

	int result = InitComm(iPort);

	if (result)
	{
		bind(isolate, Local<Function>::Cast(args[1]), Local<Function>::Cast(args[2]));
	}

	args.GetReturnValue().Set(Number::New(isolate, result));
}

void RoutonRead::DR_Start_RealReadCard(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	resume();

	args.GetReturnValue().Set(Number::New(isolate, 1));
}

void RoutonRead::DR_Stop_RealReadCard(const FunctionCallbackInfo<Value> &args)
{
	Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	suspend();

	args.GetReturnValue().Set(Number::New(isolate, 1));
}

void RoutonRead::execute()
{
	Receiver receiver;

	if (Authenticate())
	{
		receiver.type = ReceiveType::IDCard;

		int result = ReadBaseInfosPhoto(receiver.name, receiver.gender, receiver.folk, receiver.birthDay, receiver.code, receiver.address, receiver.agency, receiver.expireStart, receiver.expireEnd, "C:\\");

		if (result)
		{
			doReceive(receiver);
		}
		else
		{
			doError(0, GBKToUTF8("读取身份证信息错误!"));
		}
	}
	else if (Routon_IC_FindCard())
	{
		receiver.type = ReceiveType::ICCard;

		int result = Routon_IC_HL_ReadCardSN(receiver.code);

		if (result)
		{
			doReceive(receiver);
		}
		else
		{
			doError(0, GBKToUTF8("读取卡信息错误!"));
		}
	}
}

void InitAll(Handle<Object> exports)
{
	RoutonRead::Init(exports);
}

NODE_MODULE(RoutonRead, InitAll)
