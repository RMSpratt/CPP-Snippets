#include <iostream>
#include <vector>

using namespace std;

//Simple single-type Node class
template <class V>
class Node {

    public:
        V value;

        Node(V value) {
            this->value = value;
        }
};

//Linked-List Implemented Stack
template <typename V>
class Stack {

    private:
        std::vector<Node<V>*> nodes;

    public:
        void push(V value);
        V pop();
        int size();

        Stack(int startSize = 10) {
            nodes.reserve(startSize);
        }
};

/* Function: push
 * Description: This function pushes the passed value to the stack by assigning it to a new node.
*/ 
template <typename V>
void Stack<V>::push(V value) {
    Node<V>* newNode = new Node<V>(value);
    nodes.push_back(newNode);

    if (nodes.size() == nodes.capacity()) {
        nodes.resize(nodes.size() * 2);
    }
}

/* Function: pop
 * Description: This function pops the most recent value added to the stack, and deletes the associated node.
*/ 
template <typename V>
V Stack<V>::pop() {
    V popValue;

    //Retrieve the node's value and remove it from the stack
    if (nodes.size() > 0) {
        popValue = nodes.back()->value;
        delete nodes.back();
        nodes.pop_back();

        //Halve node stack size when num nodes N < Capacity/4
        if (nodes.size() < floor((nodes.capacity() / 4))) {
            nodes.resize(nodes.size() / 2);
        }
    }
    
    else {
        cout << "Error: Attempt to pop from empty stack.\n";
        exit(1);
    }

    return popValue;
}

//Return number of nodes in the stack
template <typename V>
int Stack<V>::size() {
  return nodes.size();
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