#include <ctime>
#include <random>
#include <iostream>
#include <initializer_list>



//���ݽṹ--����


struct Node {
	int key;
	Node(int key):key(key){}
	~Node(){}
	Node* next[1];//��������
};

class skipList {
private:
	Node* head;
	int maxLevel;
	enum{
		kMaxLevel = 12
	};
public:

	skipList() :maxLevel(1)
	{
		head = newNode(0, kMaxLevel);
	}
	skipList(std::initializer_list<int> init) :skipList()
	{
		for (const int& key : init) {
			insert(key);
		}
	}

	~skipList() 
	{
		Node* pNode = head;
		Node* delNode;
		while (pNode != nullptr) {
			delNode = pNode;
			pNode = pNode->next[0];
			free(delNode);
		}
	}

	//��ֹ��������
	skipList(const skipList&) = delete;
	skipList& operator=(const skipList&) = delete;
	skipList& operator=(skipList&&) = delete;

private:
	Node* newNode(const int& key, int level)
	{
		/*
		* ����sizeof(Node) + sizeof(Node*) * (level - 1)��С�Ŀռ�
		* sizeof(Node*) * (level - 1)��С�Ŀռ��Ǹ�Node.next[1]ָ�������õ�
		* Ϊʲô��level-1������level����Ϊsizeof(Node)�Ѱ���һ��Node*ָ��Ŀռ�
		*/
		void* node_memory = malloc(sizeof(Node) + sizeof(Node*) * (level - 1));
		Node* node = new(node_memory) Node(key);
		for (int i = 0; i < level; ++i)
			node->next[i] = nullptr;

		return node;
	}

	static int randomLevel()
	{
		int level = 1;
		while (rand() % 2 && level < kMaxLevel)
			++level;

		return level;
	}
public: 
	Node* find(const int& key)
	{
		// ����߲㿪ʼ���ң�ÿ��������һ��С��key��ǰ�̽ڵ㣬������С��Χ
		Node* pNode = head;
		for (int i = maxLevel - 1; i >= 0; --i)
		{
			while (pNode->next[i] != nullptr && pNode->next[i]->key < key)
			{
				pNode = pNode->next[i];
			}
		}

		// �����һ���pNode[0]->key == key���򷵻�pNode->next[0]�����ҵ�key
		if (nullptr != pNode->next[0] && pNode->next[0]->key == key)
			return pNode->next[0];

		return nullptr;
	}

	void insert(const int& key)
	{
		int level = randomLevel();
		Node* new_node = newNode(key, level);
		Node* prev[kMaxLevel];
		Node* pNode = head;
		//����߲㿪ʼ���ң��ҵ�ÿһ�����һ��С��key��ǰ���ڵ�
		for (int i = level - 1; i >= 0; --i) {
			while (pNode->next[i] != nullptr && pNode->next[i]->key < key) {
				pNode = pNode->next[i];
			}
			prev[i] = pNode;
		}
		//ÿ�㽫�½ڵ�����ǰ���ڵ��
		for (int i = 0; i < level; ++i) {
			new_node->next[i] = prev[i]->next[i];
			prev[i]->next[i] = new_node;
		}
		//����������
		if (maxLevel < level)
			maxLevel = level;
	}


	void erase(const int& key)
	{
		Node* prev[maxLevel];
		Node* pNode = head;
		//����߲㿪ʼ���ң�ÿ��������һ��С��key��ǰ���ڵ�
		for (int i = maxLevel - 1; i >= 0; --i) {
			while (pNode->next[i] != nullptr && pNode->next[i]->key < key)
				pNode = pNode->next[i];
			prev[i] = pNode;
		}

		//�ж��Ƿ��ҵ�key
		if (pNode->next[0] != nullptr && pNode->next[0]->key == key) {
			Node* delNode = pNode->next[0];
			//����߲㿪ʼ�� �����ǰ���next�ڵ��ֵ����key,��ɾ��next�ڵ�
			for (int i = maxLevel - 1; i >= 0; --i) {
				if (prev[i]->next[i] != nullptr && key == prev[i]->next[i]->key)
					prev[i]->next[i] = prev[i]->next[i]->next[i];
			}
			free(delNode);//ɾ�����ͷſռ�
		}

		//maxLevel����1��ͷ����nextָ��Ϊ�գ���˵���ò���������
		//����в�����һ
		while (maxLevel > 1 && head->next[maxLevel] == nullptr)
			--maxLevel;
	}
};

int main() { return 0; }
