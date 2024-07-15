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
    Node* sibling();
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

Node* 
Node::sibling() {
    if (parent->left == this)
        return parent->right;
    else
        return parent->left;
}



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
        DeleteTree(p->leftTree);
        DeleteTree(p->rightTree);
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

//左旋
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

//右旋
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



bool 
rbTree::delete_child(Node* p, int data) {
    if (p->value > data) {
        if (p->left == NIL)
            return false;

        return delete_child(p->left, data);
    }
    else if (p->value < data) {
        if (p->right == NIL)
            return false;

        return delete_child(p->right, data);
    }
    else if (p->value == data) {
        if (p->right == NIL) {
            delete_one_child(p);
            return true;
        }

        Node* smallest = getSmallestChild(p->right);
        _swap(p->value, smallest->value);
        delete_one_child(smallest);

        return true;
    }
    else
        return false;
}


void 
rbTree::delete_one_child(Node* p) {
    Node* child = p->left == NIL ? p->right : p->left;
    if (p->parent == NULL && p->left == NIL && p->right == NIL) {
        p = NULL;
        root = p;
        return;
    }

    if (p->parent == NULL) {
        delete p;
        child->parent = NULL;
        root = child;
        root->color = Color::BLACK;
        return;
    }

    if (p->parent->left == p)
        p->parent->left = child;
    else
        p->parent->right = child;

    child->parent = p->parent;

    if (p->color == Color::BLACK) {
        if (child->color == Color::RED)
            child->color = Color::BLACK;
        else
            delete_case(child);
    }

    delete p;
}



void 
rbTree::delete_case(Node* p) {
    if (p->parent == NULL) {
        p->color = Color::BLACK;
        return;
    }

    if (p->sibling()->color == Color::RED) {
        p->parent->color = Color::RED;
        p->sibling()->color = Color::BLACK;
        if (p == p->parent->left)
            rotate_left(p->parent);
        else
            rotate_right(p->parent);
    }

    if (p->parent->color == Color::BLACK && p->sibling()->color == Color::BLACK &&
            p->sibling()->left->color == Color::BLACK && p->sibling()->right->color == Color::BLACK) {
        p->sibling()->color = Color::RED;
        delete_case(p->parent);
    }
    else if (p->parent->color == Color::RED && p->sibling()->color == Color::BLACK &&
            p->sibling()->left->color == Color::BLACK && p->sibling()->right->color == Color::BLACK) {
        p->sibling()->color = Color::RED;
        p->parent->color = Color::BLACK;
    }
    else {
        if (p->sibling()->color == Color::BLACK) {
            if (p == p->parent->left && p->sibling()->left->color == Color::RED &&
                    p->sibling()->right->color == Color::BLACK) {
                p->sibling()->color = Color::RED;
                p->sibling()->left->color = Color::BLACK;
                rotate_right(p->sibling()->left);
            }
            else if (p == p->parent->right && p->sibling()->left->color == Color::BLACK &&
                    p->sibling()->right->color == Color::RED) {
                p->sibling()->color = Color::RED;
                p->sibling()->right->color = Color::BLACK;
                rotate_left(p->sibling()->right);
            }
        }
        p->sibling()->color = p->parent->color;
        p->parent->color = Color::BLACK;
        if (p == p->parent->left) {
            p->sibling()->right->color = Color::BLACK;
            rotate_left(p->sibling());
        }
        else {
            p->sibling()->left->color = Color::BLACK;
            rotate_right(p->sibling());
        }
    }

}




int main()
{
    
    return 0;
}