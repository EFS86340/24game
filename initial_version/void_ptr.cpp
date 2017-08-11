//-----------------------------------------------------------------------------------------------------------------------------------------------
//Note:about output format:
//		mode[i] suggests where the ~ (or) operation should apply,transfer i to binary format,
//		for example i = 5, that is 0101 in binary format which suggest the program applys the or operation to both the second and fourth number,
//		and after the "exp:" is the operation order in brackets, for example fun1 suggest the first function of the function transited in.
//		At end output the number count all solutions
//-----------------------------------------------------------------------------------------------------------------------------------------------
//Update:
//Wed Oct 19, 2016
//last version cover assignments both at week 4 and week 5
//this program runs increditable slowly
//Note:revised the callback function,added op to output the exactly what kind of operation the computer have done
//and make it to control the work flow when came to / and % operation with zero,callback functions will return 256 when meet any operand which 
//	greater than 256, besides the Mod and Division function will return 256 when meet the second oprand as zero
//-----------------------------------------------------------------------------------------------------------------------------------------------
//Name Wang Xu
//Student Number 2014301500298
//Grade 2014 , Class 5, Major Information Security
//Thu Oct 6, 2016
//Note:plz compile using -std=c++11
//Note:this version support input four number and a target and then output how many method those functions can generate target
//		one point that hard to solve is that how to make program continue running when the / and % operation meets zero
//-----------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <cstdarg>
#include <utility>
#include <fstream>

using namespace std;

int format(int x) {
	if(x > 255)
	  return x % 256;
	else if(x < 0) {
		while( (x += 256) < 0)
		  ;
		return x;
	}
}

int Not(int x, ...) {
	if(x == -1)
	  return 1;

	else 
	  return format(255-x);
}

int Plus(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else
	  return format(x + y);
}

int Minus(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else
	  return format(x - y);
}

int Multiple(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else
	  return format(x * y);
}

int Division(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256 || y == 0)
	  return 256;
	else
	  return format(x / y);
}

int Mod(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256 || y == 0)
	  return 256;
	else
	  return format(x % y);
}

int And(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else
	  return format(x & y);
}

int Or(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else
	  return format(x | y);
}

int Rshift(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else
	  return format(x >> y);
}

int Lshift(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else
	  return format(x << y);
}

int Xor(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else
	  return format(x ^ y);
}

int cRshift(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else {
	while( --y >= 0) {
		if(x % 2) {
			x = x >> 1;
			x += 128;
		}
		else
		  x = x >> 1;
	}
	return x;
	}
}

int cLshift(int x, ...) {
	if(x == -1)
	  return 2;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	if(x >= 256 || y >= 256)
	  return 256;
	else {
	while( --y >= 0) {
		if( x / 128) {
			x = x << 1;
			x = x % 256;
			x += 1;
		}
		else 
		  x = x << 1;
	}
	return x;
	}
}

int threeXone(int x, ...) {
	if(x == -1)
	  return 3;

	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	int z = va_arg(ap, int);
	if(x >= 256 || y >= 256 || z >= 256)
	  return 256;
	else
	  return x?y:z;
}

/*
int main() {
	fptr plusPtr = &plus12;
	cout << plusPtr << endl;
	cout << plusPtr(1, 2) << endl;
	
	return 0;
}
*/

/*
struct vafptr_wrapper {
	int vafun_sample(int x, ...) { };
};
*/

void permutation(const vector<int> model, vector<vector<int>> &rtn, vector<int> &recur, size_t i) {
	if(i == 4)
	  rtn.push_back(recur);
	else {
		recur[i] = model[i];
		permutation(model, rtn, recur, i+1);
		recur[i] = Not(model[i]);
		permutation(model, rtn, recur, i+1);
	}
}

template<typename T1, typename T2>
inline int sfp(const T1 cont, const T2 fun) {
	for(int i = 0; i < cont.size(); ++i) 
	  if(cont[i] == fun)
		return i;
};

int vafun_sample(int x, ...) { };

