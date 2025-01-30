#include <iostream>
#include <vector>
using namespace std;

int main() {
    int arraySize, maxSegmentSum;
    cin >> arraySize >> maxSegmentSum;

    vector<int> array(arraySize);
    for (int i = 0; i < arraySize; i++) {
        cin >> array[i];
    }

    vector<int> maxEndIndex(arraySize);
    for (int startIndex = 0, endIndex = 0, currentSum = array[0]; startIndex < arraySize; startIndex++) {
        while (endIndex + 1 < arraySize && currentSum + array[endIndex + 1] <= maxSegmentSum) {
            currentSum += array[++endIndex];
        }
        maxEndIndex[startIndex] = endIndex;
        currentSum -= array[startIndex];
    }

    int totalWeightedSum = 0;
    for (int segmentStart = 0; segmentStart < arraySize; segmentStart++) {
        int segmentWeight = 1, currentStart = segmentStart;
        while (currentStart < arraySize) {
            totalWeightedSum += segmentWeight * (maxEndIndex[currentStart] - currentStart + 1);
            currentStart = maxEndIndex[currentStart] + 1;
            segmentWeight++;
        }
    }

    cout << totalWeightedSum << endl;
    return 0;
}
