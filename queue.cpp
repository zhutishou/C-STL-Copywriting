#include <iostream>


namespace cx
{
    //版本一：非适配器写法：
    template<class T>
    //利用链表实现：
    struct Node
    {
        //构造函数：
        Node(const T& val)
        {
            _val = val;
            _next = nullptr;
        }
        //不需要实现析构函数！！！
        //成员变量：
        T _val;
        Node* _next;
    };

    template<class T>
    class queue
    {
        typedef Node<T> Node;
    public:
        //构造函数:
        queue()
        {
            _begin = _end = nullptr;
        }

        //析构函数：
        ~queue()
        {
            if(_begin)
            {
                while(_begin!= _end)
                {
                    Node* tmp = _begin;
                    while(tmp ->_next != _end)
                    {
                        tmp = tmp->_next;
                    }
                    delete _end;
                    _end = tmp;
                }
                delete _begin;
                _begin = _end =nullptr;
            }
        }

        //modifiers:
        bool empty()const
        {
            return _begin == nullptr;
        }
        T& front()
        {
            if(_begin != nullptr)
                return _begin->_val;
        }
        T& back()
        {
            if(_begin != nullptr)
                return _end-> _val;
        }
        void push(const T& val)
        {
            Node* tmp = new Node(val);
            //判断是不是第一个插入的元素：
            if(_begin == nullptr)
            {
                _begin = _end = tmp;
            }
            else
            {
                _end ->_next = tmp;
                _end = _end ->_next;
            }
        }
        void pop()
        {
            //头部删除：
            _front = _front -> _next;
        }

    private:
        //定义两个成员，一个指向队列头，一个指向队列尾
        Node* _begin;//队头，出队列
        Node* _end;//队尾，入队列
    };


    //版本二：利用适配器写法：
    template<class T,class container = deque<T>>
    class queue
    {
    public:
        bool empty()const{
            return _con.empty();
        }
        void push(const T& val)
        {
            _con.push_back(val);
        }
        void pop()
        {
            _con.pop_front();
        }
        const T& front()
        {
            return _con.front();
        }
        const T& back()
        {
            return _con.back();
        }
    private:
        container _con;
    };
    //这就不具体举例了！！！
}
