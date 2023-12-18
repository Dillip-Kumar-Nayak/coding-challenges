#include <iostream>
#include <set>

struct Interval {
    int start;
    int end;

    Interval(int s, int e) : start(s), end(e) {}

    // Define a custom comparison operator for sorting intervals in the set
    bool operator<(const Interval& other) const {
        return end < other.start; // Compare based on the end time
    }
};

class IntervalScheduler {
private:
    std::set<Interval> schedule;

public:
    bool canAcceptTask(const Interval& newTask) {
        auto it = schedule.lower_bound(newTask);

        if (it != schedule.end() && newTask.end > it->start) {
            std::cout << "Task overlaps and cannot be accepted.\n";
            return false;
        } else {
            std::cout << "Task accepted and added to the schedule.\n";
            schedule.insert(newTask);
            return true;
        }
    }
};

int main() {
    IntervalScheduler scheduler;

    // Example usage
    Interval task1(1, 3);
    Interval task2(2, 5);
    Interval task3(6, 8);

    scheduler.canAcceptTask(task1);
    scheduler.canAcceptTask(task2);
    scheduler.canAcceptTask(task3);

    return 0;
}

