#include <iostream>
#include <fstream>
using namespace std;

////************************************////////
// Employees password keeped in README.md file //
///*************************************/////////


class Student
{
    char name[255], family[255];
    int age, studentNumber;

public:
    static void add();
    static void read(int studentNumber);
    static void edit(int studentNumber);
    static void removeStudent(int studentNumber);
    friend istream &operator>>(istream &input, Student &student);
    friend ostream &operator<<(ostream &output, const Student &student);
    bool studentExists();
    friend class Student_Lesson;
};


istream &operator>>(istream &input, Student &student)
{
    cout << "\nName: ";
    input >> student.name;
    cout << "\nFamily: ";
    input >> student.family;
    cout << "\nAge: ";
    input >> student.age;
    cout << "\nStudent Number: ";
    input >> student.studentNumber;

    return input;
}

ostream &operator<<(ostream &output, const Student &student)
{
    output << "\n---------------------------------------------\n";
    output << "\nStudent Number: " << student.studentNumber;
    output << "\nName: " << student.name;
    output << "\nFamily: " << student.family;
    output << "\nAge: " << student.age;
    cout << endl;
    return output;
}

class Lesson
{
    char name[255];
    int count;

public:
    static void readLessons();
    static void add();
    static void edit(char name[]);
    static void removeLessons(char name[]);
    friend istream &operator>>(istream &input, Lesson &lesson);
    friend ostream &operator<<(ostream &output, const Lesson &lesson);
    friend class Student_Lesson;
};

// Many to Many Relationship //
class Student_Lesson
{
    int studentNumber;
    char name[255];

public:
    static void addLesson(Student student, Lesson lesson);
    static void removeLesson(Student student, Lesson lesson);
};

istream &operator>>(istream &input, Lesson &lesson)
{
    cout << "\nLesson Name: ";
    input >> lesson.name;
    cout << "\nCount: ";
    input >> lesson.count;
    return input;
}

ostream &operator<<(ostream &output, const Lesson &lesson)
{
    output << "\n---------------------------------------------\n";
    output << "\nLesson Name: " << lesson.name;
    output << "\nCount: " << lesson.count;
    cout << endl;
    return output;
}
void Lesson::add()
{
    Lesson lesson;
    ofstream lessonsFile("lessons", ios::binary | ios::app);
    cin >> lesson;

    lessonsFile.write((char *)&lesson, sizeof(lesson));
    cout << "\nLesson Added Successfully!\n";

    lessonsFile.close();
}

void Lesson::readLessons()
{
    Lesson lesson;
    ifstream lessonsFile("lessons", ios::binary);
    while (lessonsFile.read((char *)&lesson, sizeof(lesson)))
    {
        cout << lesson;
    }
    lessonsFile.close();
}

void Lesson::edit(char name[])
{
    Lesson lesson;
    Lesson specificlesson;
    ifstream lessonsFile("lessons", ios::binary);
    ofstream tempFile("temp", ios::binary | ios::app);
    while (lessonsFile.read((char *)&lesson, sizeof(lesson)))
    {
        if (lesson.name == name)
        {
            cin >> lesson;
            specificlesson = lesson;
        }
        tempFile.write((char *)&lesson, sizeof(lesson));
    }
    cout << specificlesson;
    lessonsFile.close();
    tempFile.close();
    remove("lessons");
    rename("temp", "lessons");
}

void Lesson::removeLessons(char name[])
{
    Lesson lesson;
    ifstream lessonsFile("lessons", ios::binary);
    ofstream tempFile("temp", ios::binary | ios::app);
    while (lessonsFile.read((char *)&lesson, sizeof(lesson)))
    {
        if (lesson.name != name)
        {
            tempFile.write((char *)&lesson, sizeof(lesson));
        }
    }
    cout << "lesson Successufy Removed!\n";
    lessonsFile.close();
    tempFile.close();
    remove("lessons");
    rename("temp", "lessons");
}

void Student::add()
{
    Student student;
    ofstream studentsFile("students", ios::binary | ios::app);
    cin >> student;
    if (!student.studentExists())
    {
        studentsFile.write((char *)&student, sizeof(student));
        cout << "\nStudent Added Successfully!\n";
    }
    else
    {
        cout << "Student with this student number exists!\n";
    }
    studentsFile.close();
}

void Student::read(int studentNumber)
{
    Student student;
    ifstream studentsFile("students", ios::binary);
    while (studentsFile.read((char *)&student, sizeof(student)))
    {
        if (student.studentNumber == studentNumber)
        {
            cout << student;
        }
    }
    studentsFile.close();
}

