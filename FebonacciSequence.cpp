#include "FebonacciSequence.h"

long long int FebonacciSequence(long long int number, string type) {
	if (type == "parallel") {
        if (number <= 1) return number;

        vector<long long int> fib(number + 1);
        fib[0] = 0;
        fib[1] = 1;

        
        #pragma omp parallel for
        for (int i = 2; i <= number; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }

        return fib[number];
	}
	else {
		if (number <= 1) {
			return number;
		}
		return FebonacciSequence(number - 1, type) + FebonacciSequence(number - 2, type);
	}

}