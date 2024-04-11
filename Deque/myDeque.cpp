/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*       yichenyan  QAQ        *
* 编程学习应该是简单且有趣的  *
*******************************/




#include<iostream>
#include<limits.h>




struct Node {
	int data;     
	struct Node* prev;
	struct Node* next;
	Node(int data);
	~Node();
};

Node::Node(int data) 
	:data(data){}

Node::~Node(){}


class mydeque {
private:
	int size;     //元素个数
	Node* head;   //队首结点
	Node* tail;   //队尾结点

	//void tergodic(Node*);
	
	void dequeClear(Node*);

	mydeque(const mydeque& m);
	mydeque operator=(const mydeque& m);
public:
	mydeque();
	~mydeque();
	void trueLeftPush(int);
	void trueRightPush(int);
	int dequeLeftPop();
	int dequeRightPop();
	void ergodic();
	void nclear();
};

mydeque::mydeque()
	:size(0), head(nullptr)
	,tail(nullptr)
{
	
}

mydeque::~mydeque()
{
	if (this->head != nullptr && this->tail != nullptr)
		this->dequeClear(this->head);
}



void 
mydeque::trueLeftPush(int data)
{
	if (this->head == nullptr && this->tail == nullptr) {
		Node* node = new Node(std::move(data));
		this->head = node;
		this->tail = node;
		this->size++;
	}
	else {
		Node* node = new Node(std::move(data));
		node->next = this->head;
		this->head->prev = node;
		this->head = node;
		this->size++;
	}

}

void
mydeque::trueRightPush(int data)
{
	if (this->tail == nullptr && this->head == nullptr) {
		Node* node = new Node(std::move(data));
		this->head = node;
		this->tail = node;
		this->size++;
	}
	else {
		Node* node = new Node(std::move(data));
		node->prev = this->tail;
		this->tail->next = node;
		this->tail = node;
		this->size++;
	}

}

void 
mydeque::dequeClear(Node* start)
{
	if (start == nullptr)
		return;
	if (this->size == 0 && this->head == nullptr && this->tail == nullptr)
		return;
	Node* tmp = start;
	while (tmp != nullptr) {
		delete tmp;
		start = start->next;
		tmp = start;
		
	}
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

void 
mydeque::nclear()
{
	if (this->size == 0 && this->head == nullptr && this->tail == nullptr)
		return;

	this->dequeClear(this->head);
}

int 
mydeque::dequeRightPop()
{
	if (this->size == 0)
		return -INT_MAX;
	if (this->head == nullptr && this->tail == nullptr)
		return -INT_MAX + 1;

	int res = this->tail->data;
	Node* tmp = this->tail;
	this->tail = this->tail->prev;
	this->tail->next = nullptr;
	this->size--;
	delete tmp;
	return res;
}


int
mydeque::dequeLeftPop()
{
	if (this->size == 0)
		return -INT_MAX;
	if (this->head == nullptr && this->tail == nullptr)
		return -INT_MAX + 1;

	int res = this->head->data;
	Node* tmp = this->tail;
	this->head = this->head->prev;
	this->head->next = nullptr;
	this->size--;
	delete tmp;
	return res;
}



void
mydeque::ergodic()
{
	if (this->size == 0) {
		std::cout<<"the deque is null\n";
		return;
	}
	
	for (Node* node = this->head; node != nullptr; node = node->next) {
		std::cout << node->data << " ";
	}
	std::cout << std::endl;
}

void testFunc1()
{
	mydeque* _deque = new mydeque();
	if (_deque == nullptr)
		return;
	_deque->trueRightPush(1);
	_deque->trueRightPush(2);
	_deque->trueRightPush(3);
	_deque->trueRightPush(4);
	_deque->trueLeftPush(-1);
	_deque->trueLeftPush(-3);
	_deque->ergodic();
	delete _deque;
}


int main()
{
	testFunc1();

	return 0;
}