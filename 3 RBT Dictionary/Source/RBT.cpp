#include "../Headers/RBT.hpp"
#include <string>

RBT::RBT() {
    nil = new node;

    nil -> color = color::black;
    nil -> key = "";
    nil -> parent = nil -> left = nil -> right = nullptr;

    root = nil;
}

RBT::RBT(std::string key) : RBT() {
    insert(key);
}

void RBT::insert(std::string key) {
    node *current = root, *trailingParent = nil;

    //First we traverse the tree to find the first empty node
    while (current != nil) {
        trailingParent = current;
        if (key < current->key) current = current->left;
        else if (key > current->key) current = current->right;
        else return; //if word already exists,, exit
    }

    node *newNode = new node;
    newNode -> key = key;
    newNode -> parent = trailingParent; //note1
    newNode -> left = newNode -> right = nil;
    newNode -> color = color::red;

    //if trailingParent is nil, the loop never ran; the tree is empty, so set new node as root
    if (trailingParent == nil) root = newNode;
    //if trailingParent is nill, the parent of the root would be nil because of note1
    else
        if (key < trailingParent->key) trailingParent -> left = newNode;
        else if (key > trailingParent->key) trailingParent -> right = newNode;

    insertFixup(newNode);
}

//=========== LEFT ROTATE ===========\\
//       [P]                      [P]
//        |                        |
//       [X]      Rotates to      [Y]
//      /   \        --->        /   \
//    T1    [Y]                [X]    T3
//         /   \              /   \
//       T2     T3          T1     T2



void RBT::leftRotate(node *x) {
    node *y = x->right;
    node *temp = y->left;//temp is [T2]

    x->right = temp;
    if (temp != nil) temp->parent = x; //changes the parent of [T2] to [X]

    y->parent = x->parent; //change [Y] to point to [P]
    if (x->parent == nil) root = y; //if X was the root, let the new root be [Y]
    else if (x->parent->left == x) x->parent->left = y; //Change [P] to point to [Y]
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

//=========== RIGHT ROTATE ===========\\

//       [P]                      [P]
//        |                        |
//       [X]      Rotates to      [Y]
//      /   \        --->        /   \
//    [Y]    T3                T1    [X]
//   /   \                          /   \
// T1     T2                      T2     T3

void RBT::rightRotate(node *x) {
    node *y = x->left;
    node *temp = y->right;

    x->left = temp;
    if (temp != nil) temp->parent = x;

    y->parent = x->parent;
    if (x->parent == nil) root = y;
    else if (x->parent->left == x) x->parent->left = y;
    else x->parent->right = y;

    y->right = x;
    x->parent = y;
}

void RBT::insertFixup(node *n) {
    while (n->parent->color == color::red) {
        node *parent = n->parent;
        node *grandparent = parent->parent;
        node *uncle = grandparent->left==parent ? grandparent->right : grandparent->left;

        if (uncle->color == color::red) { //Case 1: uncle is red
            parent->color = color::black;
            uncle->color = color::black;
            grandparent->color = color::red;
            n=grandparent;
            continue;
        }

        if (grandparent->left == parent) {
            if (parent->right == n) {//bent elbow case, we need to straighten it first
                //straighten the bend, n and parent switch places. and we switch the pointers as well
                n = parent; //first we let n point to the parent as well, which is on top
                leftRotate(parent); //then we switch around the places of the parent (node on top) and the child
                parent = n->parent; //lastly, since they switched places, the node on the top became the node at the bottom
                //but it still has both the "n" and the "parent" pointers on it, so we correct the "parent" pointer so
                //that it points to the node on top
            }
            parent->color = color::black; //straight arm case, change colors then rotate grandparent
            grandparent->color = color::red;
            rightRotate(grandparent);
        } else {
            if (parent->left == n) {
                n = parent;
                rightRotate(parent);
                parent = n->parent;
            }
            parent->color = color::black;
            grandparent->color = color::red;
            leftRotate(grandparent);
        }
    }
    root->color = color::black;
}