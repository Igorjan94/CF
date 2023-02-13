
// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(size(a))

typedef  pair<int, int>   pii;
typedef   vector<int>     vi;
typedef    long long      ll;
typedef    unsigned int      uint;
typedef    unsigned long long      ull;

#define pb push_back
#define all(a) begin(a), end(a)
#define ints(a...) int a; readln(a)

[[maybe_unused]] const int MOD = 1000000007;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

static const auto IOSetup = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(6) << std::fixed;
    return nullptr;}();
struct IOPre {static constexpr int TEN = 10, SZ = TEN * TEN * TEN * TEN;std::array<char, 4 * SZ> num;constexpr IOPre() : num{} {for (int i = 0; i < SZ; i++) {int n = i;for (int j = 3; j >= 0; j--) {num[i * 4 + j] = static_cast<char>(n % TEN + '0');n /= TEN;}}}};
struct IO {
#if !HAVE_DECL_FREAD_UNLOCKED
#define fread_unlocked fread
#endif
#if !HAVE_DECL_FWRITE_UNLOCKED
#define fwrite_unlocked fwrite
#endif
    static constexpr int SZ = 1 << 17, LEN = 32, TEN = 10, HUNDRED = TEN * TEN,THOUSAND = HUNDRED * TEN, TENTHOUSAND = THOUSAND * TEN,MAGIC_MULTIPLY = 205, MAGIC_SHIFT = 11, MASK = 15,TWELVE = 12, SIXTEEN = 16;static constexpr IOPre io_pre = {};std::array<char, SZ> input_buffer, output_buffer;int input_ptr_left, input_ptr_right, output_ptr_right;
    IO(): input_buffer{},output_buffer{},input_ptr_left{},input_ptr_right{},output_ptr_right{} {}
    IO(const IO&) = delete;IO(IO&&) = delete;IO& operator=(const IO&) = delete;IO& operator=(IO&&) = delete;
    ~IO() { flush(); }
    template <class T>struct is_char {static constexpr bool value = std::is_same_v<T, char>;};
    template <class T>struct is_bool {static constexpr bool value = std::is_same_v<T, bool>;};
    template <class T>struct is_string {static constexpr bool value =std::is_same_v<T, std::string> || std::is_same_v<T, const char*> ||std::is_same_v<T, char*> || std::is_same_v<std::decay_t<T>, char*>;;};
    template <class T, class D = void>struct is_custom {static constexpr bool value = false;};
    template <class T>struct is_custom<T, std::void_t<typename T::internal_value_type>> {static constexpr bool value = true;};
    template <class T>struct is_default {static constexpr bool value = is_char<T>::value || is_bool<T>::value ||is_string<T>::value ||std::is_integral_v<T>;};
    template <class T, class D = void>struct is_iterable {static constexpr bool value = false;};
    template <class T>struct is_iterable <T, typename std::void_t<decltype(std::begin(std::declval<T>())) >> {static constexpr bool value = true;};
    template <class T, class D = void, class E = void>struct is_applyable {static constexpr bool value = false;};
    template <class T>struct is_applyable<T, std::void_t<typename std::tuple_size<T>::type>,std::void_t<decltype(std::get<0>(std::declval<T>()))>> {static constexpr bool value = true;};
    template <class T>static constexpr bool needs_newline = (is_iterable<T>::value || is_applyable<T>::value) && (!is_default<T>::value);
    template <typename T, typename U> struct any_needs_newline {static constexpr bool value = false;}; template <typename T>
    struct any_needs_newline<T, std::index_sequence<>> {static constexpr bool value = false;};
    template <typename T, std::size_t I, std::size_t... Is>struct any_needs_newline<T, std::index_sequence<I, Is...>> {static constexpr bool value = needs_newline<decltype(std::get<I>(std::declval<T>()))> || any_needs_newline<T, std::index_sequence<Is...>>::value;};
    inline void load() {memmove(std::begin(input_buffer), std::begin(input_buffer) + input_ptr_left, input_ptr_right - input_ptr_left); input_ptr_right = input_ptr_right - input_ptr_left + static_cast<int>(fread_unlocked(std::begin(input_buffer) + input_ptr_right - input_ptr_left, 1, SZ - input_ptr_right + input_ptr_left, stdin)); input_ptr_left = 0;}
    inline void read_char(char& c) {if (input_ptr_left + LEN > input_ptr_right) load(); c = input_buffer[input_ptr_left++];}
    inline void read_string(std::string& x) {char c; while (read_char(c), c < '!') continue; x = c; while (read_char(c), c >= '!') x += c;}
    template <class T> inline std::enable_if_t<std::is_integral_v<T>, void> read_int(T& x) {if (input_ptr_left + LEN > input_ptr_right) load(); char c = 0; do c = input_buffer[input_ptr_left++]; while (c < '-'); [[maybe_unused]] bool minus = false; if constexpr (std::is_signed<T>::value == true)if (c == '-') minus = true, c = input_buffer[input_ptr_left++]; x = 0; while (c >= '0')x = x * TEN + (c & MASK), c = input_buffer[input_ptr_left++]; if constexpr (std::is_signed<T>::value == true)if (minus) x = -x;}
    inline void skip_space() {if (input_ptr_left + LEN > input_ptr_right) load(); while (input_buffer[input_ptr_left] <= ' ') input_ptr_left++;}
    inline void flush() {fwrite_unlocked(std::begin(output_buffer), 1, output_ptr_right, stdout); output_ptr_right = 0;}
    inline void write_char(char c) {if (output_ptr_right > SZ - LEN) flush(); output_buffer[output_ptr_right++] = c;}
    inline void write_bool(bool b) {if (output_ptr_right > SZ - LEN) flush(); output_buffer[output_ptr_right++] = b ? '1' : '0';}
    inline void write_string(const std::string& s) {for (auto x : s) write_char(x);}
    inline void write_string(const char* s) {while (*s) write_char(*s++);}
    inline void write_string(char* s) {while (*s) write_char(*s++);}
    template <typename T>inline std::enable_if_t<std::is_integral_v<T>, void> write_int(T x) {if (output_ptr_right > SZ - LEN) flush(); if (!x) {output_buffer[output_ptr_right++] = '0'; return;} if constexpr (std::is_signed<T>::value == true)if (x < 0) output_buffer[output_ptr_right++] = '-', x = -x; int i = TWELVE; std::array<char, SIXTEEN> buf{}; while (x >= TENTHOUSAND) {memcpy(std::begin(buf) + i, std::begin(io_pre.num) + (x % TENTHOUSAND) * 4, 4); x /= TENTHOUSAND; i -= 4;} if (x < HUNDRED) {if (x < TEN) {output_buffer[output_ptr_right++] = static_cast<char>('0' + x);} else {std::uint32_t q = (static_cast<std::uint32_t>(x) * MAGIC_MULTIPLY) >> MAGIC_SHIFT; std::uint32_t r = static_cast<std::uint32_t>(x) - q * TEN; output_buffer[output_ptr_right] = static_cast<char>('0' + q); output_buffer[output_ptr_right + 1] = static_cast<char>('0' + r); output_ptr_right += 2;}} else {if (x < THOUSAND) {memcpy(std::begin(output_buffer) + output_ptr_right, std::begin(io_pre.num) + (x << 2) + 1, 3), output_ptr_right += 3;} else {memcpy(std::begin(output_buffer) + output_ptr_right, std::begin(io_pre.num) + (x << 2), 4), output_ptr_right += 4;}} memcpy(std::begin(output_buffer) + output_ptr_right, std::begin(buf) + i + 4, TWELVE - i); output_ptr_right += TWELVE - i;}
    template <typename T_>IO& operator<<(T_&& x) {using T = typename std::remove_cv < typename std::remove_reference<T_>::type >::type; static_assert(is_custom<T>::value or is_default<T>::value or is_iterable<T>::value or is_applyable<T>::value); if constexpr (is_custom<T>::value) {write_int(x.get());} else if constexpr (is_default<T>::value) {if constexpr (is_bool<T>::value) {write_bool(x);} else if constexpr (is_string<T>::value) {write_string(x);} else if constexpr (is_char<T>::value) {write_char(x);} else if constexpr (std::is_integral_v<T>) {write_int(x);}} else if constexpr (is_iterable<T>::value) {using E = decltype(*std::begin(x)); constexpr char sep = needs_newline<E> ? '\n' : ' '; int i = 0; for (const auto& y : x) {if (i++) write_char(sep); operator<<(y);}} else if constexpr (is_applyable<T>::value) {constexpr char sep = (any_needs_newline < T, std::make_index_sequence<std::tuple_size_v<T> >>::value) ? '\n' : ' '; int i = 0; std::apply([this, &sep, &i](auto const & ... y) {(((i++ ? write_char(sep) : void()), this->operator<<(y)), ...);}, x);} return *this;}
    template <typename T>IO& operator>>(T& x) {static_assert(is_custom<T>::value or is_default<T>::value or is_iterable<T>::value or is_applyable<T>::value); static_assert(!is_bool<T>::value); if constexpr (is_custom<T>::value) {typename T::internal_value_type y; read_int(y); x = y;} else if constexpr (is_default<T>::value) {if constexpr (is_string<T>::value) {read_string(x);} else if constexpr (is_char<T>::value) {read_char(x);} else if constexpr (std::is_integral_v<T>) {read_int(x);}} else if constexpr (is_iterable<T>::value) {for (auto& y : x) operator>>(y);} else if constexpr (is_applyable<T>::value) {std::apply([this](auto & ... y) { ((this->operator>>(y)), ...); }, x);} return *this;}
    IO* tie(std::nullptr_t) { return this; }
    void sync_with_stdio(bool) {}
} io;
#define cin io
#define cout io
 

