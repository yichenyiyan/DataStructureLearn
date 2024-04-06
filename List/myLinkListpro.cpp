/******************************
*  ���ߣ��õ�����ŵ���(CSDN) *
*  Github:��С���С�Ե�      *
*       yichenyan  QAQ        *
* ���ѧϰӦ���Ǽ�����Ȥ��  *
*******************************/



#include<cstdio>
#include<cassert>
#include<iostream>

using namespace std;

//ban STL
//Ϊ���չ�ѧ��ѧ�ܣ����߾Ͳ��������ģ��ʵ�ַ�����
//���ǵ������������ȫ��һ��Դ�ļ�
//������Ҫ�Ƕ�C����ʵ�ְ汾�����޸ģ�����û����ע�ͣ�
//����ˮƽҲ�����ޣ����в���֮�������λ���Ը���



struct Node {
	int data;
	struct Node* prev;
	struct Node* next;
	Node(int);
	~Node();
};


Node::Node(int data)
	:data(data),prev(nullptr)
	,next(nullptr)
{

}

Node::~Node(){}



class List {
private:
	int size;       //������
	bool isEmpty;	//�Ƿ�Ϊ��
	Node* headNode; //�߼��ϵ�ͷ��
	Node* tailNode; //�߼��ϵ�β��
	//֮ǰʵ�ֵ����ݽṹ��CPP�汾�����˽��ÿ��������������
	List(const List& l);
	List& operator=(const List&);
public:
	List();
	~List();
	const int& getSize();
	Node* getHeadNode();//���������ݰ�ȫ��������Ϊ�˴����ܻᵼ�·�װ�����ݱ��۸ģ�
	Node* getTailNode();//����Ϊ�˱��ڲ��Բ���ô�������Ƽ���������
	bool push_btw(Node*, Node*, Node*);
	bool push_back(Node*);
	bool push_front(Node*);
	bool del_btw(Node*, Node*, bool);
	bool del_back(bool);
	bool del_front(bool);
	void ergodic();
	void clear(bool);
};



List::List()
	:size(0), isEmpty(true)
	,headNode(nullptr),tailNode(nullptr)
{

}


List::~List()
{

}


const int& 
List::getSize()
{
	return this->size;
}

Node*
List::getHeadNode()
{
	return this->headNode;
}

Node*
List::getTailNode()
{
	return this->tailNode;
}


bool
List::push_back(Node* node)
{
	if (node == nullptr)
		return false;

	if (this->isEmpty) {
		this->headNode = node;
		this->tailNode = node;
		node->prev = node;
		node->next = node;
		this->isEmpty = false;
		this->size++;
		return true;
	}
	else {
		Node* tmp = this->tailNode;
		tmp->next = node;
		node->prev = tmp;
		node->next = this->headNode;
		this->tailNode = node;
		this->size++;
		return true;
	}

	return false;
}


bool
List::push_front(Node* node)
{
	if (node == nullptr)
		return false;

	if (this->isEmpty) {
		this->headNode = node;
		this->tailNode = node;
		node->prev = node;
		node->next = node;
		this->isEmpty = false;
		this->size++;
		return true;
	}
	else {
		Node* tmp = this->headNode;
		tmp->prev = node;
		node->next = tmp;
		node->prev = this->tailNode;
		this->headNode = node;
		this->size++;
		return true;
	}

	return false;
}


bool
List::del_back(bool flag)
{
	if (this->isEmpty || this->size == 0) {
		printf("the list is null!\n");
		return false;
	}
	Node* tmp = this->tailNode;
	this->size--;
	if (this->size == 0) {
		this->isEmpty = true;
		this->headNode = nullptr;
		this->tailNode = nullptr;
		goto NEXT;
	}

	this->tailNode = this->tailNode->prev;
	this->tailNode->next = this->headNode;
	this->headNode->prev = this->tailNode;

NEXT:
	if (flag)
		free(tmp);

	return true;
}



bool
List::del_front(bool flag)
{
	if (this->isEmpty || this->size == 0) {
		printf("the list is null!\n");
		return false;
	}

	Node* tmp = this->headNode;
	this->size--;
	if (this->size == 0) {
		this->isEmpty = true;
		
		this->headNode = nullptr;
		
		this->tailNode = nullptr;
		goto NEXT;
	}

	this->headNode = this->headNode->next;
	this->headNode->prev = this->tailNode;
	this->tailNode->next = this->headNode;


NEXT:
	if (flag)
		free(tmp);

	return true;
}


