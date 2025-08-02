int Block, N = 1e6 + 10;
struct Query {
	int l, r, index;
	bool operator<(const Query &obj) {
		return (l / Block != obj.l / Block) ? l / Block < obj.l / Block: r < obj.r;
	}
};
template <typename T>
class MOsAlgo {
	T ans;
	int l, r;
	vector<T> lst;
public:
	MOsAlgo(vector<T> & arr): lst(arr) {
		l = 0, r = -1, ans = 0;
	}
	void insert(int i) {

	}
	void remove(int i) {

	}
	T get(int i, int j) {
		while (l > i) insert(--l);
		while (r < j) insert(++r);
		while (l < i) remove(l++);
		while (r > j) remove(r--);
		return ans;
	}
};
