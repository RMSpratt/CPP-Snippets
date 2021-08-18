#include <iostream>
#include <string.h>
using namespace std;

const bool RED = true;
const bool BLACK = false;

//Node class for all key-value pairs in the RedBlack
template <class K, class V>
class Node {

    public:
        K key;
        V value;
        Node<K,V>* left;
        Node<K,V>* right;
        bool colour;
        
        Node(K newKey, V newValue, bool nodeColour) {
            key = newKey;
            value = newValue;
            left = NULL;
            right = NULL;
            colour = nodeColour;
        }
};

//RedBlack class to store nodes in a binary-search tree format
template <typename K, typename V>
class RedBlack {
    private:
        Node<K,V> *root = NULL;
        
        Node<K,V>* fixImbalances(Node<K,V>* currNode);  
        Node<K,V>* flipColours(Node<K,V>* currNode);  
        Node<K,V>* getMax(Node<K,V>* currNode);
        Node<K,V>* getSuccessor(Node<K,V>* currNode);    
        bool isRed(Node<K,V>* currNode);
        void printInorder(Node<K,V>* currNode);
        Node<K,V>* moveRedLeft(Node<K,V>* currNode);
        Node<K,V>* moveRedRight(Node<K,V>* currNode);
        void printPostorder(Node<K,V>* currNode);
        void printPreorder(Node<K,V>* currNode);
        Node<K,V>* put(Node<K,V>* root, K newKey, V newValue);
        Node<K,V>* remove(Node<K,V>* currNode, K searchKey);
        Node<K,V>* removeMin(Node<K,V>* currNode);
        Node<K,V>* removeMax(Node<K,V>* currNode);
        Node<K,V>* rotateLeft(Node<K,V>* currNode);
        Node<K,V>* rotateRight(Node<K,V>* currNode);

    public:
        bool contains(K searchKey);
        V get(K searchKey);
        V min();
        V max();
        void printPreorder();
        void printPostorder();
        void printInorder();
        void put(K newKey, V newValue);
        void remove(K searchKey);
        void removeMin();
        void removeMax();
};

//PRIVATE FUNCTIONS

template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::fixImbalances(Node<K,V>* currNode) {

    if (isRed(currNode->right)) {
        currNode = rotateLeft(currNode);
    }

    if (isRed(currNode->left) && isRed(currNode->left->left)) {
        currNode = rotateRight(currNode);
    }

    if (isRed(currNode->left) && isRed(currNode->right)) {
        currNode = flipColours(currNode);
    }

    return currNode;
}

/* Function: flipColours
 * Description: Flips the colour of the passed node and its two child nodes to be the opposite colour.
 *
 * Param: currNode (The current node to flip)
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::flipColours(Node<K,V>* currNode) {
    currNode->colour = !currNode->colour;
    currNode->left->colour = !currNode->left->colour;
    currNode->right->colour = !currNode->right->colour;
    return currNode;
}

/* Function: getSuccessor
 * Description: Used in node deletion to get the right subtree node for the node replacing the node being deleted.
 * 
 * Param: Node<K,V>* searchNode, K newKey, V newValue
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::getSuccessor(Node<K,V>* currNode) {
    if (currNode->left == NULL) {
        return currNode->right;
    }

    currNode->left = getSuccessor(currNode->left);
    return currNode;
}


/* Function: isRed
 * Description: Returns whether or not the passed node is RED. (NULL == BLACK).
 * 
 * Param: Node<K,V>* currNode
*/ 
template <typename K, typename V>
bool RedBlack<K,V>::isRed(Node<K,V>* currNode) {

    if (currNode == NULL) {
        return false;
    }

    return currNode->colour == RED;
}

/* Function: moveRedLeft
 * Description: Used in minimum node deletion when a red sibling is needed to be borrowed from another node.
 * This results in the node's left child or grand-child becoming red.
 *
 * Param: currNode (The current node being viewed)
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::moveRedLeft(Node<K,V>* currNode) {
    currNode = flipColours(currNode);

    if (isRed(currNode->right->left)) {
        currNode->right = rotateRight(currNode->right);
        currNode = rotateLeft(currNode);
        currNode = flipColours(currNode);
    }

    return currNode;
}

/* Function: moveRedRight
 * Description: Used in maximum node deletion when a red sibling is needed to be borrowed from another node.
 * This results in the node's right child or grand-child becoming red.
 *
 * Param: currNode (The current node being viewed)
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::moveRedRight(Node<K,V>* currNode) {
    currNode = flipColours(currNode);

    //If the left->left grandchild is red, move it to the right
    if (isRed(currNode->left->left)) {
        currNode = rotateRight(currNode);
        currNode = flipColours(currNode);
    }

    return currNode;
}

/* Function: put
 * Description: Inserts a new node with the passed key and value into the RedBlack, organized by key.
 *              This function searches the tree recursively.
 * 
 * Param: Node<K,V>* searchNode, K newKey, V newValue
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::put(Node<K,V>* searchNode, K newKey, V newValue) {
    if (searchNode == NULL) {
        return new Node<K,V>(newKey, newValue, RED);
    }

    if (newKey < searchNode->key) {
        searchNode->left = put(searchNode->left, newKey, newValue);
    }

    else if (newKey > searchNode->key) {
        searchNode->right = put(searchNode->right, newKey, newValue);
    }

    else {
        searchNode->value = newValue;
    }

    return fixImbalances(searchNode);

    return searchNode;
}

/* Function: printInorder
 * Description: Navigates the tree and prints the values in in-order.
 * 
 * Param: currNode (The current node being viewed)
*/ 
template <typename K, typename V>
void RedBlack<K,V>::printInorder(Node<K,V>* currNode) {

    if (currNode == NULL) {
        return;
    }

    printInorder(currNode->left);
    cout << "K: " << currNode->key << " Colour: " << currNode->colour << endl;
    printInorder(currNode->right);
}

