// Divide and Conquer DP Optimization - O(k*n^2) => O(k*n*logn) CP ALGO
//
// dp[i][j] = min k<i { dp[k][j-1] + C[k][i] }
//
// Condition: A[i][j] <= A[i+1][j]
// A[i][j] is the smallest k that gives an optimal answer to dp[i][j]
ll C(int i, int j){/**/}

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr){
    if (l > r) return;
    int mid = (l + r) >> 1;
    pair<ll, int> best = {LINF, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
		// Watch for index when calculating cost
        best = min(best, {dp_before[k] + C(k+1, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}