const int N = 3 * 100000 + 3;
const int Q = 1000001;
 
constexpr ull lowest_bitsll[] = {0ull, 1ull, 3ull, 7ull, 15ull, 31ull, 63ull, 127ull, 255ull, 511ull, 1023ull, 2047ull, 4095ull, 8191ull, 16383ull, 32767ull, 65535ull, 131071ull, 262143ull, 524287ull, 1048575ull, 2097151ull, 4194303ull, 8388607ull, 16777215ull, 33554431ull, 67108863ull, 134217727ull, 268435455ull, 536870911ull, 1073741823ull, 2147483647ull, 4294967295ull, 8589934591ull, 17179869183ull, 34359738367ull, 68719476735ull, 137438953471ull, 274877906943ull, 549755813887ull, 1099511627775ull, 2199023255551ull, 4398046511103ull, 8796093022207ull, 17592186044415ull, 35184372088831ull, 70368744177663ull, 140737488355327ull, 281474976710655ull, 562949953421311ull, 1125899906842623ull, 2251799813685247ull, 4503599627370495ull, 9007199254740991ull, 18014398509481983ull, 36028797018963967ull, 72057594037927935ull, 144115188075855871ull, 288230376151711743ull, 576460752303423487ull, 1152921504606846975ull, 2305843009213693951ull, 4611686018427387903ull, 9223372036854775807ull, 18446744073709551615ull};
const uint NO = N; //This value will be returned in lower_bound functions, if no answer exists. Change, if need.
template<uint MAXN>           //Can correctly work with numbers in range [0; MAXN]
class fastSet {
    static const uint PREF = (MAXN <= 64 ? 0 :
                              MAXN <= 4096 ? 1 :
                              MAXN <= 262144 ? 1 + 64 :
                              MAXN <= 16777216 ? 1 + 64 + 4096 :
                              MAXN <= 1073741824 ? 1 + 64 + 4096 + 262144 : 227) + 1;
    static const uint SZ = PREF + (MAXN + 63) / 64 + 1;
    ull m[SZ] = {0};
 
