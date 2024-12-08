#include <iostream>
#include <omp.h>
#include<vector>
#include "ArraySum.h"
#include "MatrixMultiplication.h"
#include "MonteCarloMethod.h"
#include "FindMax.h"
#include "FebonacciSequence.h"

using namespace std;




void handleTask1() {
    int size;
    cout << "Enter the size of the array: ";

    cin >> size;
    cout << endl;
    vector<int> arr(size);
    //fill arrray.
    int random_number;
    for (int i = 0; i < size; i++) {
        random_number= rand() % 1000 + 1;
        arr[i] = random_number;
    }
    double seq_start = omp_get_wtime();
    long long int result = ArraySum(arr, "sequential");
    double seq_end = omp_get_wtime();

    double seq_time = seq_end-seq_start;
    cout << "Schedule type: Sequential" << endl;
    cout << "\t Time to execute: " << seq_time << " seconds." << endl;
    cout << "\t Sum result: " << result << endl << endl;

    string schedules[] = { "static","dynamic","guided"};
    for(string schedule:schedules)
    {
        auto start = omp_get_wtime();
        long long int result=ArraySum(arr,schedule);
        auto end =omp_get_wtime();

        auto time = end-start;
        double speedup=0.0;
        if(seq_time && time)
             speedup = seq_time/ time;
        cout << "Schedule type: " << schedule << endl;
        cout << "\t Time to execute: " << time << " seconds." << endl;
        cout << "\t Sum result: " << result << endl;
        cout << "\t speedup: " << speedup << endl;
        cout <<endl;

    }
    cout << "---------------------------------------------------------"<<endl<<endl;
}

void handleTask2() {
    int columnA=0, rowA=0, columnB=0, rowB=0;
    string showResult;
    cout << "Enter the row size of matrix A: ";
    cin >> rowA;
    cout << "\n Enter the column size of matrix A: ";
    cin >> columnA;
    cout << "\n Enter the row size of matrix B: ";
    cin >> rowB;
    cout << "\n Enter the column size of matrix B: ";
    cin >> columnB;

    if (columnA != rowB) {
        cout << "\nMatrix multiplication is not possible. The number of columns in Matrix A must equal the number of rows in Matrix B.\n";
        return;
    }

    cout << "show matrix result?(y/n)" << endl;
    cin >> showResult;

    

    vector<vector<int>> matrixA(rowA, vector<int>(columnA));
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < columnA; j++) {
            matrixA[i][j] = rand() % 100; 
        }
    }

    vector<vector<int>> matrixB(rowB, vector<int>(columnB));
    for (int i = 0; i < rowB; i++) {
        for (int j = 0; j < columnB; j++) {
            matrixB[i][j] = rand() % 100;
        }
    }

        double seq_start = omp_get_wtime();
        vector<vector<int>> result = MatrixMultiplication(matrixA, matrixB, "sequential");
        double seq_end= omp_get_wtime();

        double seq_time = seq_end - seq_start;

        cout << "Mode: " << "sequential" << endl;
        cout << "\tTime: " << seq_time << " seconds." << endl;
        if (showResult == "y") {
            cout << "\tresult: " << endl;
            PrintMatrix(result);
        }
        

    string types[] = {"parallel" };
    for (string type : types) {
        double start = omp_get_wtime();
        vector<vector<int>> result = MatrixMultiplication(matrixA, matrixB,type);
        double end= omp_get_wtime();

        double time = end - start;

        cout << "Mode: " << type << endl;
        cout << "\tTime: " << time << " seconds." << endl;
        cout << "\tSpeedup: " << seq_time/time<< endl;
        if (showResult == "y") {
            cout << "\tresult: " << endl;
            PrintMatrix(result);
        }
        


    }

}

