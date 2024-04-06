/******************************
*  ���ߣ��õ�����ŵ���(CSDN) *
*  Github:��С���С�Ե�      *
*          yichenyan          *
* ���ѧϰӦ���Ǽ�����Ȥ��  *
*******************************/

//��������C����ʵ�֣�

#include<stdio.h>
#include<stdlib.h>



//������
typedef struct Node {
	//������øýڵ㴢���Զ������ݣ���������ѡ���Դ���int��������Ϊ��
	int yourData;
	struct Node* next;
}Node;


//��������
typedef struct myList {
	/*Ϊ�˸��õĲ��������ͷ��β������ѡ��Ϊÿһ������
	 ��������ָ�루�ֱ�ָ�������ͷ����β��㣩
	 ĳЩ����³��ڶ����ܵĿ������ǿ��Լ�¼����Ľڵ���
	 �������ǾͲ�����ÿ�α�������������ͳ�Ƹ��������ж��ٽ����
	 ��������Ǹ������������۾������sizeҲ�Ǹ��������ͣ�
	 Ҳ������һ���Ĵ洢�ռ䡢������У����롢ɾ��ʱ�ģ�ά��
	 */

	int size; //���������
	int isEmpty; //ĳЩ�����ͨ������־λ���ж������Ƿ�Ϊ����ʡ�����¶�
	struct Node* listHead;
	struct Node* listTail;


	/*�����õ��˺���ָ�루���ܶ����֣���սӴ�C���ԵĴ�һ�����Ǻ��Ѻã�
	����C�����Բ�֧����������̣��������ú���ָ����ʵ��һ�²��뺯��
	�������ѧ��C���Խ���ѧһ�º���ָ��,�洦��࣬����ܶ��������C���Կ�Դ����
	�����õ��˺���ָ�룬��������ڻ�����ѧϰ����ָ�룬�����ѡ�񿴲���
	�ⰸ����C++ʵ�ְ汾��*/
#if 1
	//ͷ�巨
	int (*push_front)(struct myList*, struct Node*);


	//β�巨
	int (*push_back)(struct myList*, struct Node*);

	//��ĳ��ĳ���������
	int (*push_any)(struct myList*, struct Node*, struct Node*);

	//��ͷ��ʼ��������
	void (*ergodic)(struct myList*);
#endif
	//ɾ��ͷ���(int ��Ϊ0��ʾ��list�����Ԫ�����ڶ������ٵ��ڴ�
	// (��Ҫ�û�������Ա���Լ��ж�))
	int (*del_front)(struct myList*, int);

	//ɾ��β�ڵ�(ͬ��)
	int (*del_back)(struct myList*, int);

	//ɾ��ĳ��������һ�����
	int (*del_nodeNext)(struct myList*, struct Node*, int);

	//�������
	void (*claer_mylist)(struct myList*, int);
}myList;


int push_front(struct myList* list, struct Node* newNode)
{
	if (list->isEmpty) {//����Ϊ��
		list->listHead = newNode;
		list->listTail = newNode;
		newNode->next = NULL;
		list->isEmpty = 0;
		list->size += 1;
		return 0;
	}
	else if (!list->isEmpty) {//����Ϊ��
		newNode->next = list->listHead;
		list->listHead = newNode;
		list->size += 1;
		return 1;
	}
	else if (list->isEmpty != 1 && list->isEmpty != 0) {
		//�޷��ж������Ƿ�Ϊ��
		return -1;
	}

	return -2;
}


int push_back(struct myList* list, struct Node* newNode)
{
	if (list->isEmpty) {//����Ϊ��
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
		//�޷��ж������Ƿ�Ϊ��
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
		//�޷��ж������Ƿ�Ϊ��
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
	//��ʼ������
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