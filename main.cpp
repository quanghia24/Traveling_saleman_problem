#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <stdexcept>
using namespace std;

class TspDynamicProgrammingIterative
{
private:
    int N, start;
    vector<vector<double>> distance;
    vector<int> tour;
    double minTourCost = std::numeric_limits<double>::infinity();
    bool ranSolver = false;

    static bool notIn(int elem, int subset)
    {
        return ((1 << elem) & subset) == 0;
    }

    static vector<int> combinations(int r, int n)
    {
        vector<int> subsets;
        combinations(0, 0, r, n, subsets);
        return subsets;
    }

    static void combinations(int set, int at, int r, int n, vector<int> &subsets)
    {
        int elementsLeftToPick = n - at;
        if (elementsLeftToPick < r)
            return;
        if (r == 0)
        {
            subsets.push_back(set);
        }
        else
        {
            for (int i = at; i < n; ++i)
            {
                set |= (1 << i);
                combinations(set, i + 1, r - 1, n, subsets);
                set &= ~(1 << i);
            }
        }
    }

public:
    TspDynamicProgrammingIterative(const vector<vector<double>> &distance, int start = 0)
        : distance(distance), N(distance.size()), start(start)
    {
        // if (N <= 2)
        //     throw std::invalid_argument("N <= 2 not yet supported."); // TODO
        for (const auto &row : distance)
        {
            if (row.size() != N)
                throw std::invalid_argument("Matrix must be square (n x n)");
        }
        if (start < 0 || start >= N)
            throw std::invalid_argument("Invalid start node.");
        if (N > 32)
            throw std::invalid_argument("Matrix too large! Requires too much computation.");
    }

    vector<int> getTour()
    {
        if (!ranSolver)
            solve();
        return tour;
    }

    double getTourCost()
    {
        if (!ranSolver)
            solve();
        return minTourCost;
    }

    void solve()
    {
        if (ranSolver)
            return;

        const int END_STATE = (1 << N) - 1; // all bits set to 1
        vector<vector<double>> memo(N, vector<double>(1 << N, numeric_limits<double>::infinity()));

        // step 1
        for (int end = 0; end < N; ++end)
        {
            if (end == start)
                continue;
            // TODO
            if (distance[start][end] != 0)
                memo[end][(1 << start) | (1 << end)] = distance[start][end];
        }
        
        // step 2 create tour of path
        for (int r = 3; r <= N; ++r)
        {
            for (int subset : combinations(r, N))
            {
                if (notIn(start, subset))
                    continue;
                for (int next = 0; next < N; ++next)
                {
                    if (next == start || notIn(next, subset))
                        continue;
                    int subsetWithoutNext = subset ^ (1 << next);
                    double minDist = numeric_limits<double>::infinity();
                    for (int end = 0; end < N; ++end)
                    {
                        if (end == start || end == next || notIn(end, subset) || distance[end][next] == 0)
                            continue;
                        double newDistance = memo[end][subsetWithoutNext] + distance[end][next];
                        if (newDistance < minDist)
                        {
                            minDist = newDistance;
                        }
                    }
                    memo[next][subset] = minDist;
                }
            }
        }

        for (int i = 0; i < N; ++i)
        {
            if (i == start || distance[i][start] == 0)
                continue;
            double tourCost = memo[i][END_STATE] + distance[i][start];
            if (tourCost < minTourCost)
            {
                minTourCost = tourCost;
            }
        }

        int lastIndex = start;
        int state = END_STATE;
        tour.push_back(start);

        for (int i = 1; i < N; ++i){ // counter
            int bestIndex = -1; // best next node
            double bestDist = numeric_limits<double>::infinity();
            for (int j = 0; j < N; ++j)
            {
                if (j == start || notIn(j, state) || distance[j][lastIndex] == 0)
                    continue;
                // if(distance[j][lastIndex] == 0)
                //     distance[j][lastIndex] = 99999;
                double newDist = memo[j][state] + distance[j][lastIndex];
                if (newDist < bestDist)
                {
                    bestIndex = j;
                    bestDist = newDist;
                }
            }
            tour.push_back(bestIndex);
            state = state ^ (1 << bestIndex);
            lastIndex = bestIndex;
        }

        tour.push_back(start);
        reverse(tour.begin(), tour.end());

        ranSolver = true;
    }
};

string Traveling(int graph[20][20], int n, char S)
{
    vector<vector<double>> distanceMatrix;

    // turn 2d array into 2d vector
    distanceMatrix.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        vector<double> tmp(graph[i], graph[i] + n);
        distanceMatrix.push_back(tmp);
    }

    int startNode = S - 'A';
    TspDynamicProgrammingIterative solver(distanceMatrix, startNode);

    vector<int> tour = solver.getTour();
    double tourCost = solver.getTourCost();
 

    string res = "";
    for (int node : tour)
    {
        res += (char)(node + 'A');
        res += " ";
    }
    res = res.substr(0, res.length()- 1);
    return res;
}

int main()
{
    // int graph[20][20] = {
    //     {0, 200},
    //     {1, 0}};

    // int graph[20][20] = {
    //     {0, 0, 0, 8, 0, 0},
    //     {0, 0, 0, 0, 0, 12},
    //     {0, 0, 0, 0, 4, 0},
    //     {0, 0, 6, 0, 0, 0},
    //     {0, 2, 0, 0, 0, 0},
    //     {10, 0, 0, 0, 0, 0}};
    
    int graph[20][20] = {
        {0, 17, 40, 100, 32, 11, 29, 77, 73, 53, 52, 72},
        {48, 0, 23, 42, 81, 5, 12, 37, 31, 55, 18, 66},
        {48, 97, 0, 74, 21, 43, 8, 37, 48, 13, 55, 88},
        {79, 53, 66, 0, 8, 97, 38, 61, 48, 76, 75, 71},
        {18, 56, 42, 97, 0, 59, 40, 51, 77, 5, 65, 39},
        {45, 86, 82, 20, 23, 0, 96, 100, 44, 84, 45, 97},
        {15, 53, 93, 53, 80, 7, 0, 29, 21, 78, 13, 43},
        {87, 9, 1, 26, 26, 44, 98, 0, 92, 49, 9, 77},
        {30, 29, 66, 93, 28, 9, 76, 73, 0, 73, 91, 92},
        {31, 9, 38, 38, 38, 25, 83, 17, 68, 0, 69, 93},
        {35, 61, 19, 45, 24, 10, 94, 33, 53, 90, 0, 62},
        {19, 82, 57, 95, 57, 96, 67, 13, 54, 65, 90, 0}}; 
    
    cout << Traveling(graph, 12, 'A');

    return 0;
}
