#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Punto {
    int x, y;
};

vector<Punto> P;

long long dist2(const Punto& a, const Punto& b) {
  long long dx = a.x - b.x;
  long long dy = a.y - b.y;
  return dx * dx + dy * dy;
}

bool porX(const Punto& a, const Punto& b) { return a.x < b.x; }
bool porY(const Punto& a, const Punto& b) { return a.y < b.y; }

const long long INF = 4000000000000000000LL;

long long resolv(int izq, int der) {
  if (der - izq <= 3) {
    long long mejor = INF;
    for (int i = izq; i < der; i++)
      for (int j = i + 1; j < der; j++)
        mejor = min(mejor, dist2(P[i], P[j]));
      sort(P.begin() + izq, P.begin() + der, porY);
    return mejor;
  }

  int med = (izq + der) / 2;
  int xMedio = P[med].x;    

  long long d = min(resolv(izq, med), resolv(med, der));

  inplace_merge(P.begin() + izq, P.begin() + med, P.begin() + der, porY);

  vector<Punto> franja;
  for (int i = izq; i < der; i++) {
    long long dx = P[i].x - xMedio;
    if (dx * dx < d) franja.push_back(P[i]);
  }

  for (int i = 0; i < (int)franja.size(); i++) {
    for (int j = i + 1; j < (int)franja.size(); j++) {
      long long dy = franja[j].y - franja[i].y;
      if (dy * dy >= d) break;
      d = min(d, dist2(franja[i], franja[j]));
    }
  }
  return d;
}

int main() {
  int n;
  while (scanf("%d", &n) == 1 && n != 0) {
    P.assign(n, Punto());
    for (int i = 0; i < n; i++) scanf("%d %d", &P[i].x, &P[i].y);

    if (n <= 1) {
    printf("INFINITY\n");
    continue;
    }

    sort(P.begin(), P.end(), porX);    
    long long d = resolv(0, n);

    if (d >= 100000000LL) {                
    printf("INFINITY\n");
    } else { 
    printf("%.4f\n", sqrt((double)d));
    }
  }
  return 0;
}