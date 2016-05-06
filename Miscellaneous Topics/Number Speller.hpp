#include<bits/stdc++.h>
using namespace std;
namespace NumberSpeller{
    template<class T>string run(T a){
        map<T,string>m;
        m[0]="zero";
        m[1]="one";
        m[2]="two";
        m[3]="three";
        m[4]="four";
        m[5]="five";
        m[6]="six";
        m[7]="seven";
        m[8]="eight";
        m[9]="nine";
        m[10]="ten";
        m[11]="eleven";
        m[12]="twelve";
        m[13]="thirteen";
        m[14]="fourteen";
        m[15]="fifteen";
        m[16]="sixteen";
        m[17]="seventeen";
        m[18]="eighteen";
        m[19]="nineteen";
        m[20]="twenty";
        m[30]="thirty";
        m[40]="forty";
        m[50]="fifty";
        m[60]="sixty";
        m[70]="seventy";
        m[80]="eighty";
        m[90]="ninety";
        if(a<0)
            return"minus "+run(-a);
        if(m.count(a))
            return m[a];
        if(a<100)
            return run(a/10*10)+"-"+run(a%10);
        if(a<1000&&a%100==0)
            return run(a/100)+" hundred";
        if(a<1000)
            return run(a/100*100)+" and "+run(a%100);
        vector<string>t;
        t.push_back("thousand");
        t.push_back("million");
        t.push_back("billion");
        t.push_back("trillion");
        t.push_back("quadrillion");
        t.push_back("quintillion");
        t.push_back("sextillion");
        t.push_back("septillion");
        t.push_back("octillion");
        t.push_back("nonillion");
        t.push_back("decillion");
        t.push_back("undecillion");
        t.push_back("duodecillion");
        t.push_back("tredecillion");
        t.push_back("quattuordecillion");
        t.push_back("quindecillion");
        string r=a%1000?run(a%1000):"";
        a/=1000;
        for(int i=0;a;++i,a/=1000)
            if(a%1000){
                if(!i&&r.find("and")==string::npos&&r.find("hundred")==string::npos&&r.size())
                    r=run(a%1000)+" "+t[i]+" and "+r;
                else
                    r=run(a%1000)+" "+t[i]+(r.size()?", ":"")+r;
            }
        return r;
    }
}
