#include <bits/stdc++.h>
using namespace std;
#define int long long

#define POLY 0x83 // x^7+x+1

uint8_t mul(uint8_t b0, uint8_t b1){
	int product;
    product = 0;
    for(int i = 0; i < 7; i++){
        product <<= 1;
        if(product & 0x80){
            product ^= POLY;
        }
        if(b0 & 0x40){
            product ^= b1;
        }
        b0 <<= 1;
    }
    return((uint8_t)product);
}

string pass = "lhhklqgsihffgkmjjffkgsjifsgugiig";

vector<vector<int>> A = {{84, 0, 0, 0, 0, 0, 0, 0}, 
						{113, 70, 0, 0, 0, 0, 0, 0}, 
						{26, 26, 43, 0, 0, 0, 0, 0}, 
						{105, 22, 31, 12, 0, 0, 0, 0}, 
						{101, 35, 3, 116, 112, 0, 0, 0}, 
						{29, 42, 30, 54, 97, 11, 0, 0}, 
						{17, 122, 0, 99, 22, 94, 27, 0}, 
						{95, 9, 87, 25, 22, 70, 6, 38}};

vector<int> E = {21, 106, 42, 68, 90, 55, 26, 23};
map<char, string> mpp;
map<string, char> inv_mp;

uint8_t expo(uint8_t a,uint8_t b){
	uint8_t ans=1;
	while(b){
		if(b&1)
			ans = mul(ans,a);
		a=mul(a,a);
		b>>=1;
	}
	return ans;
}

vector<int> E_fn(vector<int> v){
	vector<int> ans(8);
	for (int i = 0; i < 8; ++i)
	{
		ans[i] = expo(v[i],E[i]); 
	}

	return ans;
}
vector<int> matmul(vector<int> B){
    int m=A.size();
    int n=A[0].size();
    int o=1;
    vector<int> C(m);

    for(int i=0;i<m;i++){
        int elm=0;
        for(int k=0;k<n;k++){
            elm ^= mul(A[i][k],B[k]);
        }
        C[i]=elm;
    }

    return C;
}
vector<int> EAEAE(vector<int> v){
	vector<int> temp = v;
	temp = E_fn(temp);
	temp = matmul(temp);
	temp = E_fn(temp);
	temp = matmul(temp);
	temp = E_fn(temp);
	return temp;

}
int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;
 
    int base = 1;
 
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}
string apply(string s){
	vector<int> v(8);
	for (int i = 0; i < s.size(); i+=2)
	{
		v[i>>1] = binaryToDecimal(mpp[s[i]]+mpp[s[i+1]]);
	}
	vector<int> ans(8);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 128; ++j)
		{
			ans[i] = j;
			vector<int> x = EAEAE(ans);
			if(x[i] == v[i])
				break;
			else
				ans[i] = 0;
		}
	}

	string temp = "";
	for (int i = 0; i < ans.size(); ++i)
	{
		string s = bitset<8>(ans[i]).to_string();
		temp+=inv_mp[s.substr(0,4)];
		temp+=inv_mp[s.substr(4)];
	}

	return temp;

}
void solve(){

	for (char ch = 'f'; ch <= 'u'; ++ch)
	{
		string temp = bitset<4>(ch-'f').to_string();
		mpp[ch] = temp;	
		inv_mp[temp] = ch;
	}

	string ans = apply(pass.substr(0,16));
	ans+=apply(pass.substr(16));
	string password;
	for (int i = 0; i < ans.size(); i+=2)
	{
		string temp = mpp[ans[i]]+mpp[ans[i+1]];
		int x=binaryToDecimal(temp);
		password += (char)(x);
	}
	cout<<"Password (with padding) :"<< password<<endl;
	while(password.size() && password.back()=='0') password.pop_back();
	cout<<"Final Password :"<< password<<endl;


}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.precision(17);
    int t=1;
    // cin>>t;
    while(t--){
	    solve();
    }

    return 0;
}