void 
List::ergodic()
{
	if (this->size == 0 || this->isEmpty) {
		printf("the list is null!\n");
		return;
	}
	printf("\n+--start ergodic--+\n");
	Node* tmp = this->headNode;
	do {
		printf("%d -> ", tmp->data);
		tmp = tmp->next;
	} while (tmp != this->tailNode);
	printf("%d", tmp->data);

	printf("\n+--finish ergodic--+\n\n");

	return;
}


void 
List::clear(bool flag)
{
	Node* tmp = this->headNode;
	this->headNode = this->headNode->next;
	if (flag) {
		do {
			delete tmp;
			tmp = this->headNode;
			this->headNode = this->headNode->next;
		} while (this->headNode != this->tailNode);
		tmp = this->headNode;

		delete tmp;
	}
	this->size = 0;
	this->isEmpty = true;
	this->headNode = nullptr;
	this->tailNode = nullptr;

	return;
}


bool
List::push_btw(Node* prevNode, Node* nextNode, Node* newNode)
{
	if ((newNode == nullptr || prevNode == nullptr || nextNode == nullptr) && this->size)
		return false;

	//����ȷ��prevNode��nextNode�����ڵ�
	if ((this->size >= 2) &&
		prevNode->next == nextNode &&
		nextNode->prev == prevNode) {

		prevNode->next = newNode;
		newNode->prev = prevNode;
		nextNode->prev = newNode;
		newNode->next = nextNode;
		this->size++;
		return true;
	}
	else if ((this->size == 1) &&
		prevNode == this->headNode &&
		nextNode == this->headNode &&
		prevNode == this->tailNode &&
		nextNode == this->tailNode) {
		//�����������Ĭ�ϰ��½����벢��Ϊ�µ�β���
		this->headNode->next = newNode;
		this->headNode->prev = newNode;
		newNode->prev = this->headNode;
		newNode->next = this->headNode;
		this->tailNode = newNode;
		this->size = 2;
		return true;
	}
	else
		return false;
}

bool 
List::del_btw(Node* prevNode, Node* nextNode, bool flag)
{
	if (this->isEmpty || this->size == 0)
		return false;

	if (this->size == 1 &&
		prevNode == this->headNode &&
		nextNode == this->headNode &&
		prevNode == this->tailNode &&
		nextNode == this->tailNode) {
		Node* tmp = prevNode;
		if (flag)
			free(tmp);
		this->headNode = nullptr;
		this->tailNode = nullptr;
		this->size = 0;
		this->isEmpty = true;
		return true;
	}
	else if (this->size == 2 &&
		(prevNode->next == nextNode) &&
		(nextNode->prev == prevNode) &&
		(prevNode->prev == nextNode) &&
		(nextNode->next == prevNode)) {
		return false;
	}
	else if (this->size >= 3 &&
		prevNode->next == nextNode->prev) {
		Node* tmp = prevNode->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		this->size--;
		if (flag)
			delete tmp;
		return true;
	}
	else
		return false;
}


void testFunc1()
{
	List* list = new List();
	assert(list != nullptr);
	for (int i = 0; i < 10; ++i) {
		Node* _node = new Node(44 + i);
		if (!list->push_back(_node)) {
			printf("fail to push_back idx: %d\n", i);
		}
	}
	printf("after push_back the list size is %d\n", list->getSize());
	list->ergodic();

	for (int i = 0; i < 10; ++i) {
		Node* _node = new Node(21 + i);
		if (!list->push_front(_node)) {
			printf("fail to push_front idx: %d\n", i);
		}
	}
	printf("after push_front the list size is %d\n", list->getSize());
	list->ergodic();

	
	Node* testPrevNode1 = list->getHeadNode()->next->next;//ͷ�����¸����
	Node* testNextNode1 = testPrevNode1->next->next;
	if (list->del_btw(testPrevNode1, testNextNode1, true)) {
		printf("after del_btw the list size is %d\n", list->getSize());
		list->ergodic();
	}


	//����
	Node* _newNode = (Node*)malloc(sizeof(Node));
	Node* testNextNode2 = list->getTailNode()->prev->prev;//ͬ��
	Node* testPrevNode2 = list->getTailNode()->prev->prev->prev;
	if (list->push_btw(testPrevNode2, testNextNode2, _newNode)) {
		printf("after push_btw the list size is %d\n", list->getSize());
		list->ergodic();
	}


	if (list->del_front(true)) {
		printf("after del_front the list size is %d\n", list->getSize());
		list->ergodic();
	}

	if (list->del_back(true)) {
		printf("after del_back the list size is %d\n", list->getSize());
		list->ergodic();
	}


	list->clear(true);
	printf("after clear the list size is %d\n", list->getSize());
	list->ergodic();


	delete list;
}




int main()
{
	testFunc1();

	return 0;
}