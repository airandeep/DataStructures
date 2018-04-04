#pragma once

#include <iostream>
#include <queue>
using namespace std;
template<typename T>
class AiranTree
{
private:
	struct Node
	{
	public://写不写这个修饰符是无所谓，但是为了便于理解
		T data;
		Node *left, *right;
		Node(const T &_data = T(), Node *_left = nullptr, Node *_right = nullptr)
			:data(_data), left(_left), right(_right){}
	};

	Node *root;

	Node *findMin(Node *_node){//返回子树_node的最小节点
		if (_node){
			while (_node->left)
				_node = _node->left;
		}
		return _node;
	}

	Node *findMax(Node *_node)//返回子树_node的的最大节点
	{
		if (_node){
			while (_node->right)
				_node = _node->right;
		}
		return _node;
	}
	Node *findMax1(Node *_node){
		if (_node == nullptr)
			return nullptr;
		else{
			if (_node->right)
				_node = _node->right;
			else
				return _node;
		}
	}
	//中序遍历
	void print(Node *_node, std::ostream &os)
	{
		if (_node)//递归基，if之外即跳出
		{
			print(_node->left, os);
			os << _node->data << " ";
			print(_node->right, os);
		}
	}
	//层次遍历
	void printLevel(Node *_node, ostream &os){
		if (_node){
			queue<Node*> Q;
			Q.push(_node);
			while (!Q.empty())//队列非空检验
			{
				Node *x = Q.front(); Q.pop();
				os << x->data << " ";
				if (x->left)
					Q.push(x->left);
				if (x->right)
					Q.push(x->right);
			}
		
		}
	}

	void insert(const T &_data, Node *&_node)//这里必须指针引用，否则无法对影响传入的数据
	{
		if (_node == nullptr)
			_node = new Node(_data, nullptr, nullptr);
		else if (_data < _node->data)//如果插入数据小于当前节点数据，则向左子树递归
			insert(_data, _node->left);
		else if (_data > _node->data)
			insert(_data, _node->right);//如果插入数据大于当前节点数据，则向右子树递归
		else
			;//相同则不插入
	}

	void remove(const T &_data, Node *&_node){//与上面insert不同在于，此递归不需要对_node为nullptr进行操作  Error:所以不需要指针引用
		if (_node == nullptr)					//但还是需要指针应用，因为必须解决查到节点后父节点问题
			;//递归基，查不到此数据不操作
		else if (_data < _node->data)
			remove(_data, _node->left);
		else if (_data > _node->data)
			remove(_data, _node->right);
		else{//找到该节点了
			if (_node->right && _node->left){//该节点左子树与右子树均为空  //
				//删除策略1，用右子树最小节点数据取代该节点数据，然后递归删除该右子树最小节点(因为此节点由于最小必然左子树为空)
			/*	_node->data = findMin(_node->right)->data;
				remove(_node->data, _node->right);*/
				//对称删除策略2
				_node->data = findMax1(_node->left)->data;
				remove(_node->data, _node->left);
			}
			else{
				Node *temp = _node;
				_node = (_node->right) ? _node->right : _node->left;//三目运算符，_node->right为true即表示_node->right不为空
				delete temp;//释放节点；
				temp = nullptr;//养成良好习惯避免野指针的产生
			}
				
		}
	}

	//void insertNoRecursion2(const T &_data)//绝对不能使temp变为赋值为nullptr//错误
	//{
	//	if (root == nullptr){
	//		root = new Node(_data);
	//		return;
	//	}
	//	Node *&temp = root;
	//	while (temp)
	//	{
	//		if (_data == temp->data)
	//			return;
	//		else if (_data < temp->data)
	//			temp = temp->left;
	//		else
	//			temp = temp->right;
	//	}
	//	temp = new Node(_data);
	//}

	void insertNoRecursion(const T &_data)//绝对不能使temp变为赋值为nullptr//指针引用用于递归
	{
		if (root == nullptr){
			root = new Node(_data);
			return;
		}
		Node *temp = root;
		while (temp)
		{
			if (_data < temp->data)
			{
				if (temp->left == nullptr){
					temp->left = new Node(_data);
					return;
				}
				else
					temp = temp->left;
			}
			else if (_data > temp->data)
			{
				if (temp->right == nullptr){
					temp->right = new Node(_data);
					return;
				}
				else
					temp = temp->right;
			}
			else{//如果当前树中已经有此数据直接跳出
				return;
			}

		}
	}

