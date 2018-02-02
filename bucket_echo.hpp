//
// Created by root on 18-2-1.
//

#ifndef ECHO_BUCKET_ECHO_HPP
#define ECHO_BUCKET_ECHO_HPP

#include <muduo/net/TcpServer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/ThreadLocalSingleton.h>
#include<muduo/base/Logging.h>

/*#include <boost/circular_buffer.hpp>*/
#include <boost/unordered_set.hpp>
#include <boost/version.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "circuit_buffer.cc"
#include <unordered_set>
#include <memory>
#include <set>
#include <functional>
namespace muduo
{
    namespace net
    {
        class Echoserver
        {
        public:

            Echoserver(EventLoop *loop, const InetAddress& listenaddr, int threadnum, int time):
                    server_(loop, listenaddr, "echoserver"),
                    ideatime(time)
            {
                server_.setMessageCallback(std::bind(&Echoserver::onMessage, this, std::placeholders::_1, std::placeholders::_2,std::placeholders::_3));
                server_.setConnectionCallback(std::bind(&Echoserver::onConnection, this, std::placeholders::_1));
                loop->runEvery(1.0, std::bind(&Echoserver::timefd, this));
                buckets_.resize(ideatime);      //指定大小
                dumpConnectionBuckets();
            }

            void start()
            {
                server_.start();
            }

            typedef boost::weak_ptr<TcpConnection> weakconn;
            //这里的entry用的是weak_ptr，entry 是 Tcpconnection 的weak_prt对象，然后提供析构函数，在轮子里决定它的生命周期
            struct Entry
            {
                explicit Entry(const weakconn &conn)
                :wc(conn){}
                ~Entry()
                {
                    auto p = wc.lock();
                    if(p)
                        p->shutdown();
                }
                weakconn wc;
            };
            typedef boost::shared_ptr<Entry> EntryPtr;
            //桶中存放的是shared_ptr 如果 这里 引用计数为0 ，调用Entry 的析构函数将连接断开
            typedef boost::unordered_set<EntryPtr> Bucket;
            typedef ::circular_buffer<Bucket>  WeakConnectionList;
            typedef boost::weak_ptr<Entry> weakEntry;
        private:
            void onMessage(const TcpConnectionPtr& conn, Buffer *buffer,Timestamp arrival )
            {
                conn->send(buffer->retrieveAllAsString());

                weakEntry we = boost::any_cast<weakEntry>(conn->getContext());
                auto pwe = we.lock();
                if(pwe)
                {
                    buckets_.back().insert(pwe);
                }
                dumpConnectionBuckets();
            }

            void onConnection(const TcpConnectionPtr &conn)
            {
                if(conn->connected())
                {
                    EntryPtr en(new Entry(conn));
                    buckets_.back().insert(en);
                    weakEntry wek(en);
                    conn->setContext(wek);
                    dumpConnectionBuckets();
                } else{
                    weakEntry we = boost::any_cast<weakEntry>(conn->getContext());
                    LOG_DEBUG<<we.use_count();
                }

            }
/*            void thread_init(EventLoop *loop)
            {
                loops.insert(loop);
                loop->runEvery(1.0, timefd);
            }*/
            void timefd()
            {
                buckets_.push_back(Bucket());
                //这里 塞一个新的桶，将最开始那个挤掉
            }
            void dumpConnectionBuckets()
            {
                LOG_INFO<<"size = " <<buckets_.size();
                int idx = 0;

                for(auto  iter = buckets_.begin(); iter != buckets_.end(); ++iter)
                {
                    Bucket ba = *iter;
                    for(Bucket::iterator it = ba.begin(); it != ba.end(); ++it)
                    {
                        bool coonet = (*it)->wc.expired();
                        printf("%p(%ld)%s, ", it->get(), it->use_count(), coonet?"DEAD":" ");
                    }
                }

            }
        private:
            TcpServer server_;
            int ideatime;
            WeakConnectionList buckets_;

        };
    }
}


#endif //ECHO_BUCKET_ECHO_HPP
