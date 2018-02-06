#ifndef THREAD_H
#define THREAD_H

#include "Baton.h"

class Thread : public node::ObjectWrap
{
public:
  Thread();
  ~Thread();
  static void bind(Isolate *isolate, Local<Function> onReceive, Local<Function> onError);
  static void resume(void);
  static void suspend(void);

protected:
  static void (*doExecute)();
  static void doReceive(Receiver receiver);
  static void doError(int code, string message);

private:
  static Local<Value> getObject(Isolate *isolate, Receiver receiver);
  static void callback(uv_async_t *handle, int status);
  static void run(uv_work_t *request);
  static void stop(uv_work_t *request, int status);

private:
  static Baton *baton;
  static uv_loop_t *loop;
  static bool isWaiting;
  static bool isRan;
  static bool isDied;
};

#endif // THREAD_H