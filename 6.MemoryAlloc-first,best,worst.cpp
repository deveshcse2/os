#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

vector<int> firstFit(vector<int> blockSize, int m, vector<int> processSize, int n)
{
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    return allocation;
}

vector<int> NextFit(vector<int> blockSize, int m, vector<int> processSize, int n)
{
    vector<int> allocation(n, -1);
    int j = 0, t = m - 1;

    for (int i = 0; i < n; i++)
    {
        while (j < m)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                t = (j - 1) % m;
                break;
            }
            if (t == j)
            {
                t = (j - 1) % m;
                break;
            }
            j = (j + 1) % m;
        }
    }
    return allocation;
}

vector<int> bestFit(vector<int> blockSize, int m, vector<int> processSize, int n)
{
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++)
    {

        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    return allocation;
}

vector<int> worstFit(vector<int> blockSize, int m, vector<int> processSize, int n)
{

    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++)
    {

        int wstIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i]) // can accomodate current process
            {
                if (wstIdx == -1)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }

        if (wstIdx != -1)
        {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }
    return allocation;
}

int main()
{
    vector<int> blockSize = {100, 500, 200, 300, 600};
    vector<int> processSize = {212, 417, 112, 426};
    int m = blockSize.size();   // no of blocks
    int n = processSize.size(); // no of processes

    vector<int> firstAlloc = firstFit(blockSize, m, processSize, n);
    vector<int> bestAlloc = bestFit(blockSize, m, processSize, n);
    vector<int> worstAlloc = worstFit(blockSize, m, processSize, n);

    int gap = 24;
    cout << "\nProcess No.\tProcess Size\tBlock no.(First Fit)\tBlock no.(Best Fit)\tBlock no.(Worst Fit)\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";

        if (firstAlloc[i] != -1)
            cout << left << setw(gap) << firstAlloc[i] + 1;
        else
            cout << left << setw(gap) << "Not Allocated";

        if (bestAlloc[i] != -1)
            cout << left << setw(gap) << bestAlloc[i] + 1;
        else
            cout << left << setw(gap) << "Not Allocated";

        if (worstAlloc[i] != -1)
            cout << left << setw(gap) << worstAlloc[i] + 1;
        else
            cout << left << setw(gap) << "Not Allocated";

        cout << endl;
    }
    cout << endl;

    return 0;
}
