#include<bits/stdc++.h>
using namespace std;
struct FastWriter{
    FILE*f;
    vector<char>p;
    FastWriter(FILE*_f):
        f(_f){
    }
    FastWriter(string _f):
        f(fopen(_f.c_str(),"w")){
    }
    ~FastWriter(){
        if(p.size())
            fwrite(&p[0],1,p.size(),f);
        fclose(f);
    }
    FastWriter&operator<<(char a){
        p.push_back(a);
        return*this;
    }
    FastWriter&operator<<(const char*a){
        while(*a)
            p.push_back(*a++);
        return*this;
    }
    template<class T>FastWriter&operator<<(T a){
        if(a<0)
            p.push_back('-'),a=-a;
        static char t[19];
        char*q=t;
        do{
            T b=a/10;
            *q++=a-b*10+'0',a=b;
        }while(a);
        while(q>t)
            p.push_back(*--q);
        return*this;
    }
};
