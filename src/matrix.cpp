#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void run_test(int num_threads, int N)
{
    vector<vector<int>> A(N, vector<int>(N, 1)), B(N, vector<int>(N, 2)), C(N, vector<int>(N, 0));

    omp_set_num_threads(num_threads);

    double start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];

    double duration = omp_get_wtime() - start;
    cout << "Threads: " << num_threads << " | Time: " << duration << " seconds" << endl;
}

int main()
{
    int N = 1000;
    int tests[] = {1, 2, 4, 8};

    cout << "--- Starting Matrix Multiplication Benchmarks ---" << endl;

    for (int t : tests)
    {
        run_test(t, N);
    }

    return 0;
}