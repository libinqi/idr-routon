#ifndef RoutonRead_H
#define RoutonRead_H
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include "sdtapi.h"
#include "Thread.h"

class RoutonRead : public Thread {
public:
	static void Init(v8::Handle<v8::Object> exports);

private:
	explicit RoutonRead();
	~RoutonRead();

	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void DR_InitComm(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void DR_CloseComm(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void DR_Authenticate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void DR_ReadBaseInfos(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void DR_IC_ReadCardSN(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void DR_Open_RealReadCard(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void DR_Start_RealReadCard(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void DR_Stop_RealReadCard(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void DR_Routon_ShutDownAntenna(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Persistent<v8::Function> constructor;
    static void execute();
};

#endif
