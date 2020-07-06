#include <iostream>
#include <fstream>
using namespace std;

////************************************////////
// Employees password keeped in README.md file //
///*************************************/////////

class Student
{
    char name[255], family[255];
    int age;

public:
    int studentNumber;
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
    int count;
    string name;

public:
    static void readLessons();
    static void add();
    static void edit(string name);
    static void removeLessons(char name[]);
    friend istream &operator>>(istream &input, Lesson &lesson);
    friend ostream &operator<<(ostream &output, const Lesson &lesson);
    friend class Student_Lesson;
    static bool lessonExists(string name);
    int getVahedCount();
};

// Many to Many Relationship //
class Student_Lesson
{
    char name[255];
    int vahedCount;

public:
    static int studentNumber;
    static void addLesson();
    static void removeLesson();
    static void myLessons();
    friend istream &operator>>(istream &input, Student_Lesson &studentLesson);
    friend ostream &operator<<(ostream &output, const Student_Lesson &studentLesson);
};

int Lesson::getVahedCount()
{
    Lesson lesson;
    ifstream lessonsFile("lessons", ios::binary);
    while (lessonsFile.read((char *)&lesson, sizeof(lesson)))
    {
        if (lesson.name == name)
        {
            return lesson.count;
        }
    }
    lessonsFile.close();
    return 0;
}

int Student_Lesson::studentNumber = 0;

void Student_Lesson::addLesson()
{
    Student_Lesson studentLesson[20];
    int exit = 1;
    int totalVahed = 0;
    int step = 0;
    Lesson lesson;
    while (exit != 0)
    {
        cin >> studentLesson[step];
        if (Lesson::lessonExists(studentLesson[step].name))
        {
            step++;
            totalVahed += lesson.getVahedCount();
        }
        else
        {
            cout << "lesson does not exists!\n";
        }
        cout << "you choosed " << totalVahed << " vahed , if you want to finish enter 0 else any number.\n";
        cin >> exit;
    }
    if (totalVahed > 20 || totalVahed < 14)
    {
        cout << "you can not get more than 20 and less than 14 vaheds\n";
    }
    else
    {
        for (int i = 0; i <= step; i++)
        {
            Student_Lesson studentLesson;
            ofstream lessonsFile("student_lesson", ios::binary | ios::app);
            cin >> studentLesson;

            lessonsFile.write((char *)&studentLesson, sizeof(studentLesson));
            lessonsFile.close();
        }
        cout << "\nLesson Added for User Successfully!\n";
    }
}

void Student_Lesson::removeLesson()
{

}

void Student_Lesson::myLessons()
{
    Student_Lesson studentLesson;
    ifstream studentsFile("student_lesson", ios::binary);
    while (studentsFile.read((char *)&studentLesson, sizeof(studentLesson)))
    {
        if (Student_Lesson::studentNumber == studentNumber)
        {
            cout << studentLesson;
        }
    }
    studentsFile.close();
}

istream &operator>>(istream &input, Student_Lesson &studentLesson)
{
    cout << "\nLesson Name: ";
    input >> studentLesson.name;
    return input;
}

ostream &operator<<(ostream &output, const Student_Lesson &studentLesson)
{
    output << "\n---------------------------------------------\n";
    output << "\nLesson Name: " << studentLesson.name;
    cout << endl;
    return output;
}

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

void Lesson::edit(string name)
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

bool Lesson::lessonExists(string name)
{
    Lesson lesson;
    bool is = false;
    ifstream lessonFile("lessons", ios::binary);
    while (lessonFile.read((char *)&lesson, sizeof(lesson)))
    {
        if (lesson.name == name)
        {
            is = true;
            lessonFile.close();
            return is;
        }
    }
    lessonFile.close();
    return is;
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
    cout << "1- Employee\n";
    cout << "2- Student\n";
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
    cout << "1- Add Lesson\n";
    cout << "2- Remove Lesson\n";
    cout << "3- Student Lesson List\n";
    cout << "4- Exit\n";
    cout << "Choose: ";
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
    int userType, attempCount = 0, studentNumber;
    string password;
    bool login = false;
    char name[255];
    userTypeMessage();
    cin >> userType;
    while (userType != 3)
    {
        switch (userType)
        {
        case 2:
            cout << "Enter Your Student Number: ";
            cin >> studentNumber;
            Student student;
            student.studentNumber = studentNumber;
            if (student.studentExists())
            {
                Student_Lesson::studentNumber = studentNumber;
                int studentChoose;
                StudentDeskMessage();
                cin >> studentChoose;
                while (studentChoose <= 3)
                {
                    switch (studentChoose)
                    {
                    case 1:
                        Student_Lesson::addLesson();
                        return 0;
                        break;
                    case 2:
                        Student_Lesson::removeLesson();
                        return 0;
                        break;
                    case 3:
                        Student_Lesson::myLessons();
                        return 0;
                        break;
                    }
                }
            }
            else
            {
                cout << "Student Does not Exists!\n";
            }
            return 0;
            break;
        case 1:
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
                if (password != "yazdUniEmps")
                {
                    attempCount++;
                    cout << "Wrong Password, Try Again!\n";
                    continue;
                }
                login = true;
                int employeeDesk, studentNumber;
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
