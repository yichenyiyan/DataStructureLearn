/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*          yichenyan          *
* 编程学习应该是简单且有趣的  *
*******************************/


//老规矩(ban STL lib)栈实现(CPP Version)
//简单起见不用模板,默认只支持存储int类型

#include<cassert>
#include<cstring>
#include<iostream>

using namespace std;


#define STACK_MAX_CAP 1024

class myStack {
private:
	int* top;
	int size;
	int maxCap;
	bool isEmpty;
	bool isFull;
	int Elems[STACK_MAX_CAP];
public:
	myStack(int);
	~myStack();
	int getTop();
	int pop();
	bool push(int);
	void clear();
	void ergodic();
	int getSize();
};

myStack::myStack(int _maxCap)
	:maxCap(_maxCap),size(0),top(nullptr)
	,isEmpty(true), isFull(false)
{
	bzero(this->Elems, STACK_MAX_CAP);
	assert(_maxCap <= STACK_MAX_CAP);
}

myStack::~myStack()
{

}

int
myStack::getTop()
{
	if (this->top == nullptr) {
		cerr << "get top error" << endl;
		return -9999;
	}
	return *(this->top);
}

int
myStack::pop()
{
	if (this->isEmpty || this->top == nullptr) {
		cerr << "pop error" << endl;
		return -9999;
	}

	int ret = *(this->top);
	*(this->top) = 0;
	this->size--;
	if (this->size == 0) {
		this->isEmpty = true;
		this->top = nullptr;
		return ret;
	}
	if (this->isFull) {
		this->isFull = false;
	}
	this->top--;


	return ret;
}


bool 
myStack::push(int elem)
{
	if (this->isFull) {
		cout << "stack is full!" << endl;
		return false;
	}
	
	this->Elems[this->size] = elem;
	this->top = Elems + this->size;
	this->size++;
	if (this->size == this->maxCap)
		this->isFull = true;
	if (this->isEmpty && this->size)
		this->isEmpty = false;
	return true;
}


void
myStack::clear()
{
	bzero(this->Elems, STACK_MAX_CAP);
	this->size = 0;
	this->isEmpty = true;
	this->isFull = false;
	this->top = nullptr;
}

void
myStack::ergodic()
{
	if (this->isEmpty) {
		cout << "the stack is null!" << endl;
		return;
	}
	cout << "top -> ";
	while (top >= this->Elems) {
		cout << *(this->top) << endl;
		cout << "    -> ";
		top--;
	}
	this->top = this->Elems + this->size - 1;
	cout << endl << "finish ergodic!" << endl;
}

int 
myStack::getSize()
{
	return this->size;
}


void testFunc1()
{
	myStack* mystack = new myStack(10);

	for (int i = 0; i < 9; ++i) {
		if (!mystack->push(i))
			cout << "fail to push in index: " << i << endl;
	}
	//getTop ergodic
	cout << "now stack top is: " << mystack->getTop() << endl;
	cout << endl;
	//getSize
	cout << "now stack size is: " << mystack->getSize() << endl;
	mystack->ergodic();
	//pop
	cout << "before pop stack top elem is: " << mystack->pop() << endl;
	cout << "now stack size is: " << mystack->getSize() << endl;
	mystack->ergodic();

	//clear
	mystack->clear();
	mystack->ergodic();

	delete mystack;

}
#if 0
void testFunc2()
{
	myStack* mystack = new myStack(1025);
}
#endif


int main()
{
	testFunc1();
	//超最大容量测试
	//testFunc2();

	return 0;
}