#include <cstdio>
#include <vector>
using namespace std;
long long c;  

void mezclar(vector<int>& a, vector<int>& temp, int izq, int med, int der) {
  int i = izq;      
  int j = med + 1; 
  int k = izq;       

  while (i <= med && j <= der) {
    if (a[i] <= a[j]) {
        temp[k++] = a[i++];
    } else {
        temp[k++] = a[j++];
        c += med - i + 1;
    }
  }
  while (i <= med) temp[k++] = a[i++];
  while (j <= der) temp[k++] = a[j++];
  for (k = izq; k <= der; k++) a[k] = temp[k];
}

void ordenar(vector<int>& a, vector<int>& temp, int izq, int der) {
  if (izq >= der) return;           
  int med = (izq + der) / 2;
  ordenar(a, temp, izq, med);       
  ordenar(a, temp, med + 1, der);   
  mezclar(a, temp, izq, med, der);   
}

int main() {
  int n;
  while (scanf("%d", &n) == 1 && n != 0) {
    vector<int> a(n), temp(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
      c = 0;
      ordenar(a, temp, 0, n - 1);
      printf("%lld\n", c);
  }
  return 0;
}