	void makeEmpty(Node *_node){
		if (_node)
		{
			makeEmpty(_node->left);
			makeEmpty(_node->right);
			delete _node;
		}
		_node = nullptr;
	}


public:
	AiranTree() :root(nullptr){}
	void insert(const T &_data){
		insertNoRecursion(_data);
	}
	~AiranTree(){
		makeEmpty(root);
	}
	void printAiran(std::ostream &os)
	{
		print(root, os);//中序遍历
		cout << endl;
	}
	void remove(const T &_data){
		remove(_data, root);
	}

	void insertAiran(const T &_data){//指针引用只能用在递归插入
		
		if (root == nullptr)
			root = new Node(_data);
		else{
			Node *p = root;
			while (p)
			{
				if (_data < p->data)
				{
					if (p->left == nullptr)
						p->left = new Node(_data);
					else
						p = p->left;
				}
				else if (_data > p->data)
				{
					if (p->right == nullptr)
						p->right = new Node(_data);
					else
						p = p->right;
				}
				else
					return;
			}
		}

	}



};


template<typename T>
class AiranList
{
private:
	struct Node{
		T data;
		Node *prev;
		Node *next;
		Node(const T &_data = T(), Node *_prev = nullptr, Node *_next = nullptr)//const T &_data = T()默认初始化
			:data(_data), prev(_prev), next(_next){}
	};

	Node *head;
	Node *tail;
	void init()
	{
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;
	}

	void makeEmpty()
	{
		Node *temp = nullptr;
		while (head)
		{
			temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
	}

public:
	class const_iterator{

	protected:
		Node *current;
		T &getData() const{
			return current->data;
		}

		const_iterator(Node *_current) //交互的关键
			:current(_current){}

		friend class AiranList<T>;

	public:
		const_iterator() :current(nullptr){}

		const T &operator*() {
			return getData();
		}
		const_iterator &operator++(){//操作符前缀++itr
			current = current->next;
			return *this;
		}
		const_iterator &operator++(int){//操作符后缀意味使用时itr++
			const_iterator old = *this;
			current = current->next;
			return old;

		}


		bool operator==(const const_iterator &rhs)const{
			return current == rhs.current;
		}
		bool operator!=(const const_iterator &rhs)const{
			return !(*this == rhs);
		}
	};

	class iterator : public const_iterator{

	protected:
		iterator(Node *p) :const_iterator(p){}
		friend class AiranList<T>;
	public:
		iterator(){}

		T &operator*(){
			return getData();
		}



		iterator & operator++(){
			current = current->next;
			return *this;
		}

		iterator & operator++(int){
			iterator old = *this;
			++(*this);
			return old;
		}
	};


public:
	AiranList(){
		init();
	}
	~AiranList(){
		makeEmpty();
	}

	const_iterator beginConst() const{
		return(head->next);
	}
	iterator begin(){
		return(head->next);
	}
	const_iterator endConst() const{
		return tail;//隐式调用
	}
	iterator end(){
		return tail;
	}

	T operator[](int _n)//对操作符[]进行重载
	{
		Node *temp = head;
		for (int i = 0; i <= _n; i++){
			temp = temp->next;
		}
		return temp->data;
	}

	void push_back(const T &_data)
	{
		Node *p = new Node(_data, tail->prev, tail);
		tail->prev->next = p;
		tail->prev = p;
	}

	void push_front(const T &_data){
		Node *p = new Node(_data, head, head->next);
		head->next->prev = p;
		head->next = p;
	}

	void erase(iterator itr){//删除当前迭代器的数据
		Node *p = itr.current;
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}

	void print(iterator start,iterator end,ostream &os = cout){
		while (1)
		{
			if (start == end)
				return;
			os << *start << endl;
			start++;//输出数据后将迭代器向后退进
		}
	}
};