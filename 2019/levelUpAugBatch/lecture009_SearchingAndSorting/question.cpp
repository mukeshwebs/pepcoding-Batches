#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;
    int n = matrix.size(), m = matrix[0].size();

    int si = 0, ei = n * m - 1;
    while (si <= ei)
    {
        int mid = (si + ei) / 2;
        int val = matrix[mid / m][mid % m];

        if (val == target)
            return true;
        else if (val < target)
            si = mid + 1;
        else
            ei = mid - 1;
    }
    return false;
}

// https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1

long long totalInversionCount(long long arr[], vector<long long> &sortedArray, long long si, long long mid, long long ei)
{
    long long count = 0;
    long long i = si, j = mid, k = si;

    while (i < mid && j <= ei)
    {
        if (arr[i] <= arr[j])
        {
            sortedArray[k++] = arr[i++];
            // arr[i] > arr[j] and i > j; count += ei - j + 1;
        }
        else
        {
            sortedArray[k++] = arr[j++];
            count += mid - i;
        }
    }

    while (i < mid)
        sortedArray[k++] = arr[i++];
    while (j <= ei)
        sortedArray[k++] = arr[j++];

    while (si <= ei)
        arr[si] = sortedArray[si++];
    return count;
}

long long inversionCount(long long arr[], vector<long long> &sortedArray, long long si, long long ei)
{
    if (si >= ei)
        return 0;

    long long mid = (si + ei) / 2;
    long long count = 0;

    count += inversionCount(arr, sortedArray, si, mid);
    count += inversionCount(arr, sortedArray, mid + 1, ei);

    count += totalInversionCount(arr, sortedArray, si, mid + 1, ei);
    return count;
}

long long int inversionCount(long long arr[], long long N)
{
    if (N == 0)
        return 0;
    vector<long long> sortedArray(N, 0);
    return inversionCount(arr, sortedArray, 0, N - 1);
}

int binarySearch(vector<int> &arr, int data)
{
    int si = 0, ei = arr.size();
    while (si < ei)
    {
        int mid = (si + ei) / 2;
        if (data > arr[mid])
            si = mid + 1;
        else
            ei = mid;
    }

    return si;
}

vector<int> findClosestElements(vector<int> &arr, int k, int x)
{
    int n = arr.size();

    if (x <= arr[0])
    {
        vector<int> ans(arr.begin(), arr.begin() + k);
        return ans;
    }
    else if (x >= arr[n - 1])
    {
        vector<int> ans(arr.begin() + n - k, arr.end());
        return ans;
    }
    else
    {

        // int idx = binarySearch(arr, x); // where we suppose to find the x element.
        int idx = (lower_bound(arr.begin(), arr.end(), x) - arr.begin());

        int si = max(0, idx - k);
        int ei = min(n - 1, idx + k);

        while ((ei - si + 1) > k)
        {
            if ((x - arr[si]) > (arr[ei] - x))
                si++;
            else
                ei--;
        }

        vector<int> ans(arr.begin() + si, arr.begin() + ei + 1);
        return ans;
    }
}

//300
int lengthOfLIS(vector<int> &arr)
{
    if (arr.size() <= 1)
        return arr.size();
    int n = arr.size();

    vector<int> list;
    for (int ele : arr)
    {
        // int idx = (lower_bound(list.begin(), list.end(), ele) - list.begin());
        int idx = binarySearch(list,ele);
        if (idx == list.size())
            list.push_back(ele);

        list[idx] = ele;
    }

    return list.size();
}

int main()
{

    return 0;
}
