C++17 is now [available](http://codeforces.com/blog/entry/57646) on codeforces, community [wants](http://codeforces.com/blog/entry/15643?#comment-413401) new edition of [C++ tricks](http://codeforces.com/blog/entry/15643) by [user:Swift], so, let's start!  
Disclaimer: I have done only few examples of new features, which in my opinion are related to competitive programming. Feel free to comment and provide more real-world examples or ask to elaborate some features with more examples or explanations.

### Fold expressions

* I think that everybody knows, what reduce or fold means, but a c++11 example:

```
vector<int> v = {1, 3, 5, 7};
int res = accumulate(v.begin(), v.end(), 0, [](int a, int b) { return a + b; });
cout << res; // 16
```

* In C++17 there is also folding support for a template parameters list. It has the following syntax:

```
(pack op ...)
(... op pack)
(pack op ... op init)
(init op ... op pack)
```

* For example, implement a template function that takes a variable number of parameters and calculates their sum. 

[cut]

Before C++17 we cannot do this without explicit first argument:

```
//C++14
auto Sum()
{
    return 0;
}

template<typename Arg, typename... Args>
auto Sum(Arg first, Args... rest)
{
    return first + Sum(rest...);
}

cout << Sum(1, 2, 3, 4, 5); // 15
```

```
//C++17
template<typename... Args>
auto Func(Args... args)
{
    return (args + ...);
}

cout << Func(1, 2, 3, 4, 5); // 15
```

* This is useful, when we use comma as `op`:

```
// C++17
template<typename T, typename... Args>
void pushToVector(vector<T>& v, Args&&... args)
{
    (v.push_back(forward<Args>(args)), ...);
    //This code is expanded into a sequence of expressions separated by commas as follows:
    //  v.push_back(forward<Args_1>(arg1)),
    //  v.push_back(forward<Args_2>(arg2)),
    //  ....
}

vector<int> v;
pushToVector(v, 1, 4, 5, 8);
```

* And my favourite example:

```
//C++17
template<typename... Args>
void readln(Args&... args)
{
    ((cin >> args), ...);
}

template<typename... Args>
void writeln(Args... args)
{
    ((cout << args << " "), ...);
}

int x;
double y;
readln(x, y); // enter 100 500.1234
writeln(x, "some string", y); // 100 some string 500.1234
```

* **Note**: brackets are meaningfull

### Class template argument deduction

```
template<typename T>
struct point
{
    T x;
    T y;
    point(T x, T y) : x(x), y(y) {}
};

//C++11
pair<int, double> p1 = {14, 17.0}
point<int> u = {1, 2};

//C++17
pair p2 = {14, 17.0}
point v = {1, 2};
```

If struct is complex, there is a possibility to write deduction guides ourselves, for instance:

```
template<typename T, typename U>
struct S
{
    T first;
    U second;
};

// My deduction guide
template<typename T, typename U>
S(const T &first, const U &second) -> S<T, U>;

```
**Note**: the compiler is able to create deduction guide automatically from a constructor, but in this example, the structure S has no constructor, so, we define deduction guide manually.

### `*this` capture in lambda expressions

I don't think this is useful in CP, but who knows:

```
struct someClass
{
    int x = 0;

    void f() const
    {
        cout << x << '\n';
    }

    void g()
    {
        x++;
    }

    // C++14
    void func()
    {
        auto lambda1 = [self = *this]() { self.f(); };
        auto lambda2 = [self = *this]() mutable { self.g(); };
        lambda1();
        lambda2();
    }

    // C++17
    void funcNew()
    {
        auto lambda1 = [*this]() { f(); };
        auto lambda2 = [*this]() mutable { g(); };
        lambda1();
        lambda2();
    }
};

```
[Article](https://arne-mertz.de/2017/10/mutable/) about `mutable` keyword.

### Structured bindings

* The most useful syntax sugar for decomposition of objects.

```
template<typename T>
struct point
{
    T x;
    T y;
    point(T x, T y) : x(x), y(y) {}
};

vector<point<int>> points = {{0, 0}, {1, 0}, {1, 1}, {1, 0}};
//C++11
for (auto& point : points)
{
    int x, y;
    tie(x, y) = point;
    //...Some compex logic with x and y
}

//C++17
for (auto& [x, y] : points)
{
    //...Some compex logic with x and y
}
```

* Iterating over map:

```
map<int, string> m;
for (auto [key, value] : m)
    cout << "key: " << key << '\n' << "value: " << value << '\n';
```

* A good example of usage is problem [problem:938D]. Code with structured bindings (Dijkstra algo) is much more readable and understandable: compare [submission:35474147] and [submission:35346635].

```
while (!q.empty())
{
    auto [dist, u] = *q.begin();
    q.erase(q.begin());
    used[u] = true;
    for (auto& [w, v] : g[u])
        if (!used[v] && d[v] > dist + 2 * w)
            q.erase({d[v], v}),
            d[v] = dist + 2 * w,
            q.insert({d[v], v});
}
```

### Initializer in `if` and `switch`

```
set<int> s;

if (auto [iter, ok] = s.insert(42); ok)
{
    //...
}
else
{
    //`ok` and `iter` are available here
}
//But not here
```

### New attributes

* `[[fallthrough]]` attribute indicates that the break operator inside a case block is missing intentionally:

```
int requests, type;
cin >> requests;
for (int q = 0; q < requests; ++q)
    switch (cin >> type; type) //Initializer in switch
    {
        case 1:
            int l, r;
            cin >> l >> r;
            //proceed request of first type
            break;
        case 2:
            [[fallthrough]];
            //Compiler warning will be supressed
        case 3:
            int value;
            cin >> value;
            //Proceed requests of second and third types.
    }
```

* `[[nodiscard]]` attribute is used to indicate that the return value of the function should not be ignored and can be also applied to data types.

### std::optional

```
optional<int> findPath(graph g, int from, int to)
{
    //Find path from `from` to `to`
    if (d[to] != INF)
        return d[to];
    return {}
}

//We can check if value exists
if (auto dist = findPath(...); dist.hasValue())
    cout << dist.value(); //And get it
else
    cout << -1;

//Or use defaultValue if value is not set
cout << findPath(...).value_or(-1); //Prints distance if path exists and -1 otherwise
```

### Non-constant string::data

For C-lovers:

```
string str = "hello";
char *p = str.data();
p[0] = 'H';
cout << str; // Hello
```

### Free functions std::size, std::data and std::empty

In addition to the already existing free functions std::begin, std::end and others, some new free functions appeared, such as: std::size, std::data and std::empty:

```
vector<int> v = { 3, 2, 5, 1, 7, 6 };

size_t sz = size(v);
bool empty = empty(v);
auto ptr = data(v);
```

### std::clamp

Returns `x` if it is in the interval `[low, high]` or, otherwise, the nearest value:

```
cout << clamp(7, 0,  10); //7
cout << clamp(7, 0,  5);  //5
cout << clamp(7, 10, 50); //10
```

I think that it is convenient function, but it'll be difficult to call it in mind during contest :)

### GCD and LCM!

```
cout << gcd(24, 60); // 12
cout << lcm(8, 10);  // 40
```

### The return value from `emplace_back`

```
vector<int> v = { 1, 2, 3 };

auto &r = v.emplace_back(10);
r = 42;
//v now contains {1, 2, 3, 42}
```

### std::map functions:

* Extract (and even change key!!!)

```
map<int, string> myMap{ { 1, "Gennady" }, { 2, "Petr" }, { 3, "Makoto" } };
auto node = myMap.extract(2);
node.key() = 42;
myMap.insert(move(node));

// myMap: {{1, "Gennady"}, {42, "Petr"}, {3, "Makoto"}};
```

**Note**: Extract is the only way to change a key of a map element without reallocation

Complexity:  
extract(key): $O(\log(N))$ [doc](http://en.cppreference.com/w/cpp/container/map/extract)  
extract(iterator): $O(1)$ amortized [doc](http://en.cppreference.com/w/cpp/container/map/extract)

* Merge

```
map<int, string> m1{ { 1, "aa" }, { 2, "bb" }, { 3, "cc" } }; 
map<int, string> m2{ { 4, "dd" }, { 5, "ee" }, { 6, "ff" } };
m1.merge(m2);
// m1: { {1, "aa"}, {2, "bb"}, {3, "cc"}, {4, "dd"}, {5, "ee"}, {6, "ff"} }
// m2: {}
```

Compexity: $O(N \log(N + M))$ [doc](http://en.cppreference.com/w/cpp/container/map/merge)

* To figure out if the insert or update occurred, we had to first look for the element, and then apply the operator[]. Now we had insert_or_assign:

```
map<int, string> m;
m.emplace(1, "aaa");
m.emplace(2, "bbb");
m.emplace(3, "ccc");

auto [it1, inserted1] = m.insert_or_assign(3, "ddd");
cout << inserted1; // 0

auto [it2, inserted2] = m.insert_or_assign(4, "eee");
cout << inserted2; // 1
```

Complexity: $O(\log(N))$ [doc](http://en.cppreference.com/w/cpp/container/map/emplace)

### More rigorous evaluation order of expressions

And in general c++17 introduces new rules, defining more strictly the evaluation order of expressions:

* Postfix expressions are evaluated from left to right (including function calls and access to objects members)
* Assignment expressions are evaluated from right to left.
* Operands of operators << and >> are evaluated from left to right.

Thus, as it is mentioned in the proposal for the standard, in the following expressions a is now guaranteed to be evaluated first, then b, then c:

```
a.b
a->b
a->*b
a(b1, b2, b3)
b @= a
a[b]
a << b << c
a >> b >> c
```

**Note**: the evaluation order between b1, b2, b3 is still not defined.

P.S.: All materials are adopted with my examples from [here](https://www.viva64.com/en/b/0533)  
P.P.S.: I don't think my english is [poor](http://codeforces.com/blog/entry/57479?#comment-411601), but please PM me about grammar or other mistakes to make this article better!
