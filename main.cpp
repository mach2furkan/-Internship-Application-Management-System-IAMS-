#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

// Structure to represent an Internship Applicant
struct Applicant {
    string name;
    string email;
    string skills;
    int experienceYears;
};

// Function to display the menu options
void displayMenu() {
    cout << "\n=== Internship Application Management System ===\n";
    cout << "1. Add New Applicant\n";
    cout << "2. View All Applicants\n";
    cout << "3. Search Applicant by Name\n";
    cout << "4. Filter Applicants by Skills\n";
    cout << "5. Edit Applicant Details\n"; // New Feature
    cout << "6. Delete Applicant\n";      // New Feature
    cout << "7. Sort Applicants by Experience\n"; // New Feature
    cout << "8. Save Applicants to File\n";       // New Feature
    cout << "9. Load Applicants from File\n";     // New Feature
    cout << "10. View Statistics Dashboard\n";    // New Feature
    cout << "11. Exit\n";
    cout << "================================================\n";
}

// Function to add a new applicant
void addApplicant(vector<Applicant>& applicants) {
    Applicant newApplicant;
    cout << "\nEnter Applicant Details:\n";
    cout << "Name: ";
    getline(cin >> ws, newApplicant.name); // Use ws to ignore leftover newline
    cout << "Email: ";
    getline(cin, newApplicant.email);
    cout << "Skills (comma-separated): ";
    getline(cin, newApplicant.skills);
    cout << "Years of Experience: ";
    cin >> newApplicant.experienceYears;

    applicants.push_back(newApplicant);
    cout << "\nApplicant added successfully!\n";
}

// Function to display all applicants
void viewAllApplicants(const vector<Applicant>& applicants) {
    if (applicants.empty()) {
        cout << "\nNo applicants available.\n";
        return;
    }

    cout << "\nList of Applicants:\n";
    for (size_t i = 0; i < applicants.size(); ++i) {
        const Applicant& applicant = applicants[i];
        cout << "\nApplicant #" << i + 1 << ":\n";
        cout << "Name: " << applicant.name << "\n";
        cout << "Email: " << applicant.email << "\n";
        cout << "Skills: " << applicant.skills << "\n";
        cout << "Experience (Years): " << applicant.experienceYears << "\n";
    }
}