    inline uint left(uint v) const {return (v - 62) * 64;}
    inline uint parent(uint v) const {return v / 64 + 62;}
    inline void setbit(uint v) {m[v >> 6] |= 1ull << (v & 63);}
    inline void resetbit(uint v) {m[v >> 6] &= ~(1ull << (v & 63));}
    inline uint getbit(uint v) const {return m[v >> 6] >> (v & 63) & 1;}
    inline ull childs_value(uint v) const {return m[left(v) >> 6];}
 
    inline uint left_go(uint x, const uint c) const {
        const ull rem = x & 63;
        uint bt = PREF * 64 + x;
        ull num = m[bt >> 6] & lowest_bitsll[rem + c];
        if (num) return (x ^ rem) | __lg(num);
        for (bt = parent(bt); bt > 62; bt = parent(bt)) {
            const ull rem = bt & 63;
            num = m[bt >> 6] & lowest_bitsll[rem];
            if (num) {bt = (bt ^ rem) | __lg(num); break;}
        }
        if (bt == 62) return NO;
        while (bt < PREF * 64) bt = left(bt) | __lg(m[bt - 62]);
        return bt - PREF * 64;
    }
 
    inline uint right_go(uint x, const uint c) const {
        const ull rem = x & 63;
        uint bt = PREF * 64 + x;
        ull num = m[bt >> 6] & ~lowest_bitsll[rem + c];
        if (num) return (x ^ rem) | __builtin_ctzll(num);
        for (bt = parent(bt); bt > 62; bt = parent(bt)) {
            const ull rem = bt & 63;
            num = m[bt >> 6] & ~lowest_bitsll[rem + 1];
            if (num) {bt = (bt ^ rem) | __builtin_ctzll(num); break;}
        }
        if (bt == 62) return NO;
        while (bt < PREF * 64) bt = left(bt) | __builtin_ctzll(m[bt - 62]);
        return bt - PREF * 64;
    }
 
public:
    fastSet() {
        assert(PREF != 228);
        setbit(62);
    }
 
