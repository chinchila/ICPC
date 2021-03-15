// Link cut tree - everything O(log(n)) or O(1)
// usage: LinkCurTree<ll> lct(vertices);
// add_vertex(index, value): create vertex with value
// add_edge(u, v): create edge u<->v
// cut_edge(u, v): cut edge u<->v
// val(v): get value from v
// val_path(x, y): get sum of vertices on path x to y
// update(x, val): update vertex x with val
// update_path(x, y, val): sum val to all vertices on path x to y
// connected(x, y): true if x and y are connected
// parent(x, r): get parent of x, r must be outside of x subtree
// root(x): returns root of x
// val_subtree(x, r): returns sum of subtree of x, r must be out of
// x subtree
template<typename T>
struct LinkCutTree{
	struct Node{
		Node *p,*l,*r;
		int idx;
		T key, sum, sub, path;
		T lazy;
		bool rev;
		bool is_root(){
			return !p || (p->l != this && p->r != this);
		}
		Node(int idx, const T &key,const T &om):
			idx(idx),key(key),sum(key),sub(om),lazy(om),path(om),
			l(nullptr),r(nullptr),p(nullptr),rev(false){}
	};
	const T ident;
	vector<Node *>ver;
	LinkCutTree(int n): LinkCutTree(n,T()){}
	LinkCutTree(int n,const T ident):ver(n),ident(ident){}
	void update(Node *t){
		if(t==nullptr)return;
		t->path = t->key;
		t->sum = t->key+t->sub;
		if(t->l)t->path += t->l->path, t->sum += t->l->sum;
		if(t->r)t->path += t->r->path, t->sum += t->r->sum;	
	}
	void rot(Node *t, bool lr = 0){
		Node *x = t->p, *y = x->p;
		if(lr) {
			if((x->l = t->r))t->r->p = x;
			t->r = x, x->p = t;
		}else{
			if((x->r = t->l))t->l->p = x;
			t->l = x, x->p = t;
		}
		update(x),update(t);
		if((t->p = y)){
			if(y->l == x)y->l = t;
			if(y->r == x)y->r = t;
			update(y);
		}
	}
	void splay(Node *t){
		push(t);
		while(!t->is_root()){
			Node *q = t->p;
			if(q->is_root()){
				push(q), push(t);
				if(q->l == t)rot(t, 1);
				else rot(t);
			}
			else{
				Node *r = q->p;
				push(r), push(q), push(t);
				if(r->l == q){
					if(q->l == t)rot(q, 1), rot(t, 1);
					else rot(t), rot(t, 1);
				}
				else{
					if(q->r == t) rot(q), rot(t);
					else rot(t, 1), rot(t);
				}
			}
		}
	}
	Node *expose(Node *t){
		Node *rp = nullptr, *cur = t;
		while(cur){
			splay(cur);
			if(cur->r)cur->sub += cur->r->sum;
			cur->r = rp; rp = cur;
			if(cur->r) cur->sub -= cur->r->sum;
			update(cur); cur = cur->p;
		}
		splay(t);
		return rp;
	}
	void link(Node *child, Node *parent){
		expose(child); expose(parent);
		child->p = parent; parent->r = child;
		update(parent);
	}
	void cut(Node *child){
		expose(child);
		Node *parent = child->l;
		child->l = parent->p = nullptr;
		update(child);
	}
	void toggle(Node *t){
		swap(t->l,t->r);
		t->rev^=true;
	}
	void evert(Node *t){
		expose(t); toggle(t); push(t);
	}
	void push(Node *t){
		if(t->lazy != ident){
			if(t->l)prop(t->l, t->lazy);
			if(t->r)prop(t->r, t->lazy);
			t->lazy = ident;
		}
		if(t->rev){
			if(t->l)toggle(t->l);
			if(t->r)toggle(t->r);
			t->rev=false;
		}
	}
	Node *lca(Node *u, Node *v){
		expose(u);
		return expose(v);
	}
	void prop(Node *t, const T x){
		t->lazy += x; t->key += x;
		t->sum += x; t->path += x;
	}
	void add_vertex(int idx,T v = T()){
		ver[idx] = new Node(idx, v, ident);
	}
	void evert(int x){ evert(ver[x]); }
	void add_edge(int x,int y){
		evert(y); link(ver[y],ver[x]);
	}
	void cut_edge(int x,int y){
		evert(x); cut(ver[y]);
	}
	T val(int x){ return ver[x]->key; }
	T val_path(int x,int y){
		evert(x); expose(ver[y]);
		return ver[x]->path;
	}
	void update(int x,T v){
		expose(ver[x]);
		ver[x]->key = v;
		update(ver[x]);
	}
	void update_path(int x,int y,const T v){
		evert(x); expose(ver[y]);
		prop(ver[y], v);push(ver[y]);
	}
	int lca(int x,int y,int r = 0){
		return lca(ver[x], ver[y])->idx;
	}
	bool connected(int x,int y){
		if(x==y)return true;
		expose(ver[x]);expose(ver[y]);
		return bool(ver[x]->p);
	}
	int parent(int x,int r){
		evert(r), expose(ver[x]);
		Node *t = ver[x]->l;
		if(!t)return -1;
		push(t);
		while(t->r) t = t->r, push(t);
		return t->idx;
	}
	int root(int x){
		expose(ver[x]);
		Node *t = ver[x];
		push(t);
		while(t->l) t = t->l, push(t);
		return t->idx;
	}
	T val_subtree(int x, int r){
		int par = parent(x,r);
		if(par != -1)cut_edge(par, x);
		expose(ver[x]);
		T ret = ver[x]->sum;
		if(par != -1)add_edge(par, x);
		return ret;
	}
};

