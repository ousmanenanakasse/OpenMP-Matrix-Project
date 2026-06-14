#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{

    ifstream infile("data/results.csv");
    if (!infile.is_open())
    {
        cout << "Error: Could not open data/results.csv. Make sure the file exists!" << endl;
        return 1;
    }

    vector<int> threads;
    vector<double> raw_times;
    string line, header;

    getline(infile, header);

    while (getline(infile, line))
    {
        stringstream ss(line);
        string thread_str, time_str;

        getline(ss, thread_str, ',');
        getline(ss, time_str, ',');

        threads.push_back(stoi(thread_str));
        raw_times.push_back(stod(time_str));
    }
    infile.close();

    int window_size = 20;
    vector<double> smoothed_times(raw_times.size(), 0.0);

    for (int i = 0; i < raw_times.size(); i++)
    {
        double sum = 0;
        int count = 0;

        for (int j = i - window_size / 2; j <= i + window_size / 2; j++)
        {
            if (j >= 0 && j < raw_times.size())
            {
                sum += raw_times[j];
                count++;
            }
        }
        smoothed_times[i] = sum / count;
    }

    ofstream outfile("data/smoothed_results.csv");
    outfile << "Threads,Raw_Time,Smoothed_Time\n";

    for (int i = 0; i < threads.size(); i++)
    {
        outfile << threads[i] << "," << raw_times[i] << "," << smoothed_times[i] << "\n";
    }
    outfile.close();

    cout << "Success! Created data/smoothed_results.csv with Window Size: " << window_size << endl;
    return 0;
}