//═══════════════════════════════════════════════════════════════════════════════
//                           MATH & NUMBER THEORY
//═══════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using u128 = __uint128_t;
#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const ll MOD = 1e9 + 7;
const ll INF = 1e18;
const int MAXN = 1e6 + 5;

//═══════════════════════════════════════════════════════════════════════════════
// BASIC ARITHMETIC & MODULAR OPERATIONS
//═══════════════════════════════════════════════════════════════════════════════

// Binary exponentiation: a^b % mod
// Time: O(log b), Space: O(1)
ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// Safe modular operations (handles negative numbers)
ll add(ll a, ll b, ll mod = MOD) { return ((a % mod) + (b % mod) + mod) % mod; }
ll sub(ll a, ll b, ll mod = MOD) { return ((a % mod) - (b % mod) + mod) % mod; }
ll mul(ll a, ll b, ll mod = MOD) { return ((a % mod) * (b % mod)) % mod; }
ll inv(ll a, ll mod = MOD) { return power(a, mod - 2, mod); } // mod must be prime

// Modular inverse using extended GCD (works for any coprime mod)
ll mod_inv(ll a, ll mod) {
    ll x, y;
    ll g = extgcd(a, mod, x, y);
    if (g != 1) return -1; // no inverse exists
    return (x % mod + mod) % mod;
}

// GCD & LCM
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Extended GCD: finds gcd(a,b) and x,y such that ax + by = gcd(a,b)
// Time: O(log min(a,b))
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1, y = 0; return a; }
    ll g = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

//═══════════════════════════════════════════════════════════════════════════════
// PRIME TESTING & FACTORIZATION
//═══════════════════════════════════════════════════════════════════════════════

// Miller-Rabin primality test (deterministic for n < 2^64)
// Time: O(k log n), k = 7 (constant)
ull mulmod(ull a, ull b, ull m) { return (u128)a * b % m; }

ull powmod(ull a, ull b, ull m) {
    ull res = 1;
    while (b) {
        if (b & 1) res = mulmod(res, a, m);
        a = mulmod(a, a, m);
        b >>= 1;
    }
    return res;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (ull p : {2,3,5,7,11,13,17,19,23,29,31,37})
        if (n % p == 0) return n == p;
    
    ull d = n - 1, s = 0;
    while (!(d & 1)) d >>= 1, s++;
    
    for (ull a : {2,325,9375,28178,450775,9780504,1795265022}) {
        if (a >= n) continue;
        ull x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (ull r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// Pollard's Rho factorization
// Time: O(n^1/4) expected
ull pollard(ull n) {
    if (n % 2 == 0) return 2;
    if (isPrime(n)) return n;
    
    auto f = [&](ull x, ull c) { return (mulmod(x, x, n) + c) % n; };
    for (ull c = 1; c <= 20; c++) {
        ull x = 2, y = 2, d = 1;
        while (d == 1) {
            x = f(x, c);
            y = f(f(y, c), c);
            d = gcd(x > y ? x - y : y - x, n);
        }
        if (d > 1 && d < n) return d;
    }
    return n; // fallback
}

// Complete factorization using Pollard + Miller-Rabin
void factor(ull n, vector<ull> &factors) {
    if (n == 1) return;
    if (isPrime(n)) { factors.push_back(n); return; }
    ull d = pollard(n);
    factor(d, factors);
    factor(n / d, factors);
}

//═══════════════════════════════════════════════════════════════════════════════
// PRIME FACTORIZATION METHODS
//═══════════════════════════════════════════════════════════════════════════════

// Method 1: Simple trial division (good for small numbers)
// Time: O(√n)
vector<pair<ll, int>> getPrimeFactorsWithMultiplicity(ll n) {
    vector<pair<ll, int>> factors;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                n /= i;
                cnt++;
            }
            factors.push_back({i, cnt});
        }
    }
    if (n > 1) factors.push_back({n, 1});
    return factors;
}

vector<ll> getPrimeFactorsDistinct(ll n) {
    vector<ll> factors;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}

//═══════════════════════════════════════════════════════════════════════════════
// SIEVE & MULTIPLICATIVE FUNCTIONS
//═══════════════════════════════════════════════════════════════════════════════

