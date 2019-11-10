#include <iostream>
#include <vector>
#include <chrono>

using namespace std;


int neededPowerOfTwo(unsigned int size) {
    int neededPowerOfTwo = 1;

    while ((size /= 2) != 0)
        neededPowerOfTwo++;

    return neededPowerOfTwo;
}


int getMax(int firstValue, int secondValue, int thirdValue) {
    int maxValue = 0;

    if (firstValue > maxValue)
        maxValue = firstValue;

    if (secondValue > maxValue)
        maxValue = secondValue;

    if (thirdValue > maxValue)
        maxValue = thirdValue;

    return maxValue;
}


int getNewSize(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix) {
    return 1 << neededPowerOfTwo(getMax(firstMatrix.size(), firstMatrix[0].size(), secondMatrix[0].size()));
}


bool isPowerOfTwo(int value) {
    bool result = false;

    for (int i = 1; i <= value; i *= 2) {
        if (i == value)
            result = true;
    }

    return result;
}


vector<vector<int>> additionToSquareMatrix(vector<vector<int>> input, int newSize) {
    vector<vector<int>> output(newSize, vector<int>(newSize, 0));

    for (int i = 0; i < (int)input.size(); i++) {
        for (int j = 0; j < (int)input[i].size(); j++) {
            output[i][j] = input[i][j];
        }
    }

    return output;
}


void splitMatrix(const vector<vector<int>> &input, vector<vector<int>> &partOfInput1_1, vector<vector<int>> &partOfInput1_2,
                 vector<vector<int>> &partOfInput2_1, vector<vector<int>> &partOfInput2_2) {

    int n = (int)input.size() / 2;

    for (int i = 0; i < n; ++i) {
        copy(input[i].begin(), input[i].end() - n, back_inserter(partOfInput1_1[i]));
        copy(input[i].begin() + n, input[i].end(), back_inserter(partOfInput1_2[i]));
        copy(input[i + n].begin(), input[i + n].end() - n, back_inserter(partOfInput2_1[i]));
        copy(input[i + n].begin() + n, input[i + n].end(), back_inserter(partOfInput2_2[i]));
    }
}


vector<vector<int>> collectMatrix(vector<vector<int>> partOfInput1_1, vector<vector<int>> partOfInput1_2,
                                  vector<vector<int>> partOfInput2_1, vector<vector<int>> partOfInput2_2) {

    int size = (int)partOfInput1_1.size();
    vector<vector<int>> result(size * 2, vector<int>());

    for (int i = 0; i < size; i++) {
        copy(partOfInput1_1[i].begin(), partOfInput1_1[i].end(), back_inserter(result[i]));
        copy(partOfInput1_2[i].begin(), partOfInput1_2[i].end(), back_inserter(result[i]));
        copy(partOfInput2_1[i].begin(), partOfInput2_1[i].end(), back_inserter(result[i + size]));
        copy(partOfInput2_2[i].begin(), partOfInput2_2[i].end(), back_inserter(result[i + size]));
    }

    return result;
}


vector<vector<int>> compressionOfMatrix(vector<vector<int>> input, int rows, int columns) {
    vector<vector<int>> result(rows, vector<int>(columns));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result[i][j] = input[i][j];
        }
    }

    return result;
}


vector<vector<int>> summation(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix) {
    vector<vector<int>> result(firstMatrix.size(), vector<int>());

    for (int i = 0; i < (int)firstMatrix.size(); ++i) {
        for (int j = 0; j < (int)firstMatrix.size(); ++j) {
            result[i].push_back(firstMatrix[i][j] + secondMatrix[i][j]);
        }
    }

    return result;
}


vector<vector<int>> subtraction(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix) {
    vector<vector<int>> result(firstMatrix.size(), vector<int>());

    for (int i = 0; i < (int)firstMatrix.size(); ++i) {
        for (int j = 0; j < (int)firstMatrix.size(); ++j) {
            result[i].push_back(firstMatrix[i][j] - secondMatrix[i][j]);
        }
    }

    return result;
}


vector<vector<int>> multiply(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix) {
    vector<vector<int>> result(firstMatrix.size(), vector<int>(secondMatrix[0].size(), 0));
    for (int i = 0; i < (int)firstMatrix.size(); i++) {
        for (int j = 0; j < (int)secondMatrix[0].size(); j++) {
            for (int k = 0; k < (int)firstMatrix[0].size(); k++) {
                result[i][j] += (firstMatrix[i][k] * secondMatrix[k][j]);
            }
        }
    }

    return result;
}


