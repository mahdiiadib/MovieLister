#pragma once

// 17.4.1.2 Headers
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

#include<conio.h>



/// Debugger
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
void faltu() { std::cerr<<std::endl; }
template<typename T>void faltu(T a[], int n) { for(int i=0; i<n; ++i)std::cerr<<a[i]<<' '; std::cerr<<std::endl; }
template<typename T, typename...hello>void faltu(T arg, const hello&...rest) { std::cerr<<arg<<' '; faltu(rest...); }