// SPF (Smallest Prime Factor) sieve + fast factorization
// Time: O(n log log n) precompute + O(log n) per query
int spf[MAXN];
void computeSPF(int n = MAXN - 1) {
    for (int i = 1; i <= n; i++) spf[i] = i;
    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j <= n; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

// Method 2: Using SPF for multiple queries (FASTEST for many queries)
vector<pair<int, int>> getPrimeFactorsWithMultiplicitySPF(int x) {
    vector<pair<int, int>> factors;
    while (x > 1) {
        int p = spf[x];
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        factors.push_back({p, cnt});
    }
    return factors;
}

vector<int> getPrimeFactorsDistinctSPF(int x) {
    vector<int> factors;
    while (x > 1) {
        int p = spf[x];
        factors.push_back(p);
        while (x % p == 0) x /= p;
    }
    return factors;
}

// Method 3: Using Pollard's Rho for large numbers
vector<pair<ull, int>> getPrimeFactorsLarge(ull n) {
    vector<ull> raw_factors;
    factor(n, raw_factors);
    
    map<ull, int> factor_count;
    for (ull f : raw_factors) factor_count[f]++;
    
    vector<pair<ull, int>> result;
    for (auto [prime, count] : factor_count) {
        result.push_back({prime, count});
    }
    sort(result.begin(), result.end());
    return result;
}

// Linear sieve for primes, phi, mu, and other multiplicative functions
// Time: O(n), Space: O(n)
vector<int> primes;
int phi[MAXN], mu[MAXN], d[MAXN], sigma[MAXN]; // d = number of divisors, sigma = sum of divisors
bool is_comp[MAXN];

void linearSieve(int n = MAXN - 1) {
    phi[1] = mu[1] = d[1] = sigma[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!is_comp[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
            mu[i] = -1;
            d[i] = 2;
            sigma[i] = i + 1;
        }
        for (int j = 0; j < primes.size() && i * primes[j] <= n; j++) {
            int ip = i * primes[j];
            is_comp[ip] = true;
            
            if (i % primes[j] == 0) {
                phi[ip] = phi[i] * primes[j];
                mu[ip] = 0;
                
                // Count powers of primes[j] in i
                int temp = i, cnt = 0;
                while (temp % primes[j] == 0) {
                    temp /= primes[j];
                    cnt++;
                }
                d[ip] = d[i] / (cnt + 1) * (cnt + 2);
                sigma[ip] = sigma[i] / ((power(primes[j], cnt + 1, INF) - 1) / (primes[j] - 1)) 
                           * ((power(primes[j], cnt + 2, INF) - 1) / (primes[j] - 1));
                break;
            }
            phi[ip] = phi[i] * (primes[j] - 1);
            mu[ip] = -mu[i];
            d[ip] = d[i] * 2;
            sigma[ip] = sigma[i] * (primes[j] + 1);
        }
    }
}

//═══════════════════════════════════════════════════════════════════════════════
// COMBINATORICS
//═══════════════════════════════════════════════════════════════════════════════

// Precomputed factorials and inverse factorials
// Time: O(n) precompute + O(1) per query
ll fact[MAXN], inv_fact[MAXN];

void precompute_factorials(int n = MAXN - 1) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact[n] = inv(fact[n]);
    for (int i = n - 1; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}

ll C(int n, int r) {
    if (r > n || r < 0) return 0;
    return fact[n] * inv_fact[r] % MOD * inv_fact[n-r] % MOD;
}

ll P(int n, int r) {
    if (r > n || r < 0) return 0;
    return fact[n] * inv_fact[n-r] % MOD;
}

// Lucas theorem for C(n,r) mod p where p is prime
// Time: O(log_p(n))
ll lucas(ll n, ll r, ll p) {
    if (r == 0) return 1;
    return C(n % p, r % p) * lucas(n / p, r / p, p) % p;
}

// Catalan numbers: C_n = C(2n,n)/(n+1)
ll catalan(int n) {
    return C(2*n, n) * inv(n+1) % MOD;
}

// Stars and Bars: Number of ways to put k identical balls into n distinct boxes (non-negative integers allowed)
// Formula: C(k + n - 1, n - 1)
ll stars_and_bars(int k, int n) {
    if (k < 0 || n <= 0) return 0;
    return C(k + n - 1, n - 1);
}

//═══════════════════════════════════════════════════════════════════════════════
// ADVANCED NUMBER THEORY
//═══════════════════════════════════════════════════════════════════════════════

// Chinese Remainder Theorem for two congruences
// Solves: x ≡ a1 (mod m1), x ≡ a2 (mod m2)
// Time: O(log min(m1,m2))
pair<ll,ll> crt2(ll a1, ll m1, ll a2, ll m2) {
    ll g = gcd(m1, m2);
    if ((a2 - a1) % g != 0) return {-1, -1}; // no solution
    ll lcm_val = m1 / g * m2;
    ll x, y;
    extgcd(m1 / g, m2 / g, x, y);
    ll res = (a1 + (a2 - a1) / g * x % (m2 / g) * m1) % lcm_val;
    return {(res + lcm_val) % lcm_val, lcm_val};
}

// General CRT (requires pairwise coprime moduli)
ll crt(vector<ll> &a, vector<ll> &m) {
    ll res = a[0], mod = m[0];
    for (int i = 1; i < a.size(); i++) {
        auto [x, new_mod] = crt2(res, mod, a[i], m[i]);
        if (x == -1) return -1; // no solution
        res = x, mod = new_mod;
    }
    return res;
}

// Baby-step Giant-step (Discrete Logarithm)
// Solves: a^x ≡ b (mod m), returns smallest x
// Time: O(√m), Space: O(√m)
ll bsgs(ll a, ll b, ll m) {
    a %= m; b %= m;
    ll n = sqrt(m) + 1;
    unordered_map<ll, ll> vals;
    ll cur = 1;
    for (ll i = 0; i < n; i++) {
        if (vals.find(cur) == vals.end()) vals[cur] = i;
        cur = cur * a % m;
    }
    ll factor = power(inv(power(a, n, m), m), 1, m);
    cur = b;
    for (ll i = 0; i < n; i++) {
        if (vals.count(cur)) {
            ll ans = i * n + vals[cur];
            if (ans > 0) return ans;
        }
        cur = cur * factor % m;
    }
    return -1; // no solution
}

// Quadratic residue (Legendre symbol)
// Returns 1 if a is quadratic residue mod p, -1 if not, 0 if a ≡ 0 (mod p)
int legendre(ll a, ll p) {
    return power(a, (p-1)/2, p);
}

// Tonelli-Shanks algorithm for modular square root
// Finds x such that x^2 ≡ n (mod p) where p is odd prime
ll tonelli_shanks(ll n, ll p) {
    if (legendre(n, p) != 1) return -1; // no solution
    
    // Find Q and S such that p-1 = Q * 2^S with Q odd
    ll Q = p - 1, S = 0;
    while (Q % 2 == 0) Q /= 2, S++;
    
    if (S == 1) return power(n, (p+1)/4, p);
    
    // Find quadratic non-residue z
    ll z = 2;
    while (legendre(z, p) != p - 1) z++;
    
    ll M = S, c = power(z, Q, p), t = power(n, Q, p), R = power(n, (Q+1)/2, p);
    
    while (t != 1) {
        ll i = 1, temp = t * t % p;
        while (temp != 1) temp = temp * temp % p, i++;
        
        ll b = c;
        for (ll j = 0; j < M - i - 1; j++) b = b * b % p;
        
        M = i;
        c = b * b % p;
        t = t * c % p;
        R = R * b % p;
    }
    return R;
}

// Matrix exponentiation for linear recurrences
// Time: O(k^3 log n) where k is matrix size
vector<vector<ll>> matmul(const vector<vector<ll>> &a, const vector<vector<ll>> &b) {
    int n = a.size(), m = b[0].size(), p = b.size();
    vector<vector<ll>> c(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    return c;
}

vector<vector<ll>> matpow(vector<vector<ll>> base, ll exp) {
    int n = base.size();
    vector<vector<ll>> res(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) res[i][i] = 1; // identity
    while (exp > 0) {
        if (exp & 1) res = matmul(res, base);
        base = matmul(base, base);
        exp >>= 1;
    }
    return res;
}

//═══════════════════════════════════════════════════════════════════════════════
// UTILITY FUNCTIONS
//═══════════════════════════════════════════════════════════════════════════════

// Get all divisors of n
// Time: O(√n)
vector<ll> getDivisors(ll n) {
    vector<ll> divs;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i);
        }
    }
    sort(divs.begin(), divs.end());
    return divs;
}

