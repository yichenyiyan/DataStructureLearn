/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*       yichenyan  QAQ        *
* 编程学习应该是简单且有趣的  *
*******************************/



#include<cstdio>
#include<iostream>
using namespace std;

//老规矩实现一份面向对象的版本

struct Node {
	int data;
	Node* left;
	Node* right;
	Node(int);
	~Node();
};

Node::Node(int data)
	:data(data),left(nullptr)
	,right(nullptr)
{

}
Node::~Node(){}


class binarySearchTree {
private:
	Node* root;
	//Node* tmp_ptr;
	int size;
	//bool flag;
	void trueClear(Node*);
	void trueInsert(Node*, int);
	void truePrefaceErgodic(Node* now);
public:
	binarySearchTree(int data);
	~binarySearchTree();
	void insertNode(int);//插入方法
	void prefaceErgodic();//遍历方法（先序）
	void nclear();
	const int& getSize();
};

binarySearchTree::binarySearchTree(int data)
	:root(nullptr)
{
	this->root = new Node(data);
}

binarySearchTree::~binarySearchTree()
{
	this->trueClear(this->root);
}

void
binarySearchTree::trueClear(Node* now)
{
	if (now == nullptr)
		return;

	auto tmp = now;
	//if(tmp != this->root)
	delete tmp;
	binarySearchTree::trueClear(now->left);
	binarySearchTree::trueClear(now->right);

}

void 
binarySearchTree::nclear()
{
	this->trueClear(this->root);
	this->size = 0;
}



void 
binarySearchTree::truePrefaceErgodic(Node* now)
{
	
	if (now == nullptr)
		return;

	printf("[%d] -> ", now->data);
	binarySearchTree::truePrefaceErgodic(now->left);
	binarySearchTree::truePrefaceErgodic(now->right);

	return;
}

void 
binarySearchTree::trueInsert(Node* now, int data)
{
	if (now == nullptr)
		return;
	//大于等于放在右边吧
	if (data < now->data) {
		if (now->left == nullptr) {
			Node* newNode = new Node(data);
			now->left = newNode;
			return;
		}
		this->trueInsert(now->left, data);
	}
	else if (data >= now->data) {
		if (now->right == nullptr) {
			Node* newNode = new Node(data);
			now->right = newNode;
			return;
		}
		this->trueInsert(now->right, data);
	}
	return;
}


void 
binarySearchTree::insertNode(int data)
{
	trueInsert(this->root, data);
	this->size++;
}
const int& 
binarySearchTree::getSize()
{
	return this->size;
}


void 
binarySearchTree::prefaceErgodic()
{
	truePrefaceErgodic(this->root);
	std::cout << std::endl;
}


void testFunc1()
{
	binarySearchTree* tree = new binarySearchTree(8);
	tree->insertNode(3);
	tree->insertNode(10);
	tree->insertNode(1);
	tree->insertNode(6);
	tree->insertNode(4);
	tree->insertNode(7);
	tree->insertNode(10);
	tree->insertNode(14);
	tree->insertNode(13);
	tree->prefaceErgodic();

	delete tree;
}


int main()
{
	testFunc1();

	return 0;
}