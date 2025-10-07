#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

// Knowledge Base
map<string, vector<string>> father;
map<string, vector<string>> mother;

// Add Facts
void addFather(const string &f, const string &c) {
    father[f].push_back(c);
}
void addMother(const string &m, const string &c) {
    mother[m].push_back(c);
}

vector<string> getChildren(const string &p) {
    set<string> result;
    if (father.count(p)) result.insert(father[p].begin(), father[p].end());
    if (mother.count(p)) result.insert(mother[p].begin(), mother[p].end());
    return vector<string>(result.begin(), result.end());
}

vector<string> getParents(const string &name) {
    set<string> result;
    for (const auto &entry : father) {
        if (find(entry.second.begin(), entry.second.end(), name) != entry.second.end())
            result.insert(entry.first);
    }
    for (const auto &entry : mother) {
        if (find(entry.second.begin(), entry.second.end(), name) != entry.second.end())
            result.insert(entry.first);
    }
    return vector<string>(result.begin(), result.end());
}

vector<string> getSiblings(const string &name) {
    set<string> result;

    for (const auto &entry : father) {
        const vector<string> &children = entry.second;
        if (find(children.begin(), children.end(), name) != children.end()) {
            for (const string &c : children)
                if (c != name) result.insert(c);
        }
    }

    for (const auto &entry : mother) {
        const vector<string> &children = entry.second;
        if (find(children.begin(), children.end(), name) != children.end()) {
            for (const string &c : children)
                if (c != name) result.insert(c);
        }
    }

    return vector<string>(result.begin(), result.end());
}

vector<string> getGrandchildren(const string &gp) {
    set<string> result;

    if (father.count(gp)) {
        for (const string &child : father[gp]) {
            vector<string> gkids = getChildren(child);
            result.insert(gkids.begin(), gkids.end());
        }
    }
    if (mother.count(gp)) {
        for (const string &child : mother[gp]) {
            vector<string> gkids = getChildren(child);
            result.insert(gkids.begin(), gkids.end());
        }
    }

    return vector<string>(result.begin(), result.end());
}

vector<string> getGrandparents(const string &name) {
    set<string> result;
    vector<string> parents = getParents(name);

    for (const string &p : parents) {
        vector<string> gps = getParents(p);
        result.insert(gps.begin(), gps.end());
    }

    return vector<string>(result.begin(), result.end());
}

void printList(const vector<string> &list) {
    for (const string &item : list)
        cout << item << " ";
    cout << endl;
}

int main() {
    addFather("Yashvardhan", "Rahul");
    addFather("Yashvardhan", "Rohan");

    addMother("Nandini", "Rahul");
    addMother("Nandini", "Rohan");

    addFather("Rahul", "Krish");
    addMother("Anjali", "Krish");

    cout << "Family Tree Knowledge Base Parser\n";
    cout << "----------------------------------\n";
    cout << "  Supported Queries (Format):\n";
    cout << "  > children <name>\n";
    cout << "  > parents <name>\n";
    cout << "  > siblings <name>\n";
    cout << "  > grandchildren <name>\n";
    cout << "  > grandparents <name>\n";
    cout << "  > exit\n\n";

    string input;
    while (true) {
        cout << "Enter query: ";
        getline(cin, input);

        if (input == "exit") break;

        size_t spacePos = input.find(' ');
        if (spacePos == string::npos) {
            cout << "Invalid query format. Try: children <name>\n";
            continue;
        }

        string command = input.substr(0, spacePos);
        string name = input.substr(spacePos + 1);

        if (command == "children") {
            vector<string> res = getChildren(name);
            if (res.empty()) cout << name << " has no children.\n";
            else { cout << "Children of " << name << ": "; printList(res); }
        } 
        else if (command == "parents") {
            vector<string> res = getParents(name);
            if (res.empty()) cout << name << " has no parents recorded.\n";
            else { cout << "Parents of " << name << ": "; printList(res); }
        } 
        else if (command == "siblings") {
            vector<string> res = getSiblings(name);
            if (res.empty()) cout << name << " has no siblings.\n";
            else { cout << "Siblings of " << name << ": "; printList(res); }
        } 
        else if (command == "grandchildren") {
            vector<string> res = getGrandchildren(name);
            if (res.empty()) cout << name << " has no grandchildren.\n";
            else { cout << "Grandchildren of " << name << ": "; printList(res); }
        } 
        else if (command == "grandparents") {
            vector<string> res = getGrandparents(name);
            if (res.empty()) cout << name << " has no grandparents recorded.\n";
            else { cout << "Grandparents of " << name << ": "; printList(res); }
        } 
        else {
            cout << "Unknown query type. Try: children, parents, siblings, grandchildren, or grandparents.\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}