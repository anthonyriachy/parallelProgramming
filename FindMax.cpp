#include"FindMax.h"
#include<omp.h>
int FindMax(vector<int>arr, int thread_num,string type) {
	int max_value=0;
	if (type == "parallel") {
		omp_set_num_threads(thread_num);
		#pragma parallel for reduction(max:max_value)

		for (int i = 0; i < arr.size(); i++) {
			if (max_value < arr[i]) {
				max_value = arr[i];
			}
		}
	}
	else {
		for (int i = 0; i < arr.size(); i++) {
			if (max_value < arr[i]) {
				max_value = arr[i];
			}
		}
	}
	return max_value;
}