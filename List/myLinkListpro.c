/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*          yichenyan          *
* 编程学习应该是简单且有趣的  *
*******************************/



#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>


//重新实现一遍链表，主要是因为之前的单向链表太过鸡肋
//不灵活，导致其应用场景不大
//双向链表（C语言实现）



struct Node {
	int data;
	struct Node* prev;//前
	struct Node* next;//后
};

typedef struct Node Node;

struct myList {
	int size;       //结点个数
	bool isEmpty;	//是否为空
	Node* headNode; //逻辑上的头部
	Node* tailNode; //逻辑上的尾部

	bool (*push_front)(struct myList*, struct Node*); //头插法
	bool (*push_back)(struct myList*, struct Node*);  //尾插法
	//已知前后结点在中间插入
	bool (*push_btw)(struct myList*, struct Node*, struct Node*, struct Node*);

	//移除头（尾）部，bool为true时表示移除的数据是堆区开辟的
	//（为了防止内存泄露，需用户自行判断）
	bool (*del_front)(struct myList*, bool);
	bool (*del_back)(struct myList*, bool);
	bool (*del_btw)(struct myList*, struct Node*, struct Node*, bool);

	void (*ergodic)(struct myList*);//这里作者只实现了从逻辑上的头开始遍历到逻辑上的尾
	void (*clear)(struct myList*, bool);
};

typedef struct myList List;

bool push_front(List* list, Node* node)
{
	if (node == NULL)
		return false;

	if (list->isEmpty) {
		list->headNode = node;
		list->tailNode = node;
		node->prev = node;
		node->next = node;
		list->isEmpty = false;
		list->size++;
		return true;
	}
	else {
		Node* tmp = list->headNode;
		tmp->prev = node;
		node->next = tmp;
		node->prev = list->tailNode;
		list->headNode = node;
		list->size++;
		return true;
	}

	return false;
}


bool push_back(List* list, Node* node)
{
	if (node == NULL)
		return false;

	if (list->isEmpty) {
		list->headNode = node;
		list->tailNode = node;
		node->prev = node;
		node->next = node;
		list->isEmpty = false;
		list->size++;
		return true;
	}
	else {
		Node* tmp = list->tailNode;
		tmp->next = node;
		node->prev = tmp;
		node->next = list->headNode;
		list->tailNode = node;
		list->size++;
		return true;
	}

	return false;
}

bool del_front(List* list, bool flag)
{
	if (list->isEmpty || list->size == 0) {
		printf("the list is null!\n");
		return false;
	}

	Node* tmp = list->headNode;
	list->size--;
	if (list->size == 0) {
		list->isEmpty = true;
		/*list->headNode->prev = NULL;
		list->headNode->next = NULL;*/
		list->headNode = NULL;
		/*list->tailNode->prev = NULL;
		list->tailNode->next = NULL;*/
		list->tailNode = NULL;
		goto NEXT;
	}

	list->headNode = list->headNode->next;
	list->headNode->prev = list->tailNode;
	list->tailNode->next = list->headNode;


NEXT:
	if (flag)
		free(tmp);

	return true;
}

bool del_back(List* list, bool flag)
{
	if (list->isEmpty || list->size == 0) {
		printf("the list is null!\n");
		return false;
	}
	Node* tmp = list->tailNode;
	list->size--;
	if (list->size == 0) {
		list->isEmpty = true;
		/*list->headNode->prev = NULL;
		list->headNode->next = NULL;*/
		list->headNode = NULL;
		/*list->tailNode->prev = NULL;
		list->tailNode->next = NULL;*/
		list->tailNode = NULL;
		goto NEXT;
	}

	list->tailNode = list->tailNode->prev;
	list->tailNode->next = list->headNode;
	list->headNode->prev = list->tailNode;

NEXT:
	if (flag)
		free(tmp);

	return true;
}

void ergodic(List* list)
{
	if (list->size == 0 || list->isEmpty) {
		printf("the list is null!\n");
		return;
	}
	printf("\n+--start ergodic--+\n");
	Node* tmp = list->headNode;
	do {
		printf("%d -> ", tmp->data);
		tmp = tmp->next;
	} while (tmp != list->tailNode);
	printf("%d", tmp->data);

	printf("\n+--finish ergodic--+\n\n");
	return;
}

void clear(List* list, bool flag)
{
	Node* tmp = list->headNode;
	list->headNode = list->headNode->next;
	if (flag) {
		do {
			free(tmp);
			tmp = list->headNode;
			list->headNode = list->headNode->next;
		} while (list->headNode != list->tailNode);
		tmp = list->headNode;//or//tmp = list->tailNode;

		free(tmp);
	}
	list->size = 0;
	list->isEmpty = true;
#if 0
	list->headNode->prev = NULL;
	list->headNode->next = NULL;
#endif
	list->headNode = NULL;
#if 0
	list->tailNode->prev = NULL;
	list->tailNode->next = NULL;
#endif
	list->tailNode = NULL;

	return;
}

