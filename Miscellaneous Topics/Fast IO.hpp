#include<bits/stdc++.h>
using namespace std;
struct FastReader{
    FILE*f;
    char*p,*e;
    vector<char>v;
    void ipt(){
        for(int i=1,t;;i<<=1){
            v.resize(v.size()+i);
            if(i!=(t=fread(&v[0]+v.size()-i,1,i,f))){
                p=&v[0],e=p+v.size()-i+t;
                break;
            }
        }
    }
    void ign(){
        while(p!=e&&isspace(*p))
            ++p;
    }
    int isc(){
        return p!=e&&!isspace(*p);
    }
    int isd(){
        return p!=e&&isdigit(*p);
    }
    FastReader(FILE*_f):
        f(_f){
        ipt();
    }
    FastReader(string _f):
        f(fopen(_f.c_str(),"r")){
        ipt();
    }
    ~FastReader(){
        fclose(f);
    }
    template<class T>FastReader&operator>>(T&a){
        int n=1;
        ign();
        if(*p=='-')
            n=-1,++p;
        for(a=0;isd();)
            a=a*10+*p++-'0';
        a*=n;
        return*this;
    }
    FastReader&operator>>(char&a){
        ign();
        a=*p++;
        return*this;
    }
    FastReader&operator>>(char*a){
        for(ign();isc();)
            *a++=*p++;
        *a=0;
        return*this;
    }
    char get(){
        return*p++;
    }
};
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
