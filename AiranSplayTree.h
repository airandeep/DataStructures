#pragma once

template<typename T>
class AiranSplayTree{


private:
	struct Node{
		T data;
		Node *left;
		Node *right;
		Node(const T &_data = T(), Node *_left = nullptr, Node *_right = nullptr)
			:data(_data), left(_left), right(_right){}
	};

	Node *root;
	Node *nullNode;

	

	void splay(const T &_data,Node *&_node){
		Node *leftTreeMax, *rightTreeMin;
		static Node header;
		header.left = header.right = nullNode;
		leftTreeMax = rightTreeMin = &header;

		nullNode->data = _data;//确保比较//此步操作会使所有逻辑空节点的数据data变为最后一个插入的数据

		while (1){//建议写for(;;)表示死循环运行效率会更高一点
			if (_data < _node->data){
				if (_data < _node->left->data)
					RWLL(_node);
				if (_node->left == nullptr)
					break;
				rightTreeMin->left = _node;
				rightTreeMin = _node;
				_node = _node->left;
			}
			else if (_data > _node->data){
				if (_data > _node->right->data)
					RWRR(_node);
				if (_node->right == nullNode)
					break;
				leftTreeMax->right = _node;
				leftTreeMax = _node;
				_node = _node->right;//上面判断翻转(或未翻转)后的_node->right
									//是否存在的意义也在于此
			}
			else
				break;
		}

		leftTreeMax->right = _node->left;
		rightTreeMin->left = _node->right;
		_node->left = header.right;
		_node->right = header.left;

	}

	void RWLL(Node *&fa){//当所要查询的节点小于当前节点且小于当前节点左二子节点data
		Node *ch = fa->left;
		fa->left = ch->right;
		ch->right = fa;
		fa = ch;
	}

	void RWRR(Node *&fa){//伸展树只需要旋转，不需要高度信息
		Node *ch = fa->right;
		fa->right = ch->left;
		ch->left = fa;
		fa = ch;
	}

public:
	AiranSplayTree(){
		nullNode = new Node();//这次实例化Node对象产生的地址即可作为以后空指针检验地址
		nullNode->left = nullNode->right = nullNode;
		root = nullNode;
	}
	void insert(const T &_data){
		Node *newNode = new Node();
		newNode->data = _data;
		if (root == nullNode){
			newNode->left = newNode->right = nullNode;
			root = newNode;
		}
		else{
			splay(_data, root);//此步操作将与_data最接近的节点移植根部(root)
			if (_data < root->data){
				newNode->left = root->left;
				newNode->right = root;
				root->left = nullNode;//将根节点置为nullNode防止乱指
				root = newNode;
			}
			else if (_data > root->data){
				newNode->left = root;
				newNode->right = root->right;
				root->right = nullNode;
				root = newNode;
			}
			else
				return;//此数据与根部数据相同说明此数据已经插入
		}
	}

};

