#ifndef EXPRESSION_EVALUATION
#define EXPRESSION_EVALUATION
#include<bits/stdc++.h>
namespace CTL{
    namespace ExpressionEvaluation{
        typedef long long T;
        T run(string exp){
            map<string,int>oid;map<int,int>pro,pri,dir;
            oid["("]=0;pro[0]=6;pri[0]=0;dir[0]=1;
            oid[")"]=1;pro[1]=1;pri[1]=0;dir[1]=0;
            oid["+'"]=2;pro[2]=5;pri[2]=5;dir[2]=1;
            oid["-'"]=3;pro[3]=5;pri[3]=5;dir[3]=1;
            oid["+"]=4;pro[4]=2;pri[4]=2;dir[4]=0;
            oid["-"]=5;pro[5]=2;pri[5]=2;dir[5]=0;
            oid["*"]=6;pro[6]=3;pri[6]=3;dir[6]=0;
            oid["/"]=7;pro[7]=3;pri[7]=3;dir[7]=0;
            oid["^"]=8;pro[8]=4;pri[8]=4;dir[8]=1;
            exp="("+exp+")";stack<T>vas;
            stack<int>ops;int lstnum=0;
            for(int i=0;i<exp.size();){
                while(i<exp.size()&&isspace(exp[i]))++i;
                if(i==exp.size())break;
                if(isdigit(exp[i])){
                    int j=i;
                    while(j+1<exp.size()&&
                        (isdigit(exp[j+1])||exp[j+1]=='.'))++j;
                    stringstream ss;T v;ss<<exp.substr(i,j-i+1);ss>>v;
                    vas.push(v);lstnum=1;i=j+1;
                }else{
                    string o(1,exp[i++]);
                    if((o[0]=='+'||o[0]=='-')&&!lstnum)
                        o+="'";int id=oid[o];
                    for(;ops.size()&&(pri[ops.top()]>pro[id]||
                        (pri[ops.top()]==pro[id]&&!dir[id]));){
                        int dop=ops.top();ops.pop();
                        if(dop==3){
                            T x=vas.top();vas.pop();
                            vas.push(-x);lstnum=1;
                        }else if(dop==4){
                            T y=vas.top();vas.pop();
                            T x=vas.top();vas.pop();
                            vas.push(x+y);lstnum=1;
                        }else if(dop==5){
                            T y=vas.top();vas.pop();
                            T x=vas.top();vas.pop();
                            vas.push(x-y);lstnum=1;
                        }else if(dop==6){
                            T y=vas.top();vas.pop();
                            T x=vas.top();vas.pop();
                            vas.push(x*y);lstnum=1;
                        }else if(dop==7){
                            T y=vas.top();vas.pop();
                            T x=vas.top();vas.pop();
                            if(!y)
                                return numeric_limits<T>::max();
                            vas.push(x/y);lstnum=1;
                        }else if(dop==8){
                            T y=vas.top();vas.pop();
                            T x=vas.top(),r=1;vas.pop();
                            if(x==0||x==1)y=1;if(x==-1)y%=2;
                            for(T t=1;t<=y;++t)
                                r*=x;vas.push(r);lstnum=1;}}
                    if(id!=1)ops.push(id),lstnum=0;
                    else if(ops.empty())
                        return numeric_limits<T>::max();
                    else ops.pop();}}
            return ops.size()?numeric_limits<T>::max():
                vas.top();}}}
#endif