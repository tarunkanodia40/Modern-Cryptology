
#include <bits/stdc++.h>
using namespace std;

map<char, pair<int, int>> location;
vector<vector<char>> playfair_matrix ={{'C', 'R', 'Y', 'P', 'T'},
	{'A', 'N', 'L', 'S', 'I'},
	{'B', 'D', 'E', 'F', 'G'},
	{'H', 'K', 'M', 'O', 'Q'},
	{'U', 'V', 'W', 'X', 'Z'}};

string decrypt(string s){
	string ans;
	for (int i = 0; i < s.size(); i+=2)
	{
		pair<int, int> p1 = location[s[i]];
		pair<int, int> p2 = location[s[i+1]];

		if(p1.first == p2.first){
			ans+= playfair_matrix[p1.first][(p1.second + 4) % 5];
			ans+= playfair_matrix[p2.first][(p2.second + 4) % 5];
		}
		else if(p1.second == p2.second){
			ans+= playfair_matrix[(p1.first + 4) % 5][p1.second];
			ans+= playfair_matrix[(p2.first + 4) % 5][p2.second];
		}
		else{
			ans+= playfair_matrix[p1.first][p2.second];
			ans+= playfair_matrix[p2.first][p1.second];
		}
	}

	return ans;
}

int32_t main()
{
	string cipher_text = "DF ULYP XO CQD LFWC RUBHEDY, CQDYG LN XDYL EGIYIG LMP CQDYF. LYFNH HXPZ CQF YNILXKPB \"NDCB_AN_BBHCN\" PQ FQ CQPKZBK. OLC PMC UNUG YMB IPYDIDCQ OXY CMB LDZP AULHDFY. CX OALG RMB FWGI PMX BNTIP ZLSWS LFWFE PQ ZCYGY KIBAT XMNKI PMBYD.";
	string filtered_cipher_text = "";
	for(char ch:cipher_text){
		if(isalnum(ch))
			filtered_cipher_text+=ch;
	}

	int n=filtered_cipher_text.length();

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			location[playfair_matrix[i][j]] = {i,j};
 		}
	}

	string ans=decrypt(filtered_cipher_text);
	string complete_plain_text;
	int j=0;
	for (int i = 0; i < cipher_text.size(); ++i)
	{
		if(!isalnum(cipher_text[i])){
			complete_plain_text+=cipher_text[i];
			continue;
		}
		complete_plain_text+=ans[j];
		j++;
	}

	cout<<complete_plain_text;


    return 0;
}
