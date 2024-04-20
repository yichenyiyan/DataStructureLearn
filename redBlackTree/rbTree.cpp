/******************************
*  Github:yichenyiyan  QAQ    *
* 编程学习应该是简单且有趣的  *
*******************************/



#include <cstdio>
#include<iostream>


//红黑树
//version-1 只实现插入的版本！（待更新）


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
};


Node::Node(int value)
    :value(value), parent(nullptr)
    ,left(nullptr), right(nullptr)
{

}



Node::~Node()
{

}

Node* 
Node::uncle()
{
    if (grandparent() == nullptr)
        return nullptr;

    if (parent == grandparent()->left)
        return grandparent()->right;
    else
        return grandparent()->left;
}


Node* 
Node::grandparent()
{
    if (parent == nullptr)
        return nullptr;

    return parent->parent;
}



class rbTree {
private:
    Node* NIL;
    Node* root;
public:
    rbTree();
    ~rbTree();
    void insert(int);
    void insert(Node*, int);
    void insert_case(Node*);
    void rotate_left(Node*);//左旋
    void rotate_right(Node*);//右旋
};


rbTree::rbTree()
    :root(nullptr), NIL(new Node(0))
{
    NIL->color = Color::BLACK;
}


rbTree::~rbTree()
{

}

void 
rbTree::insert(int val)
{
    if (root == nullptr) {
        root = new Node(val);
        root->parent = nullptr;
        root->left = NIL;
    }
    else {
        insert(root, val);
    }

}

void
rbTree::insert(Node* node, int val)
{
    if (node->value >= val) {
        if (node->left != NIL)
            insert(node->left, val);
        else {
            Node* tmp = new Node(val);
            tmp->left = tmp->right = NIL;
            tmp->parent = node;
            node->left = tmp;
            insert_case(tmp);
        }
    }
    else {
        if (node->right != NIL)
            insert(node->right, val);
        else {
            Node* tmp = new Node(val);
            tmp->left = tmp->right = NIL;
            tmp->parent = node;
            node->left = tmp;
            insert_case(tmp);
        }
    }

}


void 
rbTree::rotate_left(Node* node)
{
    if (node->parent == nullptr) {
        root = node;
        return;
    }

    Node* fa = node->parent;
    Node* _left = node->left;
    Node* gp = node->grandparent();

    fa->right = _left;

    if (_left == NIL)
        _left->parent = fa;
    node->left = fa;
    fa->parent = node;

    if (root == fa)
        root = node;
    node->parent = gp;
    if (gp != nullptr) {
        if (gp->left == fa)
            gp->left = node;
        else
            gp->right = node;
    }
}


void 
rbTree::rotate_right(Node* node)
{
    Node* fa = node->parent;
    Node* _right = node->right;
    Node* gp = node->grandparent();

    fa->left = _right;
    if (_right != NIL)
        _right->parent = fa;
    node->right = fa;
    fa->parent = node;

    if (root == fa)
        root = node;
    node->parent = gp;
    if (gp != nullptr) {
        if (gp->left == fa)
            gp->left = node;
        else
            gp->right = node;
    }
}


void 
rbTree::insert_case(Node* node)
{
    if (node->parent == nullptr) {
        root = node;
        node->color = Color::BLACK;
        return;
    }

    if (node->parent->color == Color::RED) {
        if (node->uncle()->color == Color::RED) {
            node->parent->color = Color::BLACK;
            node->uncle()->color = Color::BLACK;   
            node->grandparent()->color = Color::RED;
            insert_case(node->grandparent());
        }
        else {
            //节点为父节点的右节点，父节点为爷节点的左节点
            if (node->parent->right == node &&
                node->grandparent()->left == node->parent) {
                rotate_left(node);
                node->color = Color::BLACK;
                node->parent->color = Color::RED;
                rotate_right(node);
            }
            //节点为父节点的左节点，父节点为爷节点的右节点
            else if (node->parent->left == node &&
                node->grandparent()->right == node->parent) {
                rotate_right(node);
                node->color = Color::BLACK;
                node->parent->color = Color::RED;
                rotate_left(node);
            }
            //节点为父节点的左节点，父节点为爷节点的左节点
            else if (node->parent->left == node && 
                node->grandparent()->left == node->parent) {
                node->parent->color = Color::BLACK;
                node->grandparent()->color = Color::RED;
                rotate_right(node->parent);
            }
            //节点为父节点的右节点，父节点为爷节点的右节点
            else if (node->parent->right == node 
                && node->grandparent()->right == node->parent) {
                node->parent->color = Color::BLACK;
                node->grandparent()->color = Color::RED;
                rotate_left(node->parent);
            }
        }

    }

}



int main()
{
    
    return 0;
}