// Function to search for an applicant by name
void searchApplicantByName(const vector<Applicant>& applicants) {
    string searchName;
    cout << "\nEnter the name of the applicant to search: ";
    getline(cin >> ws, searchName);

    bool found = false;
    for (const Applicant& applicant : applicants) {
        if (applicant.name.find(searchName) != string::npos) { // Partial match
            cout << "\nApplicant Found:\n";
            cout << "Name: " << applicant.name << "\n";
            cout << "Email: " << applicant.email << "\n";
            cout << "Skills: " << applicant.skills << "\n";
            cout << "Experience (Years): " << applicant.experienceYears << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo applicant found with the name '" << searchName << "'.\n";
    }
}

// Function to filter applicants by skills
void filterApplicantsBySkills(const vector<Applicant>& applicants) {
    string skillFilter;
    cout << "\nEnter the skill to filter applicants (e.g., Python, C++): ";
    getline(cin >> ws, skillFilter);

    vector<Applicant> filteredApplicants;
    for (const Applicant& applicant : applicants) {
        if (applicant.skills.find(skillFilter) != string::npos) { // Partial match
            filteredApplicants.push_back(applicant);
        }
    }

    if (filteredApplicants.empty()) {
        cout << "\nNo applicants found with the skill '" << skillFilter << "'.\n";
    } else {
        cout << "\nApplicants with the skill '" << skillFilter << "':\n";
        for (const Applicant& applicant : filteredApplicants) {
            cout << "\nName: " << applicant.name << "\n";
            cout << "Email: " << applicant.email << "\n";
            cout << "Skills: " << applicant.skills << "\n";
            cout << "Experience (Years): " << applicant.experienceYears << "\n";
        }
    }
}

// New Feature: Edit Applicant Details
void editApplicant(vector<Applicant>& applicants) {
    if (applicants.empty()) {
        cout << "\nNo applicants available to edit.\n";
        return;
    }

    viewAllApplicants(applicants);
    int index;
    cout << "\nEnter the number of the applicant to edit: ";
    cin >> index;

    if (index < 1 || index > static_cast<int>(applicants.size())) {
        cout << "\nInvalid applicant number.\n";
        return;
    }

    Applicant& applicant = applicants[index - 1];
    cout << "\nEnter updated details for Applicant #" << index << ":\n";
    cout << "Name (" << applicant.name << "): ";
    getline(cin >> ws, applicant.name);
    cout << "Email (" << applicant.email << "): ";
    getline(cin, applicant.email);
    cout << "Skills (" << applicant.skills << "): ";
    getline(cin, applicant.skills);
    cout << "Years of Experience (" << applicant.experienceYears << "): ";
    cin >> applicant.experienceYears;

    cout << "\nApplicant details updated successfully!\n";
}

// New Feature: Delete Applicant
void deleteApplicant(vector<Applicant>& applicants) {
    if (applicants.empty()) {
        cout << "\nNo applicants available to delete.\n";
        return;
    }

    viewAllApplicants(applicants);
    int index;
    cout << "\nEnter the number of the applicant to delete: ";
    cin >> index;

    if (index < 1 || index > static_cast<int>(applicants.size())) {
        cout << "\nInvalid applicant number.\n";
        return;
    }

    applicants.erase(applicants.begin() + index - 1);
    cout << "\nApplicant deleted successfully!\n";
}

// New Feature: Sort Applicants by Experience
void sortApplicantsByExperience(vector<Applicant>& applicants) {
    if (applicants.empty()) {
        cout << "\nNo applicants available to sort.\n";
        return;
    }

    int sortOrder;
    cout << "\nSort by Experience:\n";
    cout << "1. Ascending Order\n";
    cout << "2. Descending Order\n";
    cout << "Enter your choice: ";
    cin >> sortOrder;

    if (sortOrder == 1) {
        sort(applicants.begin(), applicants.end(), [](const Applicant& a, const Applicant& b) {
            return a.experienceYears < b.experienceYears;
        });
        cout << "\nApplicants sorted in ascending order by experience.\n";
    } else if (sortOrder == 2) {
        sort(applicants.begin(), applicants.end(), [](const Applicant& a, const Applicant& b) {
            return a.experienceYears > b.experienceYears;
        });
        cout << "\nApplicants sorted in descending order by experience.\n";
    } else {
        cout << "\nInvalid choice. Sorting aborted.\n";
    }
}

// New Feature: Save Applicants to a File
void saveApplicantsToFile(const vector<Applicant>& applicants) {
    ofstream file("applicants.txt");
    if (!file.is_open()) {
        cout << "\nError: Unable to open file for saving.\n";
        return;
    }

    for (const Applicant& applicant : applicants) {
        file << applicant.name << "\n";
        file << applicant.email << "\n";
        file << applicant.skills << "\n";
        file << applicant.experienceYears << "\n";
    }

    file.close();
    cout << "\nApplicants saved to file successfully!\n";
}

// New Feature: Load Applicants from a File
void loadApplicantsFromFile(vector<Applicant>& applicants) {
    ifstream file("applicants.txt");
    if (!file.is_open()) {
        cout << "\nError: Unable to open file for loading.\n";
        return;
    }

    applicants.clear(); // Clear existing applicants
    string name, email, skills;
    int experienceYears;

    while (getline(file, name)) {
        getline(file, email);
        getline(file, skills);
        file >> experienceYears;
        file.ignore(); // Ignore the remaining newline

        Applicant applicant = {name, email, skills, experienceYears};
        applicants.push_back(applicant);
    }

    file.close();
    cout << "\nApplicants loaded from file successfully!\n";
}

// New Feature: Statistics Dashboard
void viewStatisticsDashboard(const vector<Applicant>& applicants) {
    if (applicants.empty()) {
        cout << "\nNo applicants available for statistics.\n";
        return;
    }

    int totalApplicants = applicants.size();
    double totalExperience = 0;
    string allSkills;

    for (const Applicant& applicant : applicants) {
        totalExperience += applicant.experienceYears;
        allSkills += applicant.skills + ",";
    }

    double averageExperience = totalExperience / totalApplicants;

    // Find most common skills
    vector<string> skillsList;
    size_t pos = 0;
    string token;
    string skillsCopy = allSkills;
    while ((pos = skillsCopy.find(',')) != string::npos) {
        token = skillsCopy.substr(0, pos);
        skillsList.push_back(token);
        skillsCopy.erase(0, pos + 1);
    }

    sort(skillsList.begin(), skillsList.end());
    string mostCommonSkill = "";
    int maxCount = 0, currentCount = 1;

    for (size_t i = 1; i <= skillsList.size(); ++i) {
        if (i < skillsList.size() && skillsList[i] == skillsList[i - 1]) {
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
                mostCommonSkill = skillsList[i - 1];
            }
            currentCount = 1;
        }
    }

    cout << "\n=== Statistics Dashboard ===\n";
    cout << "Total Applicants: " << totalApplicants << "\n";
    cout << "Average Years of Experience: " << averageExperience << "\n";
    cout << "Most Common Skill: " << mostCommonSkill << "\n";
    cout << "============================\n";
}

int main() {
    vector<Applicant> applicants; // List of applicants
    int choice;

    cout << "Welcome to the Internship Application Management System!\n";

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addApplicant(applicants);
                break;
            case 2:
                viewAllApplicants(applicants);
                break;
            case 3:
                searchApplicantByName(applicants);
                break;
            case 4:
                filterApplicantsBySkills(applicants);
                break;
            case 5:
                editApplicant(applicants); // New Feature
                break;
            case 6:
                deleteApplicant(applicants); // New Feature
                break;
            case 7:
                sortApplicantsByExperience(applicants); // New Feature
                break;
            case 8:
                saveApplicantsToFile(applicants); // New Feature
                break;
            case 9:
                loadApplicantsFromFile(applicants); // New Feature
                break;
            case 10:
                viewStatisticsDashboard(applicants); // New Feature
                break;
            case 11:
                cout << "\nThank you for using the Internship Application Management System!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 11);

    return 0;
}