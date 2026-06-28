#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Student
{
public:
    int id;
    string name;
    float marks;

    void input()
    {
        cout << "\nEnter Student ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display()
    {
        cout << left
             << setw(10) << id
             << setw(25) << name
             << setw(10) << marks
             << endl;
    }
};

vector<Student> students;

void saveToFile()
{
    ofstream file("students.txt");

    for(auto s : students)
    {
        file << s.id << endl;
        file << s.name << endl;
        file << s.marks << endl;
    }

    file.close();
}

void loadFromFile()
{
    students.clear();

    ifstream file("students.txt");

    if (!file.is_open())
        return;

    Student s;

    while (file >> s.id)
    {
        file.ignore();

        getline(file, s.name);

        file >> s.marks;

        file.ignore();

        students.push_back(s);
    }

    file.close();
}

void addStudent()
{
    Student s;

    s.input();

    students.push_back(s);

    saveToFile();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents()
{
    cout << "\n----------------------------------------------\n";

    cout << left
         << setw(10) << "ID"
         << setw(25) << "NAME"
         << setw(10) << "MARKS"
         << endl;

    cout << "----------------------------------------------\n";

    for(auto s : students)
    {
        s.display();
    }
}

void searchStudent()
{
    int id;

    cout << "\nEnter Student ID: ";

    cin >> id;

    for(auto s : students)
    {
        if(s.id==id)
        {
            cout<<"\nStudent Found\n\n";

            s.display();

            return;
        }
    }

    cout<<"\nStudent Not Found\n";
}

void deleteStudent()
{
    int id;

    cout<<"\nEnter Student ID to Delete: ";

    cin>>id;

    for(int i=0;i<students.size();i++)
    {
        if(students[i].id==id)
        {
            students.erase(students.begin()+i);

            saveToFile();

            cout<<"\nStudent Deleted Successfully!\n";

            return;
        }
    }

    cout<<"\nStudent Not Found\n";
}

float averageMarks()
{
    if(students.empty())
        return 0;

    float sum=0;

    for(auto s:students)
        sum+=s.marks;

    return sum/students.size();
}

int main()
{
    loadFromFile();

    int choice;

    do
    {
        cout<<"\n==============================";
        cout<<"\n Student Grade Management";
        cout<<"\n==============================";

        cout<<"\n1. Add Student";
        cout<<"\n2. Display Students";
        cout<<"\n3. Search Student";
        cout<<"\n4. Delete Student";
        cout<<"\n5. Average Marks";
        cout<<"\n6. Exit";

        cout<<"\n\nEnter Choice: ";

        cin>>choice;

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                cout<<"\nAverage Marks = "<<averageMarks()<<endl;
                break;

            case 6:
                cout<<"\nThank You!\n";
                break;

            default:
                cout<<"\nInvalid Choice\n";
        }

    }while(choice!=6);

    return 0;
}