#include <iostream>

using namespace std;

//Simple single-type Node class
template <class V>
class Node {

    public:
        V value;
        Node<V>* next;
        
        Node(V value) {
            this->value = value;
            this->next = NULL;
        }
};

//Linked-List Implemented Queue
template <typename V>
class Queue {

    private:
        Node<V>* head;
        Node<V>* tail;

    public:
        void enqueue(V value);
        V dequeue();
        int size();

        Queue() {
            head = NULL;
            tail = NULL;
        }
};

/* Function: dequeue
 * Description: This function dequeues the last value added to the queue, and deletes its node.
*/
template <typename V>
V Queue<V>::dequeue() {
    Node<V>* deqNode = head;
    V deqValue = V();

    //Queue is empty
    if (deqNode != NULL) {
        deqValue = head->value;
        head = head->next;
        delete deqNode;
    }
    
    return deqValue;
}

/* Function: enqueue
 * Description: This function enqueues the passed value, adding it to the queue as a node.
*/
template <typename V>
void Queue<V>::enqueue(V value) {
    Node<V>* newNode = new Node<V>(value);

    if (newNode == NULL) {
        cout << "Err: Could not allocate new queue node.\n";
        exit(1);
    }

    //First node added
    if (tail == NULL) {
        tail = newNode;
        head = tail;
    }

    //Subsequent nodes
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

/* Function: size
 * Description: This function returns the size of the queue as the number of elements within.
*/
template <typename V>
int Queue<V>::size() {
    int queueSize = 0;
    Node<V>* iterNode;

    while (iterNode != NULL) {
        iterNode = iterNode->next;
        queueSize++;
    }

    return queueSize;
}

int main() {
    //Test code
    
    // Queue<int>* testQueue = new Queue<int>();
    // testQueue->enqueue(1);
    // testQueue->enqueue(2);
    // testQueue->enqueue(3);
    // cout << testQueue->dequeue() << endl;
    // cout << testQueue->dequeue() << endl;
    // cout << testQueue->dequeue() << endl;
    // delete testQueue;
    return 0;
}