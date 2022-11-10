
#include <iostream>
#include <Lib.h>
#include <chrono>
#include <cmath>

using namespace std;

int main() {
    //you must change/expand this code

    cout << "n,TA(n),TB(n),TC(n),log(n),log(TA),log(TB),log(TC)" << endl;

    for (int n = 100; n <= 3000; n += 100) {
        auto start = chrono::steady_clock::now();
        Lib::algorithmA(n);
        auto end = chrono::steady_clock::now();
        int TA = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start= chrono::steady_clock::now();
        Lib::algorithmB(n);
        end = chrono::steady_clock::now();
        int TB = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::steady_clock::now();
        Lib::algorithmC(n);
        end = chrono::steady_clock::now();
        int TC = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        cout << n << ',' << TA << ',' << TB << ',' << TC << ','
        << log2(n) << ',' << log2(TA) <<',' << log2(TB) <<',' << log2(TC) <<endl;
    }


/*
    int n = 20;
    Lib::algorithmA(n);
    cout << "Successful execution" <<endl;
*/

    return 0;
}