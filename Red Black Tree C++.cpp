#include <iostream>

using namespace std;
struct Node
{
    int data;
    int color;
    Node* parent;
    Node* left;
    Node* right;
};


class RedBlackTree {
    Node* root;
    Node* Tnull;
public:
    RedBlackTree()
    {
        Tnull = new Node;
        Tnull->color = 0;
        Tnull->data = 0;
        Tnull->left = nullptr;
        Tnull->right = nullptr;
        root = Tnull;
    }
    void leftRotate(Node* curr)
    {
        Node* temp = curr->right;
        curr->right = temp->left;
        if (temp->left != Tnull)
        {
            temp->left->parent = curr;
        }
        temp->parent = curr->parent;
        if (curr->parent == nullptr)
        {
            this->root = temp;
        }
        else if (curr == curr->parent->left)
        {
            curr->parent->left = temp;
        }
        else if (curr == curr->parent->right)
        {
            curr->parent->right = temp;
        }
        curr->parent = temp;
        temp->left = curr;
    }
    void rightRotate(Node* curr)
    {
        Node* temp = curr->left;
        curr->left = temp->right;
        if (temp->right != Tnull)
        {
            temp->right->parent = curr;
        }
        temp->parent = curr->parent;
        if (curr->parent == nullptr)
        {
            this->root = temp;
        }
        else if (curr == curr->parent->right)
        {
            curr->parent->right = temp;
        }
        else if (curr == curr->parent->left)
        {
            curr->parent->left = temp;
        }
        curr->parent = temp;
        temp->right = curr;
    }