/* Function: printPostorder
 * Description: Navigates the tree and prints the values in post-order.
 * 
 * Param: currNode (The current node being viewed)
*/ 
template <typename K, typename V>
void RedBlack<K,V>::printPostorder(Node<K,V>* currNode) {

    if (currNode == NULL) {
        return;
    }

    printPostorder(currNode->left);
    printPostorder(currNode->right);
    cout << "K: " << currNode->key << " Colour: " << currNode->colour << endl;
}

/* Function: printPreorder
 * Description: Navigates the tree and prints the values in pre-order.
 * 
 * Param: currNode (The current node being viewed)
*/ 
template <typename K, typename V>
void RedBlack<K,V>::printPreorder(Node<K,V>* currNode) {

    if (currNode == NULL) {
        return;
    }

    cout << "K: " << currNode->key << " Colour: " << currNode->colour << endl;

    printPreorder(currNode->left);
    printPreorder(currNode->right);
}

/* Function: remove
 * Description: Searches for the given key in the RedBlack and removes it if found. Searching is recursive.
 * 
 * Param: Node<K,V>* searchNode, K newKey, V newValue
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::remove(Node<K,V>* currNode, K searchKey) {

    if (currNode == NULL) {
        return NULL;
    }

    //Current key < search key
    if (searchKey < currNode->key) {
        if (!isRed(currNode->left) && !isRed(currNode->left->left)) {
            currNode = moveRedLeft(currNode);
        }
        currNode->left = remove(currNode->left, searchKey);
    }

    else {

        //Temporarily make left-leaning red links lean right
        if (isRed(currNode->left)) {
            currNode = rotateRight(currNode);
        }

        //Node was found at the bottom of the tree, delete it
        if (searchKey == currNode->key && currNode->right == NULL) {
            delete currNode;
            currNode = NULL;
            return NULL;
        }

        if (!isRed(currNode->right) && !isRed(currNode->right->left)) {
            currNode = moveRedRight(currNode);
        }

        if (currNode->key == searchKey) {
            Node<K,V>* tempNode = currNode->right;

            while (tempNode->left != NULL) {
                tempNode = tempNode->left;
            }

            //Copy the successor's key and value
            currNode->key = tempNode->key;
            currNode->value = tempNode->value;

            //Remove the successor node from the tree
            currNode->right = removeMin(currNode->right);
        }
        
        else {
            currNode->right = remove(currNode->right, searchKey);
        }
    }

    return fixImbalances(currNode);
}

/* Function: removeMax
 * Description: Searches through a tree and deletes the maximum node, handling imbalances along the way.
 * A red link is passed down through the tree to accomplish this.
 * 
 * Param: Node<K,V> currNode
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::removeMax(Node<K,V>* currNode) {

    //Have left-leaning red links temporarily lean right
    if (isRed(currNode->left)) {
        currNode = rotateRight(currNode);
    }

    //Delete the maximum node
    if (currNode->right == NULL) {
        delete currNode;
        currNode = NULL;
        return NULL;
    }

    else {

        //Borrow a node from a sibling node if necessary
        if (!isRed(currNode->right) && !isRed(currNode->right->left)) {
            currNode = moveRedRight(currNode);
        }

        currNode->right = removeMax(currNode->right);
    }

    //Fix imbalances when traversing back up the tree
    return fixImbalances(currNode);
}

/* Function: removeMin
 * Description: Searches through a tree and deletes the minimum node, handling imbalances along the way.
 * 
 * Param: Node<K,V> currNode
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::removeMin(Node<K,V>* currNode) {

    //Delete the minimum node
    if (currNode->left == NULL) {
        delete currNode;
        currNode = NULL;
        return NULL;
    }

    else {

        //Borrow from a sibling if necessary
        if (!isRed(currNode->left) && !isRed(currNode->left->left)) {
            currNode = moveRedLeft(currNode);
        }

        currNode->left = removeMin(currNode->left);
    }

    //Fix imbalances when traversing back up the tree
    return fixImbalances(currNode);
}

/* Function: rotateLeft
 * Description: Performs a left rotation on the current node to fix right-leaning links.
 * 
 * Param: Node<K,V> currNode
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::rotateLeft(Node<K,V>* currNode) {
    Node<K,V>* tempNode = currNode->right;
    currNode->right = tempNode->left;
    tempNode->left = currNode;
    tempNode->colour = currNode->colour;
    currNode->colour = RED;

    return tempNode;
}

/* Function: rotateRight
 * Description: Makes a left-leaning red node temporarily lean right.
 * 
 * Param: Node<K,V> currNode
*/ 
template <typename K, typename V>
Node<K,V>* RedBlack<K,V>::rotateRight(Node<K,V>* currNode) {
    Node<K,V>* tempNode = currNode->left;
    currNode->left = tempNode->right;
    tempNode->right = currNode;
    tempNode->colour = currNode->colour;
    currNode->colour = RED;

    return tempNode;
}



