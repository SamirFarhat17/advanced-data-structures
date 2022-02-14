#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct Node Data_Node;
struct Node {};
struct Tree_node {
    int key;
    Tree_node* lchild;
    Tree_node* rchild;
    Data_Node* data;
};

class SplayTree {
  public:

    SplayTree() {}

    Tree_node* Right_Rotate(Tree_node* k2) {
        Tree_node* k1 = k2->lchild;
        k2->lchild = k1->rchild;
        k1->rchild = k2;
        return k1;
    }

    Tree_node* Left_Rotate(Tree_node* k2) {
        Tree_node* k1 = k2->rchild;
        k2->rchild = k1->lchild;
        k1->lchild = k2;
        return k1;

    }
    
    Tree_node* Splay(int key, Tree_node* root) {
        // if root is null, return null;
        if (!root) return NULL;
        // Create a Tree_node Tree to grow the right, left subtrees as we go down
        Tree_node Tree;
        // Initialize right and left children of Tree as null
        Tree.lchild = NULL;
        Tree.rchild = NULL;
        // Initialize the pointers Rpoint, Lpoint as to where to insert left and right subtrees
        Tree_node* Lpoint = &Tree;
        Tree_node* Rpoint = &Tree;
        // Do until break:
        while(true) {
            if(key < root->key) {
                if(!(root->lchild)) break;
                // if key < left_child’s key
                if(key < (root->lchild->key)) {
                    root = Right_Rotate(root);
                    if(!root->lchild) break;
                }
                // Split current root and all of its right descendants into right subtree
                Rpoint->lchild = root;
                Rpoint = Rpoint->lchild;
                root = root->lchild;
                Rpoint->lchild = NULL;
            } else if(key > (root->key)) {
                if(!root->rchild) break;
                // if the new root has no left child, break out of Do
                if(key > (root->rchild->key)) {
                    root = Left_Rotate(root);
                    if(!root->rchild) break;
                }
                // Split current root and all its left descendants to left subtree
                Lpoint->rchild = root;
                Lpoint = Lpoint->rchild;
                root = root->rchild;
                Lpoint->rchild = NULL;
            } 
            else break;
        }
        // Assemble the final splay tree by merging center, left and right,
        Lpoint->rchild = root->lchild;
        Rpoint->lchild = root->rchild;
        root->lchild = Tree.rchild;
        root->rchild = Tree.lchild;

        return root;
    }

    Tree_node* New_Node(int key) {
        Tree_node*  my_node = new Tree_node;
        if (!my_node) {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        my_node->key = key;
        my_node->lchild = my_node->rchild = NULL;
        return my_node;
    }

    Tree_node* Insert(int key, Tree_node* root) {
        Tree_node* my_node = NULL;

        my_node = New_Node(key);
        if (!root) {
            root = my_node;
            return root;
        }
        root = Splay(key, root);
        if (key < root->key) {
            my_node->lchild = root->lchild;
            my_node->rchild = root;
            root->lchild = NULL;
            root = my_node;
        } else if (key > root->key) {
            my_node->rchild = root->rchild;
            my_node->lchild = root;
            root->rchild = NULL;
            root = my_node;
        } else { 
            delete my_node;
            return root;
        }
        return root;
    }

    Tree_node* Delete(int key, Tree_node* root) {
        Tree_node* temp;
        if (!root)
            return NULL;
        root = Splay(key, root);
        if (key != root->key)
            return root;
        else {
            if (!root->lchild) {
                temp = root;
                root = root->rchild;
            } else {
                temp = root;
                root = Splay(key, root->lchild);
                root->rchild = temp->rchild;
            }
            delete temp;
            return root;
        }

    }

    Tree_node* Search(int key, Tree_node* root) {
        return Splay(key, root);
    }

    void InOrder(Tree_node* root) {
        if (root) {
            InOrder(root->lchild);
            cout << "key: " << root->key;
            if(root->lchild)
                cout << " | left child: " << root->lchild->key;
            if(root->rchild)
                cout << " | right child: " << root->rchild->key;

            cout << endl;
            InOrder(root->rchild);
        }
    }
};

int main() {
    SplayTree st;
    int vector[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    Tree_node *root;
    root = NULL;
    const int length = 10;
    int i;

    for(i = 0; i < length; i++)
        root = st.Insert(vector[i], root);

    cout << "\nInOrder: \n";

    st.InOrder(root);
    int input;
    input = 6;
    root = st.Search(input, root);
    cout << "\nAfter Search " << input << endl;
    st.InOrder(root);

    input = 3;
    root = st.Search(input, root);
    cout << "\nAfter Search " << input << endl;
    st.InOrder(root);

    input = 8;
    root = st.Delete(input, root);
    cout << "\nAfter Delete " << input << endl;
    st.InOrder(root);
    cout << "\n";
    return 0;
}
