#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
const int UMBRAL = 32;

string quitarCeros(string s) {
  int i = 0;
  while (i < (int)s.size() - 1 && s[i] == '0') i++;
  return s.substr(i);
}

string sumar(string a, string b) {
  string res = "";
  int i = a.size() - 1, j = b.size() - 1, llevo = 0;
  while (i >= 0 || j >= 0 || llevo > 0) {
    int suma = llevo;
    if (i >= 0) suma += a[i--] - '0';
    if (j >= 0) suma += b[j--] - '0';
    res += char('0' + suma % 10);
    llevo = suma / 10;
  }
  reverse(res.begin(), res.end());
  return quitarCeros(res);
}

string restar(string a, string b) {
  string res = "";
  int i = a.size() - 1, j = b.size() - 1, prestado = 0;
  while (i >= 0) {
    int d = (a[i] - '0') - prestado;
    if (j >= 0) d -= b[j--] - '0';
    if (d < 0) { d += 10; prestado = 1; }
    else prestado = 0;
    res += char('0' + d);
    i--;
  }
  reverse(res.begin(), res.end());
  return quitarCeros(res);
}

string escolar(string a, string b) {
  int la = a.size(), lb = b.size();
  vector<int> res(la + lb, 0);

  for (int i = la - 1; i >= 0; i--) {
    for (int j = lb - 1; j >= 0; j--) {
        res[i + j + 1] += (a[i] - '0') * (b[j] - '0');
    }
  }

  for (int k = la + lb - 1; k > 0; k--) {
    res[k - 1] += res[k] / 10;
    res[k] %= 10;
  }
  string s = "";
  for (int d : res) s += char('0' + d);
  return quitarCeros(s);
}

string karatsuba(string x, string y) {
  if ((int)x.size() <= UMBRAL || (int)y.size() <= UMBRAL) {
    return escolar(x, y);
  }

  int n = max(x.size(), y.size());
  x = string(n - x.size(), '0') + x;
  y = string(n - y.size(), '0') + y;

    int m = n / 2;                       
    string a = x.substr(0, n - m), b = x.substr(n - m);
    string c = y.substr(0, n - m), d = y.substr(n - m);

    string z2 = karatsuba(a, c);                                  
    string z0 = karatsuba(b, d);                                  
    string z1 = karatsuba(sumar(a, b), sumar(c, d));              
    z1 = restar(restar(z1, z2), z0);                              

    string r = sumar(z2 + string(2 * m, '0'), z1 + string(m, '0'));
    r = sumar(r, z0);
    return r;
}

int main() {
    string a, b;
    cin >> a >> b;

    auto t1 = chrono::steady_clock::now();
    string rk = karatsuba(a, b);
    auto t2 = chrono::steady_clock::now();

    string re = escolar(a, b);
    auto t3 = chrono::steady_clock::now();

    double tk = chrono::duration<double, milli>(t2 - t1).count();
    double te = chrono::duration<double, milli>(t3 - t2).count();

    cout << rk << endl;  
    cerr << "Karatsuba: " << tk << " ms" << endl;
    cerr << "Escolar:   " << te << " ms" << endl;
    cerr << (rk == re ? "Resultados iguales" : "Resultados no iguales") << endl;
    return 0;
}