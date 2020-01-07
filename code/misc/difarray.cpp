//O(1) range update
//O(n) query

vector<int> initializeDiffArray( vector<int>& A ){
	int n = A.size();
	vector<int> D(n + 1);

	D[0] = A[0], D[n] = 0;
	for (int i = 1; i < n; i++)
		D[i] = A[i] - A[i - 1];
	return D;
}

void update( vector<int>& D, int l, int r, int x ){
	D[l] += x;
	D[r + 1] -= x;
}

int printArray( vector<int>& A, vector<int>& D ){
	for (int i = 0; i < A.size(); i++) {
		if (i == 0) A[i] = D[i];
		else A[i] = D[i] + A[i - 1];
		cout << A[i] << " ";
	}
	cout << endl;
}
