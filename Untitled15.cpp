#include<iostream>
<sstream>
 using namespace std;bool f(string&s){if(s.empty()||!isalpha(s[0])&&s[0]!='_')return false;for(char c:s)if(!isalnum(c)&&c!='_')return false;return true;}int c(string&l){stringstream ss(l);int n=0;string w;while(ss>>w)if(f(w))n++;return n;}int main(){string l;while(getline(cin,l))cout<<c(l)<<endl;return 0;}

