#include <iostream>
#include <vector>
#include <stack>

using namespace std;

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
  while (1)
  {
    cout << "#############\n";
    cout << "1. BF\n";
    cout << "2. BF_path\n";
    cout << "3. TSM\n";
    cout << "4. Exit";
    int op;
    while(1){
      cout << "choose your option: ";
      cin >> op;
      cout << endl;
      switch(op){
        case 1:
          bf();
          break;
        case 2:
          bf_path();
          break;
        case 3:
          tsm();
          break;
        case 4:
          return 0;
        default:
          break;
      }
    }
  }

  return 0;
}
