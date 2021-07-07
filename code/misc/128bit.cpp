__int128 input(){
    string s;
    cin >> s;
    int fst = (s[0] == '-') ? 1 : 0;
    __int128 v = 0;
    for(int i = fst ; i < s.size() ; ++i)
        v = v * 10 + s[i] - '0';
    if(fst) v = -v;
    return v;
}

ostream& operator << (ostream& os,const __int128& v) {
    string ret, sgn;
    __int128 n = v;
    if(v < 0) sgn = "-", n = -v;
    while(n) ret.push_back(n % 10 + '0'), n /= 10;
    reverse(ret.begin(), ret.end());
    ret = sgn + ret;
    os << ret;
    return os;
}

int main(){
    __int128 n = input();
    cout << n << endl;
}
