#include <iostream>
#include <assert.h>

namespace cx
{
    class string
    {
    public:
        //构造函数：
        //string()不写会自动构造
        string(const char* str = "")//如果声明定义分离，默认值是声明时写的
        {
            _size=strlen(str);
            _capacity=_size;
            char* tmp=new char[_size+1];//'\0'
            tmp[_size]='\0';
            //清空原string 中数据
            delete[] _str;
            _str=tmp;           
        }   
        string(const cx::string& s)
        {
            //利用string(const char* str = "")
            cx::string tmp(s._str);//构造一份临时对象
            swap(s,tmp);
        }	
        string(size_t n, char c)
        {
            char* tmp= new char[n+1];
            _size=_capacity=n;
            for(int i=0;i<n;i++)
            {
                tmp[i]=c;
            }
            tmp[n]='\0';
            //清空_str
            delete[] _str;
            _str=tmp;
        }
        string(const char* s, size_t n)
        {
            char* tmp = new char[n+1];
            strncpy(tmp,s,n);
            _size=_capacity=n;
            tmp[n]='\0';
            //清空_str
            delete[] _str;
            _str=tmp;
        }
        string(const cx::string& str, size_t pos, size_t len = npos)
        {
            if (len == npos || pos + len > str._size)
            {
                char* tmp = new char[str.size() - pos + 1];
                _capacity = str.size() - pos;
                strncpy(tmp, str._str + pos, len);
                delete[] _str;
                _str = tmp;
            }
            else
            {
                char* tmp = new char[len + 1];
                _capacity = len;
                strncpy(tmp, str._str + pos, len);
                delete[] _str;
                _str = tmp;
            }
            _size = len;
            _str[_size] = '\0';
        }

        string substr(size_t pos = 0, size_t len = npos) const
        {
            
        }

        void swap(cx::string& str)
        {
            std::swap(_str,str._str);
            std::swap(_size,str._size);
            std::swap(_capacity,str._capacity);
        }
    private:
        //定义一个char指针，一个有效大小，一个容量
        char* _str=nullptr;
        size_t _size=0;
        size_t _capacity=0;
        const static size_t npos=-1;
    }
}
