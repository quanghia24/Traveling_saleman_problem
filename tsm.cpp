#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

// Structure to represent an edge between two vertices
struct Edge
{
  int source, destination, weight;
};

// Function to calculate the distance between two points (vertices)
double distance(pair<int, int> point1, pair<int, int> point2)
{
  int dx = point1.first - point2.first;
  int dy = point1.second - point2.second;
  return sqrt(dx * dx + dy * dy);
}

// Function to find the shortest tour using brute force
vector<int> Traveling(vector<pair<int, int>> &vertices, char startVertex)
{
  int n = vertices.size();
  vector<int> tour(n);
  for (int i = 0; i < n; ++i)
  {
    tour[i] = i;
  }
  double minDistance = INT_MAX;

  do
  {
    double totalDistance = 0;
    for (int i = 0; i < n - 1; ++i)
    {
      totalDistance += distance(vertices[tour[i]], vertices[tour[i + 1]]);
    }
    totalDistance += distance(vertices[tour[n - 1]], vertices[tour[0]]); // Complete the loop
    if (totalDistance < minDistance)
    {
      minDistance = totalDistance;
    }
  } while (next_permutation(tour.begin() + 1, tour.end()));

  return tour;
}

int main()  // Chu trình có trọng số nhỏ nhất về lại node cũ
            // thật toán tự do -> kèm pdf giảm thích thuật toán
{
  vector<pair<int, int>> vertices = {{0, 0}, {1, 2}, {3, 4}, {5, 1}}; // Coordinates of vertices
  char startVertex = 'A';                                             // Start vertex

  // Calculate the shortest traveling salesman path
  vector<int> shortestTour = Traveling(vertices, startVertex);

  // Output the shortest tour
  cout << "Shortest tour: ";
  for (int vertex : shortestTour)
  {
    cout << (char)(vertex + 'A') << " ";
  }
  cout << endl;

  return 0;
}