    void insertBalance(Node* curr)
    {
        Node* uncle;
        while (curr->parent->color == 1)
        {
            if (curr->parent == curr->parent->parent->right)
            {
                uncle = curr->parent->parent->left;
                if (uncle->color == 1)
                {
                    uncle->color = 0;
                    curr->parent->color = 0;
                    curr->parent->parent->color = 1;
                    curr = curr->parent->parent;
                }
                else
                {
                    if (curr == curr->parent->left)
                    {
                        curr = curr->parent;
                        rightRotate(curr);
                    }
                    curr->parent->color = 0;
                    curr->parent->parent->color = 1;
                    leftRotate(curr->parent->parent);
                }
            }
            else
            {
                uncle = curr->parent->parent->right;
                if (uncle->color == 1)
                {
                    uncle->color = 0;
                    curr->parent->color = 0;
                    curr->parent->parent->color = 1;
                    curr = curr->parent->parent;
                }
                else
                {
                    if (curr == curr->parent->right)
                    {
                        curr = curr->parent;
                        leftRotate(curr);
                    }
                    curr->parent->color = 0;
                    curr->parent->parent->color = 1;
                    rightRotate(curr->parent->parent);
                }
            }
            if (curr == root)
                break;
        }
        root->color = 0;
    }
    void insert(int value)
    {
        Node* newNode = new Node;
        newNode->parent = nullptr;
        newNode->data = value;
        newNode->color = 1;
        newNode->left = Tnull;
        newNode->right = Tnull;

        Node* curr = root;
        Node* temp = nullptr;
        while (curr != Tnull)
        {
            temp = curr;
            if (newNode->data > curr->data)
                curr = curr->right;
            else
                curr = curr->left;

        }
        newNode->parent = temp;
        if (temp == nullptr)
            root = newNode;
        else if (temp->data > newNode->data)
            temp->left = newNode;
        else
            temp->right = newNode;
        if (newNode->parent == nullptr) {
            newNode->color = 0;
            return;
        }
        if (newNode->parent->parent == nullptr)
        {
            return;
        }
        insertBalance(newNode);
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node* min(Node* node) {
        while (node->left != Tnull)
        {
            node = node->left;
        }
        return node;
    }

    Node* max(Node* node) {
        while (node->right != Tnull)
        {
            node = node->right;
        }
        return node;
    }
    void deleteBalance(Node* curr) {
        Node* sibling;
        while (curr != root && curr->color == 0) {
            if (curr == curr->parent->left) {
                sibling = curr->parent->right;
                if (sibling->color == 1) {
                    sibling->color = 0;
                    curr->parent->color = 1;
                    leftRotate(curr->parent);
                    sibling = curr->parent->right;
                }
                if (sibling->left->color == 0 && sibling->right->color == 0) {
                    sibling->color = 1;
                    curr = curr->parent;
                }
                else if (sibling->right->color == 0) {
                    sibling->left->color = 0;
                    sibling->color = 1;
                    rightRotate(sibling);
                    sibling = curr->parent->right;
                }
                else {
                    sibling->color = curr->parent->color;
                    curr->parent->color = 0;
                    sibling->right = 0;
                    leftRotate(curr);
                    curr = root;
                }
            }
            else {
                sibling = curr->parent->left;
                if (sibling->color == 1) {
                    sibling->color = 0;
                    curr->parent->color = 1;
                    rightRotate(curr->parent);
                    sibling = curr->parent->left;
                }
                if (sibling->left->color == 0 && sibling->right->color == 0) {
                    sibling->color = 1;
                    curr = curr->parent;
                }
                else if (sibling->left->color == 0) {
                    sibling->right->color = 0;
                    sibling->color = 1;
                    leftRotate(sibling);
                    sibling = curr->parent->left;
                }
                else {
                    sibling->color = curr->parent->color;
                    curr->parent->color = 0;
                    sibling->left = 0;
                    rightRotate(curr);
                    curr = root;
                }
            }
        }
        curr->color = 0;
    }

    void help_delete(Node* node, int key) {
        Node* x;
        Node* y;
        Node* z = Tnull;
        while (node != Tnull) {
            if (node->data == key) {
                z = node;
            }
            if (node->data <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }
        if (z == Tnull) {
            cout << "Key not found in the tree" << endl;
            return;
        }
        y = z;
        int y_original_color = y->color;
        if (z->left == Tnull) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == Tnull) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = min(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
            }
        delete z;
        if (y_original_color == 0) {
            deleteBalance(x);
        }
    }

    void deleteNode(int data) {
        help_delete(this->root, data);
    }

    Node* Search(Node* Root, int key)
    {
        Node* curr = Root;
        if (curr == Tnull || curr->data == key)
            return curr;
        if (curr->data < key)
            return Search(curr->right, key);
        else
            return Search(curr->left, key);
    }
    void print(Node* Root, string Spaces, bool left)
    {
        if (Root != Tnull)
        {
            cout << Spaces;
            if (left)
                cout << "Left---";
            else {
                if (Root == root)
                    cout << "Root---";
                else
                    cout << "Right---";
            }
            Spaces += "    ";
            cout << Root->data;
            if (Root->color == 1)
                cout << "(Red)" << endl;
            else
                cout << "(Black)" << endl;
            print(Root->left, Spaces, true);
            print(Root->right, Spaces, false);

        }
    }
    Node* getRoot()
    {
        return root;
    }

    void printList()
    {
        print(root, "", false);
    }

    void printFound(Node* node)
    {
        if (node == Tnull)
            cout << "Data Not Found" << endl;
        else {
            cout << "Data Found : ";
            if (node->color == 1)
                cout << "Red -- ";
            else
                cout << "Black -- ";
            cout << node->data << endl;
        }
    }

    void clear ()
    {
        root=Tnull;
    }

};



int main()
{
    RedBlackTree bst;
    bst.insert(10);
    bst.insert(18);
    bst.insert(7);
    bst.insert(15);
    bst.insert(16);
    bst.insert(30);
    bst.insert(25);

    bst.printList();
    bst.printFound(bst.Search(bst.getRoot(), 18));
    bst.printFound(bst.Search(bst.getRoot(), 2));

    cout << "After deletion \n";
    bst.deleteNode(7);
    return 0;
}
