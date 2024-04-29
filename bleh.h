/*─────────▄▄▄▄▄▄▄▄▄▄▄▄▄
────────▄▀▀─────────────▀▀▄
───────█───────────────────█
──────█─────────────────────█
─────█───▄▄▄▄▄▄▄───▄▄▄▄▄▄▄───█
────█───█████████─█████████───█
────█──██▀────▀█████▀────▀██──█
───██████───█▀█─███───█▀█─██████
───██████───▀▀▀─███───▀▀▀─██████
────█──▀█▄────▄██─██▄────▄█▀──█
────█────▀█████▀───▀█████▀────█
────█───────────────▄▄▄───────█
────█───────▄▄▄▄██▀▀█▀▀█▄─────█
────█─────▄██▄█▄▄█▄▄█▄▄██▄────█
────█─────▀▀█████████████▀────█
───▐▓▓▌─────────────────────▐▓▓▌
───▐▐▓▓▌▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▐▓▓▌▌
───█══▐▓▄▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▄▓▌══█
──█══▌═▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▌═▐══█
──█══█═▐▓▓▓▓▓▓▄▄▄▄▄▄▄▓▓▓▓▓▓▌═█══█
──█══█═▐▓▓▓▓▓▓▐██▀██▌▓▓▓▓▓▓▌═█══█
──█══█═▐▓▓▓▓▓▓▓▀▀▀▀▀▓▓▓▓▓▓▓▌═█══█
──█───█─█──█─█▀▀█─▀▀█▀▀───▀█─█─▀█──
──█▄█▄█─█▀▀█─█▄▄█───█─────█▀─▀─█▀──
───▀─▀──▀──▀─▀──▀───▀─────▄──▄─▄───*/

///In the name of ALLAH
#pragma once

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;


/*
#include <cassert>

#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cuchar>
#include <cwchar>
#include <cwctype>

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

#include <shared_mutex>

#include <charconv>
#include <filesystem>

#include <intrin.h>
*/


/*
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstring>
#include<string>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<stack>
#include<queue>
#include<deque>
#include<numeric>
#include<bitset>
#include<chrono>
*/


/*
///debug
template<typename F, typename S>std::ostream& operator<<(std::ostream& os, const std::pair<F, S>& p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T>std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) { os<<"{"; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin())os<<", "; os<<*it; } return os<<"}"; }
template<typename T>std::ostream& operator<<(std::ostream& os, const std::set<T>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin())os<<","; os<<*it; } return os<<"]"; }
template<typename T>std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin())os<<","; os<<*it; } return os<<"]"; }
template<typename T>std::ostream& operator<<(std::ostream& os, const std::multiset<T>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin())os<<", "; os<<*it; } return os<<"]"; }
template<typename T>std::ostream& operator<<(std::ostream& os, const std::unordered_multiset<T>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin())os<<", "; os<<*it; } return os<<"]"; }
template<typename F, typename S>std::ostream& operator<<(std::ostream& os, const std::map<F, S>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin())os<<", "; os<<it->first<<" = "<<it->second; } return os<<"]"; }
template<typename F, typename S>std::ostream& operator<<(std::ostream& os, const std::unordered_map<F, S>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin())os<<", "; os<<it->first<<" = "<<it->second; } return os<<"]"; }
template<typename F, typename S>std::ostream& operator<<(std::ostream& os, const std::multimap<F, S>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<it->first<<" = "<<it->second; } return os<<"]"; }
template<typename F, typename S>std::ostream& operator<<(std::ostream& os, const std::unordered_multimap<F, S>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<it->first<<" = "<<it->second; } return os<<"]"; }
template<typename T>std::ostream& operator<<(std::ostream& os, std::stack<T> stk) { os<<"|"; while(!stk.empty()) os<<stk.top()<<", ", stk.pop(); return os<<"\b\b |"; }
template<typename T>std::ostream& operator<<(std::ostream& os, std::queue<T> q) { os<<"|"; while(!q.empty()) os<<q.front()<<", ", q.pop(); return os<<"\b\b |"; }
template<typename T>std::ostream& operator<<(std::ostream& os, std::deque<T> dq) { os<<"|"; while(!dq.empty()) os<<dq.front()<<", ", dq.pop_front(); return os<<"\b\b |"; }
template<typename T, typename V=void, typename cmp=void>std::ostream& operator<<(std::ostream& os, std::priority_queue<T, V, cmp> pq) { os<<"|"; while(!pq.empty()) os<<pq.top()<<", ", pq.pop(); return os<<"\b\b |"; }

#define dbg(...) do { std::cerr << #__VA_ARGS__ << " : "; faltu(__VA_ARGS__); } while(0)
//#define dbg(args...) do {std::cerr << #args << " : "; faltu(args); } while(0) //GCC only
void faltu() { std::cerr<<std::endl; }
template<typename T>void faltu(T a[], int n) { for(int i=0; i<n; ++i)std::cerr<<a[i]<<' '; std::cerr<<std::endl; }
template<typename T, typename...hello>void faltu(T arg, const hello&...rest) { std::cerr<<arg<<' '; faltu(rest...); }

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template<typename F, typename cmp>std::ostream& operator<<(std::ostream& os, const __gnu_pbds::tree<F, __gnu_pbds::null_type, cmp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<*it; } return os<<"]"; }
template<typename F, typename S, typename cmp>std::ostream& operator<<(std::ostream& os, const __gnu_pbds::tree<F, S, cmp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>& v) { os<<"["; for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<it->first<<" = "<<it->second; } return os<<"]"; }
*/

