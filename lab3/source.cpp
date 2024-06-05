#include <iostream>
#include <fstream>
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

    void enqueue(T value)
    {
        QueueNode<T>* newNode = new QueueNode<T>(value);
        if (this->isEmpty())
        {
            newNode->setNextNode(newNode);
            this->head = newNode;
            this->tail = newNode;
        }
        else
        {
            newNode->setNextNode(this->head);
            this->tail->setNextNode(newNode);
            this->tail = newNode;
        }
        this->size++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            throw runtime_error("Queue is empty");
        }

        T value = this->head->getValue();

        if (this->head == this->tail)
        {
            this->head = nullptr;
            this->tail = nullptr;
        }
        else
        {
            this->head = this->head->getNextNode();
            this->tail->setNextNode(this->head);
        }

        this->size--;

        return value;
    }
};

template <typename T>
void split (CircularQueue<T> &queue, CircularQueue<T> &leftQueue, CircularQueue<T> &rightQueue)
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

template <typename T>
void merge(CircularQueue<T> &queue, CircularQueue<T> &leftQueue, CircularQueue<T> &rightQueue)
{
    QueueNode<T>* currentLeftQueueNode = leftQueue.getHead();
    QueueNode<T>* currentRightQueueNode = rightQueue.getHead();

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

template <typename T>
void mergeSort(CircularQueue<T> &queue)
{
    if (queue.getSize() <= 1)
    {
        return;
    }

    CircularQueue<T> leftQueue, rightQueue;

    split(queue, leftQueue, rightQueue);
    mergeSort(leftQueue);
    mergeSort(rightQueue);
    merge(queue, leftQueue, rightQueue);
}

template <typename T>
CircularQueue<T> readQueueFromFile(const string filename)
{
    ifstream file;
    file.open(filename, ios::in);

    if (!file.is_open())
    {
        cerr << "Cannot open file " << filename << endl;
        system("pause");
        exit(1);
    }

    CircularQueue<T> data;
    T buffer;

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

template <typename T>
void printQueue(CircularQueue<T> &queue)
{
    QueueNode<T>* currentElement = queue.getHead();

    for (int index = 0; index < queue.getSize(); index++)
    {
       cout << currentElement->getValue() << " ";
       currentElement = currentElement->getNextNode();
    }

    cout << endl;
}

int main()
{
    CircularQueue<int> queue = readQueueFromFile<int>("C:\\data.txt");

    cout << "Size " << queue.getSize() << endl << "Read data is:" << endl;

    printQueue(queue);
    mergeSort(queue);

    cout << "Sorted data is:" << endl;

    printQueue(queue);
    system("pause");

    return 0;
}