    bool empty() const {return getbit(63);}
 
    void clear() {fill(m, m + SZ, 0); setbit(62);}
 
    bool count(uint x) const {return m[PREF + (x >> 6)] >> (x & 63) & 1;}
 
    void insert(uint x) {
        for (uint v = PREF * 64 + x; !getbit(v); v = parent(v)) {
            setbit(v);
        }
    }
 
    void erase(uint x) {
        if (!getbit(PREF * 64 + x)) return;
        resetbit(PREF * 64 + x);
        for (uint v = parent(PREF * 64 + x); v > 62 && !childs_value(v); v = parent(v)) {
            resetbit(v);
        }
    }
 
    uint lower_bound(uint x) const {return right_go(x, 0);}
    uint upper_bound(uint x) const {return right_go(x, 1);}
    uint inverse_lower_bound(uint x) const {return left_go(x, 1);}
    uint inverse_upper_bound(uint x) const {return left_go(x, 0);}
};
//Supports all std::set operations in O(1) on random queries / dense arrays, O(log_64(N)) in worst case (sparce array).
//Count operation works in O(1) always.
//Igorjan
//}}}

const int rotateDelta[4] = {3, 0, 0, 1};
inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0)
		return 0;
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

tuple<int, int, int, int64_t> requests[Q];
int a[N];
int ans[Q];

fastSet<N> m;
fastSet<N> diffs;
int diffsCNT[N];
int n, q;
    
inline void er(int x) {
    if (--diffsCNT[x] == 0)
        diffs.erase(x);
}

inline void ad(int x) {
    if (diffsCNT[x]++ == 0)
        diffs.insert(x);
}

inline void add(const int& id) {
    int x = a[id];
    //writeln("ADD", x); cout.flush();
    const auto& l = m.inverse_upper_bound(x);
    const auto& r = m.upper_bound(x);

    if (l == NO && r == NO)
        [](){}();
    else if (r == NO)
    {
        auto mx = m.inverse_lower_bound(N);
        ad(x - mx);
    }
    else if (l == NO)
    {
        auto mn = m.lower_bound(0);
        ad(mn - x);
    }
    else
    {
        er(r - l);
        ad(r - x);
        ad(x - l);
    }
    m.insert(x);
}

inline void del(const int& id) {
    const int& x = a[id];
    //writeln("DEL", x); cout.flush();
    const auto& r = m.upper_bound(x);
    const auto& l = m.inverse_upper_bound(x);
    if (r != NO)
        er(r - x);
    if (l != NO)
    {
        er(x - l);
        if (r != NO)
            ad(r - l);
    }
    m.erase(x);
}

void run()
{
    cin >> n >> q;
    fori(n)
        cin >> a[i];
    int w = bit_width(unsigned(n));

    fori(q)
    {
        int l, r;
        cin >> l >> r; --l; --r;
        const auto& order = hilbertOrder(l, r, w, 0);
        requests[i] = {l, r, i, order};
    }

    sort(requests, requests + q, [&](const auto& a, const auto& b) {
        return get<3>(a) < get<3>(b);
    });

    int L = 0;
    int R = -1;
    fori(q)
    {
        const auto& [l, r, id, _] = requests[i];
        while (L > l) add(--L);
        while (R < r) add(++R);
        while (L < l) del(L++);
        while (R > r) del(R--);
        ans[id] = diffs.lower_bound(0);
    }
    fori(q)
        cout << ans[i] << "\n";
}

//{{{
int main()
{
    cin.tie(0); ios_base::sync_with_stdio(false);
    run();
    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
