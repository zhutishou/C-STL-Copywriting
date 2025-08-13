#include <iostream> 

using namespace std;

//B树实现：
//Node:
template<class K,size_t M>
struct BTreeNode
{
	//正常情况下我们是定义M-1个关键字，M个孩子，但是为了方便分裂，我们是M个关键字，M+1个孩子
	K _keys[M];//每个节点的关键字数量
	BTreeNode<K,M>* _subs[M+1];//M+1个孩子 ，存放的是指针
	BTreeNode<K,M>* _parent;//父结点
	size_t n;//实际上使用的关键之数量 
	
	BTreeNode()
	{
		//将关键之和孩子全部初始化默认值
		for(size_t i = 0;i < M;++i) 
		{
			_keys[i] = K();
			_subs[i] = nullptr;
		}
		//孩子多一个
		_subs[M] = nullptr;
		//初始化父结点和实际关键字数量 
		_parent = nullptr;
		_n = 0;		
	}
}; 
//Tree
template<class K,size_t M>
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	//查找
	pair<Node*,int> Find(const K& key) 
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while(cur)
		{
			size_t i = 0;
			while(i < cur->_n)
			{
				//在当前节点中查找关键字
				if(key < cur->_keys[i])
				{
					//说明在其孩子存放的下一级中
					break; 
				} 
				else if(key > cur->_keys[i])
				{
					//还可能在其右边关键字中
					i++; 
				}
				else
				{
					//找到了
					return make_pair(cur,i);//返回当前节点和在其中关键字位置 
				}
			}
			//跳到孩子上
			parent = cur;
			cur = cur->_subs[i];//注意i对应的就是比当前节点小的孩子上 
		}
		//找到最后都没有找到，返回需要构造的父结点，其子节点可以存放该key
		return make_pair(parent,-1);
	}
	//直接使用默认构造，不s实现
	bool Insert(const K& key) 
	{
		if(root == nullptr)
		{
			//初始插入
			_root = new Node;
			_root -> _keys[0] = key;
			_root -> _n ++;
			return true; 
		}
		//非初始化插入
		//B树具有每个关键字都不相同特性，相同不允许插入
		//利用Find查找
		pair<Node*,int> res = Find(key);
		if(res.second != -1)
		{
			//已存在，不允许插入
			return false; 
		}
		//不存在，插入,插入的位置由parent标出
		Node* parent = res.first;
		K newkey = key;
		Node* child = nullptr; 
		while(1)
		{
			//先插入，后续在检查是否满了
			InsertKey(parent,newkey,child);
			//判断是否满了
			if(parent->_n < M)//等于M时就是利用了我们的多开的空间 
			{
				return true;
			}
			else
			{
				//分裂
				size_t mid = M / 2;
				Node* brother = new Node;
				int left = 0;//分裂左边[0,mid) 
				int right = mid + 1;//分裂右边[right,M)
				int tmp = 0;//计数 
				while(right < M) 
				{
					//分裂拷贝
					brother->_keys[tmp] = parent->_keys[right];
					brother->_subs[tmp] = parent->_subs[right];
					if(parent->_subs[right])
					{
						//该parent不是叶子节点，_subs[i]存在下一级
						//所以要将孩子的父指针也继承给兄弟
						parent->_subs[right]->_parent = brother; 
					}
					tmp++;
					//拷贝走的内容置空
					parent->_keys[right] = K();
					parent->_subs[right] = nullptr;	
					right++; 
				}
				//由于孩子比关键字多一个，格外处理
				brother->_subs[tmp] = parent->_subs[right];
				//也需要判断是否需要继承下一代
				if(parent->_subs[right]) 
				{
					parent->_subs[right]->_parent = brother;
				}
				parent->_subs[right] = nullptr;//处理
				//处理中位数和_n
				brother->_n = tmp;
				parent->_n -= (tmp + 1);
				K midkey = parent->_keys[mid];
				parent->_keys[mid] = K();
				
				//如果刚刚分裂的是根节点
				if(parent->_parent == nullptr) 
				{
					_root = new Node;
					_root->_keys[0] = midkey;
					_root->_subs[0] = parent;
					_root->_subs[1] = brother;
					_root->_n = 1;
					parent->_parent = _root;
					brother->_parent = _root;
					break;
				}
				else
				{
					//非根节点
					//重新走循环
					newkey = midkey;
					child = brother;
					parent = parent->_parent; 
				}
			}
		}
	}
	//方便查看:中序:左-根-右 
	void InOrder()
	{
		_InOrder(_root);
	}
private:
	void _InOrder(Node* cur)
	{
		if (cur == nullptr)
			return;

		// 左 根  左 根  ...  右
		size_t i = 0;
		for (; i < cur->_n; ++i)
		{
			_InOrder(cur->_subs[i]); // 左子树
			cout << cur->_keys[i] << " "; // 根
		}

		_InOrder(cur->_subs[i]); // 最后的那个右子树
	}
	void InsertKey(Node* node, const K& key, Node* child)
	{
		int end = node->_n - 1;
		while(end >= 0)
		{
			if(key < node->_keys[end)
			{
				//后移原位置
				node->_keys[end + 1]  = node->_keys[end];
				//不要忘了孩子
				node->_subs[end + 2] = node->_subs[end + 1];
				end--;
			}
			else
			{
				//找到要插入的位置了 
				break;
			}					
		}
		node->_keys[end + 1] = key;
		node->_subs[end + 2] = child;
		if(child)
		{
			//孩子存在，孩子的父指针也要得到相应设置
			child->_parent = node; 
		}
		_node -> _n ++;
	}
	
	//成员变量: 
	Node* root = nullptr;//根节点	
};

int main()
{
	
	return 0;
}
