//============================================================================
// Name        : CoursePlanner.cpp
// Author      : Ally Miller
// Version     : 1.0
// Description : Course Planner to read courses from CSV file, stores in Hash
//     Table,  display course list in alphanumeric order, and display course
//     individual information
//============================================================================
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <algorithm>


using namespace std;

class CoursePlanner
{
private:
    //structure to hold courseName and prerequisites
    struct CourseInfo
    {
        string courseName;
        vector<string> prerequisites;
    };

    //unordered map is a type safety hash table
    unordered_map<string, CourseInfo> courses;

    //function declarations, only accessed by menu
    vector<string> split(const string &s, char delimiter);
    void readCSV(const string &fileName, unordered_map<string, CourseInfo> &hashTable);
    void printCourse(string &courseID);
    void printCourseList();

public:
    CoursePlanner();
    void menu();
};

//default constructor
CoursePlanner::CoursePlanner() = default;

//helper function to split by delimiter (comma)
vector<string> CoursePlanner::split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

//read CSV file, split by delimiter, and store in hash table
void CoursePlanner::readCSV(const string &fileName, unordered_map<string, CourseInfo> &hashTable)
{
    ifstream file(fileName);
    string line;
    while (getline(file, line))
    {
        vector<string> tokens = split(line, ',');
        if (!tokens.empty())
        {
            CourseInfo info;
            // courseID = key
            string key = tokens[0];
            // courseName = title
            info.courseName = tokens[1];
            // add prerequisites, start at 2, if size is greater than 2, it has prerequisites, else no prerequisites
            for (size_t i = 2; i < tokens.size(); ++i)
            {
                info.prerequisites.push_back(tokens[i]);
            }
            hashTable[key] = info;
        }
    }
}

//print individual courseID, courseName, and prerequisites
void CoursePlanner::printCourse(string& courseID)
{
    //convert courseID input to upper case
    for (auto &c: courseID)
    {
        c = toupper(c);
    }

    //check if courseID is in hash table
    if (courses.find(courseID) != courses.end())
    {
        //print courseID, courseName, and coursePrerequisites
        cout << courseID << ", " << courses[courseID].courseName
             << "\nPrerequisites: ";
        for (const string &prerequisites : courses[courseID].prerequisites)
        {
            cout << prerequisites << " ";
        }
        cout << endl;
    }
    else
    {
        cout << courseID << " does not exist." << endl;
    }
}

//print course list in alphanumeric order
void CoursePlanner::printCourseList()
{
    //extract keys and sort them
    vector<string> keys;
    for (const auto &pair: courses)
    {
        keys.push_back(pair.first);
    }
    sort(keys.begin(), keys.end());

    //print courses in alphanumeric order
    cout << "Here is a sample schedule:\n" << endl;
    for (const auto &key: keys)
    {
        cout << key << ", " << courses[key].courseName << endl;
    }
}

//control menu
void CoursePlanner::menu()
{
    cout << "Welcome to the course planner." << endl;

    int choice = 0;
    while (choice != 9)
    {
        //reset courseID
        string courseID;

        cout << "\n1. Load Data Structure."
             << "\n2. Print Course List."
             << "\n3. Print Course."
             << "\n9. Exit."
             << "\n\nWhat would you like to do?" << endl;
        cin >> choice;

        switch (choice)
        {
            case 1:
                readCSV(R"(C:\Users\Ally\Desktop\School\Data Structures\Project2\courses.csv)", courses);
                break;
            case 2:
                printCourseList();
                break;
            case 3:
                cout << "What course do you want to know about?" << endl;
                cin >> courseID;
                printCourse(courseID);
                break;
            case 9:
                choice = 9;
                cout << "Thank you for using the course planner!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;
        }
    }
}

int main() {
    CoursePlanner planner;
    planner.menu();
    return 0;
}
