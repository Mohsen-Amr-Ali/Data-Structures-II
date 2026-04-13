#ifndef RBT_HPP
#define RBT_HPP

#include <string>

class RBT {
    private:
        enum class color{ red, black };

        struct node {
            node *parent;
            std::string key;
            node *left, *right;
            color color;
        };

        node *root;
        node *nil;

        bool search(std::string key, node *n);
        int getTreeHeight(node *n);
        int getBlackHeight(node *n);
        int getSize(node *n);

        void leftRotate(node *x);
        void rightRotate(node *x);

        void insertFixup(node *n);

    public:
        RBT();
        RBT(std::string key);
        void insert(std::string key);
        bool search(std::string key);
        int getTreeHeight();
        int getBlackHeight();
        int getSize();

};


#endif //RBT