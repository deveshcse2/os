#include <iostream>
#include <vector>
#include <queue>
using namespace std;
static bool mycomp(pair<int, pair<pair<int, int>, int>> p1, pair<int, pair<pair<int, int>, int>> p2)
{
    return p1.second.first.first < p2.second.first.first;
}
class mycomp1
{
public:
    bool operator()(pair<int, pair<pair<int, int>, int>> p1, pair<int, pair<pair<int, int>, int>> p2)
    {
        return p1.second < p2.second;
    }
};
int main()
{
    int n;
    cout << "Input Number of processes" << endl;
    cin >> n;
    vector<pair<int, pair<pair<int, int>, int>>> vi(n);
    for (int i = 0; i < n; i++)
    {
        cout << "\nWrite Arrival Time for process P" << i + 1 << ":";
        cin >> vi[i].second.first.first;
        cout << "Write Burst time for process P" << i + 1 << ":";
        cin >> vi[i].second.first.second;
        cout << "Write Priority for process P" << i + 1 << ":";
        cin >> vi[i].second.second;
        vi[i].first = i + 1;
    }
    cout << endl;
    sort(vi.begin(), vi.end(), mycomp);
    priority_queue<pair<int, pair<pair<int, int>, int>>, vector<pair<int, pair<pair<int, int>, int>>>, mycomp1> pq;
    int i = 0;
    int time = vi[0].second.first.first;
    for (; i < n; i++)
    {
        if (vi[i].second.first.first <= time)
        {
            pq.push(vi[i]);
        }
        else
        {
            break;
        }
    }
    int count = 0;
    vector<pair<int, pair<int, int>>> gantt_chart;
    while (!pq.empty())
    {
        for (; i < n; i++)
        {
            if (vi[i].second.first.first <= time)
            {
                pq.push(vi[i]);
            }
            else
            {
                break;
            }
        }
        int a = pq.top().first;
        int b = pq.top().second.first.first;
        int c = pq.top().second.first.second;
        int d = pq.top().second.second;
        pq.pop();
        if (c == 1)
        {
            gantt_chart.push_back({a, {time, time + c}});
            time += c;
        }
        else
        {
            gantt_chart.push_back({a, {time, time + 1}});
            time += 1;
            pq.push({a, {{b, c - 1}, d}});
        }
        count++;
    }
    int total_TAT = 0;
    int total_waiting_time = 0;
    float avg_TAT = 0;
    float avg_waiting_time = 0;
    vector<int> last_occurence(n);
    cout << "Processes will execute in the order:-" << endl;
    for (auto i : gantt_chart)
    {
        cout << "P" << i.first << " ";
        last_occurence[i.first - 1] = i.second.second;
    }
    for (int i = 0; i < n; i++)
    {
        total_TAT += last_occurence[i] - vi[i].second.first.first;
        total_waiting_time += last_occurence[i] - vi[i].second.first.first - vi[i].second.first.second;
    }
    avg_TAT = (float)total_TAT / n;
    avg_waiting_time = (float)total_waiting_time / n;
    cout << endl;
    cout << "Average Turn-Around time=" << avg_TAT << endl;
    cout << "Average waiting time=" << avg_waiting_time << endl;
    return 0;
}
