extern void sincos(double, double *, double *);

struct sincos_stret {
  double sin;
  double cos;
};

struct sincos_stret __sincos_stret(double x) {
  struct sincos_stret result;
  sincos(x, &result.sin, &result.cos);
  return result;
}
