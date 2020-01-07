// framework to solve problems of counting the numbers less (O(n))
// than equal to given number whose digits satisfy constraint
// it computes
//		 sum { prod(x) : 0 <= x <= z }
//	 where
//		 prod(x) = (((e * x[0]) * x[1])...) * x[n-1].
// struct Value {
//	 Value &operator+(Value y) 
//	 Value &operator*(int d)
// };
// struct Automaton {
//	 int init
//	 int size()
//	 int next(int state, int d)
//	 bool accept(int state)
// };
template <class Value, class Automaton>
Value digitDP(string z, Value e, Automaton M, bool eq = 1) {
	struct Maybe {
		Value value;
		bool undefined = true;
	};
	auto oplusTo = [&](Maybe &x, Maybe y) {
		if (x.undefined) x = y;
		else if (!y.undefined) x.value += y.value;
	};
	auto otimes = [&](Maybe x, int d) {
		x.value *= d;
		return x;
	};
	int n = z.size();
	vector<vector<Maybe>> curr(2, vector<Maybe>(M.size()));
	curr[1][M.init] = {e, false};
	for (int i = 0; i < n; ++i) {
		vector<vector<Maybe>> next(2, vector<Maybe>(M.size()));
		for (int tight = 0; tight <= 1; ++tight) {
			for (int state = 0; state < M.size(); ++state) {
				if (curr[tight][state].undefined) continue;
				int lim = (tight ? z[i] - '0' : 9);
				for (int d = 0; d <= lim; ++d) {
					int tight_ = tight && d == lim;
					int state_ = M.next(state, d);
					oplusTo(next[tight_][state_], otimes(curr[tight][state], d));
				}
			}
		}
		curr = next;
	}
	Maybe ans;
	for (int tight = 0; tight <= eq; ++tight) 
		for (int state = 0; state < M.size(); ++state) 
			if (M.accept(state)) oplusTo(ans, curr[tight][state]);
	return ans.value;
}

template <class T>
string toString(T x) { 
	stringstream ss;
	ss << x;
	return ss.str();
}

// Sum of digits from a to b
using Int = long long;
Int sumOfDigits(string z, bool eq = true) {
	struct Value {
		Int count, sum;
		Value &operator+=(Value y) { count+=y.count; sum+=y.sum; return *this; }
		Value &operator*=(int d) { sum+=count*d; return *this; }
	};
	struct Automaton {
		int init = 0;
		int size() { return 1; }
		int next(int s, int d) { return 0; }
		int accept(int s) { return true; }
	};
	return digitDP(z, (Value){1,0}, Automaton(), eq).sum;
}

void SPOJ_CPCRC1C() {
	for (long long a, b; cin >> a >> b; ) {
		if (a < 0 && b < 0) break;
		cout << sumOfDigits(toString(b), true) 
				- sumOfDigits(toString(a), false) << endl;
	}
}

//
// Count the zigzag numbers that is a multiple of M.
// Here, a number is zigzag if its digits are alternatively 
// increasing and decreasing, like 14283415...

struct Automaton {
	vector<vector<int>> trans;
	vector<bool> is_accept;
	int init = 0;
	int next(int state, int a) { return trans[state][a]; }
	bool accept(int state) { return is_accept[state]; }
	int size() { return trans.size(); }
};

template <class Automaton1, class Automaton2>
Automaton intersectionAutomaton(Automaton1 A, Automaton2 B) {
	Automaton M;
	vector<vector<int>> table(A.size(), vector<int>(B.size(), -1));
	vector<int> x = {A.init}, y = {B.init};
	table[x[0]][y[0]] = 0;
	for (int i = 0; i < x.size(); ++i) {
		M.trans.push_back(vector<int>(10, -1));
		M.is_accept.push_back(A.accept(x[i]) && B.accept(y[i]));
		for (int a = 0; a <= 9; ++a) {
			int u = A.next(x[i], a), v = B.next(y[i], a);
			if (table[u][v] == -1) {
				table[u][v] = x.size();
				x.push_back(u);
				y.push_back(v);
			}
			M.trans[i][a] = table[u][v];
		}
	}
	return M;
}

void AOJ_ZIGZAG() {
	char A[1000], B[1000];
	int M;
	scanf("%s %s %d", A, B, &M);

	struct Value {
		int value = 0;
		Value &operator+=(Value x) {
			if ((value += x.value) >= 10000) value -= 10000;
			return *this;
		}
		Value &operator*=(int d) {
			return *this;
		}
	} e = (Value){1};

	struct ZigZagAutomaton {
		int init = 0;
		int size() { return 29; }
		int next(int state, int a) {
			if (state == 0) return a == 0 ? 0 : a + 1;
			if (state == 1) return 1; 
			if (state <= 10) {
				int last = state - 1;
				if			(a > last) return a + 10;
				else if (a < last) return a + 20;
			} else if (state <= 19) {
				int last = state - 10;
				if (a < last) return a + 20;
			} else if (state <= 28) {
				int last = state - 20;
				if (a > last) return a + 10;
			}
			return 1;
		}
		bool accept(int state) { return state != 1; }
	} zigzag;

	// state =	x : x == n % mod
	struct ModuloAutomaton {
		int mod;
		ModuloAutomaton(int mod) : mod(mod) { }
		int init = 0;
		int size() { return mod; }
		int next(int state, int a) { return (10 * state + a) % mod; }
		bool accept(int state) { return state == 0; }
	} modulo(M);

	auto IM = intersectionAutomaton(zigzag, modulo);
	int a = digitDP(A, e, IM, 0).value;
	int b = digitDP(B, e, IM, 1).value;
	cout << (b + (10000 - a)) % 10000 << endl;
}

//
// Count the numbers that does not contain 4 and 7 in each digit.
// from a to b
void ABC007D() {
	string a, b;
	cin >> a >> b;

	struct ForbiddenNumber {
		int init = 0;
		int size() { return 2; }
		int next(int state, int a) { 
			if (state == 1) return 1;
			if (a == 4 || a == 7) return 1;
			return 0;
		}
		bool accept(int state) { return state == 1; }
	};
	struct Counter {
		long long value = 0;
		Counter &operator+=(Counter x) {
			value += x.value;
			return *this;
		}
		Counter &operator*=(int d) {
			return *this;
		}
	};
	cout << digitDP(b, (Counter){1}, ForbiddenNumber(), true).value
			- digitDP(a, (Counter){1}, ForbiddenNumber(), false).value << endl;
}

