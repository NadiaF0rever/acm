/*
 * UVA 10183
 *
 */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

typedef unsigned long uint64_t;

inline uint64_t
atou64(const char *beg, const char *end){
	uint64_t ret = 0;
	while(beg != end){
		ret *= 10;
		ret += (*beg++ - '0');
	}
	
	return ret;
}


const static int BIGINT_DATA_SIZE = 6;
const static uint64_t BIGINT_ACCE_VAL = 1000000000000000000UL;
const static int BIGINT_ACCE_SIZE = 18;

class BigInt{
	uint64_t	data[BIGINT_DATA_SIZE];
	int		top_index;

public:
	BigInt(const string &num_str): top_index(BIGINT_DATA_SIZE){
		memset(data, 0, sizeof(uint64_t) * BIGINT_DATA_SIZE);
		const char *beg, *end = num_str.c_str() + num_str.size();		
		
		do{
			beg = (end - BIGINT_ACCE_SIZE > num_str.c_str()) ? end - BIGINT_ACCE_SIZE: num_str.c_str();
			data[--top_index] = atou64(beg, end);
			end = beg;
		}while(beg != num_str.c_str());
	}

	bool operator< (const BigInt &other){
		int i = (top_index < other.top_index) ? top_index : other.top_index;
		while(i != BIGINT_DATA_SIZE){
			if(data[i] < other.data[i]) return true;
			else if(data[i] > other.data[i]) return false;
			else i++;
		}
		return false;
	}

	bool operator== (const BigInt &other){
		int i;
		for( i = 0; i < BIGINT_DATA_SIZE; i++){
			if(data[i] != other.data[i]) break;
		}
		return (i == BIGINT_DATA_SIZE);
	}

	BigInt & operator+= (const BigInt &other){
		int i = BIGINT_DATA_SIZE, min_top_index = \
				(top_index < other.top_index) ? top_index: other.top_index;
		uint64_t acce = 0, tmp;
		while(i != min_top_index){
			i--;
			tmp = data[i] + other.data[i] + acce;
			data[i] = tmp % BIGINT_ACCE_VAL;
			acce = tmp / BIGINT_ACCE_VAL;
		}
		top_index = min_top_index;
		if(acce != 0){
			data[--i] = acce;
			top_index = i;
		}
		return *this;
	}

	friend BigInt operator+ (const BigInt &a, const BigInt &b);
	friend ostream & operator<< (ostream &os, const BigInt &a);
};

inline BigInt
operator+ (const BigInt &a, const BigInt &b){
	BigInt r = a;
	return r += b;
}

ostream &
operator<< (ostream &os, const BigInt &a){
	uint64_t val = BIGINT_ACCE_VAL;	
	char buf[32];
	const char *beg = buf + (31 - BIGINT_ACCE_SIZE);
	for(int i = a.top_index; i != BIGINT_DATA_SIZE; i++){
		if(i == a.top_index){
			sprintf(buf, "%lu", a.data[i]);
			os << buf;
		}else{
			sprintf(buf, "%031lu", a.data[i]);
			os << beg;
		}
	}
	return os;
}

void
prepare_data(vector<BigInt> &data){
	char end_buf[128];
	end_buf[0] = '1';
	int i;
	for( i = 1; i < 102; i++) end_buf[i] = '0';
	end_buf[i] = '\0';

	BigInt a("1"), b("2"), c("0"), end(end_buf);

	data.push_back(a);
	data.push_back(b);
	do{
		c = a + b;
		data.push_back(c);
		a = b;
		b = c;
	}while(c < end);
}

typedef vector<BigInt>::iterator Iter;

inline Iter
find_lesser_than(Iter beg, Iter end, BigInt val){
	Iter m;
	
	while(beg <= end){
		m = beg + (end - beg) / 2;
		if( val < *m) end = m - 1;
		else beg = m + 1;
	}
	return end;
}

inline Iter
find_bigger_than(Iter beg, Iter end, BigInt val){
	Iter m;

	while(beg <= end){
		m = beg + (end - beg) / 2;
		if(*m < val){
			beg = m + 1;
		}else{
			end = m - 1;
		}
	}
	return beg;
}

int
main(void){
	vector<BigInt> data;
	prepare_data(data);
	Iter beg = data.begin(), end = data.end() - 1;

	Iter ia, ib;
	string vala, valb;
	const string ZERO = "0";
	while(cin >> vala >> valb){
		if(vala == ZERO && valb == ZERO) break;
		ia = find_bigger_than(beg, end, BigInt(vala));
		ib = find_lesser_than(beg, end, BigInt(valb));
//		cout << "debug: " << *ia << ' ' << *ib << endl;

		if(ib >= ia) cout << (ib - ia) + 1 << endl;
		else cout << 0 << endl;
	}
	return 0;
}
