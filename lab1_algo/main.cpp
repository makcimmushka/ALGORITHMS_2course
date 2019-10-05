#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#define Data "Data.bin"
#define BIG_INT 2147483647

using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(vector <int> &array, int low, int high)
{
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (array[j] < pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);

    return (i + 1);
}

void quickSort(vector <int> &array, int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

vector <int> read(const string &fileName, int n, int &pos)
{
    vector <int> result;
    ifstream file(fileName, ios_base::binary);
    int buffer;

    file.seekg(pos);

    if (file)
    {
        for (int i = 0; i < n; ++i)
        {
            if (!file.eof()) {
                file.read((char *)&buffer, sizeof(int));
                result.push_back(buffer);
            }
        }
    }

    pos = file.tellg();
    file.close();

    return result;
}

int read(const string &fileName, int &pos)
{
    ifstream file(fileName, ios_base::binary);
    int buffer = 0;

    file.seekg(pos);

    if (file)
    {
        if (!file.eof())
        {
            file.read((char *)&buffer, sizeof(int));
        }
    }

    pos = file.tellg();
    file.close();

    return buffer;
}


void write(const string &fileName, const vector <int> &array)
{
    ofstream file(fileName, ios_base::app | ios_base::binary);
    if (file)
    {
        file.write((char*)&array[0], array.size() * sizeof(array[0]));
        file.close();
    }
}


void write(const string &fileName, const int &value)
{
    ofstream file(fileName, ios_base::app | ios_base::binary);

    if (file)
    {
        file.write((char *)&value, sizeof(int));
        file.close();
    }
}


void clear(const string &fileName)
{
    ofstream file(fileName);
    if (file)
    {
        file.clear();
        file.close();
    }

    else
    {
        cout << "ERROR " + fileName;
    }
}


vector<string> creatingFiles(int n)
{
    vector <string> names;
    string name = "File";

    for (int i = 0; i < n; ++i)
    {
        string numberToChar = to_string(i);
        name += numberToChar;
        name += ".bin";
        ofstream file(name, ios_base::binary);
        names.push_back(name);
        name = "File";
    }

    return names;
}


int sumOfChunks(const vector<int> &quantityOfChunks)
{
    int sum = 0;

    for (int quantityOfChunk : quantityOfChunks)
    {
        sum += quantityOfChunk;
    }

    return sum;
}


vector<int> fibCalculation(int numbOfFiles, int m_size)
{
    vector <int> chuncks(numbOfFiles);
    int maxValue = 0, indexOfMax = 0;
    chuncks[0] = 1;

    for (int i = 1; i < (int)chuncks.size(); ++i)
        chuncks[i] = 0;

    while (sumOfChunks(chuncks) < m_size) {
        for (int i = 0; i < (int)chuncks.size(); ++i)
        {
            if (chuncks[i] > maxValue)
            {
                maxValue = chuncks[i];
                indexOfMax = i;
            }
        }

        for (int i = 0; i < (int)chuncks.size(); ++i)
        {
            if (i != indexOfMax)
                chuncks[i] += maxValue;

            else
                chuncks[i] = 0;
        }

        maxValue = 0;
        indexOfMax = 0;
    }

    return chuncks;
}


bool isSorted(const vector <string> &names)
{
    int endOfDataFile = 0;
    ifstream fileData(Data);

    if (fileData)
    {
        fileData.seekg(0, ios_base::end);
        endOfDataFile = fileData.tellg();
        fileData.close();
    }

    int endOfFile;

    ifstream file(names[0]);

    if (file)
    {
        file.seekg(0, ios_base::end);
        endOfFile = file.tellg();

        if (endOfFile > endOfDataFile)
        {
            file.close();
            return true;
        }

        file.close();
    }

    return false;
}


void divide(const string &fileSource, const vector <string> &namesOfFiles, const vector <int> &chunks, int size)
{
    string output = namesOfFiles[0];
    vector <int> buffer;
    int index = 0;
    int currentPosition = 0;

    while (currentPosition >= 0)
    {
        for (int i = 0; i < chunks[index]; ++i)
        {
            buffer = read(fileSource, size, currentPosition);
            quickSort(buffer, 0, (int)buffer.size() - 1);
            buffer.push_back(BIG_INT);
            write(output, buffer);
        }

        index++;

        if (index < namesOfFiles.size())
            output = namesOfFiles[index];
    }
}


void searchingMinValue(const vector <int> &buffer, int &minValue, int &indexMin, int emptyFile)
{
    for (int i = 0; i < (int)buffer.size(); ++i)
    {
        if (i != emptyFile)
        {
            if (minValue > buffer[i])
            {
                minValue = buffer[i];
                indexMin = i;
            }
        }
    }
}


int isEndOfFile(const vector <string> &namesOfFiles, const vector <int> &positions)
{
    for (int i = 0; i < (int)positions.size(); ++i)
    {
        ifstream file(namesOfFiles[i]);
        if (file)
        {
            int current = positions[i];
            file.seekg(0, ios_base::end);
            int end = file.tellg();

            if (end - current == 0)
            {
                file.close();
                return i;
            }

            file.close();
        }
    }

    return -1;
}


bool isEndOfChunks(const vector <int> &buffer)
{
    int counter = 0;

    for (int i : buffer)
    {
        if (i == BIG_INT)
            ++counter;
    }

    return counter == buffer.size();
}


void merge(const vector <string> &namesOfFiles, int &emptyFileOnStart)
{
    string output = namesOfFiles[emptyFileOnStart];
    vector <int> bufferForEachFile(namesOfFiles.size());
    vector <int> positionForEachBuffer(namesOfFiles.size());
    vector <int> resultBuffer;

    int minValue = BIG_INT, indexOfMinValue, emptyFile = emptyFileOnStart, newEmptyFile;

    while (!isSorted(namesOfFiles))
    {

        for (int i = 0; i < namesOfFiles.size(); ++i)
        {
            if (i != emptyFile)
                bufferForEachFile[i] = read(namesOfFiles[i], positionForEachBuffer[i]);
        }

        bufferForEachFile[emptyFile] = BIG_INT;
        positionForEachBuffer[emptyFile] = BIG_INT;
        searchingMinValue(bufferForEachFile, minValue, indexOfMinValue, emptyFile);

        while (!isEndOfChunks(bufferForEachFile))
        {
            resultBuffer.push_back(minValue);
            bufferForEachFile[indexOfMinValue] = read(namesOfFiles[indexOfMinValue], positionForEachBuffer[indexOfMinValue]);
            minValue = BIG_INT;
            searchingMinValue(bufferForEachFile, minValue, indexOfMinValue, emptyFile);
        }

        resultBuffer.push_back(BIG_INT);


        write(output, resultBuffer);

        resultBuffer.clear();

        newEmptyFile = isEndOfFile(namesOfFiles, positionForEachBuffer);

        if (newEmptyFile != -1)
        {
            clear(namesOfFiles[newEmptyFile]);
            positionForEachBuffer[emptyFile] = 0;
            emptyFile = newEmptyFile;
        }

        output = namesOfFiles[emptyFile];
    }
}


int emptyFile(const vector <int> &chunks)
{
    int i = 0;

    for (i = 0; i < chunks.size(); ++i)
    {
        if (chunks[i] == 0)
            return i;
    }

    return i;
}


void readAll(const vector <string> &names)
{
    vector <int> data;
    ifstream file(names[0], ios_base::binary);
    if (file) {
        while (!file.eof())
        {
            int buffer;
            file.read((char *)&buffer, sizeof(int));
            data.push_back(buffer);
        }

        file.close();
    }

    data.shrink_to_fit();

    cout << "size: " << data.size() - 3  << endl;

    for (int i = 1; i < data.size() - 3 ; i++)
        cout << data[i] << endl;
}


void deleteAll(const string &fileSource, const vector <string> &namesOfFiles)
{
    char *fileName = new char[30];

    fileSource.copy(fileName, fileSource.size() + 1);

    fileName[fileSource.size()] = '\0';

    remove(fileName);

    for (int i = 0; i < namesOfFiles.size(); i++)
    {
        namesOfFiles[i].copy(fileName, namesOfFiles[i].size() + 1);

        fileName[namesOfFiles[i].size()] = '\0';

        remove(fileName);
    }

    delete[] fileName;
}


void polyphaseMergeSort(int numbOfFiles, int numbOfNumbers, int size)
{
    vector <string> namesOfFiles = creatingFiles(numbOfFiles);
    vector <int> chunks = fibCalculation(numbOfFiles, numbOfNumbers / size + 1);
    int m_size = (numbOfNumbers / sumOfChunks(chunks)) + 1;
    divide(Data, namesOfFiles, chunks, m_size);
    int empty = emptyFile(chunks);
    merge(namesOfFiles, empty);
    //readAll(namesOfFiles);
    deleteAll(Data, namesOfFiles);
}



void genFile(int n)
{
    srand(time(NULL));
    vector <int> temp;

    for (int i = 0; i < n; i++)
        temp.push_back(rand() % 1000);


    write(Data, temp);
}



int main()
{
    int numbOfFiles, numbOfNumbers, m_size;

    cin >> numbOfFiles;
    cin >> numbOfNumbers;
    cin >> m_size;

    genFile(numbOfNumbers);

    polyphaseMergeSort(numbOfFiles, numbOfNumbers, m_size);

    return 0;
}