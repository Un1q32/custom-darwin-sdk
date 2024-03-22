long double powl(long double x, long double y) {
  long double result = 1.0;
  for (int i = 0; i < y; i++)
    result *= x;
  return result;
}

double pow(double x, double y) { return powl(x, y); }

float powf(float x, float y) { return powl(x, y); }

long double ldexpl(long double x, int n) { return x * powl(2.0, n); }

double ldexp(double x, int n) { return ldexpl(x, n); }

float ldexpf(float x, int n) { return ldexpl(x, n); }
