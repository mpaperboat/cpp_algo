typedef long long ll;
ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
ll egcd(ll a,ll b,ll&x,ll&y){
    if(!b){
        x=1;
        y=0;
        return a;
    }else{
        ll d=egcd(b,a%b,y,x);
        y-=a/b*x;
        return d;
    }
}