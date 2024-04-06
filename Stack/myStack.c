/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*          yichenyan          *
* 编程学习应该是简单且有趣的  *
*******************************/



#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>

//my stack write by the C programming language 



#define STACK_MAX_SIZE 1024



struct myStack {
	int size; //当前元素个数
	int maxCap; //栈最大容量
	int* topEle; //指向栈顶
	int isEmpty; //栈是否为空（非0则为空）
	int isFull;  //栈是否已满（非0则已满）
	int Elems[STACK_MAX_SIZE]; //实际存储的数据结构(这里采用数组)


	int (*push)(struct myStack*, int); //入栈
	int (*pop)(struct myStack*);   //出栈并返回栈顶值
	int (*peek)(struct myStack*);  //返回栈顶值
	void (*clear)(struct myStack*); //清空栈中所以元素
	void (*ergodic)(struct myStack*);
};

typedef struct myStack myStack;





int push(myStack* stack, int elem)
{
	if (stack->isFull) {
		printf("the stack is full!\n");
		return -1;
	}
	

	stack->Elems[stack->size] = elem;
	//stack->topEle = stack->Elems[stack->size];
	stack->topEle = stack->Elems+stack->size;
	stack->size++;
	if (stack->size == stack->maxCap) {
		stack->isFull = 1;
	}
	if (stack->isEmpty && stack->size) {
		stack->isEmpty = 0;
	}

	return 0;
}


int pop(myStack* stack)
{
	if (stack->isEmpty || stack->topEle == NULL) {
		printf("fail to pop,because it is Empty or top is NULL!\n");
		return -9999;
	}

	int ret = stack->Elems[stack->size - 1];//int ret = *(stack->topEle);
	/*if (flag)
		free(stack->Elems[stack->size - 1]);*/
	stack->Elems[stack->size - 1] = 0;//*(stack->topEle) = 0;
	stack->size--;
	if (stack->size == 0) {
		stack->isEmpty = 1;
		stack->topEle = NULL;
		return ret;
	}
	if (stack->isFull)
		stack->isFull = 0;
	//stack->topEle = stack->Elems[stack->size - 1];
	//stack->topEle = stack->Elems+(stack->size - 1);
	stack->topEle--;

	return ret;
}


int peek(myStack* stack)
{
	return *(stack->topEle);
}



void ergodeic(myStack* stack)
{
	if (stack->isEmpty) {
		printf("this stack is empty!\n");
		return;
	}
	int i = stack->size;
	printf("top: ");
	while (i > 0) {
		printf("%d\n", stack->Elems[i - 1]);
		printf("|\n");
		--i;
	}

	printf("finish ergosic!\n");
	return;
}

void clear(myStack* stack)
{
	bzero(stack->Elems, STACK_MAX_SIZE);
	stack->size = 0;
	stack->isEmpty = 1;
	stack->isFull = 0;
	stack->topEle = NULL;
}


void stackInit(myStack* stack, int _maxCap)
{
	assert(_maxCap < STACK_MAX_SIZE);
	stack->size = 0;
	stack->isEmpty = 1;
	stack->isFull = 0;
	stack->topEle = NULL;
	stack->maxCap = _maxCap;
	bzero(stack->Elems, STACK_MAX_SIZE);
	stack->push = push;
	stack->pop = pop;
	stack->ergodic = ergodeic;
	stack->peek = peek;
	stack->clear = clear;

}


void testFunc1()
{
	myStack* stack = (myStack*)malloc(sizeof(myStack));
	stackInit(stack, 20);
	for (int i = 0; i < 5; ++i) {
		stack->push(stack, i);
	}
	printf("+------------------------+\n");
	printf("stack size:%d\n", stack->size);
	printf("stack peek return value:%d\n", stack->peek(stack));
	printf("\n");

	printf("stack size:%d\n", stack->size);
	printf("stack pop return value:%d\n", stack->pop(stack));
	printf("\n");

	printf("stack size:%d\n", stack->size);
	stack->ergodic(stack);

	stack->clear(stack);
	printf("stack size:%d\n", stack->size);
	stack->ergodic(stack);


	free(stack);
}






int main()
{
	testFunc1();

	return 0;
}















