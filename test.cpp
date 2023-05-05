//Bahdan Shakh
//b.shakh@innopolis.university
#include<bits/stdc++.h>
using namespace std;

#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"

int main() {

   int v0, k0;
   double a1,b1,a2,b2;
   double T, N;
   cout << setprecision(2) << fixed;
   cin >> v0 >> k0;
   cin >> a1 >> b1 >> a2 >> b2;
   cin >> T >> N;

   double sqrt_a1a2 = sqrt(a1 * a2);
   double sqrt_a1 = sqrt(a1);
   double sqrt_a2 = sqrt(a2);

   double step = T/N;
   vector <double> t;
   for (double i = 0; i <= T; i += step) {
      t.push_back(i);
   }
   double fix1 = a2 / b2, fix2 = a1 / b1;
   v0 = v0 - fix1;
   k0 = k0 - fix2;

   vector <double> v, k;
   for (double time : t){
      v.push_back( v0 * cos(sqrt_a1a2 * time) - k0 * sqrt_a2 * b1 * sin(sqrt_a1a2 * time) / (b2 * sqrt_a1) + fix1);
      k.push_back( v0 * sqrt_a1 * b2 * sin(sqrt_a1a2 * time) / (b1 * sqrt_a2) + k0 * cos(sqrt_a1a2 * time) + fix2);
   }

   FILE* pipe1 = _popen(GNUPLOT_NAME, "w");
   FILE* pipe2 = _popen(GNUPLOT_NAME, "w");

   fprintf(pipe1, "plot '-' using 1:2 with lines title 'victims', '-' using 1:2 with lines title 'killers'\n\n'");
   for (int i = 0; i <= N; i++)
      fprintf(pipe1, "%lf %lf\n", t[i], v[i]);

   fprintf(pipe1, "e\n");

   for (int i = 0; i <= N; i++)
      fprintf(pipe1, "%lf %lf\n", t[i], k[i]);

   fprintf(pipe1, "e\n");

   fprintf(pipe2, "plot '-' using 1:2 with lines title 'v to k'\n");
   for (int i = 0; i <= N; i++)
      fprintf(pipe2, "%lf %lf\n", k[i], v[i]);

   fprintf(pipe2, "e\n");
   _pclose(pipe1);
   _pclose(pipe2);

}