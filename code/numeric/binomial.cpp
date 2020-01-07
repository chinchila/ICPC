// compute binomial coeficient O(n*k)
inv[(n-2)!]=inv[(n-1)!] *(n-1)
fat[1]=1, inv[0]=1;
for(int i=2;i<=n;i++){
	fat[i]=(fat[i-1]*i)%mod;
}
inv[n-1]=power(fat[n-1], mod-2, mod);
for(int i=n-2;i>=1;i--){
	inv[i]=(inv[i+1]*(i+1))%mod;
}
for(int i=1;i<=n;i++){
	esc[i][i]=1ll;
	esc[i][0]=1ll;
	for(int j=1;j<=i-1;j++){
		esc[i][j]=((fat[i]*inv[j])%mod*inv[i-j])%mod;
	}
}