//PUBLIC FUNCTIONS



/* Function: contains
 * Description: Searches for a node with the given key and returns whether or not it appears in the tree.
 * 
 * Param: K searchKey
*/ 
template <typename K, typename V>
bool RedBlack<K,V>::contains(K searchKey) {
    Node<K,V>* iter = root;
    bool containsKey = false;

    while (iter != NULL) {
        if (searchKey < iter->key) {
            iter = iter->left;
        }

        else if (searchKey > iter->key) {
            iter = iter->right;
        }

        else if (searchKey == iter->key) {
            containsKey = true;
            break;
        }
    }

    return containsKey;
}

/* Function: get
 * Description: Searches for a node with the given key and returns its associated value if found within the tree.
 *              This function searches the tree iteratively.
 * 
 * Param: K searchKey
*/ 
template <typename K, typename V>
V RedBlack<K,V>::get(K searchKey) {
    Node<K,V>* iter = root;

    while (iter != NULL) {
        if (searchKey < iter->key) {
            iter = iter->left;
        }

        else if (searchKey > iter->key) {
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
V RedBlack<K,V>::max() {
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
V RedBlack<K,V>::min() {
    Node<K,V>* iterNode = root;

    while (iterNode->left != NULL) {
       iterNode = iterNode->left;
    }

   return iterNode->value;
}

//Public in-order
template <typename K, typename V>
void RedBlack<K,V>::printInorder() {
    printInorder(root);
}

//Public post-order
template <typename K, typename V>
void RedBlack<K,V>::printPostorder() {
    printPostorder(root);
}

//Public pre-order
template <typename K, typename V>
void RedBlack<K,V>::printPreorder() {
    printPreorder(root);
}

//Public put
template <typename K, typename V>
void RedBlack<K,V>::put(K newKey, V newValue) {
    if (root == NULL) {
        root = new Node<K,V>(newKey, newValue, BLACK);
    }

    else {
        root = put(root, newKey, newValue);
        root->colour = BLACK;
    }
}

//Public remove
template <typename K, typename V>
void RedBlack<K,V>::remove(K searchKey) {

    if (contains(searchKey)) {
        root = remove(root, searchKey);

        if (root != NULL) {
            root->colour = BLACK;
        }
    }
}

//Public removeMax function
template <typename K, typename V>
void RedBlack<K,V>::removeMax() {
    root = removeMax(root);

    if (root != NULL) {
        root->colour = BLACK;
    }
}

//Public removeMin function
template <typename K, typename V>
void RedBlack<K,V>::removeMin() {

    if (!isRed(root->left) && !(isRed(root->right))) {
        root->colour = RED;
    }

    root = removeMin(root);

    if (root != NULL) {
        root->colour = BLACK;
    }
}

//Driver for testing
int main() {

    //Allocations

    // RedBlack<int,string>* testTree = new RedBlack<int,string>();

    // testTree->put(1,"Alpha");
    // testTree->put(3,"Charlie");
    // testTree->put(6,"Frank");
    // testTree->put(5,"Echo");
    // testTree->put(8,"Hotel");
    // testTree->put(11,"Kilo");
    // testTree->put(12,"Larry");
    // testTree->put(13,"Mike");
    // testTree->put(17,"Ridley");
    // testTree->put(18,"Sierra");
    // testTree->put(26,"Zulu");

    //Prints 

    // testTree->printPreorder();
    // cout << endl;
    // testTree->printInorder();
    // cout << endl;
    // testTree->printPostorder();
    // cout << endl;

    //Deletions

    // testTree->remove(18);
    // testTree->remove(26);
    // testTree->remove(17);
    // testTree->remove(1);
    // testTree->remove(5);
    // testTree->remove(3);
    // testTree->printPreorder();
    // testTree->remove(6);
    // testTree->remove(8);
    // testTree->remove(11);
    // testTree->remove(12);
    // testTree->remove(17);
    // testTree->remove(13);
    // delete testTree;
}