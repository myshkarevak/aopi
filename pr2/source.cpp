#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <typename T>
class QueueNode 
{
    private:
    T value;
    QueueNode* nextNode;

    public:
    QueueNode(T value)
    {
        this->value = value;
        this->nextNode = nullptr;
    }

    void setValue(T value)
    {
        this->value = value;
    }

    T getValue()
    {
        return this->value;
    }

    void setNextNode(QueueNode<T>* nextNode)
    {
        this->nextNode = nextNode;
    }

    QueueNode<T>* getNextNode()
    {
        return this->nextNode;
    }
};

template <typename T>
class CircularQueue 
{
    private:
    QueueNode<T>* head;
    QueueNode<T>* tail;
    int size;

    public:
    CircularQueue() 
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    ~CircularQueue()
    {
        while(!this->isEmpty())
        {
            this->dequeue();
        }
    }

    int getSize()
    {
        return this->size;
    }

    bool isEmpty()
    {
        return this->size == 0;
    }

    QueueNode<T>* getHead()
    {
        return this->head;
    }

    void enqueue(T value) {
        QueueNode<T>* newNode = new QueueNode<T>(value);
        if (this->isEmpty()) {
            newNode->setNextNode(newNode);
            this->head = newNode;
            this->tail = newNode;
        } else {
            newNode->setNextNode(this->head);
            this->tail->setNextNode(newNode);
            this->tail = newNode;
        }
        this->size++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }

        T value = this->head->getValue();

        if (this->head == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
        } else {
            this->head = this->head->getNextNode();
            this->tail->setNextNode(this->head);
        }

        this->size--;

        return value;
    }
};

void split (CircularQueue<int> &queue, CircularQueue<int> &leftQueue, CircularQueue<int> &rightQueue)
{
    for (int index = 0; index < queue.getSize() / 2; index++)
    {
        leftQueue.enqueue(queue.dequeue());
    }

    while (!queue.isEmpty())
    {
        rightQueue.enqueue(queue.dequeue());
    }
}

void merge(CircularQueue<int> &queue, CircularQueue<int> &leftQueue, CircularQueue<int> &rightQueue)
{
    QueueNode<int>* currentLeftQueueNode = leftQueue.getHead();
    QueueNode<int>* currentRightQueueNode = rightQueue.getHead();

    while (!leftQueue.isEmpty() && !rightQueue.isEmpty())
    {
        if (currentLeftQueueNode->getValue() <= currentRightQueueNode->getValue())
        {
            currentLeftQueueNode = currentLeftQueueNode->getNextNode();
            queue.enqueue(leftQueue.dequeue());
        }
        else
        {
            currentRightQueueNode = currentRightQueueNode->getNextNode();
            queue.enqueue(rightQueue.dequeue());
        }
    }

    while (!leftQueue.isEmpty())
    {
        queue.enqueue(leftQueue.dequeue());
    }

    while (!rightQueue.isEmpty())
    {
        queue.enqueue(rightQueue.dequeue());
    }
}

void mergeSort(CircularQueue<int> &queue)
{
    if (queue.getSize() <= 1)
    {
        return;
    }

    CircularQueue<int> leftQueue, rightQueue;

    split(queue, leftQueue, rightQueue);
    mergeSort(leftQueue);
    mergeSort(rightQueue);
    merge(queue, leftQueue, rightQueue);
}

CircularQueue<int> readQueueFromFile(const string filename)
{
    ifstream file;
    file.open(filename, ios::in);

    if (!file.is_open())
    {
        cerr << "Cannot open file " << filename << endl;
        system("pause");
        exit(1);
    }

    CircularQueue<int> data;
    int buffer;

    while (!file.eof())
    {
        if (file.fail())
        {
            cerr << "Cannot read file " << filename << endl;
            system("pause");
            file.close();
            exit(1);
        }
        file >> buffer;
        data.enqueue(buffer);
    }
    
    file.close();
    cout << "File read successfully" << endl;

    return data;
}

void printQueue(CircularQueue<int> &queue)
{
    QueueNode<int>* currentElement = queue.getHead();

    for (int index = 0; index < queue.getSize(); index++)
    {
       cout << currentElement->getValue() << " ";
       currentElement = currentElement->getNextNode();
    }

    cout << endl;
}

int main()
{
    const string filename = "C:\\data.txt";
    CircularQueue<int> queue = readQueueFromFile(filename);
    cout << "Size " << queue.getSize() << endl;

    cout << "Read data is:" << endl;
    printQueue(queue);

    mergeSort(queue);

    cout << "Sorted data is:" << endl;
    printQueue(queue);

    system("pause");

    return 0;
}
