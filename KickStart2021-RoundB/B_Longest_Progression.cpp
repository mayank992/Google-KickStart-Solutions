#include<bits/stdc++.h>

using namespace std;
#define pii pair<int, int>

int main() {
  int tt; cin >> tt;
  for (int t = 1; t <= tt; t++) {
    cout << "Case #" << t << ": ";
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
      cin >> vec[i];
    }
    vector<pii> prefix(n), suffix(n);
    prefix[0] = suffix[n - 1] = {1, INT_MAX};
    prefix[1] = {2, vec[0] - vec[1]};
    suffix[n - 2] = {2, vec[n - 2] - vec[n - 1]};
    int ans = 2;
    for (int i = 2; i < n; i++) {
      prefix[i] = {(vec[i - 1] - vec[i] == prefix[i - 1].second) 
                  ? prefix[i - 1].first + 1 
                  : 2, vec[i - 1] - vec[i]};

      ans = max(ans, prefix[i].first);
    }
    for (int j = n - 3; j >= 0; j--) {
      suffix[j] = {(vec[j] - vec[j + 1] == suffix[j + 1].second) 
                  ? suffix[j + 1].first + 1 
                  : 2, vec[j] - vec[j + 1]};

      ans = max(ans, suffix[j].first);
    }

    ans = max(ans, prefix[n - 2].first + 1);
    ans = max(ans, suffix[1].first + 1);

    for (int i = 1; i < n - 1; i++) {
      int diff = vec[i - 1] - vec[i + 1];
      if (diff % 2 == 0) {
        diff /= 2;
        int len = (prefix[i - 1].second == diff ? prefix[i - 1].first : 1)
                + (suffix[i + 1].second == diff ? suffix[i + 1].first : 1)
                + 1;
                
        ans = max(ans, len);
      } 
      ans = max(ans, max(prefix[i - 1].first, suffix[i + 1].first) + 1);
    }
    cout << ans << "\n";
  }
  return 0;
}