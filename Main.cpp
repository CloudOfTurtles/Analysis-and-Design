//Gabriel Brands
//Date:4/11/2023


#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//#include "course.h"

class Course {
public:
	// Constructor that initializes a course with a given course number, course title, and prerequisites
	Course(const std::string& courseNumber, const std::string& courseTitle, const std::string& prerequisites);

	// Accessor methods to retrieve the course number, course title, and prerequisite course numbers
	std::string getCourseNumber() const;
	std::string getCourseTitle() const;
	std::string getPrerequisites() const;

private:
	std::string courseNumber_;
	std::string courseTitle_;
	std::vector<std::string> prerequisites_;
};

Course::Course(const std::string& courseNumber, const std::string& courseTitle, const std::string& prerequisites) :
	courseNumber_(courseNumber),
	courseTitle_(courseTitle)
{
	// Parse the comma-separated prerequisite course numbers and store them in a vector
	std::istringstream iss(prerequisites);
	std::string prerequisite;
	while (std::getline(iss, prerequisite, ',')) {
		prerequisites_.push_back(prerequisite);
	}
}

std::string Course::getCourseNumber() const {
	return courseNumber_;
}

std::string Course::getCourseTitle() const {
	return courseTitle_;
}

std::string Course::getPrerequisites() const {
	// Join the prerequisite course numbers into a comma-separated string
	std::string prerequisitesString;
	for (const auto& prerequisite : prerequisites_) {
		prerequisitesString += prerequisite + ",";
	}
	if (!prerequisitesString.empty()) {
		// Remove the trailing comma
		prerequisitesString.pop_back();
	}
	return prerequisitesString;
}
void
//prints the menu display
printMenu()
{
	std::cout << "Menu:" << std::endl;
	std::cout << "1. Load Data Structure" << std::endl;
	std::cout << "2. Print Course List" << std::endl;
	std::cout << "3. Print Course" << std::endl;
	std::cout << "4. Exit" << std::endl;
}

int
main()
{
	std::vector < Course > courses;
	std::string filename;
	bool dataLoaded = false;

	while (true)
	{
		printMenu();

		int choice;
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice)
		{
			//opens the file with the course data
		case 1: {
			std::cout << "Enter the filename of the course data: ";
			std::cin >> filename;
			std::ifstream inputFile(filename);
			if (inputFile)
			{
				std::string line;
				while (std::getline(inputFile, line))
				{
					std::istringstream iss(line);
					std::string courseNumber, courseTitle, prerequisites;
					std::getline(iss, courseNumber, ',');
					std::getline(iss, courseTitle, ',');
					std::getline(iss, prerequisites, ',');
					courses.
						push_back(Course
						(courseNumber, courseTitle, prerequisites));
				}
				std::cout << "Course data loaded successfully." << std::endl;
				dataLoaded = true;
			}
			else
			{
				std::
					cerr << "Error: Could not open file \"" << filename << "\"."
					<< std::endl;
				dataLoaded = false;
			}
			break;
		}
			  //prints the list of course data
		case 2: {
			if (dataLoaded)
			{
				std::vector < Course > csCourses;
				for (const auto& course : courses)
				{
					if (course.getCourseNumber().substr(0, 2) == "CS"
						|| course.getCourseNumber().substr(0, 2) == "MATH")
					{
						csCourses.push_back(course);
					}
				}
				std::sort(csCourses.begin(), csCourses.end(),
					[](const Course& a, const Course& b)
					{
						return a.getCourseNumber() < b.getCourseNumber(); }
				);
				std::cout << "Course List:" << std::endl;
				for (const auto& course : csCourses)
				{
					std::cout << course.getCourseNumber() << ": " << course.
						getCourseTitle() << std::endl;
				}
			}
			else
			{
				std::cout << "Error: No course data has been loaded." << std::
					endl;
			}
			break;
		}
			  //prints teh details of the specific course requested
		case 3:
		{
			if (dataLoaded)
			{
				std::string courseNumber;
				std::cout << "Enter the course number: ";
				std::cin >> courseNumber;
				auto it =
					std::find_if(courses.begin(), courses.end(),
						[courseNumber](const Course& course) {
							return course.getCourseNumber() ==
								courseNumber; }
				);
				if (it != courses.end())
				{
					std::cout << "Course Title: " << it->
						getCourseTitle() << std::endl;
					std::cout << "Prerequisites: " << it->
						getPrerequisites() << std::endl;
				}
				else
				{
					std::
						cout << "Error: Course \"" << courseNumber <<
						"\" not found." << std::endl;
				}
			}
			else
			{
				std::cout << "Error: No course data has been loaded." << std::
					endl;
			}
			break;
		}
		//exits program
		case 4:
		{
			std::cout << "Exiting program..." << std::endl;
			return 0;
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
			break;
		}
		}
	}
	return 0;
}