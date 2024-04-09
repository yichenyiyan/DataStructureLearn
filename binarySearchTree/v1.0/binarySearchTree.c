/******************************
*  作者：拿得起更放得下(CSDN) *
*  Github:大小姐的小迷弟      *
*       yichenyan  QAQ        *
* 编程学习应该是简单且有趣的  *
*******************************/



#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


//今天来实现一下二叉搜索树！！！
//这种二叉树的缺点就是太依赖根节点的选取了
//不会动态变化，过于鸡肋，
//所以大佬们基于其发明了更高级的数据结构（如随处可见的红黑树）


struct Node {
	char id;
	int idata;
	struct Node* left;
	struct Node* right;
};

typedef struct Node Node;


struct binarySearchTree {
	struct Node* root;
};

typedef struct binarySearchTree binarySearchTree;

#if 1
void rootInit(binarySearchTree* tree, int data, char id)
{
	if (tree == NULL)
		return;
	tree->root = (Node*)malloc(sizeof(Node));
	assert(tree->root != NULL);
	tree->root->idata = data;
	tree->root->left = NULL;
	tree->root->right = NULL;
	tree->root->id = id;
}
#endif

#if 1
void TreeInsertNode(Node* now, Node* newNode)
{
	if (newNode == NULL)
		return;

	//大于等于放在右边吧
	if (newNode->idata < now->idata) {
		if (now->left == NULL) {
			now->left = newNode;
			return;
		}
		TreeInsertNode(now->left, newNode);
	}
	else if(newNode->idata >= now->idata){
		if (now->right == NULL) {
			now->right = newNode;
			return;
		}
		TreeInsertNode(now->right, newNode);
	}

	
		
	return;
}

#endif

//先序遍历   传入树的根节点
void prefaceErgodic(Node* node)
{
	if (node == NULL)
		return;

	printf("%c[%d] -> ", node->id, node->idata);
	prefaceErgodic(node->left);
	prefaceErgodic(node->right);

	return;
}


//由于是乱序插入的，为了更严谨一点
//所以作者用两种遍历方案来验证结果是否遵循二叉搜索树的规律
//中序遍历
void midErgodic(Node* node)
{
	if (node == NULL)
		return;
	
	prefaceErgodic(node->left);
	printf("%c[%d] -> ", node->id, node->idata);
	prefaceErgodic(node->right);

	return;
}

//释放堆区空间
void freeTree(Node* root)
{
	if (root == NULL)
		return;

	Node* tmp = root;
	

	freeTree(root->left);
	freeTree(root->right);
	if (tmp != NULL)
		free(tmp);

	return;
}


void testFunc1()
{
	int data = 50;
	binarySearchTree* tree = (binarySearchTree*)malloc(sizeof(binarySearchTree));
	rootInit(tree, data, 'A');
#if 1
	for (int i = 0; i < 20; ++i) {
		Node* node = (Node*)malloc(sizeof(Node));
		node->id = (char)('A' + i + 1);
		int tmp = rand() % 100;
		node->idata = (tmp >= 0 ? tmp : -tmp);
		node->left = NULL;
		node->right = NULL;
		TreeInsertNode(tree->root, node);
	}
#endif


	prefaceErgodic(tree->root);
	printf("\n");
	midErgodic(tree->root);
	printf("\n");
	freeTree(tree->root);
	//printf("???\n");
	if(tree != NULL)
		free(tree);
}

#if 0
void insertNodeLeft(Node* node, char id, int data)
{
	if (node == NULL)
		return;

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->id = id;
	newNode->idata = data;
	newNode->left = NULL;
	newNode->right = NULL;
	node->left = newNode;
	
}


void insertNodeRight(Node* node, char id, int data)
{
	if (node == NULL)
		return;

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->id = id;
	newNode->idata = data;
	newNode->left = NULL;
	newNode->right = NULL;
	node->right = newNode;

}
#endif




int main()
{
	testFunc1();

	return 0;
}