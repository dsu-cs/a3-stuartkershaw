#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include "node.hpp"
using namespace std;

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    // was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
    std::vector<T> *inorderHelper(Node<T>*, std::vector<T>*);
    std::vector<T> *preorderHelper(Node<T>*, std::vector<T>*);
    std::vector<T> *postorderHelper(Node<T>*, std::vector<T>*);
    void removeHelper(Node<T>*, T);
};

template<class T>
 BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
 BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
    Node<T>* iterator = root;
    std::vector<T>* vec = new std::vector<T>;

    return inorderHelper(iterator, vec);
}

template<class T>
 std::vector<T> * BST<T>::inorderHelper(Node<T> *node, std::vector<T> *vec)
{
    if (node == NULL) {
        return NULL;
    }

    inorderHelper(node->get_left(), vec);
    (*vec).push_back(node->get_data());
    inorderHelper(node->get_right(), vec);

    return vec;
}

template<class T>
 std::vector<T> * BST<T>::preorder()
{
    Node<T>* iterator = root;
    std::vector<T>* vec = new std::vector<T>;

    return preorderHelper(iterator, vec);
}

template<class T>
 std::vector<T> * BST<T>::preorderHelper(Node<T> *node, std::vector<T> *vec)
{
    if (node == NULL) {
        return NULL;
    }

    (*vec).push_back(node->get_data());
    preorderHelper(node->get_left(), vec);
    preorderHelper(node->get_right(), vec);

    return vec;
}

template<class T>
 std::vector<T> * BST<T>::postorder()
{
    Node<T>* iterator = root;
    std::vector<T>* vec = new std::vector<T>;

    return postorderHelper(iterator, vec);
}

template<class T>
 std::vector<T> * BST<T>::postorderHelper(Node<T> *node, std::vector<T> *vec)
{
    if (node == NULL) {
        return NULL;
    }
    
    postorderHelper(node->get_left(), vec);
    postorderHelper(node->get_right(), vec);
    (*vec).push_back(node->get_data());

    return vec;
}

template<class T>
 void BST<T>::insert(T new_data)
{
    Node<T>* tmp = new Node<T>(new_data);

    if(root == NULL) {
        root = tmp;
    }
    else {
        Node<T>* current = root;
        while (current != NULL) {
            if (new_data == current->get_data()) {
                return;
            }
            else if (new_data < current->get_data()) {
                if (current->get_left() == NULL) {
                    current->set_left(tmp);
                } else {
                    current = current->get_left();
                }
            }
            else if (new_data > current->get_data()) {
                if (current->get_right() == NULL) {
                    current->set_right(tmp);
                } else {
                    current = current->get_right();
                }
            }
        }

        current->set_left(NULL);
        current->set_right(NULL);

        node_count++;
    }
}

template<class T>
 Node<T> * BST<T>::search(T val)
{
    Node<T>* current;
    Node<T>* iterator = root;
    while (iterator != NULL) {
        if (val == iterator->get_data()) {
            return iterator;
        }
        else if (val < iterator->get_data()) {
            current = iterator;
            iterator = iterator->get_left();
        }
        else if (val > iterator->get_data()) {
            current = iterator;
            iterator = iterator->get_right();
        }
    }

    if (val == current->get_data()) {
        return current;
    }
    else {
        return NULL;
    }
}

template<class T>
 void BST<T>::remove(T val)
{
    removeHelper(root, val);
}

template<class T>
 void BST<T>::removeHelper(Node<T> *node, T val)
{
    Node<T>* par = NULL;
    Node<T>* current = node;

    while (current != NULL) {
        if (val == current->get_data()) {
            if (current->get_left() == NULL && current->get_right() == NULL) {
                if (par == NULL) {
                    node = NULL;
                }
                else if (par->get_left() == current) {
                    par->set_left(NULL);
                }
                else {
                    par->set_right(NULL);
                }
            }
            else if (current->get_left() != NULL && current->get_right() == NULL) {
                if (par == NULL) {
                    node = current->get_left();
                }
                else if (par->get_left() == current) {
                    par->set_left(current->get_left());
                }
                else {
                    par->set_right(current->get_left());
                }
            }
            else if (current->get_left() == NULL && current->get_right() != NULL) {
                if (par == NULL) {
                    node = current->get_right();
                }
                else if (par->get_left() == current) {
                    par->set_left(current->get_right());
                }
                else {
                    par->set_right(current->get_right());
                }
            }
            else {
                Node<T>* suc = current->get_right();
                while (suc->get_left() != NULL) {
                    suc = suc->get_left();
                }
                T sucData = suc->get_data();
                removeHelper(root, sucData);
                current->set_data(sucData);
            }
            node_count--;
            return;
        }
        else if (current->get_data() < val) {
            par = current;
            current = current->get_right();
        }
        else {
            par = current;
            current = current->get_left();
        }
    }
    return;
}

template<class T>
 int BST<T>::get_size()
{
    return node_count;
}

