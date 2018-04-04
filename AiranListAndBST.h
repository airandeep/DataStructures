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
	public://д��д������η�������ν������Ϊ�˱������
		T data;
		Node *left, *right;
		Node(const T &_data = T(), Node *_left = nullptr, Node *_right = nullptr)
			:data(_data), left(_left), right(_right){}
	};

	Node *root;

	Node *findMin(Node *_node){//��������_node����С�ڵ�
		if (_node){
			while (_node->left)
				_node = _node->left;
		}
		return _node;
	}

	Node *findMax(Node *_node)//��������_node�ĵ����ڵ�
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
	//�������
	void print(Node *_node, std::ostream &os)
	{
		if (_node)//�ݹ����if֮�⼴����
		{
			print(_node->left, os);
			os << _node->data << " ";
			print(_node->right, os);
		}
	}
	//��α���
	void printLevel(Node *_node, ostream &os){
		if (_node){
			queue<Node*> Q;
			Q.push(_node);
			while (!Q.empty())//���зǿռ���
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

	void insert(const T &_data, Node *&_node)//�������ָ�����ã������޷���Ӱ�촫�������
	{
		if (_node == nullptr)
			_node = new Node(_data, nullptr, nullptr);
		else if (_data < _node->data)//�����������С�ڵ�ǰ�ڵ����ݣ������������ݹ�
			insert(_data, _node->left);
		else if (_data > _node->data)
			insert(_data, _node->right);//����������ݴ��ڵ�ǰ�ڵ����ݣ������������ݹ�
		else
			;//��ͬ�򲻲���
	}

	void remove(const T &_data, Node *&_node){//������insert��ͬ���ڣ��˵ݹ鲻��Ҫ��_nodeΪnullptr���в���  Error:���Բ���Ҫָ������
		if (_node == nullptr)					//��������Ҫָ��Ӧ�ã���Ϊ�������鵽�ڵ�󸸽ڵ�����
			;//�ݹ�����鲻�������ݲ�����
		else if (_data < _node->data)
			remove(_data, _node->left);
		else if (_data > _node->data)
			remove(_data, _node->right);
		else{//�ҵ��ýڵ���
			if (_node->right && _node->left){//�ýڵ�����������������Ϊ��  //
				//ɾ������1������������С�ڵ�����ȡ���ýڵ����ݣ�Ȼ��ݹ�ɾ������������С�ڵ�(��Ϊ�˽ڵ�������С��Ȼ������Ϊ��)
			/*	_node->data = findMin(_node->right)->data;
				remove(_node->data, _node->right);*/
				//�Գ�ɾ������2
				_node->data = findMax1(_node->left)->data;
				remove(_node->data, _node->left);
			}
			else{
				Node *temp = _node;
				_node = (_node->right) ? _node->right : _node->left;//��Ŀ�������_node->rightΪtrue����ʾ_node->right��Ϊ��
				delete temp;//�ͷŽڵ㣻
				temp = nullptr;//��������ϰ�߱���Ұָ��Ĳ���
			}
				
		}
	}

	//void insertNoRecursion2(const T &_data)//���Բ���ʹtemp��Ϊ��ֵΪnullptr//����
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

	void insertNoRecursion(const T &_data)//���Բ���ʹtemp��Ϊ��ֵΪnullptr//ָ���������ڵݹ�
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
			else{//�����ǰ�����Ѿ��д�����ֱ������
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
		print(root, os);//�������
		cout << endl;
	}
	void remove(const T &_data){
		remove(_data, root);
	}

	void insertAiran(const T &_data){//ָ������ֻ�����ڵݹ����
		
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
		Node(const T &_data = T(), Node *_prev = nullptr, Node *_next = nullptr)//const T &_data = T()Ĭ�ϳ�ʼ��
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

		const_iterator(Node *_current) //�����Ĺؼ�
			:current(_current){}

		friend class AiranList<T>;

	public:
		const_iterator() :current(nullptr){}

		const T &operator*() {
			return getData();
		}
		const_iterator &operator++(){//������ǰ׺++itr
			current = current->next;
			return *this;
		}
		const_iterator &operator++(int){//��������׺��ζʹ��ʱitr++
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
		return tail;//��ʽ����
	}
	iterator end(){
		return tail;
	}

	T operator[](int _n)//�Բ�����[]��������
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

	void erase(iterator itr){//ɾ����ǰ������������
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
			start++;//������ݺ󽫵���������˽�
		}
	}
};