template<typename...T>
bool runtime(int a, int b, int c, int d, int target, T&&... args) {
	auto temp_fptr = &vafun_sample;
	vector<decltype(temp_fptr)> fv = {std::forward<T>(args)...};
	
	vector<decltype(temp_fptr)> fv_arg1;
	vector<decltype(temp_fptr)> fv_arg2;
	vector<decltype(temp_fptr)> fv_arg3;

	for(auto &f : fv) {
		if(f(-1) == 1)
		  fv_arg1.push_back(f);
		else if(f(-1) == 2)
		  fv_arg2.push_back(f);
		else
		  fv_arg3.push_back(f);
	}

//	vector<void*> fv = {std::forward<T>(args)...};
//	cout << a << b << c << d << target << endl;
//	fv[1](-1);
	
//	list<int> nums = {a, b, c, d};
	
	int sltcnt = 0;//solutions count
	ofstream outfile;
	outfile.open("result.txt");

	vector<int> nums = {a, b, c, d};
	vector<vector<int>> unaryrlt;
	vector<int> temp(4);
	permutation(nums, unaryrlt, temp, 0);



	for(int i = 0; i < unaryrlt.size(); ++i) {
		int w = unaryrlt[i][0];
		int x = unaryrlt[i][1];
		int y = unaryrlt[i][2];
		int z = unaryrlt[i][3];

	//only binary operation combination,without ternary operation
	for(auto f21 : fv_arg2) {
		for(auto f22 : fv_arg2) {
			for(auto f23 : fv_arg2) {
				if( f23(z, f22(y, f21(y, x))) == target) {
					sltcnt++;
					cout << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(z, fun" << sfp(fv, f22) << "(y, fun" << sfp(fv, f21) << "(y, x)))" << endl;
					outfile << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(z, fun" << sfp(fv, f22) << "(y, fun" << sfp(fv, f21) << "(y, x)))" << endl;
				}
				if( f23(f22(w, x), f21(y, z)) == target) {
					cout << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(fun" << sfp(fv, f22)  << "(w, x), fun" << sfp(fv, f21) << "(y, z))" << endl;
					outfile << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(fun" << sfp(fv, f22)  << "(w, x), fun" << sfp(fv, f21) << "(y, z))" << endl;
					sltcnt++;
				}
				if( f23(z, f22(w, f21(x, y))) == target) {
					cout << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(z, fun" << sfp(fv, f22) << "(w, fun" << sfp(fv, f21) << "(x, y)))" << endl;
					outfile << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(z, fun" << sfp(fv, f22) << "(w, fun" << sfp(fv, f21) << "(x, y)))" << endl;
					sltcnt++;
				}
				if( f23(w, f22(z, f21(x, y))) == target) {
					cout << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(w, fun" << sfp(fv, f22) << "(z, fun" << sfp(fv, f21) << "(x, y)))" << endl;
					outfile << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(w, fun" << sfp(fv, f22) << "(z, fun" << sfp(fv, f21) << "(x, y)))" << endl;
					sltcnt++;
				}
				if( f23(w, f22(x, f21(y, z))) == target) {
					cout << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(w, fun" << sfp(fv, f22) << "(x, fun" << sfp(fv, f21) << "(y, z)))" << endl;
					outfile << "mode[" << i << "]" << " exp:fun" << sfp(fv, f23) << "(w, fun" << sfp(fv, f22) << "(x, fun" << sfp(fv, f21) << "(y, z)))" << endl;
					sltcnt++;
				}
			}
		}
	}

	//only one binary operation plus one ternary operation
	for(auto f21 : fv_arg2) {
		for(auto f31 : fv_arg3) {
			if(f21(z, f31(w, x, y)) == target) {
				cout << "mode[" << i << "] exp:fun" << sfp(fv, f21) << "(z, fun" << sfp(fv, f31) << "(w, x, y))" << endl;
				outfile << "mode[" << i << "] exp:fun" << sfp(fv, f21) << "(z, fun" << sfp(fv, f31) << "(w, x, y))" << endl;
				sltcnt++;
			}
			if(f21(w, f31(x, y, z)) == target) {
				cout << "mode[" << i << "] exp:fun" << sfp(fv, f21) << "(w, fun" << sfp(fv, f31) << "(x, y, z))" << endl;
				outfile << "mode[" << i << "] exp:fun" << sfp(fv, f21) << "(w, fun" << sfp(fv, f31) << "(x, y, z))" << endl;
				sltcnt++;
			}
			if(f31(f21(w, x), y, z) == target) {
				cout << "mode[" << i << "] exp:fun" << sfp(fv, f31) << "(fun" << sfp(fv, f21) << "(w, x), y, z)" << endl;
				outfile << "mode[" << i << "] exp:fun" << sfp(fv, f31) << "(fun" << sfp(fv, f21) << "(w, x), y, z)" << endl;
				sltcnt++;
			}
			if(f31(w, f21(x, y), z) == target) {
				cout << "mode[" << i << "] exp:fun" << sfp(fv, f31) << "(w, fun" << sfp(fv, f21) << "(x, y), z)" << endl;
				outfile << "mode[" << i << "] exp:fun" << sfp(fv, f31) << "(w, fun" << sfp(fv, f21) << "(x, y), z)" << endl;
				sltcnt++;
			}
			if(f31(w, x, f21(y, z)) == target) {
				cout << "mode[" << i << "] exp:fun" << sfp(fv, f31) << "(w, x, fun" << sfp(fv, f21) << "(y, z))" << endl;
				outfile << "mode[" << i << "] exp:fun" << sfp(fv, f31) << "(w, x, fun" << sfp(fv, f21) << "(y, z))" << endl;
				sltcnt++;
			}
		}
	}
	}

	cout << "solutions :" << sltcnt << endl;
	outfile << "solutions :" << sltcnt << endl;
}




//static int vafun_sample(int x, ...) {
//}
//struct vafptr_wrapper {
//	int vafun_sample(int x, ...) { };
//};

int main() {
	/*
	auto fptr = &vafun_sample;
	vector<decltype(fptr)> funsvec;
	funsvec.push_back(&minus12);
	funsvec.push_back(&threeXone);
	cout <<	(funsvec[0])(-1) << endl;
	cout <<	(funsvec[1])(-1) << endl;
	*/
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	int target;
	cin >> target;
	runtime(a, b, c, d, target, &Plus, &Minus, &Multiple, &threeXone, &Rshift, &Lshift, &Xor
				, &Not, &And, &Or, &cRshift, &cLshift, &Division, &Mod);
	
	
	return 0;
}
