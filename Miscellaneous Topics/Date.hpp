#include<bits/stdc++.h>
using namespace std;
struct Date{
    int y,m,d,w;
    Date&operator++(){
        return*this=*this+1;
    }
    bool leap(int a)const{
        return a%400==0||(a%4==0&&a%100!=0);
    }
    int month_sum(int a,int b)const{
        if(b==0)
            return 0;
        if(b==1)
            return 31;
        return 59+leap(a)+30*(b-2)+(b+1)/2-1+(b>=8&&b%2==0);
    }
    string month_name(int a)const{
        if(a==1)
            return"January";
        if(a==2)
            return"February";
        if(a==3)
            return"March";
        if(a==4)
            return"April";
        if(a==5)
            return"May";
        if(a==6)
            return"June";
        if(a==7)
            return"July";
        if(a==8)
            return"August";
        if(a==9)
            return"September";
        if(a==10)
            return"October";
        if(a==11)
            return"November";
        if(a==12)
            return"December";
    }
    string day_name(int a)const{
        if(a==0)
            return"Sunday";
        if(a==1)
            return"Monday";
        if(a==2)
            return"Tuesday";
        if(a==3)
            return"Wednesday";
        if(a==4)
            return"Thursday";
        if(a==5)
            return"Friday";
        if(a==6)
            return"Saturday";
    }
    operator int()const{
        int t=(y-1)*365+(y-1)/4-(y-1)/100+(y-1)/400+month_sum(y,m-1)+d;
        if(y==1752&&m>=9&&d>2||y>1752)
            t-=11;
        t-=min(y-1,1700)/400-min(y-1,1700)/100;
        if(y<=1700&&y%400!=0&&y%100==0&&m>2)
            ++t;
        return t;
    }
    Date(int _y,int _m,int _d):
        y(_y),m(_m),d(_d),w((int(*this)+5)%7){
    }
    Date(int a){
        int yl=0,yr=1e7;
        while(yl+1<yr){
            int ym=(yl+yr)/2;
            if(int(Date(ym,12,31))<a)
                yl=ym;
            else
                yr=ym;
        }
        y=yr;
        int ml=0,mr=12;
        while(ml+1<mr){
            int mm=(ml+mr)/2,mt;
            if(mm==2){
                if(y<=1700)
                    mt=28+(y%4==0);
                else
                    mt=28+(y%4==0&&y%100!=0||y%400==0);
            }else if(mm<=7)
                mt=30+mm%2;
            else
                mt=31-mm%2;
            if(int(Date(y,mm,mt))<a)
                ml=mm;
            else
                mr=mm;
        }
        m=mr;
        for(int i=1;;++i){
            if(y==1752&&m==9&&i>2&&i<14)
                continue;
            if(int(Date(y,m,i))==a){
                d=i;
                break;
            }
        }
        w=(5+a)%7;
    }
    operator string()const{
        stringstream s;
        string t;
        s<<day_name(w)+", "+month_name(m)+" "<<d<<", "<<y;
        getline(s,t);
        return t;
    }
};
ostream&operator<<(ostream&s,const Date&a){
    return s<<string(a);
}
int operator-(const Date&a,const Date&b){
    return int(a)-int(b);
}
Date operator+(const Date&a,int b){
    return Date(int(a)+b);
}
Date operator-(const Date&a,int b){
    return Date(int(a)-b);
}
bool operator<(const Date&a,const Date&b){
    if(a.y==b.y&&a.m==b.m)
        return a.d<b.d;
    if(a.y==b.y)
        return a.m<b.m;
    return a.y<b.y;
}
bool operator>(const Date&a,const Date&b){
    return b<a;
}
bool operator!=(const Date&a,const Date&b){
    return a.y!=b.y||a.m!=b.m||a.d!=b.d;
}
bool operator==(const Date&a,const Date&b){
    return !(a!=b);
}
