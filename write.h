//template igorjan94 version from 17 November 2014
#include <bits/stdc++.h>
#define DOUBLEFORMAT "%f"

template <class Head, class... Tail> inline void writeln(Head head, Tail... tail);
template <class Head, class... Tail> inline void writeln2(Head head, Tail... tail);
template <class Head, class... Tail> inline void readln(Head& head, Tail&... tail);
template <class Head, class... Tail> inline void read(Head& head, Tail&... tail);
template <class Head, class... Tail> inline void print(Head& head, Tail&... tail);
template <class Type1, class Type2>  inline void print(std::pair<Type1, Type2>& p);
template <class Type1, class Type2>  inline void print_no_space(std::pair<Type1, Type2>& p);
template <class Head, class... Tail> inline void print_no_space(Head& head, Tail&... tail);
void inline writeln(){printf("\n");}void inline writeln2(){printf("\n");}void inline readln(){}

inline void print(double a){printf(" " DOUBLEFORMAT,a);}
inline void print(int a){printf(" %d",a);}
inline void print(std::string a){printf(" %s",a.c_str());}
inline void print(long long a){printf(" %lld",a);}
inline void print(unsigned long a){printf(" %ld",a);}
inline void print(unsigned int a){printf(" %d",a);}
inline void print(char a){printf(" %c",a);}
inline void print_no_space(double a){printf(DOUBLEFORMAT, a);}
inline void print_no_space(int a){printf("%d", a);}
inline void print_no_space(std::string a){printf("%s", a.c_str());}
inline void print_no_space(long long a){printf("%lld", a);}
inline void print_no_space(unsigned long a){printf("%ld", a);}
inline void print_no_space(unsigned int a){printf("%d", a);}
inline void print_no_space(char a){printf("%c", a);}

template<class Type> inline void print(std::vector<Type>& a){for(int i=0;i<a.size();++i)print(a[i]);}
template<class Type> inline void print(std::vector<std::vector<Type> >& a){if(a.size())(a.size()==1)?print(a[0]):writeln2(a[0]);for(int i=1;i<a.size()-1;++i)writeln2(a[i]);if(a.size()>=2)print_no_space(a.back());}
template<class Type> inline void print_no_space(std::vector<Type>& a){if(a.size())print_no_space(a[0]);for(int i=1;i<a.size();++i)print(a[i]);}
template<class Type> inline void print_no_space(std::vector<std::vector<Type> >&a){for(int i=0;i<a.size()-1;++i)writeln(a[i]);if(a.size())print_no_space(a.back());}

template<class Type1, class Type2> inline void print_no_space(std::pair<Type1, Type2>&a){print_no_space(a.first); writeln2(a.second);}
template<class Type1, class Type2> inline void print(std::pair<Type1, Type2>& a)        {print_no_space(a.first); writeln2(a.second);}

template <class Head, class... Tail> inline void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
template <class Head, class... Tail> inline void writeln(Head head, Tail... tail){print_no_space(head);writeln2(tail...);}

inline void read(double &a){scanf("%lf",&a);}
inline void read(int &a){scanf("%d",&a);}
inline void read(std::string &a){std::cin>>a;}
inline void read(long long &a){scanf("%lld",&a);}
inline void read(char &a){scanf("%c",&a);}
template<class Type1, class Type2> inline void read(std::pair<Type1, Type2>&a){readln(a.first, a.second);}
template<class Type> inline void read(std::vector<Type> &a){if(a.size()==0){int n;read(n);a.resize(n);}for(int i=0;i<a.size();++i)readln(a[i]);}
template <class Head,class... Tail> inline void readln(Head& head,Tail&... tail){read(head);readln(tail...);}
