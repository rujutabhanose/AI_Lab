// Implement constraint satisfaction problem.
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

bool is_consistent(const unordered_map<string, string>& assignment, const string& var, const string& value, const unordered_map<string, vector<string>>& constraints) {
    if (constraints.find(var) != constraints.end()) {
        for (const auto& neighbor : constraints.at(var)) {
            if (assignment.find(neighbor) != assignment.end() && assignment.at(neighbor) == value) { //check neighbours
                return false;
            }
        }
    }
    return true;
}
string select_unassigned_variable(const vector<string>& variables, const unordered_map<string, string>& assignment) {
    for (const auto& var : variables) {
        if (assignment.find(var) == assignment.end()) {
            return var;
        }
    }
    return "";
}
unordered_map<string, string> backtrack(unordered_map<string, string>& assignment, const vector<string>& variables, const unordered_map<string, vector<string>>& domains, const unordered_map<string, vector<string>>& constraints) {
    if (assignment.size() == variables.size()) {
        return assignment;
    }
    string var = select_unassigned_variable(variables, assignment);
    if (var.empty()) {
        return {};
    }
    for (const auto& value : domains.at(var)) {
        if (is_consistent(assignment, var, value, constraints)) {
            assignment[var] = value;
            auto result = backtrack(assignment, variables, domains, constraints); //recursive
            if (!result.empty()) {
                return result;
            }
            assignment.erase(var); //try next colour
        }
    }
    return {};
}
unordered_map<string, string> backtracking_search(const vector<string>& variables, const unordered_map<string   , vector<string>>& domains, const unordered_map<string, vector<string>>& constraints) {
    unordered_map<string, string> assignment;
    return backtrack(assignment, variables, domains, constraints);
}

int main() {
    vector<string> variables = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};
    unordered_map<string, vector<string>> domains;
    for (const auto& var : variables) {
        domains[var] = {"red", "green", "blue"};
    }
    unordered_map<string, vector<string>> constraints = {
        {"WA", {"NT", "SA"}},
        {"NT", {"WA", "SA", "Q"}},
        {"SA", {"WA", "NT", "Q", "NSW", "V"}},
        {"Q", {"NT", "SA", "NSW"}},
        {"NSW", {"SA", "Q", "V"}},
        {"V", {"SA", "NSW"}},
        {"T", {}}
    };

    auto solution = backtracking_search(variables, domains, constraints);

    if (!solution.empty()) {
        cout << "Solution found:" << endl;
        vector<pair<string, string>> sorted_solution(solution.begin(), solution.end());
        sort(sorted_solution.begin(), sorted_solution.end());
        for (const auto& [var, color] : sorted_solution) {
            cout << var << ": " << color << endl;
        }
    } else {
        cout << "No solution found." << endl;
    }
    return 0;
}