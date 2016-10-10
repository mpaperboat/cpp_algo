#ifndef LONGEST_COMMON_PALINDROMIC_SUBSTRING
#define LONGEST_COMMON_PALINDROMIC_SUBSTRING
#include<bits/stdc++.h>
namespace CTL{
    using namespace std;
    struct LongestCommonPalindromicSubstring{
        struct node{
            node(int m,node*f,int l):nx(m),fa(f),ln(l){}
            vector<node*>nx;node*fa;complex<int>va;int ln;}*rt;
        int m;vector<int>st;vector<node*>ns;
        LongestCommonPalindromicSubstring(int _m):m(_m){
            node*n0=new node(m,0,-2),
                *n1=new node(m,n0,-1),*n2=new node(m,n1,0);
            ns.push_back(n0);ns.push_back(n1);ns.push_back(n2);
            fill(n0->nx.begin(),n0->nx.end(),n2);rt=n1;}
        ~LongestCommonPalindromicSubstring(){
            for(int i=0;i<ns.size();++i)delete ns[i];}
        node*find(node*x){
            while(x->fa&&st[st.size()-x->ln-2]!=st[st.size()-1])
                x=x->fa;
            return x;}
        node*insert(node*p,int c,complex<int>v){
            st.push_back(c);p=find(p);
            if(!p->nx[c]){
                node*np=(p->nx[c]=
                    new node(m,find(p->fa)->nx[c],p->ln+2));
                ns.push_back(np);}
            p->nx[c]->va+=v;
            return p->nx[c];}
        int run(int*a,int*b){
            node*p=rt;st=vector<int>(1,-1);
            for(int i=1;a[i]!=-1;++i)p=insert(p,a[i],1);
            p=rt;st=vector<int>(1,-1);
            for(int i=1;b[i]!=-1;++i)
                p=insert(p,b[i],complex<int>(0,1));
            for(int i=ns.size()-1;i>=1;--i)ns[i]->fa->va+=ns[i]->va;
            int r=0;for(int i=0;i<ns.size();++i)
                if(real(ns[i]->va)&&imag(ns[i]->va))
                    r=max(r,ns[i]->ln);
            return r;}};}
#endif