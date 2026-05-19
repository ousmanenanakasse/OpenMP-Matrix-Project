#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>

using namespace std;

int main()
{
    int N = 150;
    int max_threads = 1000;

    cout << "--- Starting Thread Scaling Benchmark (1 to 1000) ---" << endl;

    ofstream file("data/results.csv");
    file << "Threads,Time_Seconds\n";

    for (int num_threads = 1; num_threads <= max_threads; num_threads++)
    {
        omp_set_num_threads(num_threads);

        vector<vector<int>> A(N, vector<int>(N, 1));
        vector<vector<int>> B(N, vector<int>(N, 2));
        vector<vector<int>> C(N, vector<int>(N, 0));

        double start = omp_get_wtime();

#pragma omp parallel for
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    C[i][j] += A[i][k] * B[k][j];

        double duration = omp_get_wtime() - start;

        cout << "Threads: " << num_threads
             << " | Time: " << duration << " seconds" << endl;

        file << num_threads << "," << duration << "\n";
    }

    file.close();

    cout << "\nDONE! All results are saved in data/results.csv" << endl;

    return 0;
}