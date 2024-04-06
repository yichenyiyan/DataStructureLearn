/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*          yichenyan          *
* 编程学习应该是简单且有趣的  *
*******************************/

#include<iostream>


//单向链表(cpp version)
//博主特意禁用了STL(ban STL)



using namespace std;


struct Node {
	int Data;
	Node* next;
	Node(int);
};

Node::Node(int data)
	:Data(data), next(nullptr)
{

}


class myList {
private:
	int size;
	bool isEmpty;
	Node* headNode;
	Node* tailNode;
public:
	myList();
	~myList();
	int getSize();
	Node* getHead();
	Node* getTail();
	bool push_front(Node*);
	bool push_back(Node*);
	bool push_any(Node*, Node*);
	bool del_front(Node*, int);
	bool del_back(Node*, int);
	bool del_nodeNext(Node*, int);
	void ergodicList();
	void clearList();
	void clearListinHeap();
};


myList::myList()
	:size(0), isEmpty(true), headNode(nullptr)
	, tailNode(nullptr)
{

}



myList::~myList()
{

}

int
myList::getSize()
{
	return this->size;
}

Node*
myList::getHead()
{
	return this->headNode;
}

Node*
myList::getTail()
{
	return this->tailNode;
}


bool
myList::push_front(Node* node)
{
	if (node == nullptr) {
		return false;
	}
	if (this->isEmpty) {
		this->headNode = node;
		this->tailNode = node;
		this->tailNode = nullptr;
		this->isEmpty = false;
		this->size++;
		return true;
	}
	else {
		auto tmp = this->headNode;
		this->headNode = node;
		node->next = tmp;
		this->size++;
		return true;
	}

	return false;
}


bool
myList::push_back(Node* newNode)
{
	if (newNode == nullptr)
		return false;
	if (this->isEmpty) {
		this->headNode = newNode;
		this->tailNode = newNode;
		newNode->next = nullptr;
		this->size++;
		this->isEmpty = false;
		return true;
	}
	else {
		(this->tailNode)->next = newNode;
		this->tailNode = newNode;
		newNode->next = nullptr;
		this->size++;
		return true;
	}

	return false;
}


bool
myList::push_any(Node* node, Node* newNode)
{
	if (newNode == nullptr)
		return false;
	if (node == nullptr && this->size == 0) {
		return this->push_back(newNode);
	}
	if (node == nullptr && this->size != 0) {
		return false;
	}
	if (node == this->tailNode) {
		node->next = newNode;
		this->tailNode = newNode;
		newNode->next = nullptr;
		this->size++;
		return true;
	}


	auto tmp = node->next;
	node->next = newNode;
	newNode->next = tmp;
	this->size++;
	if (this->size > 0)
		this->isEmpty = false;
	return true;
}

bool
myList::del_front(Node* node, int flag)
{
	if (this->isEmpty) {
		return false;
	}
	if (node == nullptr) {
		return false;
	}

	auto tmp = this->headNode;
	this->headNode = this->headNode->next;
	if (flag)
		delete tmp;
	this->size--;
	if (this->size == 0)
		this->isEmpty = true;

	return true;
}


bool
myList::del_back(Node* node, int flag)
{
	if (this->isEmpty) {
		return false;
	}
	if (node == nullptr) {
		return false;
	}

	auto tmp = this->headNode;
	while (tmp->next != this->tailNode) {
		tmp = tmp->next;
	}
	if (flag)
		delete this->tailNode;
	this->tailNode = tmp;
	this->size--;
	if (this->size == 0)
		this->isEmpty = true;

	return true;
}


bool
myList::del_nodeNext(Node* node, int flag)
{
	if (this->isEmpty)
		return false;
	if (node == this->tailNode) {
		return false;
	}

	auto tmp = node->next;
	node->next = tmp->next;
	if (flag)
		delete tmp;
	this->size--;
	if (this->size == 0)
		this->isEmpty = true;

	return true;
}


void
myList::ergodicList()
{
	if (this->isEmpty) {
		cout << "this list is null!" << endl;
		return;
	}

	auto tmp = this->headNode;
	for (int i = 0; i < this->size; ++i) {
		cout << tmp->Data << " -> ";
		tmp = tmp->next;
	}
	cout << endl;
	cout << "finish ergodic!" << endl;
}

void
myList::clearList()
{
	if (this->isEmpty)
		return;

	this->isEmpty = true;
	this->headNode = nullptr;
	this->tailNode = nullptr;
	this->size = 0;
}

void
myList::clearListinHeap()
{
	if (this->isEmpty)
		return;
	auto tmp = this->headNode;
	for (int i = 0; i < this->size; ++i) {
		this->headNode = headNode->next;
		delete tmp;
		tmp = headNode;
	}
	this->isEmpty = true;
	this->headNode = nullptr;
	this->tailNode = nullptr;
	this->size = 0;
}



#if 1
void testFunc1()
{
	cout << "DEBUG:" << endl;
	myList* _list = new myList();
	if (_list == nullptr) {
		cerr << "new error" << endl;
	}
	for (int i = 0; i < 10; ++i) {
		Node* _node = new Node(i);
		_list->push_back(_node);
	}
	cout << "list size:" << _list->getSize() << endl;
	_list->ergodicList();

	Node* _node = new Node(50);
	_list->push_front(_node);
	cout << "list size:" << _list->getSize() << endl;
	_list->ergodicList();

	Node* _node2 = new Node(66);
	_list->push_any(_list->getTail(), _node2);
	cout << "list size:" << _list->getSize() << endl;
	_list->ergodicList();

	_list->clearListinHeap();
	cout << "list size:" << _list->getSize() << endl;
	_list->ergodicList();

	delete _list;
}
#endif


int main()
{

	testFunc1();

	return 0;
}




