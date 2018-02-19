C++17 уже [доступен](http://codeforces.com/blog/entry/57646) на codeforces, сообщество [хочет](http://codeforces.com/blog/entry/15643?#comment-413401) новую версию [C++ tricks](http://codeforces.com/blog/entry/15643), которую написал [user:Swift,2018-02-13], так что, начнем!  
Disclaimer: Я сделал всего лишь немного примеров новых фич, которые по моему мнению относятся к спортивному программированию. Если у Вас есть примеры лучше или Вам что-то непонятно, или нужно больше объяснений каких-то фич $---$ пишите в комментах)

### Fold expressions (Свертки)

* Я думаю все знают, что такое reduce и свертка, но все-таки приведу пример из c++11:

```
vector<int> v = {1, 3, 5, 7};
int res = accumulate(v.begin(), v.end(), 0, [](int a, int b) { return a + b; });
cout << res; // 16
```

* Начиная с C++17 есть поддержка свертки для шаблонного списка со следующим синтаксисом:

```
(pack op ...)
(... op pack)
(pack op ... op init)
(init op ... op pack)
```

* Для примера напишем функцию, которая принимает переменное число аргументов и считает их сумму.

[cut]

До С++17 мы не могли этого сделать без явной передачи первого аргумента:

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

* Это особенно полезно, когда мы в качестве  `op` используем запятую:

```
// C++17
template<typename T, typename... Args>
void pushToVector(vector<T>& v, Args&&... args)
{
    (v.push_back(forward<Args>(args)), ...);
    //Этот код раскрывается в последовательность выражений через запятую:
    //  v.push_back(forward<Args_1>(arg1)),
    //  v.push_back(forward<Args_2>(arg2)),
    //  ....
}

vector<int> v;
pushToVector(v, 1, 4, 5, 8);
```

* И мой любимый пример:

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

* **Note**: скобки значимы!

### Class template argument deduction (Вывод шаблонных типов)

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

Если структура сложная, то есть возможность указать правило вывода самим, например так:

```
template<typename T, typename U>
struct S
{
    T first;
    U second;
};

// Мой вывод типа
template<typename T, typename U>
S(const T &first, const U &second) -> S<T, U>;

```
**Note**: компилятор обычно сам может создать правило вывода из конструктора, но в этом примере конструктора нет, поэтому правило вывода написано руками.

### `*this` capture in lambda expressions (Захват `*this` в лямбда-функциях)

Я не думаю, что это особо полезно в спортивном программировании, но кто знает:

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
[Статья](https://habrahabr.ru/company/infopulse/blog/341264/) о ключевом слове `mutable`.

### Structured bindings (Структурные связывания?)

* Самое полезное нововведение $---$ синтаксический сахар для декомпозиции объектов.

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
    //...Какая-то сложная логика с x и y
}

//C++17
for (auto& [x, y] : points)
{
    //...Какая-то сложная логика с x и y
}
```

* Итерирование по map'у:

```
map<int, string> m;
for (auto [key, value] : m)
    cout << "key: " << key << '\n' << "value: " << value << '\n';
```

* Хорошим примером использования может служить задача [problem:938D]. Код со структурным связыванием (Алгоритм Дейкстры) становится намного понятнее и читаемее: сравните [submission:35474147] и [submission:35346635].

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

### Инициализатор в `if` и `switch`

```
set<int> s;

if (auto [iter, ok] = s.insert(42); ok)
{
    //...
}
else
{
    //`ok` и `iter` доступны в этой области видимости
}
//А здесь недоступны
```

### Новые атрибуты

* `[[fallthrough]]` атрибут сообщает о том, что break в данном месте пропущен намеренно:

```
int requests, type;
cin >> requests;
for (int q = 0; q < requests; ++q)
    switch (cin >> type; type) //Используем инициализатор в switch
    {
        case 1:
            int l, r;
            cin >> l >> r;
            //Обработаем запрос первого типа
            break;
        case 2:
            [[fallthrough]];
            //Предупреждение компилятора будет подавлено!
        case 3:
            int value;
            cin >> value;
            //Обработаем запрос второго и третьего типа.
    }
```

* `[[nodiscard]]` атрибут используется, чтобы показать, что возвращаемое значение функции не может быть отброшено. Может использоваться на типах.

### std::optional

```
optional<int> findPath(graph g, int from, int to)
{
    //Find path from `from` to `to`
    if (d[to] != INF)
        return d[to];
    return {}
}

//Проверим, что путь существует
if (auto dist = findPath(...); dist.hasValue())
    cout << dist.value(); //Получим его
else
    cout << -1;

//Или сразу используем defaultValue, если значение не было установлено
cout << findPath(...).value_or(-1); //Выводит расстояние если оно найдено и -1 иначе
```

### Неконстантное(ый?, ая?) string::data

Для любителей С:

```
string str = "hello";
char *p = str.data();
p[0] = 'H';
cout << str; // Hello
```

### Свободные функции std::size, std::data и std::empty

В добавку к уже существующим свободным функциям std::begin, std::end и другим, появились новые, такие как: std::size, std::data и std::empty:

```
vector<int> v = { 3, 2, 5, 1, 7, 6 };

size_t sz = size(v);
bool empty = empty(v);
auto ptr = data(v);
```

### std::clamp

Возвращает `x`, если оно попало в интервал `[low, high]` и ближайшее значение иначе:

```
cout << clamp(7, 0,  10); //7
cout << clamp(7, 0,  5);  //5
cout << clamp(7, 10, 50); //10
```

Я думаю, что это полезная функция, но будет сложно вспомнить как она называется в течение контеста :)

### GCD and LCM! (НОД и НОК)

```
cout << gcd(24, 60); // 12
cout << lcm(8, 10);  // 40
```

### Возвращаемое значение у `emplace_back`

```
vector<int> v = { 1, 2, 3 };

auto &r = v.emplace_back(10);
r = 42;
//v теперь содержит {1, 2, 3, 42}
```

### Функции в std::map:

* Extract (можно даже поменять ключ!!!)

```
map<int, string> myMap{ { 1, "Gennady" }, { 2, "Petr" }, { 3, "Makoto" } };
auto node = myMap.extract(2);
node.key() = 42;
myMap.insert(move(node));

// myMap: {{1, "Gennady"}, {42, "Petr"}, {3, "Makoto"}};
```

**Note**: Extract $---$ единственный способ поменять ключ элемента map'а без reallocation(реаллокации?)

Асимптотика:  
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

Асимптотика: $O(N \log(N + M))$ [doc](http://en.cppreference.com/w/cpp/container/map/merge)

* Раньше, чтобы понять, произошла вставка в map или обновление, необходимо было сначала найти элемент, а потом использовать operator[]. Теперь появилась функция insert_or_assign:

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

Асимптотика: $O(\log(N))$ [doc](http://en.cppreference.com/w/cpp/container/map/emplace)

### Более строгий порядок вычисления выражений

В C++17 появились новые правила, более строго определяющие порядок вычисления выражений:

* Постфиксные выражения вычисляются слева направо (в том числе вызовы функций и доступ к членам объектов)
* Выражения присваивания вычисляются справа налево.
* Операнды операторов << и >> вычисляются слева направо.

Таким образом, как указывается в предложении к стандарту, в следующих выражениях теперь гарантированно сначала вычисляется a, затем b, затем c:

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

**Note**: Порядок вычисления b1, b2, b3 все еще не определен.

P.S.: Все материалы адаптированы мной с примерами [отсюда](https://habrahabr.ru/company/pvs-studio/blog/340014/)  
