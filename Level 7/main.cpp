#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
#define rep(i, begin, end) for (int i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
const int MOD=127 ;
int gcdEx(int a, int b, int& x, int& y) {x = 1, y = 0; int x1 = 0, y1 = 1, a1 = a, b1 = b;while(b1){ int q = a1 / b1;tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1);
tie(a1, b1) = make_tuple(b1, a1 - q * b1);} return a1;}
int modI(int a,int m=MOD){int x, y; int g = gcdEx(a, m, x, y);if(g != 1) return -1; else return(x % m + m) % m;}
int modD(int a, int b,int m=MOD){return (modI(b,m)*(a%m))%m;}
int modS(int a, int b,int m=MOD){return ((a%m)-(b%m)+m)%m;}
int modP(int a, int b,int m=MOD){a %= m;int res = 1;while (b > 0){if (b & 1) res = res * a % m; a = a * a % m; b >>= 1;}return res;}
int modA(int a, int b,int m=MOD){return (((a+MOD)%m)+((b+MOD)%m))%m;}
int modM(int a, int b,int m=MOD){return (((a+MOD)%m)*((b+MOD)%m))%m;}

vector<int> p = {22,90,38,112,67,52,25,17,45,91,110,20,82,47,115,12,124,92,120,42,6,87,45,49,34,46,98,70,82,79,7,40};
map<char, int> mpp; // Global counter for number of roots
// Takes degree of polynomial, returns number of roots found
int solve(int x){

   vector<int> e(x+1); // e[i] = (-1)^i * a_k-i,a[k]=1, a[k-1]=-e1, a[k-2]=e2..
   vector<int> a(x+1); // a_k x^k + a_k-1 x^k-1...+a_0
   e[0]=1;
   rep(i,1,x+1){
    int ans=p[i];
    int k=0;
    rep(j,1,i){
        int sign = k?1:-1;
        ans=modA(ans,modM(sign,modM(e[j] ,p[i-j])));
        k^=1;
    }
    if(i&1)
        ans=modD(ans,i);
    else
        ans=modD(ans,127-i);
    e[i]=ans;
   }

   int cnt=0;
   vector<int> r;
   rep(l,102,118){
        int ans=0;
        int k=0;
        rep(j,0,x+1){
            if(k)
                ans=modA(ans,modM(e[j],modP(l,x-j)));
            else
                ans=modA(ans,modM(127-e[j],modP(l,x-j)));
            k^=1;
            }
       if(ans%127==0){
            cnt++;
            r.push_back(l);
            mpp[l]++;

       }
   }

   rep(i,0,32){
    int sub =0;
    for(int tmep:r){
        sub=modA(sub,modP(tmep,i));
    }
    p[i] = modS(p[i],sub);
   }
   return cnt;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.precision(17);
    int t=1;
    // cin>>t;
    int found=0;
    int curr=p[0];
    cout<<"Password: ";
    while(found<22){
        int temp=solve(curr);
        found+=temp;
        curr-=temp;
    }

    for(auto t:mpp){
        rep(j,0,t.second){
            cout<<t.first;
        }
    }
    cout<<endl;
    return 0;
}
