/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*          yichenyan          *
* 编程学习应该是简单且有趣的  *
*******************************/



#include<cstdio>
#include<cassert>
#include<cstring>
#include<iostream>


using namespace std;


//Queue(CPP Version!!!!)
//ban STL


constexpr int maxQueueCap = 1024;

class myQueue {
private:
	int size;
	int maxCap;
	bool isFull;
	bool isEmpty;
	int Elems[maxQueueCap];
public:
	myQueue(int);
	~myQueue();
	bool push(int);
	int pop();
	int peek();
	int getSize();
	//bool setIsFull();
	void clear();
	bool getIsEmpty();
	void ergodic();
};

myQueue::myQueue(int cap)
	:maxCap(cap), size(0), isEmpty(true)
	,isFull(false)
{
	bzero(this->Elems, maxQueueCap);
}


myQueue::~myQueue()
{

}

bool 
myQueue::push(int elem)
{
	if (this->isFull) {
		cout << "queue is full!" << endl;
		return false;
	}

	this->Elems[this->size] = elem;
	this->size++;
	if (this->isEmpty) {
		this->isEmpty = false;
	}

	return true;
}

int
myQueue::pop()
{
	if (this->isEmpty) {
		cout << "queue is full!" << endl;
		return -9999;
	}

	int ret = this->Elems[0];
	for (int i = 0; i < this->size; ++i) {
		this->Elems[i] = this->Elems[i + 1];
	}
	this->Elems[this->size--] = 0;
	if (this->isFull)
		this->isFull = false;
	if (this->size == 0)
		this->isEmpty = true;

	return ret;
}


int
myQueue::peek()
{
	return this->Elems[0];
}


int
myQueue::getSize()
{
	return this->size;
}





void
myQueue::clear()
{
	if (this->isEmpty)
		return;
	bzero(this->Elems, maxQueueCap);
	this->size = 0;
	this->isFull = false;
	this->isEmpty = true;
}


bool
myQueue::getIsEmpty()
{
	return this->isEmpty;
}

void
myQueue::ergodic()
{
	if (this->isEmpty) {
		cout << "is null" << endl;
		return;
	}
		
	printf("+");
	for (int i = 0; i < this->size; ++i)
		printf("---");
	printf("+\n");

	printf(" ");
	for (int i = 0; i < this->size; ++i) {
		cout << this->Elems[i] << " ";
	}
	printf("\n");
	printf("+");
	for (int i = 0; i < this->size; ++i)
		printf("---");
	printf("+\n");

	cout << "finish ergodic!" << endl;
}

void testFunc1()
{
	myQueue* _queue = new myQueue(20);
	assert(_queue != nullptr);
	for (int i = 0; i < 15; ++i) {
		_queue->push(i);
	}
	cout << "after push size is: " << _queue->getSize() << endl;
	_queue->ergodic();

	cout << "peek: " << _queue->peek() << endl;
	cout << "pop: " << _queue->pop() << endl;
	cout << "after pop size is: " << _queue->getSize() << endl;
	_queue->ergodic();

	_queue->clear();
	cout << "after clear size is: " << _queue->getSize() << endl;
	_queue->ergodic();


	delete _queue;

}


int main()
{
	testFunc1();

	return 0;
}