// Link-cut Tree - aresta - UFMG
//
// Valores nas arestas
// rootify(v) torna v a raiz de sua arvore
// query(v, w) retorna a soma do caminho v--w
// update(v, w, x) soma x nas arestas do caminho v--w
//
// Todas as operacoes sao O(log(n)) amortizado

namespace lct {
	struct node {
		int p, ch[2];
		ll val, sub;
		bool rev;
		int sz, ar;
		ll lazy;
		node() {}
		node(int v, int ar_) :
		p(-1), val(v), sub(v), rev(0), sz(ar_), ar(ar_), lazy(0) {
			ch[0] = ch[1] = -1;
		}
	};

	node t[2*MAX]; // MAXN + MAXQ
	map<pair<int, int>, int> aresta;
	int sz;

	void prop(int x) {
		if (t[x].lazy) {
			if (t[x].ar) t[x].val += t[x].lazy;
			t[x].sub += t[x].lazy*t[x].sz;
			if (t[x].ch[0]+1) t[t[x].ch[0]].lazy += t[x].lazy;
			if (t[x].ch[1]+1) t[t[x].ch[1]].lazy += t[x].lazy;
		}
		if (t[x].rev) {
			swap(t[x].ch[0], t[x].ch[1]);
			if (t[x].ch[0]+1) t[t[x].ch[0]].rev ^= 1;
			if (t[x].ch[1]+1) t[t[x].ch[1]].rev ^= 1;
		}
		t[x].lazy = 0, t[x].rev = 0;
	}
	void update(int x) {
		t[x].sz = t[x].ar, t[x].sub = t[x].val;
		for (int i = 0; i < 2; i++) if (t[x].ch[i]+1) {
			prop(t[x].ch[i]);
			t[x].sz += t[t[x].ch[i]].sz;
			t[x].sub += t[t[x].ch[i]].sub;
		}
	}
	bool is_root(int x) {
		return t[x].p == -1 or (t[t[x].p].ch[0] != x and t[t[x].p].ch[1] != x);
	}
	void rotate(int x) {
		int p = t[x].p, pp = t[p].p;
		if (!is_root(p)) t[pp].ch[t[pp].ch[1] == p] = x;
		bool d = t[p].ch[0] == x;
		t[p].ch[!d] = t[x].ch[d], t[x].ch[d] = p;
		if (t[p].ch[!d]+1) t[t[p].ch[!d]].p = p;
		t[x].p = pp, t[p].p = x;
		update(p), update(x);
	}
	int splay(int x) {
		while (!is_root(x)) {
			int p = t[x].p, pp = t[p].p;
			if (!is_root(p)) prop(pp);
			prop(p), prop(x);
			if (!is_root(p)) rotate((t[pp].ch[0] == p)^(t[p].ch[0] == x) ? x : p);
			rotate(x);
		}
		return prop(x), x;
	}
	int access(int v) {
		int last = -1;
		for (int w = v; w+1; update(last = w), splay(v), w = t[v].p)
			splay(w), t[w].ch[1] = (last == -1 ? -1 : v);
		return last;
	}
	void make_tree(int v, int w=0, int ar=0) { t[v] = node(w, ar); }
	int find_root(int v) {
		access(v), prop(v);
		while (t[v].ch[0]+1) v = t[v].ch[0], prop(v);
		return splay(v);
	}
	bool conn(int v, int w) {
		access(v), access(w);
		return v == w ? true : t[v].p != -1;
	}
	void rootify(int v) {
		access(v);
		t[v].rev ^= 1;
	}
	ll query(int v, int w) {
		rootify(w), access(v);
		return t[v].sub;
	}
	void update(int v, int w, int x) {
		rootify(w), access(v);
		t[v].lazy += x;
	}
	void link_(int v, int w) {
		rootify(w);
		t[w].p = v;
	}
	void link(int v, int w, int x) { // v--w com peso x
		int id = MAX + sz++;
		aresta[make_pair(v, w)] = id;
		make_tree(id, x, 1);
		link_(v, id), link_(id, w);
	}
	void cut_(int v, int w) {
		rootify(w), access(v);
		t[v].ch[0] = t[t[v].ch[0]].p = -1;
	}
	void cut(int v, int w) {
		int id = aresta[make_pair(v, w)];
		cut_(v, id), cut_(id, w);
	}
	int lca(int v, int w) {
		access(v);
		return access(w);
	}
}
