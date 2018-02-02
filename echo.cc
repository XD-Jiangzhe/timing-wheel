//
// Created by root on 18-2-1.
//
#include "echo.hpp"
using namespace muduo;
using namespace muduo::net;

int main()
{
    EventLoop loop;
    Echoserver echo(&loop, InetAddress(2018), 10);

    echo.start();
    loop.loop();
    return 0;
}