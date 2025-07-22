#include <iostream>
#include <cstring>

namespace cx
{
    //写成模版方式：
    template<class T>
    class vector
    {
    public:
        //定义：
        typedef T* iterator;
        typedef const T* const_iterator;
        //构造函数：
        vector():
            _begin(nullptr),_end(nullptr),_endofstorage(nullptr)
        {}
        //拷贝构造：
        //传统写法：
        vector(const vector<T>& v)
        {
            _begin=new T[v.capacity()];
            memcpy(_begin,v.begin,sizeof(T)*v.size());
            _end=_begin+v.size();
            _endofstorage=_begin+v.capacity();
        }
        //现代优化写法：
        vector(const vector<T>& v)
        {
            //先扩容：
            reserve(v.size());
            for(auto e : v)
            {
                *_end = e;
                _end ++;
            }
        }
        vector(size_t n, const T& val = T())
        {
            resize(n,val);
        }
        //析构函数：
        ~vector()
        {
            //检查是否存在开辟空间的情况，判断是否要析构
            if(_begin)
            {
                delete[] _begin;
                _begin = _end = _endofstorage;
            }
        }
        //运算符重载函数：
        vector<T>& operator=(const vector<T>& v)
        {
            reserve(v.capacity());
            memcpy(_begin,v._begin,sizeof(T)* size());
            _end = _begin + size();
        }

        //迭代器部分：
        iterator begin()
        {
            return _begin;
        }
        iterator end()
        {
            return _end;
        }
        const_iterator begin()const
        {
            return _begin;
        }
        const_iterator end()const
        {
            return _end;
        }

        //实操部分：
        //判断是否是空：
        bool empty()const
        {
            return _begin==_end;
        }
        //交换：
        void swap(vector<T>& v)
        {
            std::swap(_begin,v._begin);
            std::swap(_end,v._end);
            std::swap(_endofstorage,v._endofstorage);
        }
        //尾部插入：
        void push_back(const T val)
        {
            //检查容量是否足够;
            if(_end == _endofstorage)
            {
                //扩容
                size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
                reserve(newcapacity);
            }
            *_end = val;
            _end++;
        }
        //删除尾部：
        void pop_back()
        {
            if(size() > 0)
                _end--;
        }
        //得到pos位置的值：
        T& operator[](size_t pos)
        {
            if(pos > size())
            {
                std::cerr<<"pos 位置不存在"<<std::endl;
                return T();
            }
            return *(_begin + pos);
        }
        T& operator[] (size_t pos) const
        {
            if(pos > size())
            {
                std::cerr<<"pos 位置不存在"<<std::endl;
                return T();
            }
            return *(_begin + pos);
        }
        //插入：
        iterator insert(iterator pos,const T& val)
        {
            if(pos < _begin|| pos > _end)
            {
                std::cerr<<"该位置不存在"<<std::endl;
            }
            //判断是否需要扩容：
            if(_end == _endofstorage)
            {
                size_t len = _begin + pos;
                reserve(capacity()==0?4:2*capacity());
                pos = _begin + len;
            }
            //pos后续位置后移：
            iterator finish = _end -1;
            while(finish > pos)
            {
                *(finish+1) = *finish;
                finish--;
            }
            *pos = val;
            _end++;
            return pos;
        }
        //删除pos位置
        iterator erase(iterator pos)
        {
            //判断：
            if(pos < _begin || pos > _end)
            {
                std::cerr<<"该位置不存在"<<std::endl;
                return iterator();
            }
            iterator it = pos + 1;
            while(it != _end)
            {
                *(it-1) = *it;
                it++;
            }
            _end--;
            return pos;
        }
        //改变有效大小：
        void resize(size_t n, T val = T())
        {
            if(n < size())
            {
                _end = _begin + n;
            }
            else
            {
                //扩容
                reserve(n);
                size_t m = n -size();
                while(m--)
                {
                    *_end = val;
                    _end++;
                }
            }
        }
        //扩容：
        void reserve(size_t n)
        {
            if(n > capacity())
            {
                size_t old = size();
                T* tmp = new T[n];
                //检查_begin情况：
                if(_begin)
                {
                    memcpy(tmp,_begin,sizeof(T)*size());
                    delete[] _begin;//删除的是数组
                }
                _begin = tmp;
                _end = tmp + size();
                _endofstorage = tmp + n;
            }
        }
        //容量计算：
        size_t capacity()const
        {
            return _endofstorage-_begin;
        }
        //有效大小计算
        size_t size()const
        {
            return _end-_begin;
        }
        //清除：
        void clear()
        {
            resize(0);
        }
        //结尾添加n个val(追加)
        void assign(size_t n,const T& val)
        {
            reserve(_size()+n);
            while(n--)
            {
                *_end = val;
                _end ++;
            }
        }
        T& front()
        {
            return *_begin;
        }
        const T& front() const
        {
            *_begin;
        }
        T& back()
        {
            return *_end;
        }
        const T& back() const
        {
            return *_end;
        }
        T& at(size_t pos)
        {
            if(pos > size())
            {
                std::cerr<<"该位置溢出"<<std::endl;
            }
            return _begin[pos];
        }
        const T& at(size_t pos) const
        {
            if(pos > size())
            {
                std::cerr<<"该位置溢出"<<std::endl;
            }
            return _begin[pos];
        }
    protected:

        //定义成员变量：
        iterator _begin;//头位置
        iterator _end;//尾位置
        iterator _endofstorage;//容量尾结点
      
    };
}
