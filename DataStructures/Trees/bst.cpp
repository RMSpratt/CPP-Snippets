#include <iostream>
#include <string.h>
using namespace std;

//Node class for all key-value pairs in the BST
template <class K, class V>
class Node {

    public:
        K key;
        V value;
        Node<K,V>* left;
        Node<K,V>* right;
        
        Node(K newVey, V newValue) {
            key = newVey;
            value = newValue;
            left = NULL;
            right = NULL;
        }
};

//BST class to store nodes in a binary-search tree format
template <typename K, typename V>
class BST {
    private:
        Node<K,V> *root = NULL;
        Node<K,V>* put(Node<K,V>* root, K newVey, V newValue);
        Node<K,V>* remove(Node<K,V>* currNode, K searchKey);
        Node<K,V>* getSuccessor(Node<K,V>* currNode);
        Node<K,V>* getMax(Node<K,V>* currNode);

    public:
        void put(K newVey, V newValue);
        V get(K searchKey);
        void remove(K searchKey);
        V min();
        V max();
};

//PRIVATE FUNCTIONS

/* Function: getSuccessor
 * Description: Used in node deletion to get the right subtree node for the node replacing the node being deleted.
 * 
 * Param: Node<K,V>* searchNode, K newKey, V newValue
*/ 
template <typename K, typename V>
Node<K,V>* BST<K,V>::getSuccessor(Node<K,V>* currNode) {
    if (currNode->left == NULL) {
        return currNode->right;
    }

    currNode->left = getSuccessor(currNode->left);
    return currNode;
}

/* Function: put
 * Description: Inserts a new node with the passed key and value into the BST, organized by key.
 *              This function searches the tree recursively.
 * 
 * Param: Node<K,V>* searchNode, K newKey, V newValue
*/ 
template <typename K, typename V>
Node<K,V>* BST<K,V>::put(Node<K,V>* searchNode, K newVey, V newValue) {
    if (searchNode == NULL) {
        return new Node<K,V>(newVey, newValue);
    }

    if (newVey < searchNode->key) {
        searchNode->left = put(searchNode->left, newVey, newValue);
    }

    else if (newVey > searchNode->key) {
        searchNode->right = put(searchNode->right, newVey, newValue);
    }

    else {
        searchNode->value = newValue;
    }

    return searchNode;
}


/* Function: remove
 * Description: Searches for the given key in the BST and removes it if found. Searching is recursive.
 * 
 * Param: Node<K,V>* searchNode, K newKey, V newValue
*/ 
template <typename K, typename V>
Node<K,V>* BST<K,V>::remove(Node<K,V>* currNode, K searchKey) {

    if (currNode == NULL) {
        return NULL;
    }

    //Current key > search key
    if (searchKey < currNode->key) {
        if (currNode->left != NULL) {
            currNode->left = remove(currNode->left, searchKey);
        }
    }

    //Current key < search key
    else if (searchKey > currNode->key) {
        if (currNode->right != NULL) {
            currNode->right = remove(currNode->right, searchKey);
        }
    }

    //Current key == search key
    else {

        Node<K,V>* tempNode;

        if (currNode->left == NULL) {
            tempNode = currNode->right;
            delete currNode;
            currNode = NULL;
            return tempNode;
        }

        if (currNode->right == NULL) {
            tempNode = currNode->left;
            delete currNode;
            currNode = NULL;
            return tempNode;
        }

        tempNode = currNode;
     
        //Set currNode to the min node in the node to remove's subtree
        currNode = currNode->right;

        while (currNode->left != NULL) {
            currNode = currNode->left;
        }

        //Get the successor node to replace the one being removed
        currNode->right = getSuccessor(tempNode->right);
        currNode->left = tempNode->left;

        //Remove the node
        delete tempNode;
    }

    return currNode;
}

//PUBLIC FUNCTIONS

/* Function: get
 * Description: Searches for a node with the given key and returns its associated value if found within the tree.
 *              This function searches the tree iteratively.
 * 
 * Param: K searchKey
*/ 
template <typename K, typename V>
V BST<K,V>::get(K searchKey) {
    Node<K,V>* iter = root;

    while (iter != NULL) {
        if (searchKey < iter->key && iter->left != NULL) {
            iter = iter->left;
        }

        else if (searchKey > iter->key && iter->right != NULL) {
            iter = iter->right;
        }

        else {
            return iter->value;
        }
    }
    return NULL;
}


/* Function: max
 * Description: Returns the value of the maximum key node in the tree.
 * 
 * Param: K newKey, V newValue
*/ 
template <typename K, typename V>
V BST<K,V>::max() {
    Node<K,V>* iterNode = root;

   while (iterNode->right != NULL) {
       iterNode = iterNode->right;
   }

   return iterNode->value;
}

/* Function: min
 * Description: Returns the value of the minimum key node in the tree.
 * 
 * Param: K newKey, V newValue
*/ 
template <typename K, typename V>
V BST<K,V>::min() {
    Node<K,V>* iterNode = root;

    while (iterNode->left != NULL) {
       iterNode = iterNode->left;
    }

   return iterNode->value;
}

//Public put function
template <typename K, typename V>
void BST<K,V>::put(K newVey, V newValue) {
    root = put(root, newVey, newValue);
}

//Public remove function
template <typename K, typename V>
void BST<K,V>::remove(K searchKey) {
    root = remove(root, searchKey);
}

int main() {
    BST<int,string> *customers = new BST<int,string>;
    customers->put(11, "Kilo");
    customers->put(5, "Echo");
    customers->put(3, "Charlie");
    customers->put(4, "Delta");
    customers->put(26, "Zulu");
    customers->put(1, "Alpha");
    customers->put(6, "Frank");
    customers->put(8, "Hotel");
    customers->remove(5);
    customers->remove(4);
    customers->remove(6);
    customers->remove(3);
    customers->remove(8);
    customers->remove(1);
    customers->remove(26);
    customers->remove(11);

    delete customers;
    customers = NULL;
}