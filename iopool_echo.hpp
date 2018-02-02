//
// Created by root on 18-2-1.
//

#ifndef ECHO_IOPOOL_ECHO_HPP
#define ECHO_IOPOOL_ECHO_HPP

#include <muduo/net/TcpServer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/ThreadLocalSingleton.h>

#include <iostream>
#include <memory>
#include <functional>
#include <list>


namespace muduo
{
    namespace net
    {
        class Echoserver
        {
        public:
            Echoserver(EventLoop *loop, const InetAddress& listenaddr, int time, int threadnum):
                    server_(loop, listenaddr, "Echoserver"), ideatime(time)
            {
                server_.setConnectionCallback(std::bind(&Echoserver::onConnection, this, std::placeholders::_1));
                server_.setMessageCallback(std::bind(&Echoserver::onMessage, this, std::placeholders::_1,
                                                     std::placeholders::_2, std::placeholders::_3));
                /*loop->runEvery(1.0, std::bind(&Echoserver::timerd, this));*/
                server_.setThreadInitCallback(std::bind(&Echoserver::threadinit, this, std::placeholders::_1));
                server_.setThreadNum(threadnum);
            }

            void start()
            {
                server_.start();
            }
        private:
            void threadinit(EventLoop* loop)
            {
                loop->runEvery(1.0, std::bind(&Echoserver::timerd, this));
                loops.push_back(loop);
            }

            void dumpConnectionlist();

            void onMessage(const TcpConnectionPtr&conn, Buffer *buf, Timestamp arrival)
            {
                string mes = buf->retrieveAllAsString();
                conn->send(mes);

                node no = boost::any_cast<node>(conn->getContext());
                no.nodetime = Timestamp::now();
                connlist::instance().splice(no.iter, connlist::instance(), connlist::instance().end());
            }

            void onConnection(const TcpConnectionPtr& conn)
            {
                if(conn->connected())
                {
                    node no;
                    no.nodetime = Timestamp::now();
                    connlist::instance().push_back(conn);
                    no.iter = --connlist::instance().end();
                    conn->setContext(no);
                    dumpConnectionlist();
                }
                else
                {
                    node no = boost::any_cast<node>(conn->getContext());
                    connlist::instance().erase(no.iter);
                }
            }

            void timerd()
            {
                for( auto iter = connlist::instance().begin(); iter != connlist::instance().end(); ++iter)
                {
                    boost::shared_ptr<TcpConnection> conn = (*iter).lock();
                    if(conn)
                    {
                        //如果conn 还在 则比较时间
                        node n = boost::any_cast<node>(conn->getContext());
                        if(ideatime < timeDifference(Timestamp::now(), n.nodetime))
                        {
                            if(conn->connected())
                            {
                                conn->shutdown();
                                /*iter = connlist.erase(n.iter);*/
                                //这里不用 删除 这个 ，因为这是一个弱指针，每次调用弱指针都要检查对象是否存在
                                LOG_INFO << "delete the connection " << &*conn;
                            }
/*                            if(connlist.size()>0)
                                dumpConnectionlist();*/
                        } else{

                        }
                    }
                    else
                    {
                        node n = boost::any_cast<node>(conn->getContext());
                        iter = connlist::instance().erase(n.iter);
                        LOG_INFO<<"delete the connection "<<&*conn;
                    }
                }
            }

            typedef boost::weak_ptr<TcpConnection> WeakConnection;
            typedef std::list<WeakConnection> connectionlist;

            struct node
            {
                connectionlist::iterator iter;
                Timestamp nodetime;
            };
        private:

            std::list< EventLoop*> loops;         //一个io线程的列表
            typedef ThreadLocalSingleton<connectionlist> connlist; //这里要是一个线程私有的全局变量

            TcpServer server_;
            int ideatime;       //超时时间的设置
        };
        void Echoserver::dumpConnectionlist()  {
            for(auto iter = connlist::instance().begin(); iter != connlist::instance().end() ; )
            {
                boost::shared_ptr<TcpConnection> conn =  (*iter).lock();
                if(conn)
                {
                    printf("conn %p\n", conn.get());  //输出的指针
                    const node& n = boost::any_cast<const node&>(conn->getContext());
                    printf("   time %s\n", n.nodetime.toString().c_str());
                    ++iter;
                } else{
                    const node& n = boost::any_cast<const node&>(conn->getContext());
                    iter = connlist::instance().erase(n.iter);
                }
            }
        }

    }
}


#endif //ECHO_IOPOOL_ECHO_HPP
