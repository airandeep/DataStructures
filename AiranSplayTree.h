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

		nullNode->data = _data;//ȷ���Ƚ�//�˲�������ʹ�����߼��սڵ������data��Ϊ���һ�����������

		while (1){//����дfor(;;)��ʾ��ѭ������Ч�ʻ����һ��
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
				_node = _node->right;//�����жϷ�ת(��δ��ת)���_node->right
									//�Ƿ���ڵ�����Ҳ���ڴ�
			}
			else
				break;
		}

		leftTreeMax->right = _node->left;
		rightTreeMin->left = _node->right;
		_node->left = header.right;
		_node->right = header.left;

	}

	void RWLL(Node *&fa){//����Ҫ��ѯ�Ľڵ�С�ڵ�ǰ�ڵ���С�ڵ�ǰ�ڵ�����ӽڵ�data
		Node *ch = fa->left;
		fa->left = ch->right;
		ch->right = fa;
		fa = ch;
	}

	void RWRR(Node *&fa){//��չ��ֻ��Ҫ��ת������Ҫ�߶���Ϣ
		Node *ch = fa->right;
		fa->right = ch->left;
		ch->left = fa;
		fa = ch;
	}

public:
	AiranSplayTree(){
		nullNode = new Node();//���ʵ����Node��������ĵ�ַ������Ϊ�Ժ��ָ������ַ
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
			splay(_data, root);//�˲���������_data��ӽ��Ľڵ���ֲ����(root)
			if (_data < root->data){
				newNode->left = root->left;
				newNode->right = root;
				root->left = nullNode;//�����ڵ���ΪnullNode��ֹ��ָ
				root = newNode;
			}
			else if (_data > root->data){
				newNode->left = root;
				newNode->right = root->right;
				root->right = nullNode;
				root = newNode;
			}
			else
				return;//�����������������ͬ˵���������Ѿ�����
		}
	}

};