// Get number of divisors using prime factorization
int countDivisors(ll n) {
    int count = 1;
    for (ll i = 2; i * i <= n; i++) {
        int exp = 0;
        while (n % i == 0) {
            n /= i;
            exp++;
        }
        count *= (exp + 1);
    }
    if (n > 1) count *= 2;
    return count;
}

// Sum of divisors using prime factorization
ll sumDivisors(ll n) {
    ll sum = 1;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ll p = 1, exp = 0;
            while (n % i == 0) {
                n /= i;
                p *= i;
                exp++;
            }
            sum *= (p * i - 1) / (i - 1);
        }
    }
    if (n > 1) sum *= (n + 1);
    return sum;
}

// Euler's totient function φ(n)
// Time: O(√n)
ll phi_single(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

// Mobius function μ(n) - fundamental function in number theory
// Definition: μ(n) = 1 if n is square-free with even number of prime factors
//            μ(n) = -1 if n is square-free with odd number of prime factors  
//            μ(n) = 0 if n has a squared prime factor
// 
// Examples: μ(1) = 1, μ(2) = -1, μ(3) = -1, μ(4) = 0, μ(5) = -1, μ(6) = 1
//           μ(12) = 0 (divisible by 4=2²), μ(30) = -1 (2×3×5, 3 primes)
//
// Key properties:
// 1. Multiplicative: μ(mn) = μ(m)μ(n) if gcd(m,n) = 1
// 2. Mobius inversion formula: If g(n) = Σ_{d|n} f(d), then f(n) = Σ_{d|n} μ(d)g(n/d)
// 3. Sum over divisors: Σ_{d|n} μ(d) = 1 if n=1, 0 if n>1
//
// Applications: inclusion-exclusion, counting coprime pairs, Dirichlet series
// Time: O(√n)
int mobius(ll n) {
    int result = 1;
    int prime_count = 0; // count distinct prime factors
    
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            if (n % (i * i) == 0) return 0; // squared factor found → μ(n) = 0
            result = -result; // flip sign for each prime factor
            prime_count++;
            while (n % i == 0) n /= i; // remove all occurrences of this prime
        }
    }
    if (n > 1) { // remaining factor is prime
        result = -result;
        prime_count++;
    }
    
    // Alternative: return (prime_count % 2 == 0) ? 1 : -1; (when no squared factors)
    return result;
}

