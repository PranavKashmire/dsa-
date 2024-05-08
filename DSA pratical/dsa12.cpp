// Aim: Company maintains employee information as employee ID, name, designation and salary. Allow user to add, delete information of employee. Display information of particular employee. If employee does not exist an appropriate message is displayed. If it is, then the system displays the employee details. Use index sequential file to maintain the data.

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void addEmployee(fstream& file) {
    Employee emp;
    cout << "Enter employee ID: ";
    cin >> emp.id;
    cout << "Enter employee name: ";
    cin.ignore();
    cin.getline(emp.name, 50);
    cout << "Enter employee designation: ";
    cin.getline(emp.designation, 50);
    cout << "Enter employee salary: ";
    cin >> emp.salary;

    file.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
    cout << "Employee added successfully!" << endl;
}

void deleteEmployee(fstream& file) {
    int empId;
    cout << "Enter employee ID to delete: ";
    cin >> empId;

    file.seekg(0, ios::beg);
    Employee emp;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        if (emp.id == empId) {
            found = true;
            break;
        }
    }

    if (found) {
        file.seekp(-static_cast<int>(sizeof(Employee)), ios::cur);
        Employee emptyEmp = {0, "", "", 0};
        file.write(reinterpret_cast<char*>(&emptyEmp), sizeof(Employee));
        cout << "Employee deleted successfully!" << endl;
    } else {
        cout << "Employee not found!" << endl;
    }
}

void displayEmployee(fstream& file) {
    int empId;
    cout << "Enter employee ID to display: ";
    cin >> empId;

    file.seekg(0, ios::beg);
    Employee emp;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        if (emp.id == empId) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Employee ID: " << emp.id << endl;
        cout << "Employee Name: " << emp.name << endl;
        cout << "Employee Designation: " << emp.designation << endl;
        cout << "Employee Salary: " << emp.salary << endl;
    } else {
        cout << "Employee not found!" << endl;
    }
}

int main() {
    fstream file("employee.dat", ios::binary | ios::in | ios::out | ios::trunc);
    if (!file) {
        cout << "Error in opening file!";
        return 1;
    }

    int choice;
    do {
        cout << "1. Add Employee" << endl;
        cout << "2. Delete Employee" << endl;
        cout << "3. Display Employee" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                deleteEmployee(file);
                break;
            case 3:
                displayEmployee(file);
                break;
            case 4:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice!";
        }

        cout << endl;
    } while (choice != 4);

    file.close();
    return 0;
}