bool push_btw(List* list, Node* prevNode, Node* nextNode, Node* newNode)
{
	if ((newNode == NULL || prevNode == NULL || nextNode == NULL) && list->size)
		return false;

	//首先确定prevNode和nextNode是相邻的
	if ((list->size >= 2) &&
		prevNode->next == nextNode &&
		nextNode->prev == prevNode) {

		prevNode->next = newNode;
		newNode->prev = prevNode;
		nextNode->prev = newNode;
		newNode->next = nextNode;
		list->size++;
		return true;
	}
	else if ((list->size == 1) &&
		prevNode == list->headNode &&
		nextNode == list->headNode &&
		prevNode == list->tailNode &&
		nextNode == list->tailNode) {
		//这种情况作者默认把新结点插入并视为新的尾结点
		list->headNode->next = newNode;
		list->headNode->prev = newNode;
		newNode->prev = list->headNode;
		newNode->next = list->headNode;
		list->tailNode = newNode;
		list->size = 2;
		return true;
	}
	else
		return false;
}

bool del_btw(List* list, Node* prevNode, Node* nextNode, bool flag)
{
	if (list->isEmpty || list->size == 0)
		return false;

	if (list->size == 1 &&
		prevNode == list->headNode &&
		nextNode == list->headNode &&
		prevNode == list->tailNode &&
		nextNode == list->tailNode) {
		Node* tmp = prevNode;
		if (flag)
			free(tmp);
		list->headNode = NULL;
		list->tailNode = NULL;
		list->size = 0;
		list->isEmpty = true;
		return true;
	}
	else if (list->size == 2 &&
		(prevNode->next == nextNode) &&
		(nextNode->prev == prevNode) &&
		(prevNode->prev == nextNode) &&
		(nextNode->next == prevNode)) {
		//两个形成环作者选择也让其删除失败
		// 因为这种情况完全可以用头尾删解决
		// 这下该明白迭代器的意义了吧，哈哈哈）
		return false;
	}
	else if (list->size >= 3 &&
		prevNode->next == nextNode->prev) {
		Node* tmp = prevNode->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		list->size--;
		if (flag)
			free(tmp);
		return true;
	}
	else
		return false;

}

void listInit(List* list)
{
	list->size = 0;
	list->isEmpty = true;
#if 0
	list->headNode->prev = NULL;
	list->headNode->next = NULL;
#endif
	list->headNode = NULL;
#if 0
	list->tailNode->prev = NULL;
	list->tailNode->next = NULL;
#endif
	list->tailNode = NULL;
	list->push_front = push_front;
	list->push_back = push_back;
	list->del_front = del_front;
	list->del_back = del_back;
	list->push_btw = push_btw;
	list->del_btw = del_btw;
	list->clear = clear;
	list->ergodic = ergodic;
}


void testFunc1()
{
	List* list = (List*)malloc(sizeof(List));
	assert(list != NULL);
	listInit(list);
	for (int i = 0; i < 10; ++i) {
		Node* _node = (Node*)malloc(sizeof(Node));
		_node->data = 21 + i;
		_node->next = NULL;
		_node->prev = NULL;
		if (!list->push_back(list, _node)) {
			printf("fail to push_back idx: %d\n", i);
		}
	}
	printf("after push_back the list size is %d\n", list->size);
	list->ergodic(list);

	for (int i = 0; i < 10; ++i) {
		Node* _node = (Node*)malloc(sizeof(Node));
		_node->data = 21 + i;
		_node->next = NULL;
		_node->prev = NULL;
		if (!list->push_front(list, _node)) {
			printf("fail to push_front idx: %d\n", i);
		}
	}
	printf("after push_front the list size is %d\n", list->size);
	list->ergodic(list);

	//偷懒：不想写寻找某个结点的函数了
	//测试删除的
	Node* testPrevNode1 = list->headNode->next->next;//头的下下个结点
	Node* testNextNode1 = testPrevNode1->next->next;
	if (list->del_btw(list, testPrevNode1, testNextNode1, true)) {
		printf("after del_btw the list size is %d\n", list->size);
		list->ergodic(list);
	}

#if 1
	//测试插入的
	Node* _newNode = (Node*)malloc(sizeof(Node));
	Node* testNextNode2 = list->tailNode->prev->prev;//同理
	//Node* testPrevNode2 = testNextNode2->prev;//这种情况会出错
	Node* testPrevNode2 = list->tailNode->prev->prev->prev;
	if (list->push_btw(list, testPrevNode2, testNextNode2, _newNode)) {
		printf("after push_btw the list size is %d\n", list->size);
		list->ergodic(list);
	}
#endif	

	if (list->del_front(list, true)) {
		printf("after del_front the list size is %d\n", list->size);
		list->ergodic(list);
	}

	if (list->del_back(list, true)) {
		printf("after del_back the list size is %d\n", list->size);
		list->ergodic(list);
	}


	list->clear(list, true);
	printf("after clear the list size is %d\n", list->size);
	list->ergodic(list);


	free(list);
}



int main()
{
	testFunc1();

	return 0;
}
