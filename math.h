inline static double
poly_eval(const double c[], const int len, const double x) {
    int i;
    double ans = c[len - 1];
    for (i = len - 1; i > 0; i--)
        ans = c[i - 1] + x * ans;
    return ans;
}

inline static int ipow(int base, int exp) {
    int result = 1;
    while (1) {
        if (exp & 1) result *= base;
        exp >>= 1;
        if (!exp) break;
        base *= base;
    }
    return result;
}
