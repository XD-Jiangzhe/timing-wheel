//
// Created by root on 18-2-1.
//
#include "bucket_echo.hpp"

using namespace muduo;
using namespace muduo::net;

int main()
{
    EventLoop loop;
    Echoserver server(&loop, InetAddress(2018), 10, 5);

    server.start();
    loop.loop();

    return 0;
}

