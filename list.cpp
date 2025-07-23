#include <iostream>


namespace cx
{
    //定义一个节点内容：
    template<class T>
    struct ListNode
    {
        //构造函数：
        ListNode(const T& val = T())
            :_prev(nullptr),_next(nullptr),_val(val)
        {
        }

        //成员变量：
        ListNode<T>* _prev;//指向前一个位置
        ListNode<T>* _next;//指向后一个位置
        T _val;//当前节点的值
    };

    template<class T>
    class List 
    {
    public:
        typedef ListNode<T> Node;
        //构造函数：
        List()
        {
            empty_list();
        }
        //拷贝构造：
        List(const List<T>& list)
        {
            empty_list();
            for(auto e: list)
            {
                push_back(e);//val             
            }
        }
        //运算符重载;
        List<T> operator=(const List<T>& list)
        {
            //判断是否为同一个;
            if(this 1= &list)
            {
                //先清除this的内容
                clear();
                //插入：
                for(T val : list)
                {
                    push_back(val);
                }
            }
            return *this;
        }
        //析构函数：
        ~List()
        {
            
        }



        //modfifers:
        void clear()
        {

        }
        void push_back(const T& val)
        {
            Node* tmp = new Node(val);
            //头节点的_prev指针指向最后一个节点：
            Node* tail = _head->_prev;
            tail->_next = tmp;
            tmp->_prev = tail;
            tmp->_next = _head;
            _head->_prev = tail;
        }
        void push_front(const T& val)
        {
            Node* tmp = new Node(val);
            Node* head = _head->_next;
            head->_prev = tmp;
            tmp->_next = head;
            tmp->_prev = _head;
            _head->_next = tmp;
        }
        void pop_back()
        {
            Node* tmp = _head->_prev->_prev;
            tmp->_next = _head;
            _head->_prev = tmp;
        }
        void pop_front()
        {
            Node* tmp = _head->_next->_next;
            tmp->_prev = _head;
            _head->_next = tmp;
        }
    private:
        void empty_list()
        {
            //将虚拟头节点赋予实际空间：
            _head = new Node;
            _head->_next = nullptr;
            _head->_prev = _head;
        }
        //定义一个函数可以满足构造、拷贝构造
        Node* _head;//定义一个虚拟头结点
    };
}