void Student::edit(int studentNumber)
{
    Student student;
    Student specificStudent;
    ifstream studentsFile("students", ios::binary);
    ofstream tempFile("temp", ios::binary | ios::app);
    while (studentsFile.read((char *)&student, sizeof(student)))
    {
        if (student.studentNumber == studentNumber)
        {
            cin >> student;
            specificStudent = student;
        }
        tempFile.write((char *)&student, sizeof(student));
    }
    cout << specificStudent;
    studentsFile.close();
    tempFile.close();
    remove("students");
    rename("temp", "students");
}

void Student::removeStudent(int studentNumber)
{
    Student student;
    ifstream studentsFile("students", ios::binary);
    ofstream tempFile("temp", ios::binary | ios::app);
    while (studentsFile.read((char *)&student, sizeof(student)))
    {
        if (student.studentNumber != studentNumber)
        {
            tempFile.write((char *)&student, sizeof(student));
        }
    }
    cout << "Student Successufy Removed!\n";
    studentsFile.close();
    tempFile.close();
    remove("students");
    rename("temp", "students");
}

bool Student::studentExists()
{
    Student student;
    bool is = false;
    ifstream studentsFile("students", ios::binary);
    while (studentsFile.read((char *)&student, sizeof(student)))
    {
        if (student.studentNumber == studentNumber)
        {
            is = true;
            studentsFile.close();
            return is;
        }
    }
    studentsFile.close();
    return is;
}

void userTypeMessage()
{
    cout << "1- Student\n";
    cout << "2- Employee\n";
    cout << "3- Exit\n";
    cout << "Choose: ";
}

void passwordMessage()
{
    cout << "Enter Password: ";
}

void employeeDeskMessage()
{
    cout << "1- Add Student\n";
    cout << "2- Add Lesson\n";
    cout << "3- Remove Lesson\n";
    cout << "4- Edit Lesson\n";
    cout << "5- Select Unit\n";
    cout << "6- Student Lesson List\n";
    cout << "7- Remove Student\n";
    cout << "8- Edit Student\n";
    cout << "9- Student Info\n";
    cout << "10- Lessons List\n";
    cout << "11- Exit\n";
    cout << "Choose: ";
}

void StudentDeskMessage()
{
}

void getStudentNumberMessage()
{
    cout << "Enter Student Number: ";
}

void getLessonNameMessage()
{
    cout << "Enter Lesson Name: ";
}

int main()
{
    int userType;
    int attempCount = 0;
    string password;
    bool login = false;
    char name[255];
    userTypeMessage();
    cin >> userType;
    while (userType != 3)
    {
        switch (userType)
        {
        case 1:

            break;
        case 2:
            while (attempCount < 3 && !login)
            {
                passwordMessage();
                cin >> password;
                if (attempCount == 2 && password != "yazdUniEmps")
                {
                    attempCount++;
                    cout << "Many Attempt!\n";
                    return 0;
                }
                if (password != "1")
                {
                    attempCount++;
                    cout << "Wrong Password, Try Again!\n";
                    continue;
                }
                login = true;
                int employeeDesk;
                int studentNumber;
                employeeDeskMessage();
                cin >> employeeDesk;
                while (employeeDesk != 11)
                {
                    switch (employeeDesk)
                    {
                    case 1:
                        Student::add();
                        return 0;
                        break;
                    case 2:
                        Lesson::add();
                        return 0;
                        break;
                    case 3:
                        getLessonNameMessage();
                        cin >> name;
                        Lesson::removeLessons(name);
                        return 0;
                        break;
                    case 4:
                        getLessonNameMessage();
                        cin >> name;
                        Lesson::edit(name);
                        return 0;
                        break;
                    case 5:

                        break;
                    case 6:

                        break;
                    case 7:
                        getStudentNumberMessage();
                        cin >> studentNumber;
                        Student::removeStudent(studentNumber);
                        return 0;
                        break;
                    case 8:
                        getStudentNumberMessage();
                        cin >> studentNumber;
                        Student::edit(studentNumber);
                        return 0;
                        break;
                    case 9:
                        getStudentNumberMessage();
                        cin >> studentNumber;
                        Student::read(studentNumber);
                        return 0;
                        break;
                    case 10:
                        Lesson::readLessons();
                        return 0;
                        break;
                    case 11:
                        return 0;
                    default:
                        return 0;
                    }
                }
                return 0;
            }
            break;
        default:
            return 0;
        }
    }
}