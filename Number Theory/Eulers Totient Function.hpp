#ifndef EULERS_TOTIENT_FUNCTION
#define EULERS_TOTIENT_FUNCTION
#include<bits/stdc++.h>
namespace CTL{
    using namespace std;
    namespace EulersTotientFunction{
        vector<int>run(int n){
            vector<int>p,ntp(n+1),u(n+1);ntp[1]=1;u[1]=1;
            for(int i=2;i<=n;++i){
                if(!ntp[i])p.push_back(i),u[i]=i-1;
                for(int j=0;j<p.size()&&p[j]*i<=n;++j){
                    ntp[p[j]*i]=1;
                    if(i%p[j]==0){u[p[j]*i]=u[i]*p[j];break;}
                    else u[p[j]*i]=u[i]*(p[j]-1);}}
            return u;}}}
#endif