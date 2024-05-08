
// Aim: Department maintains a student information. The file contains roll number, name, division and  address. Allow user to add, delete information of student. Display information of particular employee. If  record of student does not exist an appropriate message is displayed. If it is, then the system displays the  student details. Use sequential file to main the data


#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class tel {
public:
    int rollNo;
    char name[10];
    char div;
    char address[20];

    void accept() {
        cout << "\n\tEnter Roll Number : ";
        cin >> rollNo;
        cout << "\n\tEnter the Name : ";
        cin >> name;
        cout << "\n\tEnter the Division : ";
        cin >> div;
        cout << "\n\tEnter the Address : ";
        cin >> address;
    }

    int getRollNo() {
        return rollNo;
    }

    void show() {
        cout << "\n\t" << rollNo << "\t\t" << name << "\t\t" << div << "\t\t" << address;
    }
};

int main() {
    int ch;
    tel t1;

    fstream f;

    do {
        cout << "\n\t------MENU-------";
        cout << "\n1.Insert and overwrite\n2.Show\n3.Search & Edit(number)\n4.Delete a Student Record\n5.Exit\n\tEnter the Choice\t:";

        cin >> ch;

        switch (ch) {
            case 1: {
                f.open("StuRecord.txt", ios::out | ios::app);
                t1.accept();
                f.write(reinterpret_cast<char *>(&t1), sizeof(tel));
                f.close();
                break;
            }
            case 2: {
                f.open("StuRecord.txt", ios::in);
                while (f.read(reinterpret_cast<char *>(&t1), sizeof(tel))) {
                    t1.show();
                }
                f.close();
                break;
            }
            case 3: {
                int rec, count = 0;
                cout << "\nEnter the roll number you want to find : ";
                cin >> rec;
                f.open("StuRecord.txt", ios::in | ios::out);
                while (f.read(reinterpret_cast<char *>(&t1), sizeof(tel))) {
                    if (rec == t1.rollNo) {
                        cout << "\nRecord found";
                        f.seekp(-sizeof(tel), ios::cur);
                        t1.accept();
                        f.write(reinterpret_cast<char *>(&t1), sizeof(tel));
                        f.close();
                        count++;
                        break;
                    }
                }
                if (count == 0) cout << "\nRecord not found";
                f.close();
                break;
            }
            case 4: {
                int roll;
                cout << "Please Enter the Roll No. of Student Whose Info You Want to Delete: ";
                cin >> roll;
                f.open("StuRecord.txt", ios::in);
                ofstream temp("temp.txt", ios::out);
                while (f.read(reinterpret_cast<char *>(&t1), sizeof(tel))) {
                    if (t1.getRollNo() != roll) temp.write(reinterpret_cast<char *>(&t1), sizeof(tel));
                    else cout << "The record with the roll no. " << roll << " has been deleted." << endl;
                }
                f.close();
                temp.close();
                remove("StuRecord.txt");
                rename("temp.txt", "StuRecord.txt");
                break;
            }
            case 5:
                cout << "\n\tThank you";
                break;
            default:
                cout << "\n\tInvalid choice. Please enter a valid choice.";
                break;
        }
    } while (ch != 5);

    return 0;
}
