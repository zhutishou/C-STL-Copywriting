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
        string(const string& s)
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
        string(const string& str, size_t pos, size_t len = npos)
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

        //运算符重载构造
        cx::string& operator= (const char* str);
        {
            //大小
            _size=_capacity=strlen(str);
            char* tmp=new char[_size+ 1];
            //检查：
            if(tmp==nullptr)
            {
                return "";
            }
            strcpy(tmp,str);
            tmp[_size]='\0';
            delete[] _str;
            _str=tmp;
            return *this;
        }
        cx::string& operator= (char c)
        {
            char* tmp=new char[2];
            //检查;
            if(tmp==nullptr)
            {
                return "";
            }
            tmp[0]=c;
            tmp[1]='\0';
            delete[] _str;
            _size=_capacity=1;
            _str=tmp;
            return *this;
        }	
        cx::string& operator= (const string& str)
        {
            cx::string tmp(str);
            swap(tmp);
        }

        //析构函数
        ~string()
        {
            delete[] _str;
            _str = nullptr;
            _size = _capacity = 0;
        }

        typedef char* iterator;
        typedef const char* const_iterator;
        iterator begin()
        {
            return _str;
        }
        const_iterator begin() const
        {
            return _str;
        }
        iterator end()
        {
            return _str+_size;
        }
        const_iterator end() const
        {
            return _str + _size;
        }
        iterator rbegin()
        {
            return end();
        }
        const_iterator rbegin() const
        {
            return end();
        }
        iterator rend()
        {
            return begin();
        }
        const_iterator rend() const
        {
            return begin();
        }

        //inline与static修饰函数对比
        size_t size()const
        {
            return _size;
        }
        size_t length()const
        {
            return _size;
        }
        size_t capacity()const
        {
            return _capacity;
        }
        bool empty()const
        {
            return _size == 0;
        }
        size_t max_size() const
        {
            return -1;
        }
        void clear()
        {
            erase();
        }	
        string& erase(size_t pos = 0, size_t len = npos)
        {
            assert(pos <= _size);
            if (len == npos || len + pos > _size)
            {
                _str[pos] = '\0';
                _size = pos;
            }
            else
            {
                strcpy(_str + pos, _str + pos + len);
                _size -= len;
                _str[_size] = '\0';
            }
            return *this;
        }
        void swap(string& str)
        {
            std::swap(_str,str._str);
            std::swap(_size,str._size);
            std::swap(_capacity,str._capacity);
        }
        void reserve(size_t n = 0)
        {
            if (n > _capacity)
            {
                char* tmp = new char[n + 1];
                strcpy(tmp, _str);		
                delete[] _str;
                _str = tmp;
                _capacity = n;
            }
        }
        string& operator+= (const string& str)
        {
            append(str);
            return *this;
        }
        string & operator+= (const char* str)
        {
            append(str);
            return *this;
        }
        string& operator+= (char c)
        {
            push_back(c);
            return *this;
        }
        void push_back(char c)
        {
            if (_capacity == _size)
            {
                size_t newcapacity = _capacity == 0 ? 4 : 2 * _capacity;
                reserve(newcapacity);
            }
            _str[_size++] = c;
            _str[_size] = '\0';
        }
		string& append(const string& str)
        {
            if (str._size + _size > _capacity)
            {
                reserve(str._size + _size);
            }
            strcpy(_str + _size, str._str);
            _size += str._size;
            _str[_size] = '\0';
            return *this;
        }
		string& append(const string& str, size_t subpos, size_t sublen)
        {   
            //检查
            if (sublen + _size > _capacity)
            {
                reserve(sublen + _size);
            }
            strncpy(_str+_size, str._str+subpos, sublen);
            _size += sublen;
            _str[_size] = '\0';
            return *this;
        }
		string & append(const char* s)
        {
            size_t len = strlen(s);
            if (len + _size > _capacity)
            {
                reserve(_size + len);
            }
            strcpy(_str + _size, s);
            _size += len;
            _str[_size] = '\0';
            return *this;
        }
		string& append(const char* s, size_t n)
        {
            //检查
            if (n + _size > _capacity)
            {
                reserve(n + _size);
            }
            strncpy(_str+_size, s, n);
            _size += n;
            _str[_size] = '\0';
            return *this;
        }
		string& append(size_t n, char c)
        {
            //检查
            if (n + _size > _capacity)
            {
                reserve(n + _size);
            }
            for (size_t i = _size; i < _size + n; i++)
            {
                _str[i] = c;
            }
            _size += n;
            _str[_size] = '\0';
            return *this;
        }
        void pop_back()
        {
            erase(_size - 1, 1);
        }
        string& replace(size_t pos, size_t len, const string& str)
        {
            //检查
            if (pos + len > _size)
            {
                reserve(pos + len);
                strncpy(_str + pos, str._str, len);
                _size = pos + len;
                _str[_size] = '\0';
            }
            else
            {
                strncpy(_str + pos, str._str, len);
                _size = pos + len;
            }
            return *this;
        }
        string& replace(size_t pos, size_t len, const char* s)
        {
            //检查
            if (pos + len > _size)
            {
                reserve(pos + len);
                strncpy(_str + pos, s, len);
                _size = pos + len;
                _str[_size] = '\0';
            }
            else
            {
                strncpy(_str + pos, s, len);
                _size = pos + len;
            }
            return *this;
        }

        //比较：
        bool operator<(const string& s)
        {
            size_t n = _size > s._size ? s._size : _size;
            for (size_t i = 0; i < n; i++)
            {
                if (_str[i] >= s._str[i])return false;
            }
            if (n == s._size)return false;
            else
            return true;
        }
        bool operator<=(const string& s)
        {
            return !(*this > s);
        }
        bool operator>(const string& s)
        {
	        return !((*this == s) || (*this < s));
        }
        bool operator>=(const string& s)
        {
	        return !(*this < s);
        }
        bool operator==(const string& s)
        {
            if (_size != s._size)return false;
            for (size_t i = 0; i < _size; i++)
            {
                if (_str[i] != s._str[i])return false;
            }
            return true;
        }
        bool operator!=(const string& s)
        {
	        return !(*this == s);
        }
        char& operator[] (size_t pos)
        {
            assert(pos < _size);
            return *(_str + pos);//等价于_str[pos]
        }
        const char& operator[] (size_t pos) const
        {
            assert(pos < _size);
            return *(_str + pos);//等价于_str[pos]
        }
        char& at(size_t pos)
        {
            assert(pos < _size);
            return _str[pos];
        }
        const char& at(size_t pos) const
        {
            assert(pos < _size);
            return _str[pos];
        }

        size_t find(const string& str, size_t pos = 0) const
        {
            char* tmp = new char[str._size + 1];
            strcpy(tmp, str._str);
            tmp[str._size ] = '\0';
            const char* ptr = strstr(_str + pos, tmp);
            if (ptr == nullptr)
            {
                delete[] tmp;
                tmp = nullptr;
                return npos;
            }
            else
            {
                delete[] tmp;
                tmp = nullptr;
                return ptr - _str;
            }
        }
		size_t find(const char* s, size_t pos = 0) const
        {
            const char* ptr = strstr(_str + pos, s);
            if (ptr == nullptr)
            {
                return npos;
            }
            else
            {
                return ptr - _str;
            }
        }
		size_t find(const char* s, size_t pos, size_t n) const
        {
            char* tmp = new char[n];
            strcpy(tmp, s);
            tmp[n] = '\0';
            const char* ptr = strstr(_str + pos, tmp);
            if (ptr == nullptr)
            {
                delete[] tmp;
                tmp = nullptr;
                return npos;
            }
            else
            {
                delete[] tmp;
                tmp = nullptr;
                return ptr - _str;
            }
        }
		size_t find(char c, size_t pos = 0) const
        {
            for (size_t i = pos; i < _size; i++)
            {
                if (_str[i] == c)
                    return i;
            }
            return npos;
        }
		string substr(size_t pos = 0, size_t len = npos) const
        {
            //检查：
            assert(pos < _size);
            size_t end = pos + len;
            if (len == npos || pos + len >= _size)
            {
                end = _size;
            }
            string str;
            str.reserve(end - pos);
            for (size_t i = pos; i < end; i++)
            {
                str += _str[i];
            }
            return str;
        }
        char& front()
        {
            return _str[0];
        }
        const char& front() const
        {
            return _str[0];
        }
        char& back()
        {
            return _str[_size];
        }
        const char& back() const
        {
            return _str[_size];
        }
        
        //友元部分：
        friend ostream& operator<<(ostream& _cout, const cx::string& s);	
        friend istream& operator>>(istream& _cin, cx::string& s);

    private:
        //定义一个char指针，一个有效大小，一个容量
        char* _str=nullptr;
        size_t _size=0;
        size_t _capacity=0;
        const static size_t npos=-1;
    };
}

ostream& cx::operator<<(ostream& _cout, const cx::string& s)
{
	for (auto e : s)
	{
		_cout << e;
	}
	return _cout;
}
istream& cx::operator>>(istream& _cin, cx::string& s)
{
	s.clear();//清除内容
	char ch = _cin.get();
	//建立一个缓冲数组
	char buff[64];
	size_t i = 0;
	while((ch != ' ') && (ch != '\n'))
	{
		//读入buff中
		buff[i++] = ch;
		if (65 == i)
		{
			buff[i] = '\0';//注意：置零
			s += buff;//利用operator+=数组
			i = 0;
		}
		ch = _cin.get();
	}
	if (i > 0)
	{
		buff[i] = '\0';
		s += buff;
	}
	return _cin;
}
