// Interval tree is capable of giving you all intervals overllaping
// usage: ITree::vector_t intervals; ITree tree(move(intervals));
template <class Sca, typename Val>
class Interval {
public:
	Sca start, stop;
	Val value;
	Interval(const Sca& s, const Sca& e, const Val& v)
	: start(min(s, e))
	, stop(max(s, e))
	, value(v)
	{}
};

template <class Sca, class Val>
class IntervalTree {
public:
	typedef Interval<Sca, Val> interval;
	typedef vector<interval> vector_t;

	struct IntervalStartCmp {
		bool operator()(const interval& a, const interval& b) {
			return a.start < b.start;
		}
	};

	struct IntervalStopCmp {
		bool operator()(const interval& a, const interval& b) {
			return a.stop < b.stop;
		}
	};
	IntervalTree() : left(nullptr) , right(nullptr) , center(0) {}
	~IntervalTree() = default;

	unique_ptr<IntervalTree> clone() const {
		return unique_ptr<IntervalTree>(new IntervalTree(*this));
	}

	IntervalTree(const IntervalTree& other)
	:   intervals(other.intervals),
		left(other.left ? other.left->clone() : nullptr),
		right(other.right ? other.right->clone() : nullptr),
		center(other.center)
	{}

	IntervalTree& operator=(IntervalTree&&) = default;
	IntervalTree(IntervalTree&&) = default;

	IntervalTree& operator=(const IntervalTree& other) {
		center = other.center;
		intervals = other.intervals;
		left = other.left ? other.left->clone() : nullptr;
		right = other.right ? other.right->clone() : nullptr;
		return *this;
	}

	IntervalTree(
			vector_t&& ivals,
			size_t depth = 16,
			size_t minbucket = 512,
			size_t maxbucket = 1024,
			Sca leftextent = 0,
			Sca rightextent = 0)
	  : left(nullptr), right(nullptr)
	{
		--depth;
		const auto minmaxStop = minmax_element(
			ivals.begin(), ivals.end(),
			IntervalStopCmp());
		const auto minmaxStart = minmax_element(
			ivals.begin(), ivals.end(),
			IntervalStartCmp());
		if (!ivals.empty())
			center = (minmaxStart.first->start + minmaxStop.second->stop) / 2;
		if (leftextent == 0 && rightextent == 0) 
			sort(ivals.begin(), ivals.end(), IntervalStartCmp());
		if (depth == 0 || (ivals.size() < minbucket && ivals.size() < maxbucket)) {
			sort(ivals.begin(), ivals.end(), IntervalStartCmp());
			intervals = move(ivals);
			return;
		} else {
			Sca leftp = 0;
			Sca rightp = 0;

			if (leftextent || rightextent) {
				leftp = leftextent;
				rightp = rightextent;
			} else {
				leftp = ivals.front().start;
				rightp = max_element(ivals.begin(), ivals.end(),
									IntervalStopCmp())->stop;
			}

			vector_t lefts;
			vector_t rights;

			for (auto i = ivals.begin() ; i != ivals.end() ; ++i) {
				const interval& interval = *i;
				if (interval.stop < center) lefts.push_back(interval);
				else if (interval.start > center) rights.push_back(interval);
				else intervals.push_back(interval);
			}

			if (!lefts.empty())
				left.reset(new IntervalTree(move(lefts),
							depth, minbucket, maxbucket,
							leftp, center));
			if (!rights.empty())
				right.reset(new IntervalTree(move(rights),
							depth, minbucket, maxbucket,
							center, rightp));
		}
	}

	template <class F>
	void visit_near(const Sca& start, const Sca& stop, F f) const {
		if (!intervals.empty() && ! (stop < intervals.front().start))
			for (auto & i : intervals) f(i);
		if (left && start <= center) left->visit_near(start, stop, f);
		if (right && stop >= center) right->visit_near(start, stop, f);
	}

	template <class F>
	void visit_overlapping(const Sca& pos, F f) const {
		visit_overlapping(pos, pos, f);
	}

	template <class F>
	void visit_overlapping(const Sca& start, const Sca& stop, F f) const {
		auto filterF = [&](const interval& i) {
			if (i.stop >= start && i.start <= stop) f(i);
		};
		visit_near(start, stop, filterF);
	}

	template <class F>
	void visit_contained(const Sca& start, const Sca& stop, F f) const {
		auto filterF = [&](const interval& i) {
			if (start <= i.start && i.stop <= stop) f(i);
		};
		visit_near(start, stop, filterF);
	}

	vector_t findOverlapping(const Sca& start, const Sca& stop) const {
		vector_t result;
		visit_overlapping(start, stop, [&](const interval& i) {
			result.emplace_back(i);
		});
		return result;
	}

	vector_t findContained(const Sca& start, const Sca& stop) const {
		vector_t result;
		visit_contained(start, stop, [&](const interval& i) {
			result.push_back(i);
		});
		return result;
	}

	bool empty() const {
		if (left && !left->empty()) return false;
		if (!intervals.empty()) return false;
		if (right && !right->empty()) return false;
		return true;
	}

	template <class F>
	void visit_all(F f) const {
		if (left) left->visit_all(f);
		for_each(intervals.begin(), intervals.end(), f);
		if (right) right->visit_all(f);
	}
private:
	vector_t intervals;
	unique_ptr<IntervalTree> left;
	unique_ptr<IntervalTree> right;
	Sca center;
};