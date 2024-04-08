/******************************
*  ���ߣ��õ�����ŵ���(CSDN) *
*  Github:��С���С�Ե�      *
*       yichenyan  QAQ        *
* ���ѧϰӦ���Ǽ�����Ȥ��  *
*******************************/



#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//���ݽṹ��������v1.0(���Ż��汾��
// ������������Node�кܶ���Ϣ��δʹ��)


struct Node {
	char myData;
	int inDeep;   //�������
	struct Node* left;
	struct Node* right;
	struct Node* father;
};

typedef struct Node Node;

//���ڵ�����Ϊ0�����ӽڵ�����Ϊ1

struct binTree {
	Node* root;   //���ڵ�
	int treeHigh; //���ĸ߶�
};

typedef struct binTree binTree;


void binTreeInit(binTree* tree, char data)
{
	tree->root = (Node*)malloc(sizeof(Node));
	tree->root->myData = data;
	tree->root->father = NULL;
	tree->root->inDeep = 0;
	tree->root->left = NULL;
	tree->root->right = NULL;
	tree->treeHigh = 0;
}


//��ĳ������������
bool addOnNodeLeft(Node* srcNode, char data)
{
	if (srcNode == NULL)
		return false;

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	newNode->myData = data;
	newNode->father = srcNode;
	newNode->inDeep = srcNode->inDeep + 1;
	newNode->left = NULL;
	newNode->right = NULL;

	srcNode->left = newNode;
	return true;
}


//��ĳ���������ҽ��
bool addOnNodeRight(Node* srcNode, char data)
{
	if (srcNode == NULL)
		return false;

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	newNode->myData = data;
	newNode->father = srcNode;
	newNode->inDeep = srcNode->inDeep + 1;
	newNode->left = NULL;
	newNode->right = NULL;

	srcNode->right = newNode;
	return true;
}


//�������
void preoderErgodicTree(Node* now)
{
	if (now == NULL)
		return;

	printf("%c -> ", now->myData);
	preoderErgodicTree(now->left);
	preoderErgodicTree(now->right);
}


//�������
void mediateErgodicTree(Node* now)
{
	if (now == NULL)
		return;

	mediateErgodicTree(now->left);
	printf("%c -> ", now->myData);
	mediateErgodicTree(now->right);
}


//�������
void postErgodicTree(Node* now)
{
	if (now == NULL)
		return;

	mediateErgodicTree(now->left);
	mediateErgodicTree(now->right);
	printf("%c -> ", now->myData);
}


void freeTree(Node* TreeRoot)
{
	if (TreeRoot == NULL)
		return;

	Node* tmp = TreeRoot;
	free(TreeRoot);
	freeTree(TreeRoot->left);
	freeTree(TreeRoot->right);
}


void testFunc1()
{
	binTree* tree = (binTree*)malloc(sizeof(binTree));
	binTreeInit(tree, 'A');
	addOnNodeLeft(tree->root, 'B');
	addOnNodeRight(tree->root, 'C');
	addOnNodeLeft(tree->root->left, 'D');
	addOnNodeRight(tree->root->left, 'E');
	addOnNodeLeft(tree->root->right, 'F');
	addOnNodeRight(tree->root->right, 'G');
	addOnNodeLeft(tree->root->left->left, 'H');
	addOnNodeLeft(tree->root->right->left, 'I');
	addOnNodeRight(tree->root->right->right, 'J');
	addOnNodeRight(tree->root->left->left->left, 'K');
	printf("���������\n");
	preoderErgodicTree(tree->root);
	printf("\n+---------------------------------------------+\n");
	printf("���������\n");
	mediateErgodicTree(tree->root);
	printf("\n+---------------------------------------------+\n");
	printf("���������\n");
	postErgodicTree(tree->root);
	printf("\n+---------------------------------------------+\n");
	freeTree(tree->root);
	free(tree);
}


int main()
{
	testFunc1();

	return 0;
}

