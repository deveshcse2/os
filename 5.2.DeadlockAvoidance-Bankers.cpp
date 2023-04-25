#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
    int n;
    cout << "Enter number of processes" << endl;
    cin >> n;
    int m;
    cout << "Enter number of resources" << endl;
    cin >> m;
    vector<int> available(m);
    vector<vector<int>> allocation(n, vector<int>(m, 0));
    vector<vector<int>> max_need(n, vector<int>(m, 0));
    cout << "Enter Availability for:-" << endl;
    for (int i = 0; i < m; i++)
    {
        cout << "R" << i << "- ";
        cin >> available[i];
        cout << endl;
    }
    cout << "Enter allocation matrix" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }
    cout << "Enter Max_need Matrix" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> max_need[i][j];
        }
    }
    vector<vector<int>> need(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }
    queue<int> safe_sequence;
    vector<bool> vis(n, 0);
    for (int i = 0; i < n; i++)
    {
        bool got = false;
        for (int j = 0; j < n; j++)
        {
            if (!vis[j])
            {
                bool flag = true;
                for (int k = 0; k < m; k++)
                {
                    if (available[k] < need[j][k])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    safe_sequence.push(j);
                    vis[j] = 1;
                    for (int t = 0; t < m; t++)
                    {
                        available[t] += allocation[j][t];
                        got = true;
                    }
                }
            }
        }
        if (!got)
        {
            break;
        }
    }
    if (safe_sequence.size() < n)
    {
        cout << "The system is in deadlock" << endl;
    }
    else
    {
        cout << "Safe sequence should be:-" << endl;
        while (!safe_sequence.empty())
        {
            cout << "P" << safe_sequence.front() << " ";
            safe_sequence.pop();
        }
        cout << endl;
    }
}