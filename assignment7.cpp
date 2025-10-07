// Implement Forward Chaining Algorithm
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

// Function to apply forward chaining
set<string> apply_forward_chaining(vector<string> initial_facts,
                                   vector<pair<vector<string>, string>> inference_rules) {
    set<string> known_facts(initial_facts.begin(), initial_facts.end());
    bool new_fact_found = true;

    while (new_fact_found) {
        new_fact_found = false;

        for (auto &rule : inference_rules) {
            vector<string> prerequisites = rule.first;
            string outcome = rule.second;

            // Check if all prerequisites are met
            bool prerequisites_met = all_of(prerequisites.begin(), prerequisites.end(),
                [&](const string &cond) {
                    return known_facts.find(cond) != known_facts.end();
                });

            // If prerequisites are met and the outcome is new
            if (prerequisites_met && known_facts.find(outcome) == known_facts.end()) {
                known_facts.insert(outcome);
                cout << "Derived new fact: " << outcome << endl;
                new_fact_found = true;
            }
        }
    }

    return known_facts;
}

int main() {
    // Initial facts
    vector<string> initial_facts = {"X", "Y"};

    // Rules in the format (conditions, conclusion)
    vector<pair<vector<string>, string>> inference_rules = {
        {{"X", "Y"}, "Z"},   // If X and Y then Z
        {{"Z"}, "W"},        // If Z then W
        {{"W"}, "V"}         // If W then V
    };

    cout << "Starting facts: ";
    for (auto &fact : initial_facts) cout << fact << " ";
    cout << endl;

    // Apply forward chaining
    set<string> derived_facts = apply_forward_chaining(initial_facts, inference_rules);

    cout << "Final derived facts: ";
    for (auto &fact : derived_facts) cout << fact << " ";
    cout << endl;

    return 0;
}