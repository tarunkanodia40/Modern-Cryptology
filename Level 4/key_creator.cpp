#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;
string dectobin(long long n, long long size)
{
    string ans = "";
    for (long long i = size - 1; i >= 0; i--)
    {
        long long k = n >> i;
        if (k & 1)
            ans += '1';
        else
            ans += '0';
    }
    return ans;
}
int main()
{
    int mapping[8][6] = {
        {24, 27, 21, 6, 11, 15},
        {13, 10, 25, 16, 3, 20},
        {5, 1, 22, 14, 8, 18},
        {26, 17, 9, 2, 23, 12},
        {51, 34, 41, 47, 29, 37},
        {40, 50, 33, 55, 43, 30},
        {54, 31, 49, 38, 44, 35},
        {56, 52, 32, 46, 39, 42},
    };

    map<int, int> known_bits;
    known_bits[1] = 45;
    known_bits[2] = 51;
    known_bits[5] = 15;
    known_bits[6] = 48;
    known_bits[7] = 9;
    known_bits[8] = 61;

    vector<char> partially_known_master_key(56, 'X');

    for (auto i = known_bits.begin(); i != known_bits.end(); i++)
    {
        string binary_bits = dectobin(i->second, 6);
        for (int j = 0; j < binary_bits.size(); j++)
        {
            if (binary_bits[j] == '1')
            {
                partially_known_master_key[mapping[i->first - 1][j] - 1] = '1';
            }
            else
            {
                partially_known_master_key[mapping[i->first - 1][j] - 1] = '0';
            }
        }
    }

    string PNKeys = "";
    for (int i = 0; i < 56; i++)
    {
        cout << partially_known_master_key[i];
        PNKeys += partially_known_master_key[i];
    }
    cout << endl;

    ofstream File("Output_keys.txt");
    long long itr = 0, number = (long long)pow(2, 20);
    for (long long i = 0; i < number; i++)
    {
        string itr_string = "";
        string bits = dectobin(i, 20);
        itr = 0;
        for (int j = 0; j < PNKeys.size(); j++)
        {
            if (PNKeys[j] == 'X')
            {
                itr_string += bits[itr];
                itr++;
            }
            else
                itr_string += PNKeys[j];
        }

        File << itr_string << endl;
        itr_string = "";
    }
    File.close();
    return 0;
}