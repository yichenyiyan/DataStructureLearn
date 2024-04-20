#include <ctime>
#include <random>
#include <iostream>
#include <initializer_list>



//数据结构--跳表


struct Node {
	int key;
	Node(int key):key(key){}
	~Node(){}
	Node* next[1];//柔性数组
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

	//禁止拷贝构造
	skipList(const skipList&) = delete;
	skipList& operator=(const skipList&) = delete;
	skipList& operator=(skipList&&) = delete;

private:
	Node* newNode(const int& key, int level)
	{
		/*
		* 开辟sizeof(Node) + sizeof(Node*) * (level - 1)大小的空间
		* sizeof(Node*) * (level - 1)大小的空间是给Node.next[1]指针数组用的
		* 为什么是level-1而不是level，因为sizeof(Node)已包含一个Node*指针的空间
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
		// 从最高层开始查找，每层查找最后一个小于key的前继节点，不断缩小范围
		Node* pNode = head;
		for (int i = maxLevel - 1; i >= 0; --i)
		{
			while (pNode->next[i] != nullptr && pNode->next[i]->key < key)
			{
				pNode = pNode->next[i];
			}
		}

		// 如果第一层的pNode[0]->key == key，则返回pNode->next[0]，即找到key
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
		//从最高层开始查找，找到每一层最后一个小于key的前驱节点
		for (int i = level - 1; i >= 0; --i) {
			while (pNode->next[i] != nullptr && pNode->next[i]->key < key) {
				pNode = pNode->next[i];
			}
			prev[i] = pNode;
		}
		//每层将新节点插入的前驱节点后
		for (int i = 0; i < level; ++i) {
			new_node->next[i] = prev[i]->next[i];
			prev[i]->next[i] = new_node;
		}
		//更新最大层数
		if (maxLevel < level)
			maxLevel = level;
	}


	void erase(const int& key)
	{
		Node* prev[maxLevel];
		Node* pNode = head;
		//从最高层开始查找，每层查找最后一个小于key的前驱节点
		for (int i = maxLevel - 1; i >= 0; --i) {
			while (pNode->next[i] != nullptr && pNode->next[i]->key < key)
				pNode = pNode->next[i];
			prev[i] = pNode;
		}

		//判断是否找到key
		if (pNode->next[0] != nullptr && pNode->next[0]->key == key) {
			Node* delNode = pNode->next[0];
			//从最高层开始， 如果当前层的next节点的值等于key,则删除next节点
			for (int i = maxLevel - 1; i >= 0; --i) {
				if (prev[i]->next[i] != nullptr && key == prev[i]->next[i]->key)
					prev[i]->next[i] = prev[i]->next[i]->next[i];
			}
			free(delNode);//删除后释放空间
		}

		//maxLevel大于1且头结点的next指针为空，则说明该层已无数据
		//则进行层数减一
		while (maxLevel > 1 && head->next[maxLevel] == nullptr)
			--maxLevel;
	}
};

int main() { return 0; }
