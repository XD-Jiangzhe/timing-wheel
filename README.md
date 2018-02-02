timing-wheel
时间轮踢掉空闲连接 的 两种大致的做法：

第一种 是 使用 boost/circurt_buffer 和  boost/unordered_set

unorder_set 使用hash 来存储 数据当桶，无序容器，而 circuryt_buffer 来当做 桶的轮盘，大小resize 之后固定，

这里使用shared_ptr 指针 来管理每个连接的 声明周期，连接 进来一个数据 将绑定在 tcpconnection context 上的 weak_ptr lock() 然后塞进 最后一个桶中 此时 引用计数+1 ，给该连接续了一条命

时间到了的时候 往 circuit_bufffer 中 塞入一个新的桶， 最先的那个桶 就被弹出去了， 引用计数为0 的 调用 entry的析构函数 关闭连接

第二种是 用有序链表 来实现

每个tcpconnection 的context  存放一个node 对象，一个弱指针 + 在连接链表的位置， 进来一个连接， 就std::list.splice(iter, list, list.end())，将当前连接放到最后一个，并更新时间

每隔n 秒 检查一次 链表， 从头开始，将超时的erase 掉就可以了
