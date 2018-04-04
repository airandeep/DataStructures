#pragma

#include <iostream>
#include <queue>
using namespace std;

template<typename T>
class AiranAvlTree//��ת�㷨�ǹؼ�
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
	int height(Node *_node){//����߶�,���ڵ�߶�Ϊ0��//���������һ���ڵ㣬�˽ڵ�(�����˽ڵ�)���������и��ڵ�߶ȶ������
		//�������ĸ߶�Ϊ-1��Ҷ�ӵĸ߶�Ϊ0
		return _node == nullptr ? -1 : _node->height;//
	}
	int max(int a, int b){
		return a > b ? a : b;
	}
	Node *root;


	void insert(const T &_data, Node *&_node){//�ݹ�������ָ�����ã��Һ����ƽ�����Ҳ����ָ������
		if (_node == nullptr)
			_node = new Node(_data);
		else if (_data < _node->data)
			insert(_data, _node->left);
		else if (_data > _node->data)
			insert(_data, _node->right);
		/*else
			;*/
		balance(_node);//��������ô˺����ᵼ�²���ڵ㼰�˽ڵ����еĸ��ڵ�ȫ����ִ�д˺���
	}
	static const int ALLOWED_IMBALANCE = 1;//����Ĳ�ƽ��
	
	void balance(Node *&_node){
		if (_node == nullptr)
			return;
		if (height(_node->left) - height(_node->right) > ALLOWED_IMBALANCE){
			if (height(_node->left->left) > height(_node->left->right))//��ƽ���⵽�ƻ��Ľڵ�����������������������ƻ���ƽ��
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


	void RWLL(Node *&fa){//����
		Node *ch = fa->left;
		fa->left = ch->right;
		ch->right = fa;
		fa->height = max(height(fa->left), height(fa->right)) + 1;
		ch->height = max(height(ch->left), fa->height) + 1;//��Ϊch���Ҷ����Ѿ�����Ϊfa�ڵ�
		fa = ch;//��Ϊ��ָ�����ã�����ͨ���˷��������븸�ڵ����ϣ�
	}
	void RWLR(Node *&fa){//����
		RWRR(fa->left);
		RWLL(fa);
	}

	void RWRR(Node *&fa){//����
		Node *ch = fa->right;
		fa->right = ch->left;
		ch->left = fa;
		fa->height = max(height(fa->left), height(fa->right)) + 1;
		ch->height = max(fa->height, height(ch->right)) +1;
		fa = ch;
	}

	void RWRW(Node *&fa){//����
		RWLL(fa->right);
		RWRR(fa);
	}
	//�������
	void printPre(Node *_node, std::ostream &os){
		if (_node){
			os << _node->data << " ";
			printR(_node->left, os);
			printR(_node->right, os);
		}
	}
	//�������
	void printPost(Node *_node, std::ostream &os){
		if (_node){
			printPost(_node->left, os);
			printPost(_node->right, os);
			os << _node->data << " ";
		}
	}
	//�������
	void printIn(Node *_node, std::ostream &os){//�������//һ���õ��ݹ�ʱ��������Node*
		if (_node){
			printIn(_node->left,os);
			os << _node->data << " ";
			printIn(_node->right,os);
		}
	}

	//��α���
	void printLevel(Node *_node, ostream &_os){
		if (_node){//�ȼ��һ�µ�ǰ�ڵ��Ƿ�Ϊ��
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

	Node *getMax(Node *_node){//�ǵݹ�
		if (_node){
			while (_node->right)
				_node = _node->right;
		}
		return _node;
	}
	Node *getMax1(Node *_node){//�ݹ�
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
		if (_node == nullptr)//�ݹ��
			return;
		else if (_data < _node->data)
			remove(_node->left, _data);
		else if (_data > _node->data)
			remove(_node->right, _data);
		else{//�ҵ��ýڵ�
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