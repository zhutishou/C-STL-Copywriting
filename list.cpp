#include <iostream>
#include <assert>

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

    //定义迭代器部分：
    template<class T,class Ref,class Ptr>
    struct _list_iterator
    {
        typedef ListNode<T> Node;
		typedef _list_iterator<T,Ref, Ptr> self;
        //构造函数：
        _list_iterator(Node* x)
			:_node(x)
		{}
        //注意：无析构函数
        //常见使用函数：
        self& operator++()//前置++
		{
			_node = _node->_next;
			return (*this);
		}
		self& operator++(int)//后置++
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		self& operator--()//前置--
		{
			_node = _node->_prev;
			return *this;
		}
		self& operator--(int)//后置--
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		Ref operator*()//Ref---是指解引用指向的内容
		{
			return _node->_val;
		}
		bool operator!=(const self& s)
		{
			return !(_node == s._node);
		}
		bool operator==(const self& s)
		{
			return !(*this != s);
		}
		Ptr operator->()//Ptr---是指地址
		{
			return &_node->_val;
		}
        //成员对象：
        Node* _node;
    };

    template<class T>
    class List 
    {
    public:
        typedef ListNode<T> Node;

		typedef _list_iterator<T, T&, T*> iterator;
		typedef _list_iterator<T,const T&,const T*> const_iterator;

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
            clear();//清除有效数据部分
            delete _head;
            _head = nullptr;
        }

        //迭代器部分；
        iterator begin()//有效第一个节点
		{
            //可以检查下：
            if(_head->_next)
			    return _head->_next;
		}
		const_iterator begin() const
		{
            if(_head->_next)
			    return _head->_next;
		}
		iterator end()
		{
			return _head;
		}
		const_iterator end() const
		{
			return _head;
		}

        //modfifers:
        iterator erase(iterator pos)
		{
			//检查pos位置非_head位置
			if(pos ==end())
                std::cerr<<"该位置不存在"<<std::endl;
			//删除的是pos位置
			Node* current = pos._node;
			Node* prev = current->_prev;
			Node* next = current->_next;
			//删除操作
			prev->_next = next;
			next->_prev = prev;
			delete current;
			return next;//返回的是pos下一个位置
		}
		iterator erase(iterator first, iterator last)//区间左闭右开
		{
			assert(first != end());
			assert(last != end());
			while (first != last)
			{
				if (first == end())
					break;
				first = erase(first);
			}
			return first;
		}
        void clear()
        {
            //注意：clear只删除有效数据部分，不删除_head
            iterator it = begin();
            while(it != end())
            {
                it = erase(it);
            }
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
        bool empty() const
		{
			return _head->_next == _head;
		}
		size_t size() const
		{
			size_t n = 0;
			Node* tmp = _head->_next;
			while (tmp!=_head)
			{
				tmp = tmp->_next;
				n++;
			}
			return n;
		}
        void swap(list<T>& tmp)
		{
			std::swap(_head, tmp._head);
		}
		iterator insert(iterator pos, const T& x)
		{
			//insert是指在pos位置前插入
			Node* current = pos._node;
			Node* prev = current->_prev;
			//开空间
			Node* tmp = new Node(x);
			tmp->_prev = prev;
			prev->_next = tmp;
			tmp->_next = current;
			current->_prev = tmp;
			//return iterator(tmp);
			return tmp;//注意点：单参数的类可以隐式类型转换
		}

        //Element access:
		T& front()
		{
			return _head->_next->_val;
		}
		const T& front() const
		{
			return _head->_next->_val;
		}
		T& back()
		{
			return _head->_prev->_val;
		}
		const T& back() const
		{
			return _head->_prev->_val;
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
