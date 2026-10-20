#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<long long> calcular(string s) {
  vector<long long> result;

  for (int i = 0; i < (int)s.size(); i++) {
    char c = s[i];
    if (c == '+' || c == '-' || c == '*') {
      vector<long long> izq = calcular(s.substr(0, i));
      vector<long long> der = calcular(s.substr(i + 1));

      for (long long a : izq) {
        for (long long b : der) {
          if (c == '+') result.push_back(a + b);
          else if (c == '-') result.push_back(a - b);
          else result.push_back(a * b);
        }
      }
    }
  }

  if (result.empty()) {
    result.push_back(stoll(s));
  }
  return result;
}

int main() {
  string expresion;
  cin >> expresion;

  vector<long long> res = calcular(expresion);
  sort(res.begin(), res.end());   

  for (int i = 0; i < (int)res.size(); i++) {
    if (i > 0) cout << " ";
    cout << res[i];
  }
  cout << endl;
  return 0;
}