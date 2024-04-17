//============================================================================
// Name        : VectorSorting.cpp
// Author      : Richard Pashko
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting for Final Project
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold course information
struct Course {
    string courseID; // unique identifier
    string courseName;
    vector<string> prerequisites;
    Course() {
    	courseID = "";
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayCourse(Course c) { //Will display all of our courses alphanumerically.

	string combinedPrerequisites = c.prerequisites[0]; // Will contain concatenated prerequisites.
	for (size_t i = 1; i < c.prerequisites.size(); ++i) { //Loops across prerequisites.
		combinedPrerequisites += ", " + c.prerequisites[i]; //Combines them into a string.
	}

	//Outputs data to console.
    cout << c.courseID << " | " << c.courseName << " | " << "Prerequisites: " <<
    		(combinedPrerequisites.empty() ? "None" : combinedPrerequisites ) << endl;
    return;
}

/**
 * Display a specific course to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displaySpecificCourse(vector<Course> courseVector, string courseID) { //Will display a specific course.

	for (size_t i = 0; i < courseVector.size(); i++) { //Loops over our courses

		if (courseVector[i].courseID == courseID) { //If a courseID matches with provided courseID:

			string combinedPrerequisites = courseVector[i].prerequisites[0]; // Will contain concatenated prerequisites.
			for (size_t j = 1; j < courseVector[i].prerequisites.size(); ++j) { //Loops across prerequisites.
				combinedPrerequisites += ", " + courseVector[i].prerequisites[j]; //Combines them into a string.
			}

			//Outputs course info to console.
			cout << courseVector[i].courseID << " | " << courseVector[i].courseName << " | " << "Prerequisites: " <<
			    		(combinedPrerequisites.empty() ? "None" : combinedPrerequisites ) << endl;
			    return;
		}
	}

	//If no matching course is found, outputs error message and leaves.
    cout << "The course you specified does not exist." << endl;
    return;
}

/*
 * Compares course ID's alphanumerically
 */

bool compareCourses(const Course& c1, const Course& c2) {
    return c1.courseID < c2.courseID;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Course> loadCourses(string csvPath) { //Will load courses from filepath.

    // Define a vector data structure to hold a collection of bids.
    vector<Course> courses;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {

        // loop to read rows of a CSV file
        for (size_t i = 0; i < file.rowCount(); i++) {
        	// Create a data structure and add to the collection of bids
			Course c; //Declares a new course c.
			c.courseID = file[i][0]; //Gets ID.
			c.courseName = file[i][1]; //Gets Name.

            for (size_t j = 2; j < file[i].size(); j++) { //Loops over prequesites.
                c.prerequisites.push_back(file[i][j]); //Does not push anything if course has no prerequisites.
            }

			// pushes this course to the coruses vector.
			courses.push_back(c);
        }

        cout << "Proceeding to sort courses in vector container." << endl;

        sort(courses.begin(), courses.end(), compareCourses); //Sorts courses alphanumerically.

    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl; //If there is an error, outputs an error message.
    }
    return courses; //Returns vector of courses.
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "YOUR FILE PATH HERE"; //Enter filepath here.
    }

    // Define a vector to hold all the bids
    vector<Course> courses;

    int choice = 0;
    while (choice != 9) { //This is our menu.
        cout << "Course planner options are:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Find and Print Specific Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Complete the method call to load the courses
            courses = loadCourses(csvPath);

            cout << courses.size() << " courses loaded" << endl; //Outputs # of courses loaded.

            break;

        case 2:
            // Loop and display the bids read
            for (size_t i = 0; i < courses.size(); ++i) {
                displayCourse(courses[i]);
            }
            cout << endl;

            break;

        case 3:
            string input;
            cout << "Enter course number >> "; //Will crash if provided strings with spaces.
            cin >> input;

            for (char &c : input) { //Makes all letters uppercase.
				c = toupper(c);
			}

            displaySpecificCourse(courses, input); //Finds and displays a specific course.

            break;

        }
    }

    cout << "Good bye." << endl;

    return 0;
}

