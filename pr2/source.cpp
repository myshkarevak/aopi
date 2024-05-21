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
        this->nextNode = NULL;
    }

    void setValue(T value)
    {
        this->value = value;
    }

    T getValue()
    {
        return this->value;
    }

    void setNextNode(QueueNode* nextNode)
    {
        this->nextNode = nextNode;
    }

    QueueNode* getNextNode()
    {
        return this->nextNode;
    }
}

class CircularQueue 
{
    private:
    QueueNode head;
    QueueNode tail;
    int size;

    public:
    CircularQueue() 
    {
        this->head = NULL;
        this->tail = NULL;
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
        return this
    }

    QueueNode* getHead()
    {
        return this->head;
    }

    void enqueue(T value) {
        QueueNode* newNode = new Node(value);
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
            this->head = NULL;
            this->tail = NULL;
        } else {
            this->head = this->head->getNextNode();
            this->tail->setNextNode(this->head);
        }

        this->size--;

        return value;
    }
}

void split (vector<int> &array, vector<int> &leftArray, vector<int> &rightArray)
{
    const int leftArraySize = array.size() / 2;
    const int rightArraySize = array.size() - leftArraySize;

    leftArray.reserve(leftArraySize);
    rightArray.reserve(rightArraySize);

    for (int index = 0; index < leftArraySize; index++)
    {
        leftArray.push_back(array[index]);
    }

    for (int index = 0; index < rightArraySize; index++)
    {
        rightArray.push_back(array[leftArraySize + index]);
    }
}

void merge(vector<int> &array, vector<int> &leftArray, vector<int> &rightArray)
{
    int leftArrayIndex = 0, rightArrayIndex = 0, mergedArrayIndex = 0;

    while (leftArrayIndex < leftArray.size() && rightArrayIndex < rightArray.size())
    {
        if (leftArray[leftArrayIndex] <= rightArray[rightArrayIndex])
        {
            array[mergedArrayIndex] = leftArray[leftArrayIndex];
            leftArrayIndex++;
        }
        else
        {
            array[mergedArrayIndex] = rightArray[rightArrayIndex];
            rightArrayIndex++;
        }
        mergedArrayIndex++;
    }

    while (leftArrayIndex < leftArray.size())
    {
        array[mergedArrayIndex] = leftArray[leftArrayIndex];
        leftArrayIndex++;
        mergedArrayIndex++;
    }

    while (rightArrayIndex < rightArray.size())
    {
        array[mergedArrayIndex] = rightArray[rightArrayIndex];
        rightArrayIndex++;
        mergedArrayIndex++;
    }
}

void mergeSort(vector<int> &array)
{
    if (array.size() <= 1)
    {
        return;
    }

    vector<int> leftArray, rightArray;

    split(array, leftArray, rightArray);
    mergeSort(leftArray);
    mergeSort(rightArray);
    merge(array, leftArray, rightArray);

    leftArray.clear();
    rightArray.clear();
}

vector<int> readArrayFromFile(const string filename)
{
    ifstream file;
    file.open(filename, ios::in);

    if (!file.is_open())
    {
        cerr << "Cannot open file " << filename << endl;
        system("pause");
        exit(1);
    }

    vector<int> data;
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
        data.push_back(buffer);
    }
    
    file.close();
    cout << "File read successfully" << endl;

    return data;
}

void printArray(vector<int> &array)
{
    for (int index = 0; index < array.size(); index++)
    {
        cout << array[index] << " ";
    }

    cout << endl;
}

int main()
{
    const string filename = "C:\\data.txt";
    vector<int> array = readArrayFromFile(filename);
    cout << "Size " << array.size() << endl;

    cout << "Read array is:" << endl;
    printArray(array);

    mergeSort(array);

    cout << "Sorted array is:" << endl;
    printArray(array);

    array.clear();

    system("pause");
    return 0;
}
