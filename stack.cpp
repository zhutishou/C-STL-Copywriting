#include <iostream>

namespace cx
{
    //版本一：在未学习C++适配器时写法：
    //写成模版方式：
    template<class T>
    class stack
    {
    public:
        //构造函数:
        stack()
            :_a(nullptr),_top(0),_capacity(0)
        {}
        //析构函数：
        ~stack()
        {
            delete[] _a;
            _a = nullptr;
            _top = _capacity =0;
        }
        //modifiers:
        bool empty()const
        {
            return _top == 0;
        }
        size_t size()const
        {
            return _top;
        }
        T& top()
        {
            if(_top > 0)
                return *(_a + _top -1);
        }
        const T& top()const
        {
            if(_top > 0)
                return *(_a + _top -1);
        }
        void push(const T& val)
        {
            if(_top == _capacity)
            {
                //扩容
                size_t newcapacity = _capacity == 0? 4:2*_capacity;
                T* tmp = new T[newcapacity];
                //判断开辟情况：
                if(tmp == nullptr)
                    std::cerr<<"空间开辟失败"<<std::endl;
                memcpy(_a,tmp,sizeof(T)*_top);
                delete[] _a;
                _capacity = newcapacity;
                _a = tmp;
            }
            //插入：
            *(_a + _top) = val;
            _top++;
        }
        void pop()
        {
            if(_top > 0)
            {
                _top --;
            }
        }

    private:
        T* _a;//内容指针
        size_t _top;//初入有效位置
        size_t _capacity;//容量
    };


    //版本二：利用C++中的适配器来实现：
    template<class T,class container = deque<T>>
    class stack
    {
    public:
        //我们直接利用适配器的各自功能即可：
        const T& top()
        {
            return _con.back();
        }
        void pop()
        {
            _con.pop_back();
        }
        void push(const T& val)
        {
            _con.push_back(val);
        }
        bool empty()
        {
            return _con.empty();
        }
        size_t size()const
        {
            return _con.size();
        }

    private:
        container _con;
    };
    //我们只需要讲适配器实例化即可使用，以下是举例：

    void test_1()
    {
        cx::stack<int,vector<int>> _st;
        _st.push(1);
        _st.push(2);
        _st.push(3);
        _st.push(4);
        _st.push(5);
        _st.push(6);
        while (!_st.empty())
        {
            std::cout << _st.top() << " ";
            _st.pop();
        }
        std::cout<<std::endl;
    }
    int main()
    {
        test_1();
        return 0;
    }

}
