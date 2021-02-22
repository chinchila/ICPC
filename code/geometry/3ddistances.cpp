// Distancia ponto-triangulo
// retorna infinito se distancia do ponto ao triangulo eh maior q a distancia
// do ponto a algum dos segmentos ou seja, retorna infinito se ponto nao
// pertence ao prisma do triangulo
PType distPointTriangle(P3 p, vector<P3> v){
	PType ans = INF;
	P3 v1 = v[1]-v[0];
	P3 v2 = v[2]-v[0];
	P3 n = v1.cross(v2);
	for(int i=0;i<3;++i){
		P3 vb = v[(i+1)%3]-v[i];
		P3 eq = vb.cross(n);
		PType d = eq.dot(v[i]);
		P3 vp = p-v[i];
		if(!(vp.cross(vb)).isZero() and (v[(i+2)%3].dot(eq)>d) ^ (p.dot(eq)>d))
			return INF;
	}
	return fabs(DC(P3(),p-v[0],v1,v2)/n.dist());
}

// Distancia ponto-reta
PType distPointLine(P3 p, vector<P3> li){
	return ((li[1]-li[0]).cross(p-li[0])).dist()/(li[1]-li[0]).dist();
}

// Distancia reta-reta
PType distLineLine(vector<P3> vp1, vector<P3> vp2){
	P3 n = (vp1[1]-vp1[0]).cross(vp2[1]-vp2[0]);
	if(n.isZero()) return distPointLine(vp2[0],vp1);
	P3 o1o2 = vp2[0]-vp1[0];
	return fabs(o1o2.dot(n)/n.dist());
}

#define PI 3.141592653589793238462643383279502884L
// Distancia segmento-segmento
// vp1 e vp2 precisam ter 2 elementos
PType distSegSeg(vector<P3> vp1, vector<P3> vp2){
	PType ans = INF;
	for(int i=0;i<2;++i)
		for(int j=0;j<2;++j) ans = min(ans,(vp1[i]-vp2[j]).dist());
	for(int T=0;T<2;++T){
		for(int i=0;i<2;++i){
			int curok = 1;
			for(int cor=0;cor<2;++cor){
				P3 vb = vp2[!cor]-vp2[cor];
				P3 vv = vp1[i]-vp2[cor];
				PType ang = atan2((vb.cross(vv)).dist(),vb.dot(vv));
				if(ang>PI/2) curok = 0;
			}
			if(curok) ans = min(ans,distPointLine(vp1[i],vp2));
		}
		swap(vp1,vp2);
	}
	P3 v1 = vp1[1]-vp1[0], v2 = vp2[1]-vp2[0];
	P3 n = v1.cross(v2);
	if(!n.isZero()){
		int ok = 1;
		for(int T=0;T<2;++T){
			P3 n2 = v2.cross(n);
			P3 o1o2 = vp2[0]-vp1[0];
			PType S = o1o2.dot(n2)/v1.dot(n2);
			if(S<0 or S>1) ok = 0;
			swap(vp1,vp2),swap(v1,v2);
		}
		if(ok) ans = min(ans,distLineLine(vp1,vp2));
	}
	return ans;
}