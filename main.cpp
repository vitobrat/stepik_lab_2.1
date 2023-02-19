#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#include <windows.h>
const std::string fileName = "C:\\FirstCursProgramm\\C++\\stepik_lab_2.1\\StudentList.txt";
//оценки по предметам - АиГ, Матан, Прога, Инфа, Англ, Философия, Физика, Курсовая
using namespace std;

struct Student{
    int id;
    string fullName;
    string sex;
    int group;
    int groupId;
    int marks[8];
};

void readDataBase(vector<Student> &listOfStudent){
    ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            Student student;
            string stringId, stringName, stringGroup, stringGroupId;
            int i = 0;
            while(line[i] != '|'){
                stringId += line[i];
                i++;
            }
            i++;
            student.id = stoi(stringId);
            while(line[i] != '|'){
                stringName += line[i];
                i++;
            }
            i++;
            student.fullName = stringName;
            student.sex = line[i];
            i+=2;
            while(line[i] != '|'){
                stringGroup += line[i];
                i++;
            }
            i++;
            try {
                student.group = stoi(stringGroup);
            }
            catch (const std::invalid_argument& e) {
                cout << "ERROR" << "\n";
            }
            catch (const std::out_of_range& e) {
                cout << "ERROR" << "\n";
            }
            while(line[i] != '|'){
                stringGroupId += line[i];
                i++;
            }
            i++;
            try {
                student.groupId = stoi(stringGroupId);
            }
            catch (const std::invalid_argument& e) {
                cout << "ERROR" << "\n";
            }
            catch (const std::out_of_range& e) {
                cout << "ERROR" << "\n";
            }
            for(int j = 0; j < 8 && i<=line.length(); j++,i++){
                student.marks[j] = stoi(std::string(1, line[i]));
            }
            listOfStudent.push_back(student);
        }
        cin.clear();
        inputFile.close();
    }
    else {
        cout << "Unable to open file" << "\n";
    }
}

void printDataBase(vector<Student> &listOfStudent){
    cout << "Student list:" << "\n";
    for (int i = 0; i < listOfStudent.size(); i++){
        cout << "Id: " << listOfStudent[i].id<< "\n";
        cout << "Full name: " << listOfStudent[i].fullName<< "\n";
        cout << "Sex: " << listOfStudent[i].sex<< "\n";
        cout << "Group: " << listOfStudent[i].group<< "\n";
        cout << "Group id: " << listOfStudent[i].groupId<< "\n";
        cout << "Marks:" << "\n";
        cout << "Алгебра и Геометрия - " << listOfStudent[i].marks[0]<< "\n";
        cout << "Математический анализ - " << listOfStudent[i].marks[1]<< "\n";
        cout << " - " << listOfStudent[i].marks[2]<< "\n";
        cout << " - " << listOfStudent[i].marks[3]<< "\n";
        cout << " - " << listOfStudent[i].marks[4]<< "\n";
        cout << " - " << listOfStudent[i].marks[5]<< "\n";
        cout << " - " << listOfStudent[i].marks[6]<< "\n";
        cout << " - " << listOfStudent[i].marks[7]<< "\n";
        cout << "___" << "\n";
    }
}

void addStudent(vector<Student> &listOfStudent){
    Student student;
    student.id = listOfStudent[listOfStudent.size() - 1].id + 1;
    cout << "Full name: ";
    getline(cin, student.fullName);
    cin.clear();
    cout << "Sex (М/Ж): ";
    cin >> student.sex;
    cin.clear();
    cout << "Group: ";
    cin >> student.group;
    cout << "Group id: ";
    cin >> student.groupId;
    cout << "Term grades: ";
    string stringMarks;
    for (int i = 0; i < 8; i++) {
        cin >> student.marks[i];
        stringMarks += to_string(student.marks[i]);
        if (!(student.marks[i] >= 3 && student.marks[i] <= 5)){
            cout << "Неправильный формат оценок";
            return;
        }
    }
    cin.clear();
    ofstream file(fileName, std::ios::app);
    if (file.is_open()) {
        file << "\n";
        string newLine = to_string(student.id) + "|" + student.fullName + "|" + student.sex + "|" + to_string(student.group)  + "|" +
                to_string(student.groupId) + "|" + stringMarks;
        file << newLine << endl;
        file.close();
    } else {
        cout << "ERROR";
    }
    listOfStudent.push_back(student);
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<Student> listOfStudent;
    readDataBase(listOfStudent);
    printDataBase(listOfStudent);
    addStudent(listOfStudent);
    printDataBase(listOfStudent);
    getchar();
    getchar();
    getchar();
    return 0;
}