/// Debugger _Muhammad
template < typename F, typename S >
ostream& operator << (ostream& os, const pair< F, S >& p)
{
	return os<<"("<<p.first<<", "<<p.second<<")";
}
template < typename T >
ostream& operator << (ostream& os, const vector< T >& v)
{
	os<<"{";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<*it; }
	return os<<"}";
}
template < typename T >
ostream& operator << (ostream& os, const set< T >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<*it; }
	return os<<"]";
}
template < typename T >
ostream& operator << (ostream& os, const unordered_set< T >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<*it; }
	return os<<"]";
}
template < typename T >
ostream& operator << (ostream& os, const multiset< T >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<*it; }
	return os<<"]";
}
template < typename T >
ostream& operator << (ostream& os, const unordered_multiset< T >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<*it; }
	return os<<"]";
}
template < typename F, typename S >
ostream& operator << (ostream& os, const map< F, S >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<it->first<<" = "<<it->second; }
	return os<<"]";
}
template < typename F, typename S >
ostream& operator << (ostream& os, const unordered_map< F, S >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<it->first<<" = "<<it->second; }
	return os<<"]";
}
template < typename F, typename S >
ostream& operator << (ostream& os, const multimap< F, S >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<it->first<<" = "<<it->second; }
	return os<<"]";
}
template < typename F, typename S >
ostream& operator << (ostream& os, const unordered_multimap< F, S >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<it->first<<" = "<<it->second; }
	return os<<"]";
}
template < typename T >
ostream& operator << (ostream& os, stack< T > stk)
{
	os<<"|";
	while(!stk.empty()) os<<stk.top()<<", ", stk.pop();
	return os<<"\b\b |";
}
template < typename T >
ostream& operator << (ostream& os, queue< T > q)
{
	os<<"|";
	while(!q.empty()) os<<q.front()<<", ", q.pop();
	return os<<"\b\b |";
}
template < typename T >
ostream& operator << (ostream& os, deque< T > dq)
{
	os<<"|";
	while(!dq.empty()) os<<dq.front()<<", ", dq.pop_front();
	return os<<"\b\b |";
}
template < typename T, typename V=void, typename cmp=void >
std::ostream& operator << (std::ostream& os, std::priority_queue< T, V, cmp > pq)
{ 
	os<<"|";
	while(!pq.empty()) os<<pq.top()<<", ", pq.pop();
	return os<<"\b\b |";
}
////////////////////////////////TREE////////////////////////////////////
template < typename F, typename S, typename cmp >
ostream& operator << (ostream& os, const tree< F, S, cmp, rb_tree_tag, tree_order_statistics_node_update >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<it->first<<" = "<<it->second; }
	return os<<"]";
}
template < typename F, typename cmp >
ostream& operator << (ostream& os, const tree< F, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update >& v)
{
	os<<"[";
	for(auto it=v.begin(); it!=v.end(); ++it) { if(it!=v.begin()) os<<", "; os<<*it; }
	return os<<"]";
}
////////////////////////////////TREE////////////////////////////////////
#define dbg(...) do { std::cerr << #__VA_ARGS__ << " : "; faltu(__VA_ARGS__); } while(0)
//#define dbg(args...) do {std::cerr << #args << " : "; faltu(args); } while(0) //GCC only
void faltu() { cerr<<endl; }
template <typename T>
void faltu(T a[], int n) { for(int i=0; i<n; ++i) cerr<<a[i]<<' '; cerr<<endl; }
template <typename T, typename ... hello>
void faltu(T arg, const hello &... rest) { cerr<<arg<<' ', faltu(rest...); }


