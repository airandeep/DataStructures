#pragma

#include <iostream>
#include <queue>
using namespace std;

template<typename T>
class AiranAvlTree//旋转算法是关键
{
private:
	struct Node{
		T data;
		Node *left;
		Node *right;
		int height;
		Node(const T &_data = T(),Node *_left = nullptr,Node *_right = nullptr)
			:data(_data),left(_left),right(_right){}

	};
	int height(Node *_node){//这个高度,根节点高度为0；//理解概念插入一个节点，此节点(包括此节点)及以上所有父节点高度都会更新
		//即空树的高度为-1，叶子的高度为0
		return _node == nullptr ? -1 : _node->height;//
	}
	int max(int a, int b){
		return a > b ? a : b;
	}
	Node *root;


	void insert(const T &_data, Node *&_node){//递归插入必须指针引用，且后面的平衡操作也必须指针引用
		if (_node == nullptr)
			_node = new Node(_data);
		else if (_data < _node->data)
			insert(_data, _node->left);
		else if (_data > _node->data)
			insert(_data, _node->right);
		/*else
			;*/
		balance(_node);//在这里放置此函数会导致插入节点及此节点所有的父节点全部会执行此函数
	}
	static const int ALLOWED_IMBALANCE = 1;//允许的不平衡
	
	void balance(Node *&_node){
		if (_node == nullptr)
			return;
		if (height(_node->left) - height(_node->right) > ALLOWED_IMBALANCE){
			if (height(_node->left->left) > height(_node->left->right))//在平衡遭到破坏的节点的左子树的左子树插数据破坏的平衡
				RWLL(_node);
			else
				RWLR(_node);
		}
		else if (height(_node->right) - height(_node->left) > ALLOWED_IMBALANCE){
			if (height(_node->right->right) > height(_node->right->left))
				RWRR(_node);
			else
				RWRW(_node);
		}
		_node->height = max(height(_node->left), height(_node->right)) + 1;
	}


	void RWLL(Node *&fa){//左左
		Node *ch = fa->left;
		fa->left = ch->right;
		ch->right = fa;
		fa->height = max(height(fa->left), height(fa->right)) + 1;
		ch->height = max(height(ch->left), fa->height) + 1;//因为ch的右儿子已经更改为fa节点
		fa = ch;//因为是指针引用，所以通过此方法可以与父节点连上；
	}
	void RWLR(Node *&fa){//左右
		RWRR(fa->left);
		RWLL(fa);
	}

	void RWRR(Node *&fa){//右右
		Node *ch = fa->right;
		fa->right = ch->left;
		ch->left = fa;
		fa->height = max(height(fa->left), height(fa->right)) + 1;
		ch->height = max(fa->height, height(ch->right)) +1;
		fa = ch;
	}

	void RWRW(Node *&fa){//右左
		RWLL(fa->right);
		RWRR(fa);
	}
	//先序遍历
	void printPre(Node *_node, std::ostream &os){
		if (_node){
			os << _node->data << " ";
			printR(_node->left, os);
			printR(_node->right, os);
		}
	}
	//后序遍历
	void printPost(Node *_node, std::ostream &os){
		if (_node){
			printPost(_node->left, os);
			printPost(_node->right, os);
			os << _node->data << " ";
		}
	}
	//中序遍历
	void printIn(Node *_node, std::ostream &os){//中序遍历//一般用到递归时必须运用Node*
		if (_node){
			printIn(_node->left,os);
			os << _node->data << " ";
			printIn(_node->right,os);
		}
	}

	//层次遍历
	void printLevel(Node *_node, ostream &_os){
		if (_node){//先检测一下当前节点是否为空
			queue<Node*> Q;
			Q.push(_node);
			while (!Q.empty())
			{
				Node *x = Q.front(); Q.pop();
				_os << x->data << " ";
				if (x->left)
					Q.push(x->left);
				if (x->right)
					Q.push(x->right);
			}
		}
	}


	void makeEmpty(Node *_node){
		if (_node){
			makeEmpty(_node->left);
			makeEmpty(_node->right);
			delete _node;
		}
		_node = nullptr;
	}

	Node *getMax(Node *_node){//非递归
		if (_node){
			while (_node->right)
				_node = _node->right;
		}
		return _node;
	}
	Node *getMax1(Node *_node){//递归
		if (_node){
			if (_node->right == nullptr)
				return _node;
			else
				getMax1(_node->right);
		}
		return _node;
	}
	Node *getMin(Node *_node){
		if (_node){
			while (_node->left)
				_node = _node->left;
		}
		return _node;
	}

	void remove(Node *&_node,const T &_data){
		if (_node == nullptr)//递归基
			return;
		else if (_data < _node->data)
			remove(_node->left, _data);
		else if (_data > _node->data)
			remove(_node->right, _data);
		else{//找到该节点
			if (_node->left && _node->right){
				_node->data = getMin(_node->right)->data;
				remove(_node->right,_node->data);
			}
			else{
				Node *temp = _node;
				_node = _node->left ? _node->left : _node->right;
				delete temp;
			}
		}
		balance(_node);
	}

public:
	AiranAvlTree() :root(nullptr){}
	~AiranAvlTree(){
		makeEmpty(root);
	}


	void insert(const T &_data){
		insert(_data, root);
	}
	void print(std::ostream &os = std::cout){
		printLevel(root, os);
		std::cout << endl;
	}
	int getHeight(){
		return root->height;
	}

	void remove(const T&_data){
		remove(root, _data);
	}

	
};