void handleTask3() {
    long long int num_points;
    int  num_experiemnts = 1;
    vector<int>num_threads;
    cout << "Enter the number of total points: " << endl;
    cin >> num_points;

    cout << "Enter the number of expirements you want" << endl;
    cin >> num_experiemnts;
    int input;
    for (int i = 0; i < num_experiemnts; i++) {
        cout << "Enter the number of thread you want in experiment "<<i+1<<" : " << endl;
        cin >>input ; 
        num_threads.push_back(input);
    }
    
    double seq_start = omp_get_wtime();
    double result = MonteCarloMethod(num_points, 0,"sequential");
    double seq_end = omp_get_wtime();
    double seq_time = seq_end - seq_start;
    cout << "Time USING SEQUENTIAL PROGRAMMING: " << seq_time << " seconds." << endl;
    cout << "Estimated pi: " << result << endl;
    cout << endl << endl;

    for (int i = 0; i < num_threads.size(); i++) {
        double start = omp_get_wtime();
        double result = MonteCarloMethod(num_points, num_threads[i],"parallel");
        double end = omp_get_wtime();
        double time = end - start;
        cout << "Number of threads used: " << num_threads[i]<< endl;
        cout << "Time: " << time << " seconds." << endl;
        cout << "Speedup: " << seq_time/time << endl;
        cout << "Estimated pi: " << result << endl;
        cout << endl << endl;
    }
    
    



    


}

void handleTask4() {
    int size = 0;
    vector<int> arr;
    cout << "Enter the size of the array: " << endl;
    cin >> size;

    if (size <= 0) {
        cout << "size should be > 0: " << endl;
        cin >> size;
    }
    int random_number;
    for (int i = 0; i < size; i++) {
        random_number = rand() % 1000 + 1;
        arr.push_back(random_number);
    }

    int num_experiments = 1;
    vector<int> num_threads;
    cout << "Enter the number of experiments you want: " << endl;
    cin >> num_experiments;
    int choice = 1;
    for (int i = 0; i < num_experiments; i++)
    {
        cout << "Enter the number of threads in experiment "<<i+1<<" : " << endl;
        cin >> choice;
        num_threads.push_back(choice);
    }

    double seq_start = omp_get_wtime();
    int seq_result = FindMax(arr, 0, "sequential");
    double seq_end = omp_get_wtime();
    double seq_time = seq_end - seq_start;
    cout << "Time USING SEQUENTIAL PROGRAMMING: " << seq_time << " seconds" << endl;
    cout << "Max value: " << seq_result<< endl;
    cout << endl << endl;

    for (int i = 0; i < num_threads.size(); i++) {
        double start = omp_get_wtime();
        int result = FindMax(arr, num_threads[i],"parallel");
        double end = omp_get_wtime();
        double time = end - start;
        cout << "Number of threads: " << num_threads[i]<<endl;
        cout << "Time: " << time << " seconds" << endl;
        cout << "Speedup: " << seq_time/time << " seconds"<<endl;
        cout << "Max value: " << result<< endl;
        cout << endl << endl;
    }
}

void handleTask5() {
    long long  int number;
    cout << "Enter the number you want : " << endl;
    cin >> number;
    long long int result;

    double seq_start = omp_get_wtime();
    long long int seq_result = FebonacciSequence(number, "sequential");
    double seq_end = omp_get_wtime();
    double seq_time = seq_end - seq_start;

    cout << "Time: " << seq_time << " Seconds" << endl;
    cout << "Result: " << seq_result << endl;
    cout << endl << endl;
    double start=omp_get_wtime();
  
    result = FebonacciSequence(number, "parallel");    
    double end= omp_get_wtime();
    double time = end - start;
    cout << "Time: " << time << " Seconds" << endl;
    cout << "Result: " << result << endl;
    cout << "Speedup: " << result<<endl;
    cout << endl << endl;

}

int main()
{
    int choice;
    do {
        cout << "enter task number: \n";
        cout << "\t Task 1: Parallel sum of array elements. \n";
        cout << "\t Task 2: Parallel Matrix Multiplication. \n";
        cout << "\t Task 3: Parallelized Numerical Integration (Monte Carlo Method). \n";
        cout << "\t Task 4: Parallel Reduction of Maximum Value in an Array. \n";
        cout << "\t Task 5: Fibonacci Sequence. \n";
        
        cin >> choice;

        switch (choice) {
            case 1: 
                handleTask1();
                break;
            case 2:
                handleTask2();
                break;
            case 3:
                handleTask3();
                break;
            case 4:
                handleTask4();
                break;
            case 5:
                handleTask5();
                break;
        }

    } while (choice != 0);

}

