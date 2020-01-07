//Pattern search O(|T|+|P|)
vector<int> comp_shifts(string P) {
	int p = P.length();
	vector<int> shifts(p);
	for (int q = 1; q < p; q++) {
		int k = shifts[q - 1];
		while (k > 0 && P[k] != P[q])
			k = shifts[k - 1];
		if (P[k] == P[q])
			k++;
		shifts[q] = k;
	}
	return shifts;
}

int kmp(string P, string T) {
	vector<int> shifts = comp_shifts(P);
	int n = T.length();
	int m = P.length();

	int occurrences = 0;
	int q = 0;
	for (int i = 0; i < n; i++) {
		while (q && P[q] != T[i])
			q = shifts[q - 1];
		if (P[q] == T[i])
			q++;
		if (q == m) {
			occurrences++;
			q = shifts[q - 1];
		}
	}
	return occurrences;
}
