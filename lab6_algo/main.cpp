#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> z_function (const string& str) {
    int n = str.length();
    vector<int> z (n);

    for (int i = 1, left = 0, right = 0; i < n; i++) {
        if (i <= right) {
            z[i] = min (right - i + 1, z[i - left]);
        }

        while (i + z[i] < n && str[z[i]] == str[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i]-1 > right) {
            left = i, right = i + z[i] - 1;
        }
    }

    return z;
}


bool isShift (const string& str1, const string& str2) {
    if (str1.size() == str2.size()) {
        string str3 = str1 + "/" + str2 + str2;
        vector <int> z_func = z_function(str3);

        for (int val : z_func) {
            if (val == str1.size()) {
                return true;
            }
        }
    }

    return false;
}


string generateString() {
    srand(time(NULL));

    string result;
    int size;
    do {
        size = rand() % 20;
    } while (size == 0);

    for (int i = 0; i < size; ++i) {
        char symbol = (rand() % 54) + 65;
        result += symbol;
    }

    return result;
}


void shift(string& str) {
    int n = str.size() - 1;

    int temp = str[n];

    while(n--)
        str[n+1] = str[n];

    str[0] = temp;
}


string cyclicShift(string& str) {
    string cyclicStr = str;
    int n;

    do {
        srand(time(NULL));
        n = rand() % 10;
    } while (n==0);

    while (n) {
        shift(cyclicStr);
        n--;
    }

    return cyclicStr;
}



int main() {
    vector <int> z;
    //string str1 = generateString();
    //string str2 = cyclicShift(str1);

    string str1, str2;
    cin >> str1;
    cin >> str2;


    cout << str1 << endl;
    cout << str2 << endl;

    cout << isShift(str1, str2) << endl;

    return 0;
}