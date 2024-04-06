/******************************
*  ���ߣ��õ�����ŵ���(CSDN) *
*  Github:��С���С�Ե�      *
*          yichenyan          *
* ���ѧϰӦ���Ǽ�����Ȥ��  *
*******************************/



#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>

//my stack write by the C programming language 



#define STACK_MAX_SIZE 1024



struct myStack {
	int size; //��ǰԪ�ظ���
	int maxCap; //ջ�������
	int* topEle; //ָ��ջ��
	int isEmpty; //ջ�Ƿ�Ϊ�գ���0��Ϊ�գ�
	int isFull;  //ջ�Ƿ���������0��������
	int Elems[STACK_MAX_SIZE]; //ʵ�ʴ洢�����ݽṹ(�����������)


	int (*push)(struct myStack*, int); //��ջ
	int (*pop)(struct myStack*);   //��ջ������ջ��ֵ
	int (*peek)(struct myStack*);  //����ջ��ֵ
	void (*clear)(struct myStack*); //���ջ������Ԫ��
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















