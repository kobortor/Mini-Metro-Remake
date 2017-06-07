#pragma once
#include<chrono>

template<class interFunc>
class interpol {
public:
	interpol(time_t _begin, time_t _end) :begin(_begin), end(_end){}

	/*
	Returns the value interpolated if at tm
	If tm < begin, then return 0
	If tm >= _end, then return 1
	Otherwise, return another value (NOT GUARENTEED TO BE BETWEEN 0 AND 1)
	*/
	double get(time_t tm) {
		if (tm < begin) return 0;
		if (tm >= end) return 1;
		return fobj((double)(tm - begin) / (end - begin));
	}
protected:
	interFunc fobj;
	time_t begin, end;
};

namespace interpol_func {
	struct quadratic {
		double operator()(double x) {
			//compiler optimize this away kkty
			return -8. / 3 * x * x + 11. / 3 * x;
		}
	};
	struct linear {
		double operator()(double x) {
			return x;
		}
	};
}