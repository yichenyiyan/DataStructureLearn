/******************************
*  ���ߣ��õ�����ŵ���(CSDN) *
*  Github:��С���С�Ե�      *
*          yichenyan          *
* ���ѧϰӦ���Ǽ�����Ȥ��  *
*******************************/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

//�Ϲ�أ�����Cʵ�ֶ���
//�򵥻������ֻ֧�ֲ���ջ�������ݣ�����int���ͣ�

#define QUEUE_MAX_SIZE 1024


struct queue {
	int size;
	int maxCap;
	bool isEmpty;
	bool isFull;
	//����ʹ��������Ϊ�洢�ṹʵ����������ץ���
	//��Ϊʹ����������ܼ��ÿ�ε�һ��Ԫ�س���
	//������ʣ�µ�Ԫ�ؾ͵ü���Ǩ�ƣ��ڴ���������
	//����£����ܼ�����˴�ֻΪ������demo����
	//�ǴӼ򵥵ĽǶȳ����ģ�����Ҳ�������߲��Ǻ�
	//����Լ����鷳����ΪѧУ���з��˵���ҵ�أ�
	int Elements[QUEUE_MAX_SIZE];

	bool (*push)(struct queue*, int);//��β��������(���)
	int (*pop)(struct queue*);//��һ��Ԫ�س����һ�ȡ��ֵ
	int (*peek)(struct queue*);//�����ص�һ��Ԫ�ص�ֵ
	void (*clear)(struct queue*);//��ն���
	void (*ergodic)(struct queue*);//����
};

typedef struct queue queue;

bool push(queue* myqueue, int elem)
{
	if (myqueue->isFull) {
		printf("the queue is full!\n");
		return false;
	}

	myqueue->Elements[myqueue->size] = elem;
	myqueue->size += 1;
	if (myqueue->isEmpty)
		myqueue->isEmpty = false;
	if (myqueue->size == myqueue->maxCap)
		myqueue->isFull = true;

	return true;
}


int pop(queue* myqueue)
{
	if (myqueue->isEmpty) {
		printf("the queue is null!\n");
		return -9999;
	}

	int ret = myqueue->Elements[0];
	for (int i = 0; i < myqueue->size; ++i) {
		myqueue->Elements[i] = myqueue->Elements[i + 1];
	}
	if (myqueue->isFull)
		myqueue->isFull = false;

	myqueue->Elements[myqueue->size--] = 0;
	if (myqueue->size == 0)
		myqueue->isEmpty = true;

	return ret;
}


int peek(queue* myqueue)
{
	return myqueue->Elements[0];
}


void clear(queue* myqueue)
{
	if (myqueue->isEmpty)
		return;
	bzero(myqueue->Elements, (size_t)QUEUE_MAX_SIZE);
	myqueue->size = 0;
	myqueue->isEmpty = true;
	myqueue->isFull = false;
}

//�G������������������壡
void ergodic(queue* myqueue)
{
	if (myqueue->isEmpty) {
		printf("null\n");
		return;
	}
	printf("+");
	for (int i = 0; i < myqueue->size; ++i)
		printf("---");
	printf("+\n");

	printf(" ");
	int tmp = 0;
	while (tmp < myqueue->size) {
		printf("%d ", myqueue->Elements[tmp++]);
	}

	printf("\n");
	printf("+");
	for (int i = 0; i < myqueue->size; ++i)
		printf("---");
	printf("+\n");
}


void queueInit(queue* myqueue, int _maxCap)
{
	myqueue->size = 0;
	myqueue->isEmpty = true;
	myqueue->isFull = false;
	myqueue->maxCap = _maxCap;
	myqueue->push = push;
	myqueue->pop = pop;
	myqueue->clear = clear;
	myqueue->peek = peek;
	myqueue->ergodic = ergodic;
	bzero(myqueue->Elements, (size_t)QUEUE_MAX_SIZE);
}


void testFunc1()
{
	queue* _queue = (queue*)malloc(sizeof(struct queue));
	assert(_queue != NULL);
	queueInit(_queue, 100);
	for (int i = 0; i < 20; ++i){
		if (!_queue->push(_queue, i))
			printf("fail to push in index: %d\n", i);
	}
	printf("now size is: %d\n", _queue->size);
	_queue->ergodic(_queue);

	printf("pop queue front: %d\n", _queue->pop(_queue));
	printf("pop queue front: %d\n", _queue->pop(_queue));
	_queue->ergodic(_queue);

	printf("peek queue front: %d\n", _queue->peek(_queue));
	printf("peek queue front: %d\n", _queue->peek(_queue));
	_queue->ergodic(_queue);

	_queue->clear(_queue);
	printf("after clear\n");
	_queue->ergodic(_queue);

	free(_queue);
}


int main()
{
	testFunc1();

	return 0;
}
