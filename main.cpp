//
// Created by jesus on 8/6/2022.
//

/* This program is designed to help you with your final project.
Review very carefully, make sure you understand each function and what it does and
how it does it.
set up a data file like the following to test the program
*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#define CAP 20
using namespace std ;
struct Student {
    string      FirstName, LastName , Course_Grade;
    int        testScore{}, ProgrammingScore{};
    float GPA{} , Average{} ;
};
bool Equal( Student S1, Student S2);
void Print_info(const Student&);  //  Prototype
void Read_info1(Student &);  //  Prototype
Student Read_info();  //  Prototype
string grade_it (float ) ;
void assign_grade(Student &) ;
void Read_info1(Student &, ifstream &);  //  Prototype
bool open_file(ifstream &);
int Read_List(Student [], int);
void Process(Student [], int );
void Add_student(Student list[], int &size, int max);
void Print_table(Student [], int );
int Search( Student list[], int size, const string& lastName);
void Find_student(Student list[], int size);
void Sort(Student list[], int size);
void ProcessMenu(Student List[], int &size, int Max);
void displayMenu();
void runMenu(char Option, Student List[], int &size, int Max);
void Remove_student(Student list[], int &size);

int main() {
    Student Student_List[CAP] ;
    int size;
    size = Read_List(Student_List,CAP);
    if (size > 0) {
        Process(Student_List, size);
        ProcessMenu(Student_List, size, CAP);
    }
    else {
        cout << "\n\tNo data was found in the data file.\n\tProgram terminated.\n" << endl;
        system("pause");
    }
    return 0 ;
}
void ProcessMenu(Student List[], int &size, int Max){
    char Option;
    do{
        displayMenu();
        cin >> Option;
        cin.ignore(10, '\n');
        cout << endl;
        runMenu(Option, List, size, Max);
        cout << "\n\n";
        cout << "Press enter to continue\n";
        getchar();
        system("cls");
    } while (Option != 'E' && Option != 'e');
}
void runMenu(char Option, Student List[], int &size, int Max)
{
    switch (Option)
    {
        case 'A':
        case 'a':
            Add_student(List, size, Max);
            break;
        case 'P':
        case 'p':
            Print_table(List, size);
            break;
        case 'F':
        case 'f':
            Find_student(List, size);
            break;
        case 'S':
        case 's':
            Sort(List, size);
            break;
        case 'R':
        case 'r':
            Remove_student(List, size);
            break;
        case 'E':
        case 'e':
            cout << "\n\n\t\tEnd of Program.\n";
            break;
        default:
            cout << "\n\n\t\tNot a valid choice.\n"
                 << "Try again.\n";
    }
}
void displayMenu(){
    cout << endl << endl;
    cout << "\n\t\t\tThis program simulates a simple database for students.\n\n";
    cout << "\tA : To Add a new student.\n";
    cout << "\tR : To Remove a student.\n";
    cout << "\tP : To Print the list to monitor.\n";
    cout << "\tF : To Find a student on the list.\n";
    cout << "\tS : To Sort the list alphabetically based on last name.\n";
    cout << "\tE : To exit this program.\n";
    cout << "\n\tEnter your choice and press return: ";
}
void Sort(Student list[], int size)
{
    bool  flag ;
    Student Temp ;
    do{
        size--;
        flag = false ;
        for(int i = 0 ; i < size ; i++)
            if( list[i].LastName > list[i+1].LastName)
            {
                Temp = list[i];
                list[i] = list[i+1];
                list[i+1] = Temp ;
                flag = true ;
            }
    }while(flag );
}
// Function to prompt user for a file name and open it and return true if
// successful otherwise return false
bool open_file(ifstream &fin){
    string f_name;
    cout <<"Enter input file name: ";
    cin >> f_name ;
    fin.open(f_name.c_str());
    if (fin.fail())
        return false ;
    else
        return true ;
}
// Function to read a list of student information from a file and store them in an
// array and return the number of records read
int Read_List(Student list[], int size){
    ifstream fin;
    int i = 0;
    if(open_file(fin)){
        Read_info1(list[i],fin);  // Initializing
        while( !fin.eof()){
            i++;
            if (i < size)
                Read_info1(list[i],fin);
            else
            {
                cout <<"Array is full.\n";
                break;
            }
        }
    }
    return i ;
}
// Function to prcoess average and grade for all the students in a list
void Process(Student list[], int size){
    for (int i = 0 ; i < size ; i++)
        assign_grade(list[i]);
}
// Function to print the content of the array of students in a tabular form
void Print_table(Student list[], int size){
    cout << fixed << setprecision(2) << left << showpoint ;
    cout << setw(25) << "Name" << setw(8) << "GPA" << setw(20) << "Course Average" << setw(15)<< "Course Grade"<< endl ;
    cout <<"================================================================\n";
    for (int i = 0 ; i < size ; i++)
        cout << setw(25) << list[i].LastName+ ", " +list[i].FirstName <<
             setw(8) << list[i].GPA
             << setw(20) << list[i].Average << setw(15)<< list[i].Course_Grade<<
             endl ;
    cout <<"\n\n\n";
}
// Function to Read information for one student from a file all data for one
// student is stored on one line seperated by a space
// Format: First Last Programming_score  Quiz_score  GPA
void Read_info1(Student &Temp, ifstream &fin){
    fin >> Temp.FirstName ;
    fin >> Temp.LastName ;
    fin >> Temp.ProgrammingScore ;
    fin >> Temp.testScore ;
    fin >> Temp.GPA ;
}
// Function to compare 2 students' info to see if they are the same students works
bool Equal( Student S1, Student S2) // S1 == S2
{
    if ( S1.GPA == S2.GPA &&
         S1.LastName==S2.LastName &&
         S1.FirstName == S2.FirstName &&
         S1.Course_Grade == S2.Course_Grade &&
         S1.testScore == S2.testScore &&
         S1.ProgrammingScore == S2.ProgrammingScore
            )
        return true ;
    else
        return false ;
}
// Function to verify if there is room in the array to add a new student and adds
// the new student if space available
void Add_student(Student list[], int &size, int max){
    Student Temp;
    if(size < max){
        cout <<"\n\nPlease enter the data for new student: \n\n" ;
        Read_info1(Temp);
        if (Search(list, size, Temp.LastName) == -1){
            assign_grade(Temp);
            list[size] = Temp;
            cout << "\n\n" << list[size].LastName << " was successfully added.\n";
            size++;
        }
        else
            cout <<endl<<endl<< Temp.LastName<< "\a\a is already on the list and is not added.\n";
    }
    else
        cout <<"\n\nArray is full, can't add any more student.\n\n";
}
void Remove_student(Student list[], int &size){
    int index;
    string Name;
    cout << "\n\nPlease enter last name of the student to remove: ";
    getline(cin, Name);
    index = Search(list, size, Name);
    if ( index == -1)
        cout << endl<<Name << "\a\a is NOT on the list and can not be removed.\
n";
    else{
        cout << "\n\n" <<Name << " was successfully removed.\n\n";
        list[index] = list[size-1];
        size--;
    }
}
// Function to Print info for one student
void Print_info( const Student& temp) // cout << temp
{
    cout << left <<setw(30) << "\nStudent name: " << temp.FirstName << "  " <<
         temp.LastName << endl;
    cout << setw(30) << "Student Test Score:" << temp.testScore << endl;
    cout << setw(30) << "Student programming Score: "<< temp.ProgrammingScore <<
         endl ;
    cout << setw(30) << "Student GPA: " << temp.GPA << endl ;
    cout << setw(30) << "Course Grade: " << temp.Course_Grade << endl;
    cout << setw(30) << "Course Average:" << temp.Average << endl;
}
//  Function to read information from keyboard for one student and returning the structure
Student Read_info()
{
    Student  Temp ;
    cout << "Enter first name: " ;
    cin >> Temp.FirstName ;
    cout << "Enter last name: " ;
    cin >>Temp.LastName ;
    cout << "Enter programming score: " ;
    cin >> Temp.ProgrammingScore ;
    cout <<  "Enter test score: " ;
    cin >> Temp.testScore ;
    cout << "Enter GPA: " ;
    cin >> Temp.GPA ;
    cin.ignore(10, '\n');
    return(Temp);
}
//  Function to read information from keyboard for one student and send it back using pass by reference
void Read_info1(Student  &Temp ){
    cout << "Enter first name: " ;
    cin >> Temp.FirstName ;
    cout << "Enter last name: " ;
    cin >>Temp.LastName;
    cout << "Enter programming score: " ;
    cin >> Temp.ProgrammingScore ;
    cout <<  "Enter test score: " ;
    cin >> Temp.testScore ;
    cout << "Enter GPA: " ;
    cin >> Temp.GPA ;
    cin.ignore(10, '\n');
}
// Function to assign a letter grade pass or fail
string grade_it (float Average) {
    string Grade;
    if (Average >= 95)
        Grade = "A";
    else if (Average >= 90)
        Grade = "A-";
    else if (Average >= 87)
        Grade = "B+";
    else if (Average >= 83)
        Grade = "B";
    else if (Average >= 80)
        Grade = "B-";
    else if (Average >= 77)
        Grade = "C+";
    else if (Average >= 73)
        Grade = "C";
    else if (Average >= 70)
        Grade = "C-";
    else if (Average >= 67)
        Grade = "D+";
    else if (Average >= 63)
        Grade = "D";
    else if (Average >= 60)
        Grade = "D-";
    else
        Grade = "F";
    return Grade;
}
// Function to calculate the average and assign a letter grade to the student
void assign_grade(Student &S1){
    S1.Average = S1.ProgrammingScore * 0.35f;
    S1.Average += S1.testScore * 0.65f ;
    S1.Course_Grade = grade_it(S1.Average);
}
int Search( Student list[], int size, const string& lastName){
    for (int i = 0 ; i < size ; i++)
        if (list[i].LastName == lastName)
            return i ;
    return -1 ;
}
void Find_student(Student list[], int size){
    string target ;
    int index ;
    cout << "Enter student last name to search for: " ;
    cin >> target ;
    cin.ignore(10, '\n');
    index = Search(list, size, target);
    cout << "\n============================================";
    if (index == -1)
        cout << "\n\n"<<target << " is not on the list.\n\n";
    else
        Print_info(list[index]);
    cout << "\n============================================\n";
}
