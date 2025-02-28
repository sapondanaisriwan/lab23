#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

char score2grade(int score)
{
    if (score >= 80)
        return 'A';
    if (score >= 70)
        return 'B';
    if (score >= 60)
        return 'C';
    if (score >= 50)
        return 'D';
    else
        return 'F';
}

string toUpperStr(string x)
{
    string y = x;
    for (unsigned i = 0; i < x.size(); i++)
        y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades)
{
    ifstream target(filename);
    string textline = "";
    int s1, s2, s3, sum = 0;
    char name[999];
    char grade;
    while (getline(target, textline))
    {
        sscanf(textline.c_str(), "%[^:]: %d %d %d", name, &s1, &s2, &s3);
        sum = s1 + s2 + s3;
        grade = score2grade(sum);
        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(grade);
    };
}

void getCommand(string &command, string &key)
{
    string textline = "";
    cout << "Please input your command:" << endl;
    getline(cin, textline);
    int findStr = textline.find_first_of(' ');

    command = textline.substr(0, findStr);
    key = textline.substr(findStr + 1, textline.size());
    return;
    // cout << " " << command << " " << key << endl;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key)
{
    bool isFound = false;
    for (unsigned i = 0; i < names.size(); i++)
    {
        if (toUpperStr(names[i]) == key)
        {
            cout << "---------------------------------" << endl;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;

            isFound = true;
        }
    }
    if (!isFound)
    {
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key)
{
    bool isFound = false;
    cout << "---------------------------------\n";

    for (unsigned i = 0; i < grades.size(); i++)
    {
        if (grades[i] == key[0])
        {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            isFound = true;
        }
    }

    if (!isFound)
    {
        cout << "Cannot found." << endl;
    }

    cout << "---------------------------------\n";
}

int main()
{
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades;
    importDataFromFile(filename, names, scores, grades);

    do
    {
        string command, key;
        getCommand(command, key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if (command == "EXIT")
            break;
        else if (command == "GRADE")
            searchGrade(names, scores, grades, key);
        else if (command == "NAME")
        {
            searchName(names, scores, grades, key);
        }
        else
        {
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    } while (true);

    return 0;
}
