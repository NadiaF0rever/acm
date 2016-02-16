/*
 * UVA 10410
 *
 *
 */

#include <iostream>
#include <list>
#include <vector>
using namespace std;


const int ACM_NOBENUM_MAX = 1024;

struct nobe_t{
	int _parent;
	int _val;
	vector<int> _ch;
	friend ostream& operator<< (ostream &os, const nobe_t & n);

	nobe_t(): _val(0), _parent(-1){}
};

ostream & operator<< (ostream &os, const nobe_t &n){
	os << n._val << ':';	
	vector<int>::const_iterator iter = n._ch.begin();
	while(iter != n._ch.end()){
		os << ' ' << *iter++;
	}
	os << endl;
}

nobe_t g_nobes[ACM_NOBENUM_MAX];
int		g_bfs_data[ACM_NOBENUM_MAX];

void
build_data(int n){
	int i, tmp_val, last_val = 0;
	for(i = 0; i < n; i++){
		cin >> tmp_val;
		g_bfs_data[i] = tmp_val;
	}
	
	for(i = 0; i < n; i++){
		cin >> tmp_val;
		g_nobes[tmp_val]._parent = last_val;
		g_nobes[last_val]._ch.push_back(tmp_val);
		g_nobes[tmp_val]._val = tmp_val;
		last_val = tmp_val;
	}
}

void inline
change_tree_struct(int nobe, int new_parent){
	int old_parent = g_nobes[nobe]._parent;

	g_nobes[old_parent]._ch.clear();

	g_nobes[nobe]._parent = new_parent;
	
	g_nobes[new_parent]._ch.push_back(nobe);
}

typedef list<int> Queue;
void
process(int n){
	int bfs_index = 0;
	int bfs_val, nobe_val = g_nobes[0]._ch.front();
	Queue q;
	
	q.push_back(nobe_val);
	while(n != 0){
		bfs_val = g_bfs_data[bfs_index];
		nobe_val = q.front();
		
		if(bfs_val == nobe_val){
			q.pop_front();
			
			if(g_nobes[nobe_val]._ch.size() == 1){
				q.push_back(g_nobes[nobe_val]._ch[0]);
			}
			n--;
			bfs_index++;
		}else{
			int new_parent = g_nobes[g_bfs_data[bfs_index - 1]]._parent;
			change_tree_struct(bfs_val, new_parent);
			
			q.push_front(bfs_val);
			if(q.front() == q.back()){
				q.pop_back();
			}
		}
	}
}

int
main(){
	int n;
	while(cin >> n){
		build_data(n);
		process(n);
		for(int i = 1; i < n + 1; i++){
			cout << g_nobes[i];
		}

		for(int i = 0; i < n; i++){
			g_nobes[i] = nobe_t();
			g_bfs_data[i] = 0;
		}

	}
	
	return 0;
	
}