vector<vector<int>> algorithm(const vector<vector<int>> &firstMatrix, const vector<vector<int>> &secondMatrix) {

    if (firstMatrix.size() <= 128) {
        return multiply(firstMatrix, secondMatrix);
    }

    int size;
    size = (int)firstMatrix.size() / 2;

    vector<vector<int>> a11(size, vector<int>());
    vector<vector<int>> a12(size, vector<int>());
    vector<vector<int>> a21(size, vector<int>());
    vector<vector<int>> a22(size, vector<int>());

    vector<vector<int>> b11(size, vector<int>());
    vector<vector<int>> b12(size, vector<int>());
    vector<vector<int>> b21(size, vector<int>());
    vector<vector<int>> b22(size, vector<int>());

    splitMatrix(firstMatrix, a11, a12, a21, a22);
    splitMatrix(secondMatrix, b11, b12, b21, b22);

    vector<vector<int>> p1 = algorithm(summation(a11, a22), summation(b11, b22));
    vector<vector<int>> p2 = algorithm(summation(a21, a22), b11);
    vector<vector<int>> p3 = algorithm(a11, subtraction(b12, b22));
    vector<vector<int>> p4 = algorithm(a22, subtraction(b21, b11));
    vector<vector<int>> p5 = algorithm(summation(a11, a12), b22);
    vector<vector<int>> p6 = algorithm(subtraction(a21, a11), summation(b11, b12));
    vector<vector<int>> p7 = algorithm(subtraction(a12, a22), summation(b21, b22));

    vector<vector<int>> c11 = summation(summation(p1, p4), subtraction(p7, p5));
    vector<vector<int>> c12 = summation(p3, p5);
    vector<vector<int>> c21 = summation(p2, p4);
    vector<vector<int>> c22 = summation(subtraction(p1, p2), summation(p3, p6));

    return collectMatrix(c11, c12, c21, c22);
}


vector<vector<int>> matrixMultiplication(const vector<vector<int>> &firstMatrix, const vector<vector<int>> &secondMatrix) {
    int newSize = firstMatrix.size();

    if (!isPowerOfTwo((int)firstMatrix.size())) {
        newSize = getNewSize(firstMatrix, secondMatrix);
    }

    vector<vector<int>> firstSquareMatrix = additionToSquareMatrix(firstMatrix, newSize);
    vector<vector<int>> secondSquareMatrix = additionToSquareMatrix(secondMatrix, newSize);
    vector<vector<int>> result = algorithm(firstSquareMatrix, secondSquareMatrix);
    result = compressionOfMatrix(result, firstMatrix.size(), secondMatrix[0].size());

    return result;
}


int main() {

    int size = 2048;
    vector<vector<int>> a(size, vector<int>());
    chrono::time_point<chrono::system_clock> startForFirst, endForFirst, startForSecond, endForSecond;
    double timeFirstAlgorithm, timeSecondAlgorithm;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; j++) {
            a[i].push_back(rand() % 50);
        }
    }

    vector<vector<int>> b(size, vector<int>());
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 1; j++) {
            b[i].push_back(rand() % 50);
        }
    }

    startForFirst = chrono::system_clock::now();
    vector<vector<int>> result1 = matrixMultiplication(a, a);
    endForFirst = chrono::system_clock::now();
    timeFirstAlgorithm = chrono::duration_cast<chrono::seconds>(endForFirst - startForFirst).count();
    cout << "Time of multiplying by Strassen's algorithm: " << timeFirstAlgorithm << "s" << endl;

    startForSecond = chrono::system_clock::now();

    vector<vector<int>> result2 = multiply(a, a);

    endForSecond = chrono::system_clock::now();

    timeSecondAlgorithm = chrono::duration_cast<chrono::seconds>(endForSecond - startForSecond).count();

    cout << "Time of multiplying by classic algorithm: " << timeSecondAlgorithm << "s" << endl;

    bool check = true;

    for (int i = 0; i < (int) result2.size(); ++i) {
        for (int j = 0; j < (int) result2[0].size(); ++j) {
            if (result1[i][j] != result2[i][j])
                check = false;
        }
    }

    cout << "Is matrices equals: " << check << endl;

    return 0;
}