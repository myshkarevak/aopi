#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void merge(vector<int> &array, const int start, const int mid, const int end)
{
    const int leftArrayLength = mid - start + 1;
    const int rightArrayLength = end - mid;

    int leftArray[leftArrayLength], rightArray[rightArrayLength];

    for (int index = 0; index < leftArrayLength; index++)
    {
        leftArray[index] = array[start + index];
    }

    for (int index = 0; index < rightArrayLength; index++)
    {
        rightArray[index] = array[mid + 1 + index];
    }

    int leftArrayIndex = 0, rightArrayIndex = 0, mergedArrayIndex = start;

    while (leftArrayIndex < leftArrayLength && rightArrayIndex < rightArrayLength)
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

    while (leftArrayIndex < leftArrayLength)
    {
        array[mergedArrayIndex] = leftArray[leftArrayIndex];
        leftArrayIndex++;
        mergedArrayIndex++;
    }

    while (rightArrayIndex < rightArrayLength)
    {
        array[mergedArrayIndex] = rightArray[rightArrayIndex];
        rightArrayIndex++;
        mergedArrayIndex++;
    }
}

void mergeSort(vector<int> &array, const int begin, const int end)
{

    if (begin >= end)
    {
        return;
    }

    const int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void printArray(vector<int> &array, const int size)
{
    for (int index = 0; index < size; index++)
    {
        cout << array[index] << " ";
    }

    cout << endl;
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

int main()
{
    const string filename = "C:\\data.txt";
    vector<int> array = readArrayFromFile(filename);
    const int size = array.size();
    cout << "size " << size << endl;

    cout << "Read array is:" << endl;
    printArray(array, size);

    mergeSort(array, 0, size - 1);

    cout << "Sorted array is:" << endl;
    printArray(array, size);

    system("pause");
    return 0;
}
