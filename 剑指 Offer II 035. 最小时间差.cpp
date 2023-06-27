class Cmp_t{
public:
    bool operator()(const string& t1, const string& t2) const {
        int h1 = stoi(t1.substr(0, 2));
        int h2 = stoi(t2.substr(0, 2));
        if(h1 < h2) return true;
        else if(h1 > h2) return false;
        else {
            int m1 = stoi(t1.substr(3, 2));
            int m2 = stoi(t2.substr(3, 2));
            if(m1 < m2) return true;
            else return false;
        }
    }
};

class Solution {
public:
    int calGapMin(const string& t1, const string& t2, bool nextDay) {
        int h1 = stoi(t1.substr(0, 2));
        int h2 = stoi(t2.substr(0, 2));
        int m1 = stoi(t1.substr(3, 2));
        int m2 = stoi(t2.substr(3, 2));
        if(nextDay) h2 += 24;
        return (h2 - h1) * 60 + (m2 - m1);
    }

    int findMinDifference(vector<string>& timePoints) {
        if(timePoints.size() > 1440) return 0;
        sort(timePoints.begin(), timePoints.end(), Cmp_t());
        timePoints.push_back(timePoints[0]);
        int result = __INT_MAX__;
        for(int i = 0; i < timePoints.size() - 1; i++) {
            int gap = calGapMin(timePoints[i], timePoints[i + 1], i == timePoints.size() - 2 ? true : false);
            if(gap < result) result = gap;
        }
        return result;
    }
};