#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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
    cout << "size " << array.size() << endl;

    cout << "Read array is:" << endl;
    printArray(array);

    mergeSort(array);

    cout << "Sorted array is:" << endl;
    printArray(array);

    system("pause");
    return 0;
}
