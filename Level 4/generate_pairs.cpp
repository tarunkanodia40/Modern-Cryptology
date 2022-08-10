#include <iostream>
#include <bits/stdc++.h>
#include <random>
#include <math.h>
using namespace std;

int rev_perm[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                    39, 7, 47, 15, 55, 23, 63, 31,
                    38, 6, 46, 14, 54, 22, 62, 30,
                    37, 5, 45, 13, 53, 21, 61, 29,
                    36, 4, 44, 12, 52, 20, 60, 28,
                    35, 3, 43, 11, 51, 19, 59, 27,
                    34, 2, 42, 10, 50, 18, 58, 26,
                    33, 1, 41, 9, 49, 17, 57, 25};

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

string dectohex(long long n)
{
    string hexd;
    long long i = 0;
    while (n != 0)
    {
        long long temp = 0;
        temp = n % 16;
        if (temp < 10)
        {
            hexd += (char)(temp + 48);
        }
        else
        {
            hexd += (char)(temp + 55);
        }

        n /= 16;
    }
    reverse(hexd.begin(), hexd.end());
    return hexd;
}

string binarybits_to_char(string str, map<string, char> inverse_mapping)
{
    int i = 0;
    string text = "";
    while (i < 64)
    {
        string part = "";
        part += str[i];
        part += str[i + 1];
        part += str[i + 2];
        part += str[1 + 3];
        i += 4;
        text += inverse_mapping[part];
    }
    return text;
}

string inverse(string str)
{
    string inv = "";
    long long decimal = stoll(str, 0, 16);
    string binary = dectobin(decimal, 64);
    for (int i = 0; i < 64; i++)
        inv += binary[rev_perm[i] - 1];
    long long decimal_1 = stoll(inv, 0, 2);
    return dectohex(decimal_1);
}
string rand_bin()
{
    string bin = "";
    for (int i = 0; i < 64; i++)
    {
        bin += (char)(rand() % 2 + 48);
    }
    return bin;
}
int main()
{

    map<string, char> inverse_mapping;

    inverse_mapping["0000"] = 'd';
    inverse_mapping["0001"] = 'e';
    inverse_mapping["0010"] = 'f';
    inverse_mapping["0011"] = 'g';
    inverse_mapping["0100"] = 'h';
    inverse_mapping["0101"] = 'i';
    inverse_mapping["0110"] = 'j';
    inverse_mapping["0111"] = 'k';
    inverse_mapping["1000"] = 'l';
    inverse_mapping["1001"] = 'm';
    inverse_mapping["1010"] = 'n';
    inverse_mapping["1011"] = 'o';
    inverse_mapping["1100"] = 'p';
    inverse_mapping["1101"] = 'q';
    inverse_mapping["1110"] = 'r';
    inverse_mapping["1111"] = 's';

    string input_xor = inverse("405c000004000000");
    long long decimal = stoll(input_xor, 0, 16);
    string binary_bits = dectobin(decimal, 64);
    ofstream File("pairs_of_plaintexts.txt");
    long long number = (long long)pow(2, 18);
    for (long long i = 0; i < number; i++)
    {
        string bits1 = rand_bin();
        string bits2 = "";
        for (int j = 0; j < 64; j++)
        {
            bits2 += (((bits1[j] - 48) ^ (binary_bits[j] - 48)) + 48);
        }
        string p1 = binarybits_to_char(bits1, inverse_mapping);
        string p2 = binarybits_to_char(bits2, inverse_mapping);

        File << p1 << endl
             << p2 << endl;
    }
    File.close();
    return 0;
}
