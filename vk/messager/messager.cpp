#include <bits/stdc++.h>
#include <curl/curl.h>
#include <unistd.h>
#include <json/json.h>
#include <libnotifymm.h>
#include <cstdlib>
#include <exception>
#include <unistd.h>

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
string itoa(int i)
{
    string s;
    while (i >= 10)
        s.pb(i % 10 + 48),
        i /= 10;
    s.pb(i + 48);
    reverse(whole(s));
    return s;
}

string buffer;
CURL *curl;
CURLcode res;
Json::Value root, items;   
Json::Reader reader;
int countMessages = 10;
string key = "\
5fd6eba49abd5a1f94127f33803605a4660221181c8f36cdf84864e21d868982635d40ed62e95ff3407cf\
";
string get = "https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=wall,offline&response_type=token";
int user_id = 56524497;
string sendMessage = "https://api.vk.com/method/messages.send?user_id=" + itoa(user_id) + "&v=5.24&access_token=" + key + "&message=";
string getMessages = "https://api.vk.com/method/messages.getHistory?count=" + itoa(countMessages) + "&user_id=" + itoa(user_id) + "&v=5.24&access_token=" + key;
int counter = 0;

size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream)
{           
    buffer.append((char*)ptr, size*nmemb);
    return size*nmemb; 
}       

string replace(string t, char c, string to)
{
    string temp = "";
    fori(t.size())
        if (t[i] != c)
            temp.pb(t[i]);
        else
            temp.append(to);
    return temp;
}

Json::Value parse(string url)
{
    root.clear();
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.data()); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK)
        writeln("Error in curl");
    if (!reader.parse(buffer, root))
        writeln("Failed to parse configuration\n", reader.getFormatedErrorMessages());
    buffer.clear();
    return root;
}

void send(string s)
{
    parse(sendMessage + replace(replace(s, ' ', "%20"), '\n', "%0A"));
}

void toBackup(std::vector<string>& a)
{
    remove("messager.temp");
    ofstream out("messager.temp");
    fori(a.size())
        out << replace(a[i], '\n', "\3") << "\n";
    out.close();
}

void fromBackup(std::vector<string>& a)
{
    ifstream file("messager.data");
    string s;
    if (file)
        while (getline(file, s))
            a.pb(replace(s, '\3', "\n"));
    if (file)
        toBackup(a),
        counter = 1;
    writeln("read from backup:", a);
}

void run()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    vector<string> pairs, temp;
    fromBackup(pairs);
    if (pairs.size() == 0)
        fori(countMessages)
            pairs.pb("qwerty&?ADSF"),
            temp.pb("");

    writeln("all inits done");//------------------------------------------

    while (counter >= 0)
    {
        if (counter++ % 1000 == 0)
            writeln(counter);
        items.clear();
        items = parse(getMessages)["response"]["items"];
        fori(items.size())
            temp[i] = items[i]["body"].asString();
        if (temp.size() && pairs.size())
            if (pairs[0] != temp[0])
            {    
                int j = 0;
                while (j < temp.size() && pairs[0] != temp[j])
                    ++j;
                fori(temp.size())
                    pairs[i] = temp[i];
                fori(j)
                    printf("%s %s\n", (items[j - i - 1]["out"].asInt() == 0 ? "A:" : "M:"), pairs[j - i - 1]);
                toBackup(pairs);
            }
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

//:!clang++ messager.cpp -o messager -std=c++11 -lcurl -I /usr/include/jsoncpp/ -ljsoncpp `pkg-config --cflags --libs libnotifymm-1.0`
