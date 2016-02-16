/*
 * UVA 514
 *
 */

#include <iostream>
#include <vector>
#include <list>
//#inlcude <assert.h>

#define DEBUG

using namespace std;

bool
judge(list<int> &test_data){
	const int n = test_data.size();

	int queue = 1;
	vector<int> stack;
	while(test_data.size() != 0){
		if(queue == test_data.front()){
			queue++;
			test_data.pop_front();
			continue;
		}

		if(stack.size() != 0 && stack.back() == test_data.front()){
			stack.pop_back();
			test_data.pop_front();
			continue;
		}

		if(queue > n) break;

		stack.push_back(queue++);
	}

//	if(test_data.size() == 0) assert(stack.size() == 0);

	return (test_data.size() == 0) ? true: false;
}

int
main(void){
	int input_count;
	int a, tmp;

	while(cin >> input_count){
		if(input_count == 0) break;
		
		while(1){
			cin >> a;
			if(a == 0) {
				cout << "\n";
				break;
			}else{
				list<int> test_data;
				test_data.push_back(a);
				for(int i = 1; i < input_count; i++){
					cin >> tmp;
					test_data.push_back(tmp);
				}
				cout << (judge(test_data) ? "Yes\n": "No\n");
			}
		}
	}
	return 0;
}
