#include <bits/stdc++.h>
#include "basic.h"
using namespace std;

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

