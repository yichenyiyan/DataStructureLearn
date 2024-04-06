/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*          yichenyan          *
* 编程学习应该是简单且有趣的  *
*******************************/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

//老规矩：先用C实现队列
//简单化起见：只支持插入栈区的数据（且是int类型）

#define QUEUE_MAX_SIZE 1024


struct queue {
	int size;
	int maxCap;
	bool isEmpty;
	bool isFull;
	//这里使用数组作为存储结构实际上是令人抓狂的
	//因为使用数组的性能极差，每次第一个元素出队
	//数组中剩下的元素就得集体迁移，在大数据量的
	//情况下，性能极差，但此处只为了做个demo所以
	//是从简单的角度出发的，你们也懂的作者不是很
	//想给自己找麻烦，因为学校还有烦人的作业呢！
	int Elements[QUEUE_MAX_SIZE];

	bool (*push)(struct queue*, int);//队尾插入数据(入队)
	int (*pop)(struct queue*);//第一个元素出队且获取该值
	int (*peek)(struct queue*);//仅返回第一个元素的值
	void (*clear)(struct queue*);//清空队列
	void (*ergodic)(struct queue*);//遍历
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

//欸！我这该死的完美主义！
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
