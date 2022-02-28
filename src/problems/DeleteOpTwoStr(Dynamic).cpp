#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int FindIndexGreaterThan(vector<int> indexes, int index)
{
    vector<int>::iterator indexesIt;
    indexesIt = upper_bound(indexes.begin(), indexes.end(), index);
    if (indexesIt != indexes.end())
        return *indexesIt;
    else
        return -1;
}

int LongestIncreasingSubsequence(unordered_map<char, vector<int>> charToPossibleIndexes, string word)
{
    // subseq = [sequence[0]]
    // para n in sequence:
    //  it = lower_bound(subseq, n)
    //  *it = n se it != subseq.end
    //  subseq.append(n)

    int longest = 0;
    vector<vector<pair<int, int>>> alreadyCalc;
    for (int charIndex = word.length() - 1; charIndex >= 0; charIndex--)
    {
        vector<pair<int, int>> possibleLongestLoc;
        if (charToPossibleIndexes.find(word[charIndex]) != charToPossibleIndexes.end())
        {
            for (int& index : charToPossibleIndexes[word[charIndex]])
            {
                pair<int, int> index_and_longestLocCurrent({index, 1});
                for (vector<pair<int, int>>& index_and_longesLocVec : alreadyCalc)
                {
                    for (pair<int, int> index_and_longesLoc : index_and_longesLocVec)
                    {
                        if (index_and_longesLoc.first > index_and_longestLocCurrent.first && index_and_longesLoc.second + 1 > index_and_longestLocCurrent.second)
                            index_and_longestLocCurrent.second = index_and_longesLoc.second + 1;
                    }
                }

                if (index_and_longestLocCurrent.second > longest)
                    longest = index_and_longestLocCurrent.second;
                possibleLongestLoc.push_back(index_and_longestLocCurrent);
            }
        }
        else
            possibleLongestLoc.push_back({ -1, -1 });

        alreadyCalc.push_back(possibleLongestLoc);
    }
    return longest;
}

class Solution {
public:
    int minDistance(string word1, string word2)
    {
        unordered_map<char, vector<int>> charToIndexes;
        int index = 0;
        for (char& c : word1)
        {
            if (charToIndexes.find(c) != charToIndexes.end()) // already in
                charToIndexes[c].push_back(index);
            else
            {
                vector<int> empty;
                empty.push_back(index);
                charToIndexes[c] = empty;
            }
            index++;
        }

        //for (char& c : word1)
        //{
        //    cout << c << " => ";
        //    for (int& indexOfChar : charToIndexes[c])
        //        cout << indexOfChar << " ";
        //    cout << '\n';
        //}
        //cout << '\n';

        //for (char& c : word2)
        //{
        //    cout << c << " => ";
        //    for (int& indexOfChar : charToIndexes[c])
        //        cout << indexOfChar << " ";
        //    cout << '\n';
        //}

        vector<int> emptySequence;
        int nLongestSequence;
        nLongestSequence = LongestIncreasingSubsequence(charToIndexes, word2);

        //for (int& indexLongest : longestSequence)
        //    cout << indexLongest << " ";
        //cout << '\n';

        return word1.length() + word2.length() - 2 * nLongestSequence;
    }
};

// ***************************************************************************************
// ***************************************************************************************
// ***************************************************************************************
// SOLUTION
// ***************************************************************************************
// ***************************************************************************************
// ***************************************************************************************
//public class Solution {
//    public int minDistance(String s1, String s2) {
//        int[][] memo = new int[s1.length() + 1][s2.length() + 1];
//        return s1.length() + s2.length() - 2 * lcs(s1, s2, s1.length(), s2.length(), memo);
//    }
//    public int lcs(String s1, String s2, int m, int n, int[][] memo) {
//        if (m == 0 || n == 0)
//            return 0;
//        if (memo[m][n] > 0)
//            return memo[m][n];
//        if (s1.charAt(m - 1) == s2.charAt(n - 1))
//            memo[m][n] = 1 + lcs(s1, s2, m - 1, n - 1, memo);
//        else
//            memo[m][n] = Math.max(lcs(s1, s2, m, n - 1, memo), lcs(s1, s2, m - 1, n, memo));
//        return memo[m][n];
//    }
//}


int main_DeleteOpTwoStr()
{
    Solution s;
    // string word1("mart"), word2("karma");
    // string word1("trinitrophenylmethylnitramine"), word2("dinitrophenylhydrazine");
    // string word1("algorithm"), word2("altruistic");
	// string word1("leetcode"), word2("detcole");
    // string word1("vasadasd"), word2("bi");

    cout << s.minDistance("trinitrophenylmethylnitramine", "dinitrophenylhydrazine");

    return 0;
}