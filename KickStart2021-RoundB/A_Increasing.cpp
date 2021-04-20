#include<bits/stdc++.h>

using namespace std;

int main() {
  int tt; cin >> tt;
  for (int t = 1; t <= tt; t++) {
    int n, prev = 1; cin >> n;
    string str; cin >> str;
    cout << "Case #" << t << ": " << prev << " "; 
    for (int i = 1; i < n; i++) {
      if (str[i] <= str[i - 1]) prev = 0;
      prev = prev + 1;
      cout << prev << " ";
    } 
    cout << "\n";
  }
  return 0;
}