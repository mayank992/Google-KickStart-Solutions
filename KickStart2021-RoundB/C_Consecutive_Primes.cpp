#include<bits/stdc++.h>

using namespace std;

bool isPrime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int tt;
    cin >> tt;
    for (int t = 1; t <= tt; t++) {
        long long int z;
        cin >> z;
        cout << "Case #" << t << ": ";
        if (z < 35) {
            cout << (z < 15 ? 6 : 15) << "\n";
        } else {
            int l = 1, r = 1e9, x = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (1LL * mid * mid <= z)
                    x = mid, l = mid + 1;
                else
                    r = mid - 1;
            }
            // cout << x << "\n";
            vector < int > primes;
            int p = x - 1;
            while (p >= 2 && primes.size() < 2) {
                if (isPrime(p)) primes.push_back(p);
                p--;
            }
            swap(primes[0], primes[1]);
            p = x;
            while (primes.size() < 4) {
                if (isPrime(p)) primes.push_back(p);
                p++;
            }
            for (int i = 2; i >= 0; i--) {
                long long int mul = 1LL * primes[i] * primes[i + 1];
                if (mul <= z) {
                    cout << mul << "\n";
                    break;
                }
            }
        }
    }
    return 0;
}