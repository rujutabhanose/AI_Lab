// Implement backward chaining algorithm
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Function for backward chaining
bool backward_chaining(string goal, 
                       const vector<string> &known_facts, 
                       const vector<pair<vector<string>, string>> &inference_rules) {
    // If the goal is already a known fact
    if (find(known_facts.begin(), known_facts.end(), goal) != known_facts.end()) {
        cout << "Goal " << goal << " is already known." << endl;
        return true;
    }

    // Try to find a rule that can conclude this goal
    for (auto &rule : inference_rules) {
        vector<string> prerequisites = rule.first;
        string conclusion = rule.second;

        if (conclusion == goal) {
            cout << "Trying to prove goal: " << goal 
                 << " using rule with conclusion " << conclusion << endl;

            bool all_conditions_met = true;
            for (auto &condition : prerequisites) {
                if (!backward_chaining(condition, known_facts, inference_rules)) {
                    all_conditions_met = false;
                    break;
                }
            }

            if (all_conditions_met) {
                cout << "Goal " << goal << " has been proven." << endl;
                return true;
            }
        }
    }

    cout << "Goal " << goal << " cannot be proven." << endl;
    return false;
}

int main() {
    // Initial known facts
    vector<string> known_facts = {"X", "Y"};

    // Rules in (conditions, conclusion) format
    vector<pair<vector<string>, string>> inference_rules = {
        {{"X", "Y"}, "Z"},
        {{"Z"}, "W"},
        {{"W"}, "V"}
    };

    string goal_to_prove = "V";
    cout << "\nStarting backward chaining to prove goal: " << goal_to_prove << endl;

    bool can_prove_goal = backward_chaining(goal_to_prove, known_facts, inference_rules);

    if (can_prove_goal)
        cout << "Final conclusion: The goal " << goal_to_prove << " can be proven." << endl;
    else
        cout << "Final conclusion: The goal " << goal_to_prove << " cannot be proven." << endl;

    return 0;
}