#pragma once 

//红黑树条件
//1. 每一个节点或为黑色或为红色
//2. 根节点为黑色


//3. 红节点的子节点必然为黑色//（也就是说不可能出现连续的红节点）
//4. 任何一个节点到nullptr路径上的黑节点数目完全一样
//这些条件保证了红黑树的最多为2log(N+1)（也就是说是对数级别），时间复杂度为log(N)


//插入数据情况分类(前提条件:插入项必须是红色的):

//第一种情况:插入节点的父节点是黑色:无需处理，不破坏红黑树平衡条件

////////////
//第二种情况:插入节点的父节点是红色:2.1情况;2.2情况;
//2.1情况:父节点的兄弟节点是黑色(单旋转和双旋转即可解决)
//2.2情况:（可以自顶而下避免这种情况出现从而又归属为情况2.1）
//
template<typename T>
class RedBlackTree{



public:
	enum{RED,BLACK};
	explicit RedBlackTree(const T &_data){//防止RedBlackTree test = data;隐式调用构造函数 
		nullNode = new Node;//由于在Node结构体中已经定义了构造函数，所以会默认调用加不加()一样，如果没写构造函数则有区别
		nullNode->left = nullNode->right = nullNode;//逻辑空节点默认颜色也是黑色的

		header = new Node(_data);
		header->left = header->right = nullNode;
	}

	//insert item _data into the three,does nothing if x already present;
	void insert(const T &_data){//插入过程中先通过自顶而下解决插入路径上  黑节点有2个红节点的情况
		current = parent = grand = header;
		nullNode->data = _data;//将逻辑空节点数据置为插入数据_data,
		//						即可将数据存在和查到空算作一种情况
		while (current->data != _data)//这步操作将双红问题解决，即插入数据那一条路径上所有节点不可能出现左右儿子均为红色的情况
		{
			great = grand; grand = parent; parent = current;//
			current = _data < current->data ? current->left : current->right;//先到根节点，根节点不需要处理左右儿子为红色情况
			if (current->left->color = RED && current->right->color = RED){
				handleDoubleRed(_data);
			}
		}
		if (current != nullNode)
			return;
		current = new Node(_data,nullNode,nullNode);

		//由于不是指针引用，所以需要连接父节点即attach to parent;
		if (_data < parent->data)
			parent->left = current;
		else
			parent->right = current;
		handleDoubleRed(_data);
	}
private:
	struct Node{//初始化默认节点是黑色的
		T data;
		Node *left;
		Node *right;
		int color;
		Node(const T &_data = T(), Node *_left = nullptr, Node *_right = nullptr, int _color = BLACK)
			:data(_data), left(_left), right(_right), color(_color){}
	};

	Node *header;
	Node *nullNode;

	//用于insert例程及其辅助对象（逻辑上是static）
	Node *current;
	Node *parent;
	Node *grand;
	Node *great;
	//解决某个节点左右儿子为双红的问题(此节点由于性质3则必然为黑色)
	void handleDoubleRed(const T &_data){//依据插得数据判断解决双红问题后，连红问题该怎么旋转(单旋转与之字形旋转(之字形旋转可以通过一次单旋转转化为单旋转问题))
		current->color = RED;
		current - left->color = current->right->color = BLACK;
		if (parent->color == RED)//解决一条路径连续2个红节点问题,简化为2.1情况
		{
			grand->color = RED;
			if (_data < grand->data != _data < parent->data)
				parent = rotate(_data,grand);
			current = rotate(_data, great);//后面会有判断解决grand到底是great的左节点还是右节点
			current->color = BLACK;
		}
		header->right->color = BLACK; // Make root black？？
	}
	//只对theParent的左儿子或右儿子进行旋转操作
	Node *rotate(const T &_data, Node *theParent){
		if (_data < theParent->data){//if成立则是双旋转中的左边情况，先解决传入节点的左儿子的单旋转问题(进而转化为单旋转问题),
			_data < theParent->left->data ?
				RWLL(theParent->left) ://LL
				RWRR(theParent->left);//RR第一次只会触发此种情况
			return theParent->left;
		}
		else{
			_data > theParent->right->data ?
				RWRR(theParent->right) ://RR
				RWLL(theParent->right);//LL第一次只会触发此种情况
			return theParent->right;
		}
	}
	//
	void RWLL(Node *fa){
		Node *ch = fa->left;
		fa->left = ch->right;
		ch->right = fa;
		fa = ch;
	}

	//
	void RWRR(Node *fa){
		Node *ch = fa->right;
		fa->right = ch->left;
		ch->left = fa;
		fa = ch;
	}

};

