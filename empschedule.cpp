#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Configuration
const int MAX_DAYS_PER_WEEK = 5;
const int MIN_PER_SHIFT = 2;
const int MAX_PER_SHIFT = 3;

const vector<string> DAYS = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const vector<string> SHIFTS = {"Morning", "Afternoon", "Evening"};

// Employee Class
class Employee {
public:
    string name;
    string preferredShift;
    int daysWorkedCount;
    map<string, string> schedule; // Day -> Shift

    Employee(string n, string pref) : name(n), preferredShift(pref), daysWorkedCount(0) {
        for (const auto& day : DAYS) {
            schedule[day] = "OFF";
        }
    }

    bool canWork(string day) {
        return (schedule[day] == "OFF" && daysWorkedCount < MAX_DAYS_PER_WEEK);
    }

    void assignShift(string day, string shift) {
        schedule[day] = shift;
        daysWorkedCount++;
    }
};

// Global Schedule Structure: Day -> Shift -> List of Employee Names
map<string, map<string, vector<string>>> masterSchedule;

void generateSchedule(vector<Employee>& employees) {
    // Initialize Schedule
    for (const auto& day : DAYS) {
        for (const auto& shift : SHIFTS) {
            masterSchedule[day][shift] = vector<string>();
        }
    }

    // Logic Loop
    for (const auto& day : DAYS) {
        // --- Phase 1: Assign by Preference ---
        for (auto& emp : employees) {
            if (emp.canWork(day)) {
                string pref = emp.preferredShift;
                
                // Check if preferred shift is full
                if (masterSchedule[day][pref].size() < MAX_PER_SHIFT) {
                    masterSchedule[day][pref].push_back(emp.name);
                    emp.assignShift(day, pref);
                } else {
                    // CONFLICT RESOLUTION: Try other shifts
                    for (const auto& altShift : SHIFTS) {
                        if (altShift != pref && masterSchedule[day][altShift].size() < MAX_PER_SHIFT) {
                            masterSchedule[day][altShift].push_back(emp.name);
                            emp.assignShift(day, altShift);
                            break; // Stop looking for this day
                        }
                    }
                }
            }
        }

        // --- Phase 2: Ensure Minimum Staffing ---
        for (const auto& shift : SHIFTS) {
            while (masterSchedule[day][shift].size() < MIN_PER_SHIFT) {
                // Find candidates
                vector<int> candidateIndices;
                for (size_t i = 0; i < employees.size(); ++i) {
                    if (employees[i].canWork(day)) {
                        candidateIndices.push_back(i);
                    }
                }

                if (candidateIndices.empty()) {
                    break; // Cannot fill gap
                }

                // Randomly select a candidate
                int randIndex = candidateIndices[rand() % candidateIndices.size()];
                Employee& chosen = employees[randIndex];
                
                masterSchedule[day][shift].push_back(chosen.name);
                chosen.assignShift(day, shift);
            }
        }
    }
}

void printSchedule() {
    cout << "\n====== FINAL WEEKLY SCHEDULE ======\n";
    for (const auto& day : DAYS) {
        cout << "\n" << day << ":\n";
        for (const auto& shift : SHIFTS) {
            cout << "  " << shift << ": ";
            const auto& workers = masterSchedule[day][shift];
            if (workers.empty()) {
                cout << "No Staff";
            } else {
                for (size_t i = 0; i < workers.size(); ++i) {
                    cout << workers[i] << (i < workers.size() - 1 ? ", " : "");
                }
            }
            cout << endl;
        }
    }
}

int main() {
    srand(time(0)); // Seed random number generator

    // Input Simulation
    vector<Employee> staffList;
    staffList.push_back(Employee("Alice", "Morning"));
    staffList.push_back(Employee("Bob", "Morning"));
    staffList.push_back(Employee("Charlie", "Afternoon"));
    staffList.push_back(Employee("David", "Afternoon"));
    staffList.push_back(Employee("Eve", "Evening"));
    staffList.push_back(Employee("Frank", "Evening"));
    staffList.push_back(Employee("Grace", "Morning"));
    staffList.push_back(Employee("Heidi", "Afternoon"));

    // Execute
    generateSchedule(staffList);
    printSchedule();

    return 0;
}