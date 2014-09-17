#include <bits/stdc++.h>
#include <curl/curl.h>
#include <unistd.h>
#include <json/json.h>
#include <libnotifymm.h>
#include <cstdlib>

#define AUTO_REFRESH 5

#define pb push_back
#define ll long long
#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define forn(i, n) for (int i = 0; i < n; ++i)
#define forn1(i, n) for (int i = 1; i < n; ++i)
#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define ROF(i, m, n) for (int i = m; i >= n; --i)
#define fori(n) for (int i = 0; i < n; ++i)
#define forj(n) for (int j = 0; j < n; ++j)
#define fori1(n) for (int i = 1; i < n; ++i)
#define forj1(n) for (int j = 1; j < n; ++j)
#define vi vector<int>
#define vvi vector<vector<int> >
#define vll vector<long long>
#define pii pair<int, int>
#define whole(a) a.begin(), a.end()

#ifndef ONLINE_JUDGE
#define lld I64d
#endif

#define FILENAME "input"
#define INF 1000000007
#define DOUBLEFORMAT "%f"

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void writeln2(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void writeln2(){printf("\n");}void readln(){}

///----------------------------------------------------------------------------------------------------------------------------

int n, m, k;
vi a;
string buffer;

size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream)
{           
    buffer.append((char*)ptr, size*nmemb);
    return size*nmemb; 
}       

void notify(string s, string t)
{
    Notify::Notification message(s, t, "dialog-information");
    message.set_timeout(Notify::EXPIRES_NEVER);
    message.show();
}

string itoa(int i)
{
    string s = "1";
    s[0] = i + 48;
    return s;
}

void run()
{
    Notify::init("init");
    string url = "https://api.vk.com/method/wall.get?owner_id=-29253653&count=5&v=5.24&access_token=83899af71a7ca0503e3faa5ec56eb60aefd5f44371a3f59dff22debbe817bc169dac953bbeb345a925ea6";
    string get = "https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=12&response_type=token";
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    int counter = 0;
    vector< pair<string, int> > pairs, temp;
    writeln("all inits done");//------------------------------------------
    while (++counter < 10)
    {
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url.data()); 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
        res = curl_easy_perform(curl);
        writeln("got data from server");//---------------------------
        curl_easy_cleanup(curl);
        Json::Value root;   
        Json::Reader reader;
        bool parsingSuccessful = reader.parse( buffer, root );
        if ( !parsingSuccessful )
            std::cout  << "Failed to parse configuration\n" << reader.getFormatedErrorMessages();
        const Json::Value items = root["response"]["items"];
        fori(items.size())
        {
            Json::Value text = items[i]["text"];
            Json::Value comments = items[i]["comments"]["count"];
            ((counter == 1) ? pairs : temp).pb({text.asString(), comments.asInt()});
        }
        if (counter == 1)
            fori(pairs.size())
            {
                notify("Message", pairs[i].first + " (" + itoa(pairs[i].second) + ")");
                writeln(pairs[i]);//-------------------------------
            }
        else
        {
            if (pairs[0].first != temp[0].first)
            {    
                notify("New massage", temp[0].first);
                fori(temp.size())
                    pairs[i] = temp[i];
            }
            else
            {
                fori(pairs.size())
                    if (pairs[i].second != temp[i].second)
                        notify("New comment", temp[i].first),
                        pairs[i].second = temp[i].second;
            }
        }
        temp.clear();
        buffer.clear();
        sleep(AUTO_REFRESH);
    }
    curl_global_cleanup();
}

int main()
{
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
    return 0;
}

























void print(double a){printf(" " DOUBLEFORMAT,a);}
void print(int a){printf(" %d",a);}
void print(string a){printf(" %s",a.c_str());}
void print(long long a){printf(" %lld",a);}
void print(unsigned long a){printf(" %ld",a);}
void print(unsigned int a){printf(" %d",a);}
void print(char a){printf(" %c",a);}
void print_no_space(double a){printf(DOUBLEFORMAT, a);}
void print_no_space(int a){printf("%d", a);}
void print_no_space(string a){printf("%s", a.c_str());}
void print_no_space(long long a){printf("%lld", a);}
void print_no_space(unsigned long a){printf("%ld", a);}
void print_no_space(unsigned int a){printf("%d", a);}
void print_no_space(char a){printf("%c", a);}

template<class Type>
void print_no_space(vector<Type>& a);
template<class Type>
void print(vector<Type>& a){for(int i=0;i<a.size();++i)print(a[i]);}
template<class Type>
void print(vector<vector<Type> >& a){if(a.size())(a.size()==1)?print(a[0]):writeln2(a[0]);for(int i=1;i<a.size()-1;++i)writeln2(a[i]);if(a.size()>=2)print_no_space(a.back());}
template<class Type1, class Type2>
void print(pair<Type1, Type2>& a){print(a.first);print(a.second);}

template<class Type>
void print_no_space(vector<Type>& a){if(a.size())print_no_space(a[0]);for(int i=1;i<a.size();++i)print(a[i]);}
template<class Type>
void print_no_space(vector<vector<Type> >&a){for(int i=0;i<a.size()-1;++i)writeln(a[i]);if(a.size())print_no_space(a.back());}
template<class Type1, class Type2>
void print_no_space(pair<Type1, Type2>&a){print_no_space(a.first);print(a.second);}
template <class Head, class... Tail>
void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
template <class Head, class... Tail>
void writeln(Head head, Tail... tail){print_no_space(head);writeln2(tail...);}

void read(double &a){scanf("%lf",&a);}
void read(int &a){scanf("%d",&a);}
void read(string &a){cin>>a;}
void read(long long &a){scanf("%lld",&a);}
void read(char &a){scanf("%c",&a);}
template<class Type1, class Type2>
void read(pair<Type1, Type2>&a){readln(a.first, a.second);}
template<class Type>
void read(vector<Type> &a){if(a.size()==0){int n;read(n);a.resize(n);}for(int i=0;i<a.size();++i)readln(a[i]);}
template <class Head,class... Tail>
void readln(Head& head,Tail&... tail){read(head);readln(tail...);}
