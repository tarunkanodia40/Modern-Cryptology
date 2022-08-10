#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define POLY 0x83 // x^7+x+1
vector<vector<vector<int>>> PA(8, vector<vector<int>>(8));
vector<vector<int>> EXP(8);
vector<vector<int>> A(8, vector<int>(8, 0));
uint8_t mul(uint8_t b0, uint8_t b1)
{
    int product;
    product = 0;
    for (int i = 0; i < 7; i++)
    {
        product <<= 1;
        if (product & 0x80)
        {
            product ^= POLY;
        }
        if (b0 & 0x40)
        {
            product ^= b1;
        }
        b0 <<= 1;
    }
    return ((uint8_t)product);
}
uint8_t expo(uint8_t a, uint8_t b)
{
    uint8_t ans = 1;
    while (b)
    {
        if (b & 1)
            ans = mul(ans, a);
        a = mul(a, a);
        b >>= 1;
    }
    return ans;
}

vector<int> E_fn(vector<int> v)
{
    vector<int> ans(8);
    for (int i = 0; i < 8; ++i)
    {
        ans[i] = expo(v[i], EXP[i][0]);
    }

    return ans;
}

vector<int> matmul(vector<int> B)
{
    int m = 8;
    int n = 8;
    int o = 1;
    vector<int> C(m);

    for (int i = 0; i < m; i++)
    {
        int elm = 0;
        for (int k = 0; k < n; k++)
        {
            elm ^= mul(A[i][k], B[k]);
        }
        C[i] = elm;
    }

    return C;
}

vector<int> EAEAE(vector<int> v)
{
    vector<int> temp = v;
    temp = E_fn(temp);
    temp = matmul(temp);
    temp = E_fn(temp);
    temp = matmul(temp);
    temp = E_fn(temp);
    return temp;
}

int main()
{
    string text;
    ifstream InpFile("plaintexts.txt");
    ifstream OutFile("outputs.txt");
    vector<vector<string>> inp(8), out(8);
    int l = 0;
    while (getline(InpFile, text))
    {
        string temp = "";
        for (int i = 0; i < text.size(); i++)
        {
            if (text[i] == ' ')
            {
                inp[l].push_back(temp);
                temp = "";
            }
            else
            {
                temp += text[i];
            }
        }
        l++;
    }
    l = 0;
    int k = 0;
    while (getline(OutFile, text))
    {

        out[l].push_back(text);
        k++;
        if (k == 128)
        {
            l++;
            k = 0;
        }
    }
    InpFile.close();
    OutFile.close();
    // cout << out[0][1].size();
    vector<int> in(128), ou(128);

    bool flag;
    for (int i = 0; i < 8; i++)
    {

        for (int j = 0; j < 128; j++)
        {
            in[j] = 16 * (inp[i][j][2 * i] - 'f') + inp[i][j][2 * i + 1] - 'f';
            ou[j] = 16 * (out[i][j][2 * i] - 'f') + out[i][j][2 * i + 1] - 'f';
        }
        for (int m = 1; m < 127; m++)
        {
            for (int k = 1; k < 128; k++)
            {
                flag = false;
                for (int t = 0; t < 128; t++)
                {
                    if (ou[t] != expo(mul(expo(mul(expo(in[t], m), k), m), k), m))
                    {
                        flag = true;
                        break;
                    }
                }
                if (flag == false)
                {
                    PA[i][i].push_back(k);
                    EXP[i].push_back(m);
                }
            }
        }
    }
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            in[j] = 16 * (inp[i][j][2 * i] - 'f') + inp[i][j][2 * i + 1] - 'f';
            ou[j] = 16 * (out[i][j][2 * (i + 1)] - 'f') + out[i][j][2 * (i + 1) + 1] - 'f';
        }
        for (int j = 1; j < 128; j++)
        {
            for (int t = 0; t < PA[i + 1][i + 1].size(); t++)
            {
                for (int u = 0; u < PA[i][i].size(); u++)
                {
                    flag = false;
                    for (int it = 0; it < 128; it++)
                    {
                        if (ou[it] != expo(mul(expo(mul(expo(in[it], EXP[i][u]), PA[i][i][u]), EXP[i][u]), j) ^ mul(expo(mul(expo(in[it], EXP[i][u]), j), EXP[i + 1][t]), PA[i + 1][i + 1][t]), EXP[i + 1][t]))
                        {
                            flag = true;
                            break;
                        }
                    }
                    if (flag == false)
                    {
                        PA[i + 1][i].clear();
                        PA[i + 1][i].push_back(j);
                        int expp = EXP[i + 1][t];
                        EXP[i + 1].clear();
                        EXP[i + 1].push_back(expp);
                        expp = EXP[i][u];
                        EXP[i].clear();
                        EXP[i].push_back(expp);
                        expp = PA[i + 1][i + 1][t];
                        PA[i + 1][i + 1].clear();
                        PA[i + 1][i + 1].push_back(expp);
                        expp = PA[i][i][u];
                        PA[i][i].clear();
                        PA[i][i].push_back(expp);
                    }
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (PA[i][j].size() > 0)
            {
                // cout << PA[i][j][0] << " ";
                A[i][j] = PA[i][j][0];
            }
                // cout << "0 ";
        }
        // cout << endl;
    }
    // cout << endl;
    // for (int i = 0; i < 8; i++)
    // {
    //     cout << EXP[i][0] << " ";
    // }
    // cout << endl;
    for (int i = 2; i < 8; i++)
    {
        for (int j = 0; j < 8 - i; j++)
        {
            for (int k = 0; k < 128; k++)
            {
                in[k] = 16 * (inp[j][k][2 * j] - 'f') + inp[j][k][2 * j + 1] - 'f';
                ou[k] = 16 * (out[j][k][2 * (i + j)] - 'f') + out[j][k][2 * (i + j) + 1] - 'f';
            }
            for (int k = 1; k < 128; k++)
            {
                A[i + j][j] = k;
                flag = false;
                vector<int> vec(8, 0), c(8, 0);
                for (int it = 0; it < 128; it++)
                {
                    vec = {0, 0, 0, 0, 0, 0, 0, 0};
                    vec[j] = in[it];
                    c = EAEAE(vec);
                    if (ou[it] != c[i + j])
                    {
                        flag = true;
                        A[i + j][j] = 0;
                        break;
                    }
                }
                if (flag == false)
                {
                    A[i + j][j] = k;
                    break;
                }
            }
        }
    }
    cout<<"Matrix A:"<<endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout<<"Vector E:"<<endl;
    for (int i = 0; i < 8; i++)
    {
        cout << EXP[i][0] << " ";
    }
    cout << endl;
    return 0;
}
