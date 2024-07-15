#ifndef MY_RBTREE_H_
#define MY_RBTREE_H_

#include <cstdio>
#include<iostream>


//红黑树(较为完整)

using namespace std;

enum class Color:bool {
    RED = true,
    BLACK = false
};


struct Node {
    int value;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
    Node(int);
    ~Node();
    Node* uncle();
    Node* grandparent();
    Node* sibling();
};


class rbTree {
private:
    Node* NIL;
    Node* root;
    inline void _swap(int& val1, int& val2) {
        int tmp = val1;
        val1 = val2;
        val2 = tmp;
    }
public:
    rbTree();
    ~rbTree();
    void insert(int);
    void insert(Node*, int);
    void insert_case(Node*);
    void rotate_left(Node*);//左旋
    void rotate_right(Node*);//右旋
    bool delete_child(Node*, int);
    void delete_one_child(Node*);
    void delete_case(Node*);

    inline bool delete_value(int data) {
        return delete_child(root, data);
    }

    inline void DeleteTree(Node* p) {
        if (!p || p == NIL) {
            return;
        }
        DeleteTree(p->left);
        DeleteTree(p->right);
        delete p;
    }

    inline void inorder(Node* p) {
        if (p == NIL)
            return;

        if (p->left)
            inorder(p->left);

        cout << p->value << " ";

        if (p->right)
            inorder(p->right);
    }

    inline void inorder() {
        if (root == NULL)
            return;
        inorder(root);
        cout << endl;
    }


    inline string outputColor(bool color) {
        return color ? "BLACK" : "RED";
    }

    inline Node* getSmallestChild(Node* p) {
        if (p->left == NIL)
            return p;
        return getSmallestChild(p->left);
    }
};


#endif