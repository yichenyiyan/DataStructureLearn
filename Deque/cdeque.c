/******************************
*  ���ߣ��õ�����ŵ���(CSDN) *
*  Github:��С���С�Ե�      *
*       yichenyan  QAQ        *
* ���ѧϰӦ���Ǽ�����Ȥ��  *
*******************************/



#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<limits.h>


//֮ǰ�ĵ��˶��еײ�ʹ������洢
//̫�����ˣ�����һ�£�˫�˶���(������ʵ�����ݵĴ洢)


struct Node {
	int data;     //Ϊ�˷��㣬�������ѡ��int����������Ϊ�洢����
	struct Node* prev;
	struct Node* next;
};


typedef struct Node Node;

struct mydeque {
	int size;     //Ԫ�ظ���
	Node* head;   //���׽��
	Node* tail;   //��β���
};

typedef struct mydeque deque;


void dequeInit(deque* _deque)
{
	_deque->size = 0;
	_deque->head = NULL;
	_deque->tail = NULL;
}



void dequeLeftPush(deque* _deque, int  data)
{
	if (_deque->head == NULL && _deque->tail == NULL) {
		Node* node = (Node*)malloc(sizeof(Node));
		assert(node != NULL);
		node->data = data;
		node->prev = NULL;
		node->next = NULL;
		_deque->head = node;
		_deque->tail = node;
		_deque->size++;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		assert(node != NULL);
		node->data = data;
		node->prev = NULL;
		node->next = _deque->head;
		_deque->head->prev = node;
		_deque->head = node;
		_deque->size++;
	}

}


void dequeRightPush(deque* _deque, int  data)
{
	if (_deque->head == NULL && _deque->tail == NULL) {
		Node* node = (Node*)malloc(sizeof(Node));
		assert(node != NULL);
		node->data = data;
		node->prev = NULL;
		node->next = NULL;
		_deque->head = node;
		_deque->tail = node;
		_deque->size++;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		assert(node != NULL);
		node->data = data;
		node->prev = _deque->tail;
		node->next = NULL;
		_deque->tail->next = node;
		_deque->tail = node;
		_deque->size++;
	}

}


int dequeRightPop(deque* _deque)
{
	if (_deque == NULL)
		return -INT_MAX;
	if (_deque->head == NULL && _deque->tail == NULL && _deque != NULL)
		return -INT_MAX + 1;

	int res = _deque->tail->data;
	Node* tmp = _deque->tail;
	_deque->tail = _deque->tail->prev;
	_deque->tail->next = NULL;
	_deque->size--;
	free(tmp);
	return res;
}


int dequeLeftPop(deque* _deque)
{
	if (_deque == NULL)
		return -INT_MAX;
	if (_deque->head == NULL && _deque->tail == NULL && _deque != NULL)
		return -INT_MAX + 1;

	int res = _deque->head->data;
	Node* tmp = _deque->head;
	_deque->head = _deque->head->next;
	_deque->head->prev = NULL;
	_deque->size--;
	free(tmp);
	return res;
}


void ergodicDeque(deque* _deque)
{
	if (_deque->size == 0) {
		printf("the deque is null\n");
		return;
	}
	Node* tmp = _deque->head;
	printf("ergodic start from deque head to tail deque_size[%d]:\n\t", _deque->size);
	while (tmp != _deque->tail) {
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	printf("%d\n", tmp->data);

}

void dequeClear(deque* _deque)
{
	Node* tmp = NULL;
	while (_deque->head != _deque->tail) {
		tmp = _deque->head;
		_deque->head = _deque->head->next;
		free(tmp);
	}
	tmp = _deque->head;
	free(tmp);
	_deque->head = NULL;
	_deque->tail = NULL;
	_deque->size = 0;
}


void testFunc1()
{
	deque* _deque = (deque*)malloc(sizeof(deque));
	assert(_deque != NULL);
	dequeInit(_deque);
	for (int i = 1; i < 8; ++i) {
		dequeRightPush(_deque, i);
	}
	for (int i = 520; i < 525; ++i) {
		dequeLeftPush(_deque, i);
	}
	ergodicDeque(_deque);
	dequeLeftPop(_deque);
	dequeRightPop(_deque);
	ergodicDeque(_deque);
	dequeClear(_deque);
	ergodicDeque(_deque);
	free(_deque);
}


int main()
{
	testFunc1();

	return 0;
}
