#include<bits/stdc++.h>
using namespace std;
struct Integer operator+(Integer a,Integer b);
Integer operator+(Integer a,int b);
Integer operator-(Integer a,Integer b);
Integer operator*(Integer a,Integer b);
Integer operator*(Integer a,Integer b);
Integer operator/(Integer a,Integer b);
Integer operator%(Integer a,Integer b);
Integer operator%(Integer a,int b);
Integer operator%(Integer a,long long b);
bool operator!=(Integer a,int b);
bool operator<=(Integer a,int b);
struct Integer{
    operator bool(){
        return *this!=0;
    }
    Integer(long long a=0){
        if(a<0){
            s=-1;
            a=-a;
        }else
            s=a!=0;
        do{
            d.push_back(a%B);
            a/=B;
        }while(a);
    }
    Integer(string a){
        s=(a[0]=='-')?-1:(a!="0");
        for(int i=a.size()-1;i>=(a[0]=='-');i-=L){
            int t=0,j=max(i-L+1,int(a[0]=='-'));
            for(int k=j;k<=i;++k)
                t=t*10+a[k]-'0';
            d.push_back(t);
        }
    }
    Integer(const Integer&a){
        d=a.d;
        s=a.s;
    }
    Integer&operator=(long long a){
        return*this=Integer(a);
    }
    Integer&operator+=(Integer a){
        return*this=*this+a;
    }
    Integer&operator-=(Integer a){
        return*this=*this-a;
    }
    Integer&operator*=(Integer a){
        return*this=*this*a;
    }
    Integer&operator/=(Integer a){
        return*this=*this/a;
    }
    Integer&operator%=(Integer a){
        return*this=*this%a;
    }
    Integer&operator++(){
        return*this=*this+1;
    }
    operator string()const{
        string r;
        for(int i=0;i<d.size();++i){
            stringstream ts;
            ts<<d[i];
            string tt;
            ts>>tt;
            reverse(tt.begin(),tt.end());
            while(i+1!=d.size()&&tt.size()<L)
                tt.push_back('0');
            r+=tt;
        }
        reverse(r.begin(),r.end());
        return r;
    }
    int s;
    vector<int>d;
    static const int B=1e8,L=8;
};
string str(const Integer&a){
    return string(a);
}
bool operator<(Integer a,Integer b){
    if(a.s!=b.s)
        return a.s<b.s;
    if(a.d.size()!=b.d.size())
        return (a.s!=1)^(a.d.size()<b.d.size());
    for(int i=a.d.size()-1;i>=0;--i)
        if(a.d[i]!=b.d[i])
            return (a.s!=1)^(a.d[i]<b.d[i]);
    return false;
}
bool operator>(Integer a,Integer b){
    return b<a;
}
bool operator<=(Integer a,Integer b){
    return !(a>b);
}
bool operator>=(Integer a,Integer b){
    return !(a<b);
}
bool operator==(Integer a,Integer b){
    return !(a<b)&&!(a>b);
}
bool operator!=(Integer a,Integer b){
    return !(a==b);
}
istream&operator>>(istream&s,Integer&a){
    string t;
    s>>t;
    a=Integer(t);
    return s;
}
ostream&operator<<(ostream&s,Integer a){
    if(a.s==-1)
        s<<'-';
    for(int i=a.d.size()-1;i>=0;--i){
        if(i!=a.d.size()-1)
            s<<setw(Integer::L)<<setfill('0');
        s<<a.d[i];
    }
    s<<setw(0)<<setfill(' ');
    return s;
}
void dzero(Integer&a){
    while(a.d.size()>1&&a.d.back()==0)
        a.d.pop_back();
}
Integer operator-(Integer a){
    a.s*=-1;
    if(a.d.size()==1&&a.d[0]==0)
        a.s=1;
    return a;
}
Integer operator+(Integer a,int b){
    return a+Integer(b);
}
Integer operator*(Integer a,int b){
    return a*Integer(b);
}
Integer operator%(Integer a,int b){
    return a%Integer(b);
}
Integer operator%(Integer a,long long b){
    return a%Integer(b);
}
bool operator!=(Integer a,int b){
    return a!=Integer(b);
}
bool operator<=(Integer a,int b){
    return a<=Integer(b);
}
Integer operator+(Integer a,Integer b){
    if(a.s*b.s!=-1){
        Integer c;c.s=a.s?a.s:b.s;
        c.d.resize(max(a.d.size(),b.d.size())+1);
        for(int i=0;i<c.d.size()-1;++i){
            if(i<a.d.size())
                c.d[i]+=a.d[i];
            if(i<b.d.size())
                c.d[i]+=b.d[i];
            if(c.d[i]>=Integer::B){
                c.d[i]-=Integer::B;
                ++c.d[i+1];
            }
        }
        dzero(c);
        return c;
    }
    return a-(-b);
}
Integer operator-(Integer a,Integer b){
    if(a.s*b.s==1){
        if(a.s==-1)
            return (-b)-(-a);
        if(a<b)
            return -(b-a);
        if(a==b)
            return 0;
        for(int i=0;i<b.d.size();++i){
            a.d[i]-=b.d[i];
            if(a.d[i]<0){
                a.d[i]+=Integer::B;
                --a.d[i+1];
            }
        }
        dzero(a);
        return a;
    }
    return a+(-b);
}
Integer operator*(Integer a,Integer b){
    vector<long long>t(a.d.size()+b.d.size());
    for(int i=0;i<a.d.size();++i)
        for(int j=0;j<b.d.size();++j)
            t[i+j]+=(long long)a.d[i]*b.d[j];
    for(int i=0;i<t.size()-1;++i){
        t[i+1]+=t[i]/Integer::B;
        t[i]%=Integer::B;
    }
    Integer c;
    c.s=a.s*b.s;c.d.resize(t.size());
    copy(t.begin(),t.end(),c.d.begin());
    dzero(c);
    return c;
}
Integer div2(Integer a){
    for(int i=a.d.size()-1;i>=0;--i){
        if(i)
            a.d[i-1]+=(a.d[i]&1)*Integer::B;
        a.d[i]>>=1;
    }
    dzero(a);
    if(a.d.size()==1&&a.d[0]==0)
        a.s=0;
    return a;
}
Integer operator/(Integer a,Integer b){
    if(!a.s)
        return 0;
    if(a.s<0)
        return-((-a)/b);
    if(a<b)
        return 0;
    Integer l=1,r=1;
    while(r*b<=a)
        r=r*2;
    while(l+1<r){
        Integer m=div2(l+r);
        if(m*b>a)
            r=m;
        else
            l=m;
    }
    return l;
}
Integer operator%(Integer a,Integer b){
    return a-a/b*b;
}
Integer gcd(Integer a,Integer b){
    Integer r=1;
    while(a!=0&&b!=0){
        if(!(a.d[0]&1)&&!(b.d[0]&1)){
            a=div2(a);
            b=div2(b);
            r=r*2;
        }else if(!(a.d[0]&1))
            a=div2(a);
        else if(!(b.d[0]&1))
            b=div2(b);
        else{
            if(a<b)
                swap(a,b);
            a=div2(a-b);
        }
    }
    if(a!=0)
        return r*a;
    return r*b;
}
int length(Integer a){
    a.s=1;
    return string(a).size();
}
int len(Integer a){
    return length(a);
}
