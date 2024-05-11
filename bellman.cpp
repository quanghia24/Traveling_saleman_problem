#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

struct Edge
{
  int source, destination, weight;
};

// Function to perform one step of Bellman-Ford algorithm
void BF(Edge graph[], int V, char startVertex, int step, vector<int> &valueArray, vector<int> &previousArray)
{
  // Initialize updated arrays with current values
  vector<int> updatedValue = valueArray;
  vector<int> updatedPrevious = previousArray;

  // Convert startVertex to integer representation
  int start = startVertex - 'A';

  while (step--)
  {
    for (int i = 0; i < V; i++)
    {
      int u = graph[i].source;
      int v = graph[i].destination;
      int w = graph[i].weight;

      if (valueArray[u] != -1 && valueArray[u] + w < updatedValue[v])
      {
        updatedValue[v] = valueArray[u] + w;
        updatedPrevious[v] = u;
      }
    }
    // check for negative circuit
    for (int i = 0; i < V; i++)
    {
      int u = graph[i].source;
      int v = graph[i].destination;
      int w = graph[i].weight;

      if (valueArray[u] != -1 && valueArray[u] + w < updatedValue[v])
      {
        cout << "Contains circuit of negative weight";
        exit(1);
      }
    }
  }

  // Update the current Bellman-Ford value and previous arrays
  valueArray = updatedValue;
  previousArray = updatedPrevious;
}

void BF_Path(Edge graph[], int V, char startVertex, char goalVertex, vector<int> &valueArray, vector<int> &previousArray)
{
  string ans = "hllo";
  BF(graph, V, startVertex, V - 1, valueArray, previousArray);
  int start = startVertex - 'A';
  int goal = goalVertex - 'A';
  stack<char> path;

  // Check if there is a path from start to goal
  if (valueArray[goal] == -1)
  {
    cout << "No path exists from " << startVertex << " to " << goalVertex << endl;
    return;
  }

  // BACKTRACK AND PRINT THE PATH BACKWARD USING STACK TO STORE PATH WHILE MOVING BACKWARD
  // Use a stack to store the vertices of the shortest path

  // Backtrack from goal to start vertex using Bellman-Ford previous array
  while (goal != start)
  {
    path.push(goal);
    goal = previousArray[goal];
  }
  path.push(goal);
  // Print the shortest path
  cout << "Shortest path from " << startVertex << " to " << goalVertex << ": ";
  while (!path.empty())
  {
    cout << (char)(path.top() + 'A') << " ";
    path.pop();
  }
}

void print(int V, vector<int> &valueArray, vector<int> &previousArray)
{
  // Output updated Bellman-Ford value array
  cout << "Value array:" << endl;
  for (int i = 0; i < V; ++i)
    cout << (char)(i + 'A') << ": " << valueArray[i] << endl;

  // Output updated Bellman-Ford previous array
  cout << "Previous array:" << endl;
  for (int i = 0; i < V; ++i)
    cout << (char)(i + 'A') << ": " << (previousArray[i] == -1 ? '-' : (char)(previousArray[i] + 'A')) << endl;
}

int main()
{
  Edge graph[10] = {
      {0, 1, 6},
      {0, 2, 7},
      {1, 2, 8},
      {1, 3, 4},
      {1, 4, 5},
      {2, 3, 9},
      {2, 4, 3},
      {3, 4, 7},
      {3, 5, 2},
      {4, 5, 7}};

  char startVertex; // Start vertex
  char goalVertex;  // Goal vertex
  int step;
  map<char, int> _map;

  int V = sizeof(graph) / sizeof(graph[0]); // Number of vertices
  for (int i = 0; i < V; i++)
  {
    _map[graph[i].source]++;
    _map[graph[i].destination]++;
  }

  cout << "Start Vertext (A-Z): ";
  cin >> startVertex;
  cout << "step: ";
  cin >> step;

  // Initialize Bellman-Ford value and previous arrays
  vector<int> valueArray(V, -1);
  vector<int> previousArray(V, -1);
  valueArray[startVertex - 'A'] = 0;

  for (int i = 1; i <= step; i++)
  {
    print(V, valueArray, previousArray);
    BF(graph, V, startVertex, i, valueArray, previousArray);
  }
  print(V, valueArray, previousArray);

  cout << "Start Vertext (A-Z): ";
  cin >> startVertex;
  cout << "Goal Vertext (A-Z):";
  cin >> goalVertex;

  BF_Path(graph, V, startVertex, goalVertex, valueArray, previousArray);

  return 0;
}
