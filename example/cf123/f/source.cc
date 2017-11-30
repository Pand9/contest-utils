#include <bits/stdc++.h>
using namespace std;

using u64 = uint64_t;
using i64 = int64_t;

// print tuples {{{
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& t) {
    return os << '[' << t.first << ',' << t.second << ']';
}
void print_tpl_helper(ostream&, bool) {}
template <typename T, typename ...Ts>
void print_tpl_helper(ostream& os, bool first, const T& v, const Ts& ...vs) {
    if (!first){os << ',';} os << v; print_tpl_helper(os, false, vs...);
}
template <typename ...Ts>
ostream& print_struct(ostream& os, const char* classname, const Ts& ...vs) {
        // todo: named fields
    os << classname << '('; print_tpl_helper(os, true, vs...); return os << ')';
}
struct Example {
    char symbol;
    u64 val;
    friend ostream& operator<<(ostream& os, const Example& elem) {
        return print_struct(os, "Op", elem.symbol, elem.val);
    }
};
// }}}
// print containers {{{
template <typename It>
void print(ostream& os, It begin, It end, u64 len, u64 limit = 17) {
    u64 count = 0;
    os << "{";
    while (begin != end && count < limit) {
        os << "(" << *begin << ")";
        count++;
        begin++;
    }
    if (begin != end)
        os << "... " << len << " total";
    os << "}";
}
#define MAKE_PRINTER_1(container) \
template <typename T> ostream& operator<<(ostream& os, const container<T>& t) { print(os, t.begin(), t.end(), t.size()); return os; }
#define MAKE_PRINTER_2(container) \
template <typename T1, typename T2> \
ostream& operator<<(ostream& os, const container<T1, T2>& t) { \
    print(os, t.begin(), t.end(), t.size()); \
    return os; \
}
MAKE_PRINTER_1(vector)
MAKE_PRINTER_2(map)
MAKE_PRINTER_1(set)
MAKE_PRINTER_2(unordered_map)
MAKE_PRINTER_1(unordered_set)
#undef MAKE_PRINTER_1
#undef MAKE_PRINTER_2
// }}}
// read/write {{{
template <typename T> T read() { T e; cin >> e; return e; }
void read() {}
template <typename T, typename ...Ts> void read(T& v, Ts& ...ts) { v = read<T>(); read(ts...); }
template <typename T> vector<T> readv(u64 n) { vector<T> v; for (u64 i = 0; i < n; i++) v.push_back(read<T>()); return v; }
template <typename T> struct identity { const T& operator()(const T& t) const { return t; } };
#define PRINTERS(FNAME, OUTP) \
    template <typename T> void FNAME(const T& t) { OUTP << t << ' '; } \
    void FNAME##ln() { OUTP << '\n'; } \
    template <typename T> void FNAME##ln(const T& t) { OUTP << t << '\n'; } \
    template <typename T, typename F = identity<typename T::value_type>> \
    void FNAME##v(const T& t, F f = F()) { for (const auto& e : t) FNAME(f(e)); FNAME##ln(); }
PRINTERS(print, cout)
#ifdef DEBUG_PRINTS
    PRINTERS(dprint, cerr)
#else
# define dprint(...)
# define dprintv(...)
# define dprintln(...)
#endif
/// }}}

struct Other {
    std::string d;
};

struct TestStruct {
    std::string a;
    u64 b;
    Other c;
    friend ostream& operator<<(ostream& os, const TestStruct& elem) {
        return print_struct(os, "TestStruct", elem.a, elem.b, elem.c.d);
    }
};

void go() {
    TestStruct s;
    read(s.a, s.b, s.c.d);
    cout << s;
    vector<TestStruct> v(1);
    dprint(v);
    cout << v;
    vector<int> v2 = {3, 4, 5};
    dprint(v2);
    dprintv(v2); dprintln();
}


int main () { // {{{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    go();
} //

