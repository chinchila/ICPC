// Computa todos os primos menores que n
// O(n)
// lp[i] = the least (menor) prime factor of i
// pr[i] = is the ith prime
// cnt = number of primes until n (size of pr)
// phi[i] = totient euler function of i
// mob[i] = mobius function of i
// SE NAO PRECISAR DE PHI NEM MOB NAO COPIA ELES :)
int pr[MAXN];
bool is_composite[MAXN];
int lp[MAXN];
int phi[MAXN];
int cnt;

void linear_sieve(int n) {
	phi[1] = mob[1] = 1;
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) {
			lp[i] = pr[cnt++] = i;
			phi[i] = i - 1;
			mob[i] = -1;
		}
		for (int j = 0; j < cnt && i * pr[j] < n; ++j) {
			long long v = i * pr[j];
			is_composite[v] = true;
			lp[v] = pr[j];
			if (i % pr[j] == 0) {
				mob[v] = 0;
				phi[v] = phi[i] * pr[j];
				break;
			} else {
				mob[v] = -mob[i];
				phi[v] = phi[i] * phi[pr[j]];
			}
		}
	}
}

// O(n log log n)
void sieve( int n ) {
	vector<bool> is_prime(n+1, true);
	is_prime[0] = is_prime[1] = false;
	for (int i = 2; i * i <= n; i++) {
		if (is_prime[i]) {
			for (int j = i * i; j <= n; j += i)
				is_prime[j] = false;
		}
	}
}

