/******************************
*  ���ߣ��õ�����ŵ���(CSDN) *
*  Github:��С���С�Ե�      *
*       yichenyan  QAQ        *
* ���ѧϰӦ���Ǽ�����Ȥ��  *
*******************************/



#include<cstdio>
#include<iostream>
using namespace std;

//�Ϲ��ʵ��һ���������İ汾

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
	void insertNode(int);//���뷽��
	void prefaceErgodic();//��������������
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
	//���ڵ��ڷ����ұ߰�
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