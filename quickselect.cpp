#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int quickselect(vector<int>& a, int pos) {
  int izq = 0, der = a.size() - 1;
  while (true) {
      if (izq == der) return a[izq];
      int pivote = a[izq + rand() % (der - izq + 1)];
      int men = izq, i = izq, may = der;
      while (i <= may) {
        if (a[i] < pivote) {
        swap(a[men], a[i]);
        men++;
        i++;
        } else if (a[i] > pivote) {
        swap(a[i], a[may]);
        may--;
        } else {
          i++;
        }
      }

      if (pos < men) {
        der = men - 1;        
      } else if (pos > may) {
        izq = may + 1;       
      } else {
        return pivote;       
      }
  }
}

int main() {
  srand(time(NULL));
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  cout << quickselect(a, n - k) << endl;
  return 0;
}