#include <iostream>
#include <map>

template <typename T>
class ResultSet {
private:
    std::map<T, T> ranges;

public:
    void add(T start, T end) {
        auto it = ranges.upper_bound(start);
        
        // Merge overlapping ranges
        if (it != ranges.begin() && (--it)->second >= start) {
            start = std::min(start, it->first);
            end = std::max(end, it->second);
            ranges.erase(it);
        }

        // Insert the merged or new range
        ranges[start] = end;
    }

    bool test(T val) {
        auto it = ranges.upper_bound(val);
        if (it != ranges.begin() && (--it)->second >= val) {
            return true;
        }
        return false;
    }
};

int main() {
    ResultSet<int> resultSet;

    // Adding ranges to the ResultSet
    resultSet.add(1, 5);
    resultSet.add(8, 10);
    resultSet.add(15, 20);

    // Testing values
    std::cout << resultSet.test(3) << std::endl;  // Should output 1 (true)
    std::cout << resultSet.test(12) << std::endl; // Should output 0 (false)

    return 0;
}
