#include "Thread.h"

Baton *Thread::baton = NULL;
uv_loop_t *Thread::loop = NULL;
void (*Thread::doExecute)() = NULL;
bool Thread::isWaiting = false;
bool Thread::isRan = false;
bool Thread::isDied = false;

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

static std::string UNICODE_to_UTF8(const WCHAR *pSrc, int stringLength)
{
    static std::string strOutUTF8 = "";

    char *buffer = new char[stringLength + 1];
    WideCharToMultiByte(CP_UTF8, NULL, pSrc, wcslen(pSrc), buffer, stringLength, NULL, NULL);
    buffer[stringLength] = '\0';

    strOutUTF8 = buffer;

    delete[] buffer;

    const string &delim = " \t";
    string r = strOutUTF8.erase(strOutUTF8.find_last_not_of(delim) + 1);
    return r.erase(0, r.find_first_not_of(delim));
}

static std::string base64_encode(unsigned char const *bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';
    }

    return ret;
}

Local<Value> Thread::getObject(Isolate *isolate, Receiver receiver)
{
    Local<Object> data = Object::New(isolate);
    data->Set(String::NewFromUtf8(isolate, "cardType"), Number::New(isolate, receiver.type));

    switch (baton->receiver.type)
    {
        case ReceiveType::IDCard:
        {
			data->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, GBKToUTF8(receiver.name).c_str()));
			data->Set(String::NewFromUtf8(isolate, "gender"), String::NewFromUtf8(isolate, GBKToUTF8(receiver.gender).c_str()));
			data->Set(String::NewFromUtf8(isolate, "folk"), String::NewFromUtf8(isolate, GBKToUTF8(receiver.folk).c_str()));
			data->Set(String::NewFromUtf8(isolate, "birthDay"), String::NewFromUtf8(isolate, receiver.birthDay));
			data->Set(String::NewFromUtf8(isolate, "code"), String::NewFromUtf8(isolate, receiver.code));
			data->Set(String::NewFromUtf8(isolate, "address"), String::NewFromUtf8(isolate, GBKToUTF8(receiver.address).c_str()));
			data->Set(String::NewFromUtf8(isolate, "agency"), String::NewFromUtf8(isolate, GBKToUTF8(receiver.agency).c_str()));
			data->Set(String::NewFromUtf8(isolate, "expireStart"), String::NewFromUtf8(isolate, receiver.expireStart));
			data->Set(String::NewFromUtf8(isolate, "expireEnd"), String::NewFromUtf8(isolate, receiver.expireEnd));
            break;
        }

        case ReceiveType::ICCard:
        {
			std::string cardIdStr = receiver.code;
			cardIdStr = cardIdStr.substr(0, 2) + cardIdStr.substr(2, 2) + cardIdStr.substr(4, 2) + cardIdStr.substr(6, 2);
			data->Set(String::NewFromUtf8(isolate, "code"), String::NewFromUtf8(isolate, cardIdStr.c_str()));
            break;
        }
    }

    return {data};
}

void Thread::callback(uv_async_t *request, int status)
{
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Baton *baton = static_cast<Baton *>(request->data);
    Local<Value> argv[2];

    if (!baton->onReceive.IsEmpty() && (baton->state == 0))
    {
        // argv[0] = Number::New(isolate, baton->receiver.type);
        argv[0] = getObject(isolate, baton->receiver);
        // argv[1] = baton->receiver.data.;
        Local<Function>::New(isolate, baton->onReceive)->Call(isolate->GetCurrentContext()->Global(), 1, argv);
    }

    if (!baton->onError.IsEmpty() && (baton->state == 1))
    {
        argv[0] = Number::New(isolate, baton->error.code);
        argv[1] = String::NewFromUtf8(isolate, baton->error.message.c_str());
        Local<Function>::New(isolate, baton->onError)->Call(isolate->GetCurrentContext()->Global(), 2, argv);
    }
}

Thread::Thread()
{
}

void Thread::run(uv_work_t *request)
{
    isDied = false;

    while (true)
    {
        try
        {
            if (isDied)
            {
                break;
            }

            uv_mutex_lock(&baton->mutex);
            if (baton->isWaiting)
            {
                uv_cond_wait(&baton->condvar, &baton->mutex);
                baton->isWaiting = false;
            }
            uv_mutex_unlock(&baton->mutex);

            doExecute();
            Sleep(10);
        }
        catch (exception &e)
        {
            cout << "exception: " << e.what() << endl;
        }
    }

    isDied = true;
}

void Thread::stop(uv_work_t *request, int status)
{
    isDied = true;
    Baton *baton = static_cast<Baton *>(request->data);
    uv_close((uv_handle_t *)&baton->asyncRequest, NULL);
}

void Thread::bind(Isolate *isolate, Local<Function> onReceive, Local<Function> onError)
{
    baton = new Baton();
    baton->onReceive.Reset(isolate, Persistent<Function>::Persistent(isolate, onReceive));
    baton->onError.Reset(isolate, Persistent<Function>::Persistent(isolate, onError));
    baton->request.data = baton;

    loop = uv_default_loop();
    uv_async_init(loop, &baton->asyncRequest, (uv_async_cb)callback);
    uv_cond_init(&baton->condvar);
    uv_mutex_init(&baton->mutex);
}

void Thread::resume(void)
{
    if (!isRan)
    {
        uv_queue_work(loop, &baton->request, run, stop);
        uv_run(loop, UV_RUN_NOWAIT);
        isRan = true;
    }

    uv_mutex_lock(&baton->mutex);
    uv_cond_signal(&baton->condvar);
    uv_mutex_unlock(&baton->mutex);
}

void Thread::suspend(void)
{
    uv_mutex_lock(&baton->mutex);
    baton->isWaiting = true;
    uv_mutex_unlock(&baton->mutex);
}

void Thread::doReceive(Receiver receiver)
{
    baton->state = 0;
    baton->receiver = receiver;
    baton->asyncRequest.data = baton;
    uv_async_send(&baton->asyncRequest);
}

void Thread::doError(int code, string message)
{
    baton->state = 1;
    baton->error.code = code;
    baton->error.message = message;
    baton->asyncRequest.data = baton;
    uv_async_send(&baton->asyncRequest);
}

Thread::~Thread()
{
    uv_mutex_destroy(&baton->mutex);
    delete baton;
}