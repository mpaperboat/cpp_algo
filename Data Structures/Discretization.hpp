#ifndef DISCRETIZATION
#define DISCRETIZATION
#include<bits/stdc++.h>
namespace CTL{
    using namespace std;
    template<class T>struct Discretization{
        vector<T>a;
        void add(T v){a.push_back(v);}
        void build(){
            sort(begin(a),end(a));
            a.erase(unique(begin(a),end(a)),end(a));}
        int order(T v){
            return lower_bound(begin(a),end(a),v)-begin(a)+1;}
        int size(){return a.size();}
        T value(int v){return a[v-1];}};}
#endif