// Fast Fibonacci using matrix exponentiation
ll fibonacci(ll n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    vector<vector<ll>> base = {{1, 1}, {1, 0}};
    auto result = matpow(base, n - 1);
    return result[0][0];
}

// Prefix/Suffix GCD for range queries
int n, A[MAXN], prefixGCD[MAXN], suffixGCD[MAXN];
void buildGCD() {
    prefixGCD[0] = A[0];
    for (int i = 1; i < n; i++) prefixGCD[i] = gcd(prefixGCD[i-1], A[i]);
    suffixGCD[n-1] = A[n-1];
    for (int i = n-2; i >= 0; i--) suffixGCD[i] = gcd(suffixGCD[i+1], A[i]);
}

// Range GCD query (excluding element at index idx)
int rangeGCD(int l, int r, int exclude = -1) {
    if (exclude == -1) return gcd(prefixGCD[l], suffixGCD[r]);
    int left_gcd = (exclude > l) ? prefixGCD[exclude-1] : 0;
    int right_gcd = (exclude < r) ? suffixGCD[exclude+1] : 0;
    if (left_gcd == 0) return right_gcd;
    if (right_gcd == 0) return left_gcd;
    return gcd(left_gcd, right_gcd);
}

//═══════════════════════════════════════════════════════════════════════════════
// BONUS: COMMON SEQUENCES & FORMULAS
//═══════════════════════════════════════════════════════════════════════════════

// Sum of first n natural numbers: n(n+1)/2
ll sum_natural(ll n) { return n * (n + 1) / 2; }

// Sum of squares: n(n+1)(2n+1)/6
ll sum_squares(ll n) { return n * (n + 1) * (2 * n + 1) / 6; }

// Sum of cubes: [n(n+1)/2]^2
ll sum_cubes(ll n) { ll s = sum_natural(n); return s * s; }

// Sum of arithmetic progression: n/2 * (2a + (n-1)d)
ll sum_ap(ll a, ll d, ll n) { return n * (2 * a + (n - 1) * d) / 2; }

// Sum of geometric progression: a * (r^n - 1) / (r - 1)
ll sum_gp(ll a, ll r, ll n) {
    if (r == 1) return a * n % MOD;
    return a * (power(r, n) - 1 + MOD) % MOD * inv(r - 1) % MOD;
}

//═══════════════════════════════════════════════════════════════════════════════
// INITIALIZATION TEMPLATE
//═══════════════════════════════════════════════════════════════════════════════
/*
void init() {
    computeSPF();           // if using SPF for factorization
    linearSieve();          // if using phi/mu/multiplicative functions
    precompute_factorials(); // if using combinatorics
}

int main() {
    fastio;
    init(); // call once at the beginning
    
    int t = 1;
    // cin >> t;
    while (t--) {
        // solve();
    }
    return 0;
}

// Example usage for prime factorization:
void example_factorization() {
    int n = 12345;
    
    // Method 1: Simple (for single queries)
    auto factors1 = getPrimeFactorsWithMultiplicity(n);
    auto distinct1 = getPrimeFactorsDistinct(n);
    
    // Method 2: Using SPF (for multiple queries, precompute SPF first)
    auto factors2 = getPrimeFactorsWithMultiplicitySPF(n);
    auto distinct2 = getPrimeFactorsDistinctSPF(n);
    
    // Method 3: For large numbers (using Pollard's Rho)
    auto factors3 = getPrimeFactorsLarge(n);
}
*/
