/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*       yichenyan  QAQ        *
* 编程学习应该是简单且有趣的  *
*******************************/



#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//数据结构：二叉树v1.0(待优化版本，
// 创建二叉树和Node中很多信息都未使用)


struct Node {
	char myData;
	int inDeep;   //所处深度
	struct Node* left;
	struct Node* right;
	struct Node* father;
};

typedef struct Node Node;

//根节点的深度为0，其子节点的深度为1

struct binTree {
	Node* root;   //根节点
	int treeHigh; //树的高度
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


//给某个结点添加左结点
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


//给某个结点添加右结点
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


//先序遍历
void preoderErgodicTree(Node* now)
{
	if (now == NULL)
		return;

	printf("%c -> ", now->myData);
	preoderErgodicTree(now->left);
	preoderErgodicTree(now->right);
}


//中序遍历
void mediateErgodicTree(Node* now)
{
	if (now == NULL)
		return;

	mediateErgodicTree(now->left);
	printf("%c -> ", now->myData);
	mediateErgodicTree(now->right);
}


//后序遍历
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
	printf("先序遍历：\n");
	preoderErgodicTree(tree->root);
	printf("\n+---------------------------------------------+\n");
	printf("中序遍历：\n");
	mediateErgodicTree(tree->root);
	printf("\n+---------------------------------------------+\n");
	printf("后序遍历：\n");
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