/*

typedef long long LL;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef double dl;

#define PB push_back
#define F first
#define S second
#define MP make_pair
#define endl '\n'
#define all(a) (a).begin(),(a).end()
#define sz(x) (int)x.size()
#define rep(x,start,end) for(auto x=(start)-((start)>(end));x!=(end)-((start)>(end));((start)<(end)?x++:x--))
#define mid(l,r) (l+((r-l)/2))
#define left(node) (node*2)
#define right(node) (node*2+1)
#define mx_int_prime 999999937
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

const double PI=acos(-1);
const double eps=1e-12;
const int inf=2000000000;
const ll infLL=9000000000000000000;
#define MOD 1000000007

#define mem(a,b) memset(a, b, sizeof(a) )
#define sqr(a) ((a) * (a))

#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin.exceptions(ios::badbit|ios::failbit);
#define fraction(a) cout.unsetf(ios::floatfield), cout.precision(a), cout.setf(ios::fixed,ios::floatfield);
#define file() freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
#define START() auto start=chrono::high_resolution_clock::now();
#define END auto end=chrono::high_resolution_clock::now(); chrono::duration<double>ets=end-start; cerr<<"\nElapsed time: "<<ets.count()*1e3<<" ms\n"

typedef vector<int>::iterator vit;
typedef set<int>::iterator sit;

int dx[]={0, 0, +1, -1};
int dy[]={+1, -1, 0, 0};
//int dx[] = {+1, 0, -1, 0, +1, +1, -1, -1};
//int dy[] = {0, +1, 0, -1, +1, -1, +1, -1};


int Set(int N,int pos){return N=N | (1<<pos);}
int reset(int N,int pos){return N= N & ~(1<<pos);}
bool check(int N,int pos){return (bool)(N & (1<<pos));}


///Modular Arithmetic
inline void normal(LL& a) { a%=MOD; (a<0)&&(a+=MOD); }
inline LL modMul(LL a, LL b) { a%=MOD, b%=MOD; normal(a), normal(b); return (a*b)%MOD; }
inline LL modAdd(LL a, LL b) { a%=MOD, b%=MOD; normal(a), normal(b); return (a+b)%MOD; }
inline LL modSub(LL a, LL b) { a%=MOD, b%=MOD; normal(a), normal(b); a-=b; normal(a); return a; }
inline LL modPow(LL b, LL p) { LL r=1; while(p) { if(p&1) r=modMul(r, b); b=modMul(b, b); p>>=1; } return r; }
inline LL modInverse(LL a) { return modPow(a, MOD-2); }
inline LL modDiv(LL a, LL b) { return modMul(a, modInverse(b)); }

*/



/* *************************GNU ONLY!************************* //

// #include <ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class K, class M, class cmp_fn=less<>> using Tree=tree<K, M, cmp_fn, rb_tree_tag, tree_order_statistics_node_update>;
	/// cout<<*X.find_by_order(k)<<endl; // iterator to the k-th element
	/// cout<<X.order_of_key(item)<<endl;  // number of items in a set that are strictly smaller than our item
/// #define gcd(a, b) __gcd(a, b)
/// #define lcm(a, b) a*(b/__gcd(a, b))

// *********************************************************** */