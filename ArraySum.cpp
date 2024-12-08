#include "ArraySum.h"
long long int ArraySum(vector<int>arr,string schedule) {
	int sum = 0;
	if (schedule == "static") { 
		#pragma  omp parallel for schedule(static) reduction(+:sum)
			for (int i = 0; i < arr.size(); i++) {
				sum += arr[i];
			}
	}
	else if (schedule == "dynamic") { 
		#pragma	omp parallel for schedule(dynamic) reduction(+:sum)
		for (int i = 0; i < arr.size(); i++) {
			sum += arr[i];
		}
	}
	else if (schedule == "guided") {
		#pragma	omp parallel for schedule(guided) reduction(+:sum)
			for (int i = 0; i < arr.size(); i++) {
				sum += arr[i];
			}
	}
	else if (schedule == "sequential") {
		for (int i = 0; i < arr.size(); i++) {
			sum += arr[i];
		}
	}
	return sum;
}