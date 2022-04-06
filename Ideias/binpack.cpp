#include<iostream>
using namespace std;
void binPacking(int *a, int size, int n) {
   int binCount = 1;
   int m = size;
   for (int i = 0; i < n; i++) {
      if (m - *(a + i) > 0) {
         m -= *(a + i);
         continue;
      } else {
         binCount++;
         m = size;
         i--;
      }
   }
   cout << "Number of bins required: " << binCount;
}
int main(int argc, char **argv) {
   cout << "Enter the number of items in Set: ";
   int n;
   cin >> n;
   cout << "Enter " << n << " items:";
   int a[n];
   for (int i = 0; i < n; i++)
      cin >> a[i];
   cout << "Enter the bin size: ";
   int size;
   cin >> size;
   binPacking(a, size, n);
}