//
// Created by root on 18-2-1.
//
#include "iopool_echo.hpp"

using namespace muduo;
using namespace muduo::net;

int main()
{
    EventLoop loop;
    Echoserver server_(&loop, InetAddress(2018), 10, 3);

    server_.start();
    loop.loop();
    return 0;
}