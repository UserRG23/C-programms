#include <stdio.h>

static long long unsigned gcd(long long unsigned a, long long unsigned b) {
    while (b) {
        long long unsigned t = a % b;
        a = b;
        b = t;
    }
    return ( a & ( 1LL << 63 ) ) != 0 ? -a : a;
}


static long long unsigned extended_gcd(long long unsigned a, long long unsigned b, long long unsigned *x, long long unsigned *y) {
    if (b == 0) { *x = 1; *y = 0; return a; }
    long long unsigned x1, y1;
    long long unsigned g = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}


static long long unsigned modinv(long long unsigned a, long long unsigned m) {
    long long unsigned x, y;
    long long unsigned g = extended_gcd(a, m, &x, &y);
    if (g != 1) return -1;                  
    long long unsigned inv = x % m;
    if (inv & ( 1LL << 63 )) inv += m;
    return inv;
}

int main(void) {
    long long unsigned a, b;

    printf("Track length:\n");
    if (scanf(" %llu %llu", &a, &b) != 2) {
        printf("Invalid input.\n");
        return 0;
    }
    if ( a & ( 1LL << 63 ) || a == 0  || b & ( 1LL << 63 ) || b == 0 || a == b) {
        printf("Invalid input.\n");
        return 0;
    }

    printf("Distance:\n");
    char mode;
    long long unsigned L;
    if (scanf(" %c %llu", &mode, &L) != 2) {
        printf("Invalid input.\n");
        return 0;
    }
    if ((mode != '+' && mode != '-') || L & ( 1LL << 63 ) ) {
        printf("Invalid input.\n");
        return 0;
    }

    
    long long unsigned d = gcd(a, b);
    if (L % d != 0) {
        printf("No solution.\n");
        return 0;
    }

    
    long long unsigned ap = a / d, bp = b / d, Lp = L / d;

    
    if (Lp == 0) {
        if (mode == '+') {
            printf("= %llu * 0 + %llu * 0\n", a, b );
        }
        printf("Total variants: %d\n", 1);
        return 0;
    }

    
    long long unsigned inv = modinv(ap % bp, bp);                  
    if (inv & ( 1LL << 63 )) { 
        printf("No solution.\n");
        return 0;
    }

    
    long long unsigned Lmod = Lp % bp;
    long long unsigned r = (long long unsigned)((Lmod * (inv % bp)) % bp);
    if (r & (1LL << 63)) r += bp;

    
    long long unsigned maxX = Lp / ap;

    if (r > maxX) {
        printf("No solution.\n");
        return 0;
    }

    long long unsigned cnt = (maxX - r) / bp + 1;

    if (mode == '+') {
        for (long long unsigned t = 0; t < cnt; ++t) {
            long long unsigned x = r + t * bp;                    
			x = x & (1LL << 63) ? -x : x; 
            
            long long unsigned y = (Lp - ap * x) / bp;
			y = y & (1LL << 63) ? -y : y; 
            
            printf("= %llu * %llu + %llu * %llu\n", a, x, b, y);
        }
        printf("Total variants: %llu\n", cnt);
    } else { 
        printf("Total variants: %llu\n", cnt);
    }

    return 0;
}

