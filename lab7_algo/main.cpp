#include <iostream>
#include <string>
#include <vector>

using namespace std;

int search(const string &pattern, const string &text)
{
    const int p = 31;

    vector<long long> p_pow (max(pattern.length(), text.length()));
    p_pow[0] = 1;
    for (size_t i = 1; i < p_pow.size(); i++)
    {
        p_pow[i] = p_pow[i-1] * p;
    }

    vector<long long> hashes_for_text (text.length());
    for (size_t i = 0; i < text.length(); ++i)
    {
        hashes_for_text[i] = (text[i] - 'a' + 1) * p_pow[i];
        if (i) hashes_for_text[i] += hashes_for_text[i - 1];
    }

    long long hash_for_pattern = 0;
    for (size_t i = 0; i < pattern.length(); i++)
    {
        hash_for_pattern += (pattern[i] - 'a' + 1) * p_pow[i];
    }

    for (size_t i = 0; i + pattern.length() - 1 < text.length(); ++i)
    {
        long long cur_h = hashes_for_text[i + pattern.length() - 1];
        if (i)
            cur_h -= hashes_for_text[i - 1];

        if (cur_h == hash_for_pattern * p_pow[i])
        {
            return i;
        }
    }

    return -1;
}

bool search_in_matrices(string pattern[], string text[])
{
    int index;

    for (int i = 0; i < (int) text[0].length(); ++i)
    {
        if (text[0].length() - i < pattern[0].length())
        {
            return false;
        }

        index = search(pattern[0], text[i]);

        while (index >= 0)
        {
            int counter = 1;

            for (int j = i + 1; j < (int) text[0].length(); j++)
            {
                if (pattern[counter] == text[j].substr(index, pattern[0].length()))
                {
                    counter++;
                } else {
                    break;
                }

                if (counter == pattern[0].length())
                {
                    return true;
                }
            }

            index = search(pattern[0], text[i].substr(index + 1, text[0].length() - index - 1));
        }
    }

    return false;
}

string generateString(int size) {
    srand(time(NULL));

    string result = "";

    for (int i = 0; i < size; ++i) {
        char symbol = (rand() % 54) + 65;
        result += symbol;
    }

    return result;
}

int main() {

    int N;
    int M;

    cout << "Input size of text :" << endl;
    cin >> N;
    cout << "Input size of pattern :" << endl;
    cin >> M;

    auto *text = new string[N];
    auto *pattern = new string[M];

    //cout << "Input elements of text :" << endl;

    for (int i = 0; i < N; ++i)
    {
        text[i] = generateString(N);
    }

    int rand_index = rand () % (N - M);

    //cout << "Input elements of pattern :" << endl;

    int counter = 0;

    for (int i = rand_index; i < M + rand_index; ++i)
    {
        pattern[counter] = text[i].substr(rand_index, M);
        counter++;
    }

    cout << search_in_matrices(pattern, text) << endl;

//    for (int i = 0; i < N; ++i)
//    {
//        cout << text[i] << endl;
//    }
//
//    cout << endl << endl;
//
//    for (int i = 0; i < M; i++) {
//        cout << pattern[i] << endl;
//    }


    return 0;
}