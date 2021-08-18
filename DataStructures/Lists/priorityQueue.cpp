#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Simple single-type Node class
template <class V>
class Node {

    public:
        int priority;
        V value;

        Node(int priority, V value) {
            this->priority = priority;
            this->value = value;
        }
};

//Linked-List Implemented PriorityQ
template <typename V>
class PriorityQ {

    private:
        std::vector<Node<V>*> nodes;

        void exchange(int firstKey, int secondKey);
        void swim(int searchNode);
        void sink(int searchNode);

    public:
        void clear();
        V deleteMax();
        void insert(int priority, V value);
        int size();

        PriorityQ(int startSize=10) {
            nodes.reserve(startSize);
        }
};

/* Function: clear
 * Description: This function removes all values from the queue.
*/
template <typename V>
void PriorityQ<V>::clear() {
    while (nodes.size() > 1) {
        deleteMax();
    }
}

/* Function: deleteMax
 * Description: This function removes and returns the value pair with the highest priority (key) from the queue.
*/
template <typename V>
V PriorityQ<V>::deleteMax() {
    V max = V();

    if (nodes.size() > 1) {
        max = nodes[1]->value;
        exchange(1,nodes.size() - 1);
        delete nodes.back();
        nodes.pop_back();
        sink(1);
    }
    return max;
}

/* Function: exchange
 * Description: This function exchanges two nodes in the queue by swapping their positions.
 */
template <typename V>
void PriorityQ<V>::exchange(int firstIndex, int secondIndex) {
    Node<V>* swapNode = nodes[firstIndex];
    nodes[firstIndex] = nodes[secondIndex];
    nodes[secondIndex] = swapNode;
}

/* Function: insert
 * Description: This function inserts a node into the queue and places it accordingly by its priority.
 */
template <typename V>
void PriorityQ<V>::insert(int newPriority, V newValue) {
    Node<V>* newNode = new Node<V>(newPriority, newValue);

    if (nodes.size() == 0) {
        nodes.push_back(NULL);
        nodes.push_back(newNode);
    }

    else {
        nodes.push_back(newNode);
        swim(nodes.size()-1);
    }
}

/* Function: sink
 * Description: This function sinks a node to its proper position by swapping it with one of its children.
 * This function is used when a parent key is lower priority than one or both of its children.
 */
template <typename V>
void PriorityQ<V>::sink(int nodeIndex) {
    int numNodes = nodes.size()-1;

    while (2 * nodeIndex <= numNodes) {
        int j = 2 * nodeIndex;

        //If the second child > first child, the swap should be with that child
        if (j < numNodes && nodes[j]->priority < nodes[j+1]->priority) {
            j++;
        }

        //Node is in its proper position
        if (nodes[nodeIndex]->priority >= nodes[j]->priority) {
            break;
        }

        //Swap parent node with higher-priority child node
        exchange(nodeIndex, j);
        nodeIndex = j;
    }
}

/* Function: swim
 * Description: This function swims a node (up) to its proper position by swapping its parent.
 * This function is used when a child key is higher priority than its parent.
 */
template <typename V>
void PriorityQ<V>::swim(int nodeIndex) {
    while (nodeIndex > 1 && nodes[floor(nodeIndex / 2)]->priority < nodes[nodeIndex]->priority) {
        exchange(floor(nodeIndex / 2), nodeIndex);
        nodeIndex /= 2;
    }
}


int main() {
    // PriorityQ<string>* testPQ = new PriorityQ<string>();
    // testPQ->insert(1, "Alpha");
    // testPQ->insert(3, "Charlie");
    // testPQ->insert(11, "Kilo");
    // testPQ->insert(8, "Hotel");
    // testPQ->insert(6, "Frank");
    // testPQ->insert(5, "Echo");
    // testPQ->insert(26, "Zulu");
    // testPQ->insert(18, "Sierra");
    // cout << testPQ->deleteMax() << endl;
    // cout << testPQ->deleteMax() << endl;
    // cout << testPQ->deleteMax() << endl;
    // cout << testPQ->deleteMax() << endl;
    // cout << testPQ->deleteMax() << endl;
    // cout << testPQ->deleteMax() << endl;
    // cout << testPQ->deleteMax() << endl;
    // cout << testPQ->deleteMax() << endl;
    // delete testPQ;
    return 0;
}