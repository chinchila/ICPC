// Interseção de plano com reta
//retorna 0 se forem paralelos (0 msm q se intersecao infinita ou nula)
//p assume o valor da intersecao entre o plano e a reta
bool intersectPlaneLine(vector<P3> tri, vector<P3> li, P3 &p){
	P3 n = (tri[1]-tri[0]).cross(tri[2]-tri[0]);
	PType d = n.dot(tri[0]);
	P3 dl = li[1]-li[0];
	P3 ol = li[0];
	if(!sgn(n.dot(dl))) return 0;
	PType k = (d-n.dot(ol))/n.dot(dl);
	p = ol+(dl*k);
	return 1;
}

// Se linha cruza o triangulo
bool cruza(vector<P3> tri, vector<P3> li){
	P3 p;
	if(intersectPlaneLine(tri,li,p)==0) return 0;
	return distPointTriangle(p,tri)<EPS and (p-li[0]).dot(p-li[1])<0;
}