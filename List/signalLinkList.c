/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*          yichenyan          *
* 编程学习应该是简单且有趣的  *
*******************************/

//单向链表（C语言实现）

#include<stdio.h>
#include<stdlib.h>



//链表结点
typedef struct Node {
	//你可以用该节点储存自定义数据，本案例中选择以储存int数据类型为例
	int yourData;
	struct Node* next;
}Node;


//单向链表
typedef struct myList {
	/*为了更好的操作链表的头和尾，博主选择为每一条链表
	 定义两个指针（分别指向链表的头结点和尾结点）
	 某些情况下出于对性能的考虑我们可以记录链表的节点数
	 这样我们就不用在每次遍历整条链表来统计该条链表有多少结点了
	 这对性能是个提升，但代价就是这个size也是个数据类型，
	 也得消耗一定的存储空间、对其进行（插入、删除时的）维护
	 */

	int size; //链表结点个数
	int isEmpty; //某些情况下通过个标志位来判断链表是否为空能省不少事儿
	struct Node* listHead;
	struct Node* listTail;


	/*这里用到了函数指针（可能对新手（如刚接触C语言的大一）不是很友好）
	由于C的特性不支持面向对象编程，所以这用函数指针来实现一下插入函数
	如果你想学好C语言建议学一下函数指针,益处多多，此外很多优秀的用C语言开源库中
	大量用到了函数指针，如果你现在还不想学习函数指针，你可以选择看博主
	这案例中C++实现版本的*/
#if 1
	//头插法
	int (*push_front)(struct myList*, struct Node*);


	//尾插法
	int (*push_back)(struct myList*, struct Node*);

	//在某个某个结点后插入
	int (*push_any)(struct myList*, struct Node*, struct Node*);

	//从头开始遍历链表
	void (*ergodic)(struct myList*);
#endif
	//删除头结点(int 不为0表示在list储存的元素是在堆区开辟的内存
	// (需要用户（程序员）自己判断))
	int (*del_front)(struct myList*, int);

	//删除尾节点(同理)
	int (*del_back)(struct myList*, int);

	//删除某个结点的下一个结点
	int (*del_nodeNext)(struct myList*, struct Node*, int);

	//清空链表
	void (*claer_mylist)(struct myList*, int);
}myList;


int push_front(struct myList* list, struct Node* newNode)
{
	if (list->isEmpty) {//链表为空
		list->listHead = newNode;
		list->listTail = newNode;
		newNode->next = NULL;
		list->isEmpty = 0;
		list->size += 1;
		return 0;
	}
	else if (!list->isEmpty) {//链表不为空
		newNode->next = list->listHead;
		list->listHead = newNode;
		list->size += 1;
		return 1;
	}
	else if (list->isEmpty != 1 && list->isEmpty != 0) {
		//无法判断链表是否为空
		return -1;
	}

	return -2;
}


int push_back(struct myList* list, struct Node* newNode)
{
	if (list->isEmpty) {//链表为空
		list->listHead = newNode;
		list->listTail = newNode;
		newNode->next = NULL;
		list->isEmpty = 0;
		list->size += 1;
		return 0;
	}
	else if (!list->isEmpty) {
		(list->listTail)->next = newNode;
		newNode->next = NULL;
		list->listTail = newNode;
		list->size += 1;
		return 1;
	}
	else if (list->isEmpty != 1 && list->isEmpty != 0) {
		//无法判断链表是否为空
		return -1;
	}

	return -2;
}


int push_any(struct myList* list, struct Node* prev, struct Node* newNode)
{
	if (list->isEmpty && prev == NULL) {
		list->listHead = newNode;
		list->listTail = newNode;
		newNode->next = NULL;
		list->isEmpty = 0;
		list->size += 1;
		return 0;
	}
	else if (!list->isEmpty && prev != NULL) {
		newNode->next = prev->next;
		prev->next = newNode;
		list->size += 1;
		return 1;
	}
	else if (list->isEmpty && prev != NULL) {
		//无法判断链表是否为空
		return -1;
	}

	return -2;
}

void ergodicList(struct myList* list)
{
	if (list->isEmpty) {
		printf("the list is null!\n");
		return;
	}

	struct Node* tmp = list->listHead;
	for (int i = 0; i < list->size; ++i) {
		printf("%d -> ", tmp->yourData);
		tmp = tmp->next;
	}
	printf("\n");
	printf("finish trgodic\n");
	return;
}

void clear_mylist(struct myList* list, int flag)
{
	if (list->isEmpty)
		return;
	struct Node* tmp = list->listHead;
	for (int i = 0; i < list->size; ++i) {
		list->listHead = list->listHead->next;
		if (flag)
			free(tmp);
		tmp = list->listHead;
	}
	list->isEmpty = 1;
	list->listHead = NULL;
	list->listTail = NULL;
	list->size = 0;
}

int del_front(struct myList* list, int flag)
{
	if (list->isEmpty && list->size == 0)
		return -1;
	if (list == NULL)
		return -2;
	if (list->isEmpty && list->size > 0)
		return -3;

	struct Node* head = list->listHead;
	list->listHead = list->listHead->next;
	if (flag)
		free(head);
	list->size -= 1;
	if (list->size == 0)
		list->isEmpty = 1;
	return 0;
}

int del_back(struct myList* list, int flag)
{
	if (list->isEmpty && list->size == 0)
		return -1;
	if (list == NULL)
		return -2;
	if (list->isEmpty && list->size > 0)
		return -3;

	struct Node* node = list->listHead;
	while (node->next != list->listTail) {
		node = node->next;
	}
	if (node->next == list->listTail) {
		if (flag)
			free(list->listTail);
		list->listTail = node;
		list->size -= 1;
		if (list->size == 0)
			list->isEmpty = 1;
	}

	return 0;
}

int del_nodeNext(struct myList* list, struct Node* node, int flag)
{
	if (node->next == NULL) {
		printf("the node's next is null!\n");
		return -1;
	}

	struct Node* tmp = node->next;
	node->next = tmp->next;
	if (tmp->next == NULL) {
		list->listTail = node;
	}
	if (flag)
		free(tmp);
	list->size -= 1;
	if (list->size == 0)
		list->isEmpty = 1;


	return 0;
}

void testFunc1()
{
	//初始化链表
	struct myList* list = (struct myList*)malloc(sizeof(struct myList));
	if (list == NULL) {
		//perror("malloc");
		printf("fail to malloc!\n");
		exit(-1);
	}
	list->isEmpty = 1;
	list->listHead = NULL;
	list->listTail = NULL;
	list->size = 0;

	list->push_back = push_back;
	list->push_front = push_front;
	list->push_any = push_any;
	list->ergodic = ergodicList;
	list->claer_mylist = clear_mylist;
	list->del_back = del_back;
	list->del_front = del_front;
	list->del_nodeNext = del_nodeNext;

	for (int i = 0; i < 10; ++i) {
		struct Node* node = (struct Node*)malloc(sizeof(struct Node));
		node->yourData = i;
		push_back(list, node);
	}
	printf("list size: %d\n", list->size);
	list->ergodic(list);


	list->del_back(list, 1);
	printf("after del_back list size: %d\n", list->size);
	list->ergodic(list);


	list->del_front(list, 1);
	printf("after del_front list size: %d\n", list->size);
	list->ergodic(list);

	list->del_nodeNext(list, list->listHead, 1);
	printf("after del_nodeNext list size: %d\n", list->size);
	list->ergodic(list);

	list->claer_mylist(list, 1);
	printf("list size: %d\n", list->size);
	list->ergodic(list);


	free(list);
}




int main()
{
	testFunc1();
	return 0;
}