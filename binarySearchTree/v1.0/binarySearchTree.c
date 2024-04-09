/******************************
*  ���ߣ��õ�����ŵ���(CSDN) *
*  Github:��С���С�Ե�      *
*       yichenyan  QAQ        *
* ���ѧϰӦ���Ǽ�����Ȥ��  *
*******************************/



#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


//������ʵ��һ�¶���������������
//���ֶ�������ȱ�����̫�������ڵ��ѡȡ��
//���ᶯ̬�仯�����ڼ��ߣ�
//���Դ����ǻ����䷢���˸��߼������ݽṹ�����洦�ɼ��ĺ������


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

	//���ڵ��ڷ����ұ߰�
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

//�������   �������ĸ��ڵ�
void prefaceErgodic(Node* node)
{
	if (node == NULL)
		return;

	printf("%c[%d] -> ", node->id, node->idata);
	prefaceErgodic(node->left);
	prefaceErgodic(node->right);

	return;
}


//�������������ģ�Ϊ�˸��Ͻ�һ��
//�������������ֱ�����������֤����Ƿ���ѭ�����������Ĺ���
//�������
void midErgodic(Node* node)
{
	if (node == NULL)
		return;
	
	prefaceErgodic(node->left);
	printf("%c[%d] -> ", node->id, node->idata);
	prefaceErgodic(node->right);

	return;
}

//�ͷŶ����ռ�
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