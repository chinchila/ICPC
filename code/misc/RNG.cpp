mt19937 get_rng() {
	seed_seq seq {
		(uint64_t) chrono::duration_cast<chrono::nanoseconds>(
			chrono::high_resolution_clock::now().time_since_epoch()).count(),
		(uint64_t) __builtin_ia32_rdtsc(),
		(uint64_t)(uintptr_t) unique_ptr<char>(new char).get()
	};
	return mt19937( seq );
}

int main() {
	auto rng = get_rng();
	uniform_int_distribution<int> distr( 0, 99 );
	cout << distr(rng) << endl;
	return 0;
}

