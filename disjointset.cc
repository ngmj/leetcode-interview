class Disjointset {
public:
    explicit Disjointset(int N) {
        capacity_ = N;
        roots_ = new int[N];
        for (int i = 0; i < N; ++i) {
            roots_[i] = i;
        }
    }
    ~Disjointset() {
        delete []roots_;
    }

    int find(int i) {
        // find root
        int root = i;
        while (root != roots_[root]) {
            root = roots_[root];
        }

        // reconnect 
        while (i != roots_[i]) {
            int tmp = roots_[i];
            roots_[i] = root;
            i = tmp;
        }
        return root;
    }

    int union_join(int i, int j) {
        int r1 = find(i);
        int r2 = find(j);
        roots_[r2] = r1;
    }

    bool is_connected(int i, int j) {
        return find(i) == find(j);
    }

private:
    int *roots_;
    int capacity_;
};
