/*
 * UVA 10038
 *
 */

#include <iostream>
#include <list>
#include <string.h>

using namespace std;

char g_symbol[3000];

inline int
sugar(int a, int b){
	return (a > b) ? a - b : b - a;
}

bool
fun(list<int> &data){
	int n = data.size();
	int a = data.front(), b, c;
	data.pop_front();
	while(data.size() != 0){
		b = data.front();
		data.pop_front();
		c = sugar(a, b);
		if(c > n - 1 || c == 0 || g_symbol[c] == 1) return false;
		g_symbol[c] = 1;

		a = b;
	}
	return true;
}


int
main(){
	int n, t;
	list<int> data;
	while(cin >> n){
		data.clear();
		memset(g_symbol, 0, 3000);
		for(int i = 0; i < n; i++){
			cin >> t;
			data.push_back(t);
		}
		cout << (fun(data) ? "Jolly" : "Not jolly") << endl;
	}

	return 0;
}
