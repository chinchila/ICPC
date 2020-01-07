// Add(x) adds x to every element in the queue
// to maxqueue change >= to <=
// O(1)
struct MinQueue {
	int plus = 0;
	int sz = 0;
	deque<pair<int, int> > dq;
	void push( int x ) {
		x -= plus;
		int amt = 1;
		while( dq.size() and dq.back().first >= x )
			amt += dq.back().second, dq.pop_back();
		dq.push_back( { x, amt } ), ++sz;
	}
	void pop() {
		--dq.front().second, --sz;
		if( !dq.front().second ) dq.pop_front();
	}
	bool empty() { return dq.empty(); }
	void clear() { plus = 0; sz = 0; dq.clear(); }
	void add( int x ) { plus += x; }
	int min() { return dq.front().first + plus; }
	int size() { return sz; }
};
