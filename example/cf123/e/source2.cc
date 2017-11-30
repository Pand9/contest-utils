// 2017-11-30 22:14:25
#include <bits/stdc++.h>
using namespace std;

// misc {{{
using u64 = uint64_t;
using u32 = uint32_t;
using i64 = int64_t;
using i32 = int32_t;
const i64 inf = (1ll << 62);
const i64 imax = numeric_limits<i64>::max();
const i64 umax = numeric_limits<u64>::max();
void merror(string msg, i64 line_number) { cerr << "assert >> " << line_number << ": " << msg << endl; exit(42); }
#define massert(c, msg) do { if (!(c)) merror(msg, __LINE__); } while(0)
#define massert2(c) massert(c, "")
template <typename C> i64 isize(const C& c) { return static_cast<i64>(c.size()); }
template <typename T, size_t N> i64 isize(const array<T, N>& = {}) { return static_cast<i64>(N); }
template <typename It, typename Cont> bool it_last(It it, const Cont& c) { return ++it == c.cend(); }
// }}}
// functors {{{
namespace fun {
template <typename T> const auto identity = [](const T& t) -> const T& { return t; };
template <typename T> const auto first = [](const T& t) { return t.first; };
template <typename T> const auto second = [](const T& t) { return t.second; };
template <typename T, u32 n> const auto nth = [](const T& t) { return get<n>(t); };
template <typename TOut, typename F, typename TIn> vector<TOut> transf(const TIn& in, F f) { vector<TOut> v; transform(in.begin(), in.end(), back_inserter(v), f); return v; }
template <typename F, typename T> void sort(T& v, F f) { sort(v.begin(), v.end(), f); }
template <typename TOut, typename F, typename TIn> vector<TOut> sorted(const TIn& in, F f) { vector<TOut> v(in.begin(), in.end()); sort(v, f); return v; }
} // fun
// }}}
// class traits {{{
template<class...> using void_t = void;
template <class, class = void> struct has_repr : false_type {};
template <class T> struct has_repr<T, void_t<decltype(declval<T>()._repr())>> : true_type {};
template <class, class = void> struct has_str : false_type {};
template <class T> struct has_str<T, void_t<decltype(declval<T>()._str())>> : true_type {};
template <class, class = void> struct has_read : false_type {};
template <class T> struct has_read<T, void_t<decltype(T::_read)>> : true_type {};
template <class, class = void> struct is_map : false_type {};
template <class T> struct is_map<T, void_t<typename T::key_type, typename T::mapped_type>> : true_type {};
template <class, class = void> struct is_set : false_type {};
template <class T> struct is_set<T, void_t<typename T::key_type>> : true_type {};
// }}}
// str {{{
template <typename T, class = void> struct _Str { string operator()(const T& t) { return to_string(t); } };
template <> struct _Str<string> { string operator()(const string& t) { return t; } };
template <> struct _Str<const char*> { string operator()(const char* t) { return t; } };
template <typename T> string str(const T& t) { return _Str<T>()(t); }
template <typename T> struct _Str<T, enable_if_t<has_str<T>::value>> { string operator()(const T& t) {
    return t._str();
} };
template <typename T>
struct _Str<vector<T>> {
    string operator()(const vector<T>& t) {
        string s = "";
        for (i64 i = 0; i < isize(t); i++) {
            s += str(t[i]);
            if (i != isize(t) - 1)
                s += ' ';
        }
        return s;
    }
};
// }}}
// string tuples {{{
template <i32 rev_index, typename T> struct _StrTuple { string operator() (const T& tpl) {
    return str(get<tuple_size<T>::value - rev_index>(tpl)) + ' ' + _StrTuple<rev_index - 1, T>()(tpl);
} };
template <typename T> struct _StrTuple<1, T> { string operator()(const T& t) {
    return str(get<tuple_size<T>::value - 1>(t));
} };
template <> struct _StrTuple<0, tuple<>> { string operator()(const tuple<>&) { return ""; } };
template <typename ...Ts> struct _Str<tuple<Ts...>> { string operator()(const tuple<Ts...>& t) {
    using T = tuple<Ts...>;
    return _StrTuple<tuple_size<T>::value, T>()(t);
} };
template <class T1, class T2> struct _Str<pair<T1, T2>> { string operator()(const pair<T1, T2>& p) {
    return str(make_tuple(p.first, p.second));
} };
// }}}
// repr {{{
template <typename T, class = void> struct _Repr { string operator()(const T& t) { return str(t); } };
template <typename T> string repr(const T& t) { return _Repr<T>()(t); }
template <> struct _Repr<string> { string operator()(const string& t) { return '"' + t + '"'; } };
template <> struct _Repr<const char*> { string operator()(const char* const& t) { return repr(string(t)); } };
template <typename T> struct _Repr<T, enable_if_t<has_repr<T>::value>> { string operator()(const T& t) {
    return t._repr();
} };
template <typename T>
struct _Repr<vector<T>> {
    string operator()(const vector<T>& t) {
        string s = "[";
        for (i64 i = 0; i < isize(t); i++) {
            s += repr(t[i]);
            if (i != isize(t) - 1)
                s += ',';
        }
        s += ']';
        return s;
    }
};
template <typename T>
struct _Repr<T, enable_if_t<is_set<T>::value && !is_map<T>::value>> {
    string operator()(const T& t) {
        string s = "{";
        for (auto it = t.cbegin(); it != t.cend(); it++) {
            s += repr(*it);
            if (!it_last(it, t))
                s += ',';
        }
        s += '}';
        return s;
    }
};
template <typename T>
struct _Repr<T, enable_if_t<is_map<T>::value>> {
    string operator()(const T& t) {
        string s = "{";
        for (auto it = t.cbegin(); it != t.cend(); it++) {
            s += repr(it->first) + ':' + repr(it->second);
            if (!it_last(it, t))
                s += ',';
        }
        s += '}';
        return s;
    }
};
// }}}
// struct repr helpers {{{
string _repr_helper(i64 i, const vector<string>& header) {
    massert(i == isize(header), "header too long");
    return "";
}
template <typename T, typename ...Ts>
string _repr_helper(i64 i, const vector<string>& header, const T& t, const Ts&... ts) {
    massert(i < isize(header), "header too short");
    auto s = header[i] + "=" + repr(t);
    if (i < isize(header) - 1)
        s += "," + _repr_helper(i + 1, header, ts...);
    return s;
}
template <typename ...Ts>
string make_repr(string classname, const vector<string>& header, const Ts&... ts) {
    return classname + '(' + _repr_helper(0, header, ts...) + ')';
}
/// }}}
// repring tuples {{{
template <i32 rev_index, typename T> struct _ReprTuple { string operator() (const T& tpl) {
    return repr(get<tuple_size<T>::value - rev_index>(tpl)) + ',' + _ReprTuple<rev_index - 1, T>()(tpl);
} };
template <typename T> struct _ReprTuple<1, T> { string operator()(const T& t) {
    return repr(get<tuple_size<T>::value - 1>(t));
} };
template <> struct _ReprTuple<0, tuple<>> { string operator()(const tuple<>&) { return ""; } };
template <typename ...Ts> struct _Repr<tuple<Ts...>> { string operator()(const tuple<Ts...>& t) {
    using T = tuple<Ts...>;
    return '(' + _ReprTuple<tuple_size<T>::value, T>()(t) + ')';
} };
template <class T1, class T2> struct _Repr<pair<T1, T2>> { string operator()(const pair<T1, T2>& p) {
    return repr(make_tuple(p.first, p.second));
} };
// }}}
// print containers {{{
template <typename It> void _print_collection(ostream& os, It begin, It end) { os << "["; while (begin != end) { os << *(begin++); if (begin != end) os << ','; } os << "]"; }
#define MAKE_PRINTER_1(container) template <typename T> ostream& operator<<(ostream& os, const container<T>& t) { _print_collection(os, t.begin(), t.end()); return os; }
#define MAKE_PRINTER_2(container) template <typename T1, typename T2> ostream& operator<<(ostream& os, const container<T1, T2>& t) { _print_collection(os, t.begin(), t.end()); return os; }
MAKE_PRINTER_1(vector)
MAKE_PRINTER_2(map)
MAKE_PRINTER_1(set)
MAKE_PRINTER_2(unordered_map)
MAKE_PRINTER_1(unordered_set)
#undef MAKE_PRINTER_1
#undef MAKE_PRINTER_2
// }}}
// read/write {{{
template <typename T, class = void> T read() { T e; cin >> e; return e; }
template <typename T, enable_if_t<has_read<T>::value>> T read() { T t; t._read(); return t; }
void read() {}
template <typename T, typename ...Ts> void read(T& v, Ts& ...ts) { v = read<T>(); read(ts...); }
template <typename T> vector<T> readv(i64 n) { vector<T> v; readv(n, v); return v; }
template <typename T> void readv(i64 n, vector<T>& v) { for (i64 i = 0; i < n; i++) v.push_back(read<T>()); }
#define PRINTERS(FNAME, OUTP) \
    void FNAME() {} \
    template <typename T, typename ...Ts> void FNAME(const T& t, const Ts& ...ts) { OUTP << t << ' '; FNAME(ts...); } \
    template <typename T> void FNAME(const T& t) { OUTP << t; } \
    void FNAME##ln() { FNAME('\n'); } \
    template <typename T, typename ...Ts> void FNAME##ln(const T& t, const Ts& ...ts) { OUTP << t << ' '; FNAME##ln(ts...); } \
    template <typename T> void FNAME##ln(const T& t) { FNAME(t); FNAME##ln(); } \
    template <typename T, typename F> void FNAME##v(const T& t, F f) { for (i64 i = 0; i < isize(t); i++) if (i == isize(t) - 1) FNAME(f(t[i])); else FNAME(f(t[i]), ""); FNAME##ln(); } \
    template <typename T> void FNAME##v(const T& t) { FNAME##v(t, fun::identity<typename T::value_type>); }
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
