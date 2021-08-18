#include <iostream>

using namespace std;

//Simple single-type Node class
template <class V>
class Node {

    public:
        V value;
        Node<V>* next;
        
        Node(V value, Node<V>* head) {
            this->value = value;
            next = head;
        }
};

//Linked-List Implemented Stack
template <typename V>
class Stack {

    private:
        Node<V>* head;

    public:
        void push(V value);
        V pop();
        int size();

        Stack() {
            head = NULL;
        }
};

/* Function: push
 * Description: This function pushes the passed value to the stack by assigning it to a new node.
*/
template <typename V>
void Stack<V>::push(V value) {
    Node<V>* newNode = new Node<V>(value, this->head);
    this->head = newNode;
}

/* Function: pop
 * Description: This function pops the most recent value added to the stack, and deletes the associated node.
*/
template <typename V>
V Stack<V>::pop() {
    Node<V>* poppedNode = this->head;
    V poppedValue = poppedNode->value;
    this->head = this->head->next;
    delete poppedNode;

    return poppedValue;    
}

//Return number of nodes in the stack
template <typename V>
int Stack<V>::size() {
    int stackSize = 0;

    Node<V>* iterNode = this->head;

    while (iterNode != NULL) {
        iterNode = iterNode->next;
        stackSize += 1;
    }

    return stackSize;
}

int main() {
    // Stack<int>* numStack = new Stack<int>();
    // numStack->push(1);
    // numStack->push(2);
    // numStack->push(3);
    // numStack->push(4);
    // numStack->push(5);
    // cout << "Stack size: " << numStack->size() << endl;
    // cout << numStack->pop() << endl;
    // cout << numStack->pop() << endl;
    // cout << numStack->pop() << endl;
    // cout << numStack->pop() << endl;
    // cout << numStack->pop() << endl;
    // delete numStack;
}