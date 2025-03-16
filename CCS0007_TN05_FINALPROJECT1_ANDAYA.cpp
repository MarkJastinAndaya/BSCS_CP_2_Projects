#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <limits>
#include <cmath>

using namespace std;

class Data {
    public:
            // Lecture Data
        double summativePoints[4] = {0}, summativeScore[4] = {0};
        double m_ProjectPoints = 0,  m_ProjectScore = 0;
        double m_ExamPoints    = 0,  m_ExamScore    = 0;
        double f_ProjectPoints = 0,  f_ProjectScore = 0;
        double f_ExamPoints    = 0,  f_ExamScore    = 0;

            // Laboratory Data
        double technicalPoints[8] = {0}, technicalScore[8] = {0};
        double m_lab_examPoints = 0, m_lab_examScore = 0;
        double f_lab_examPoints = 0, f_lab_examScore = 0;

            // Stored Computed Grades
        double midtermLectureGrade = 0, finalLectureGrade = 0;
        double midtermLabGrade     = 0, finalLabGrade     = 0;
        double midtermCourseGrade  = 0, finalCourseGrade  = 0;

            // Weights for Calculation
        static constexpr double SA_WEIGHT             = 0.50;
        static constexpr double PROJECT_WEIGHT        = 0.10;
        static constexpr double MIDTERM_EXAM_WEIGHT   = 0.40;
        static constexpr double FINAL_EXAM_WEIGHT     = 0.25;
        static constexpr double LAB_TECH_WEIGHT       = 0.60;
        static constexpr double LAB_EXAM_WEIGHT       = 0.40;
        static constexpr double COURSE_LECTURE_WEIGHT = 0.70;
        static constexpr double COURSE_LAB_WEIGHT     = 0.30;

            //Initialize All Values
        Data() {
            memset(summativePoints, 0, sizeof(summativePoints));
            memset(summativeScore, 0, sizeof(summativeScore));
            memset(technicalPoints, 0, sizeof(technicalPoints));
            memset(technicalScore, 0, sizeof(technicalScore));
            m_ProjectPoints = m_ProjectScore = 0;
            m_ExamPoints = m_ExamScore = 0;
            f_ProjectPoints = f_ProjectScore = 0;
            f_ExamPoints = f_ExamScore = 0;
            m_lab_examPoints = m_lab_examScore = 0;
            f_lab_examPoints = f_lab_examScore = 0;
            midtermLectureGrade = finalLectureGrade = 0;
            midtermLabGrade = finalLabGrade = 0;
            midtermCourseGrade = finalCourseGrade = 0;
        }

            // Functions to Calculate & Store Grades
        void calculateMidtermLectureGrade() {
            double sumTotal = 0, sumScore = 0;
            for (int i = 0; i < 2; i++) {
                sumTotal += summativePoints[i];
                sumScore += summativeScore[i];
            }
            double sumAverage = (sumTotal > 0) ? (sumScore * 100 / sumTotal) : 0;
            double projGrade  = (m_ProjectPoints > 0) ? (m_ProjectScore * 100 / m_ProjectPoints) : 0;
            double examGrade  = (m_ExamPoints > 0) ? (m_ExamScore * 100 / m_ExamPoints) : 0;
        
            midtermLectureGrade = (sumAverage * SA_WEIGHT) + (projGrade * PROJECT_WEIGHT) + (examGrade * MIDTERM_EXAM_WEIGHT);
        }
            
        void calculateFinalLectureGrade() {
            double sumTotal = 0, sumScore = 0;
            for (int i = 0; i < 4; i++) {
                sumTotal += summativePoints[i];
                sumScore += summativeScore[i];
            }
            double sumAverage = (sumTotal > 0) ? (sumScore * 100 / sumTotal) : 0;
            double midExamGrade = (m_ExamPoints > 0) ? (m_ExamScore * 100 / m_ExamPoints) : 0;
            double finalExamGrade = (f_ExamPoints > 0) ? (f_ExamScore * 100 / f_ExamPoints) : 0;
            double projGrade = ((m_ProjectPoints + f_ProjectPoints) > 0) ?
                               ((m_ProjectScore + f_ProjectScore) * 100 / (m_ProjectPoints + f_ProjectPoints)) : 0;
        
            finalLectureGrade = (sumAverage * SA_WEIGHT) + (projGrade * PROJECT_WEIGHT) + (midExamGrade * 0.15) + (finalExamGrade * FINAL_EXAM_WEIGHT);
        }
        
        void calculateMidtermLabGrade() {
            double techTotal = 0, techScore = 0;
            for (int i = 0; i < 4; i++) {
                techTotal += technicalPoints[i];
                techScore += technicalScore[i];
            }
            double techGrade = (techTotal > 0) ? (techScore * 100 / techTotal) : 0;
            double examGrade = (m_lab_examPoints > 0) ? (m_lab_examScore * 100 / m_lab_examPoints) : 0;
        
            midtermLabGrade = (techGrade * LAB_TECH_WEIGHT) + (examGrade * LAB_EXAM_WEIGHT);
        }        

        void calculateFinalLabGrade() {
            double techTotal = 0, techScore = 0;
            for (int i = 0; i < 8; i++) {
                techTotal += technicalPoints[i];
                techScore += technicalScore[i];
            }
            double techGrade      = (techTotal > 0) ? (techScore * 100 / techTotal) : 0;
            double midExamGrade   = (m_lab_examPoints > 0) ? (m_lab_examScore * 100 / m_lab_examPoints) : 0;
            double finalExamGrade = (f_lab_examPoints > 0) ? (f_lab_examScore * 100 / f_lab_examPoints) : 0;
        
            finalLabGrade = (techGrade * LAB_TECH_WEIGHT) + (midExamGrade * 0.15) + (finalExamGrade * FINAL_EXAM_WEIGHT);
        }        
};

class Student {
    public:
        int studentID;
        string studentFN, studentLN, studentMI, studentSection;

        Data lecture, laboratory;

        Student* next;

        Student(int id, string fn, string ln, string mi, string sec) {
            studentID = id;
            studentFN = fn;
            studentLN = ln;
            studentMI = mi;
            studentSection = sec;
            next = nullptr;
        }

        void calculateMidtermCourseGrade() {
            if (lecture.midtermLectureGrade == 0 || laboratory.midtermLabGrade == 0) {
                lecture.midtermCourseGrade = 0; 
            } else {
                lecture.midtermCourseGrade = (lecture.midtermLectureGrade * Data::COURSE_LECTURE_WEIGHT) +
                                                (laboratory.midtermLabGrade * Data::COURSE_LAB_WEIGHT);
            }
        }

        void calculateFinalCourseGrade() {
            if (lecture.finalLectureGrade == 0 || laboratory.finalLabGrade == 0) {
                lecture.finalCourseGrade = 0;
            } else {
                lecture.finalCourseGrade = (lecture.finalLectureGrade * Data::COURSE_LECTURE_WEIGHT) +
                                            (laboratory.finalLabGrade * Data::COURSE_LAB_WEIGHT);
            }
        }

        string getFullName() {
            return studentLN + ", " + studentFN + " " + studentMI + ".";
        }
};

void Horline(char symbol, int count);
void Center_Text(const string& text, int totalLength);

class StudentManager {
    private:
        Student* head;
    
    public:
        StudentManager() { head = nullptr; }

        Student* getHead() { return head; }

        void addStudent(int id, string fn, string ln, string mi, string sec) {
            Student* newStudent = new Student(id, fn, ln, mi, sec);
            newStudent->next = head;
            head = newStudent;
        }

        Student* searchStudent(int id) {
            Student* temp = head;
            while (temp) {
                if (temp->studentID == id) return temp;
                temp = temp->next;
            }
            return nullptr;
        }

        void displaySingleStudentInfo(Student* student) {
            if (!student) {
                cout << " Warning: Student not found!\n";
                return;
            }
        
            Horline('-', 71);
            Center_Text("STUDENT INFORMATION", 70);
            Horline('-', 71);
            
            cout << left;
            cout << "| " << setw(30) << "Student Name"      << ": " << setw(36) << student->getFullName()  << " |\n";
            cout << "| " << setw(30) << "Student ID Number" << ": " << setw(36) << student->studentID     << " |\n";
            cout << "| " << setw(30) << "Section"           << ": " << setw(36) << student->studentSection << " |\n";
        
            Horline('-', 71);
        }
            
        void saveToFile() {
            ofstream file("students.txt");
        
            if (!file) {
                cout << "Error opening file for writing!" << endl;
                return;
            }
        
            Student* temp = head;
        
            file << left 
                    << setw(12) << "ID"
                    << setw(15) << "First Name"
                    << setw(12) << "Last Name"
                    << setw(3)  << "MI"
                    << setw(8)  << "Section"
                    << endl;
        
            file << string(50, '=') << endl;
        
            while (temp) {
                file << left 
                        << setw(12) << temp->studentID 
                        << setw(15) << temp->studentFN 
                        << setw(12) << temp->studentLN 
                        << setw(3)  << (temp->studentMI.empty() ? "N/A" : temp->studentMI.substr(0, 1)) // Fix MI
                        << setw(8)  << (temp->studentSection.empty() ? "N/A" : temp->studentSection)   // Fix Section
                        << endl;
                temp = temp->next;
            }
        
            file.close();
        }

        void loadFromFile() {
            ifstream studentFile("students.txt");
            ifstream lectureFile("Lecture Grades.txt");
            ifstream labFile("Laboratory Grades.txt");
        
            if (!studentFile || !lectureFile || !labFile) {
                cout << "Error opening files for reading!" << endl;
                return;
            }
        
            string line, headerLine, separatorLine;
            int id;
            cout << "Loading Student Data...\n";

            getline(studentFile, headerLine);
            getline(studentFile, separatorLine);

            while (getline(studentFile, line)) {
                if (line.length() < 40) continue; 
        
                id = stoi(line.substr(0, 12));
                string fn  = trim(line.substr(12, 15));
                string ln  = trim(line.substr(27, 12));
                string mi  = trim(line.substr(39, 3));
                string sec = trim(line.substr(42, 8));
        
                cout << "Adding Student: ID = " << id << ", First Name = " << fn
                        << ", Last Name = " << ln << ", MI = " << mi << ", Section = " << sec << endl;
        
                addStudent(id, fn, ln, mi, sec);
            }

            studentFile.close();
        
            cout << "\nLoading Lecture Data...\n";
            getline(lectureFile, headerLine);  
            getline(lectureFile, separatorLine);
        
            while (lectureFile >> id) {
                Student* student = searchStudent(id);
                if (student) {
                    cout << "Found Student (Lecture): ID = " << id << endl;
                    for (int i = 0; i < 4; i++) lectureFile >> student->lecture.summativeScore[i];
                    lectureFile >> student->lecture.m_ProjectScore
                                >> student->lecture.f_ProjectScore
                                >> student->lecture.m_ExamScore
                                >> student->lecture.f_ExamScore
                                >> student->lecture.midtermLectureGrade
                                >> student->lecture.finalLectureGrade;
                } else {
                    cout << "Warning: Student ID " << id << " not found in linked list (Lecture Data).\n";
                }

            }

            lectureFile.close();

            cout << "\nLoading Laboratory Data...\n";
            getline(labFile, headerLine);
            getline(labFile, separatorLine);
        
            while (labFile >> id) {
                Student* student = searchStudent(id);
                if (student) {
                    cout << "Found Student (Lab): ID = " << id << endl;
                    for (int i = 0; i < 8; i++) labFile >> student->laboratory.technicalScore[i];
                    labFile >> student->laboratory.m_lab_examScore
                            >> student->laboratory.f_lab_examScore
                            >> student->laboratory.midtermLabGrade
                            >> student->laboratory.finalLabGrade;
                } else {
                    cout << "Warning: Student ID " << id << " not found in linked list (Lab Data).\n";
                }
            }

            labFile.close();
        
            cout << "\nAll Data Successfully Loaded!\n";
            system("pause");
        }

        string trim(const string &str) {
            size_t first = str.find_first_not_of(" \t");
            if (first == string::npos) return "";
            size_t last = str.find_last_not_of(" \t");
            return str.substr(first, (last - first + 1));
        }

        void saveLectureToFile() {
            ofstream file("Lecture Grades.txt");
        
            if (!file) {
                cout << "Error opening file for writing!" << endl;
                return;
            }
        
            file << left 
                 << setw(12) << "ID"
                 << setw(4)  << "SA1"
                 << setw(4)  << "SA2"
                 << setw(4)  << "SA3"
                 << setw(4)  << "SA4"
                 << setw(4)  << "MP"
                 << setw(4)  << "FP"
                 << setw(4)  << "ME"
                 << setw(4)  << "FE"
                 << setw(6)  << "MLEC"
                 << setw(6)  << "FLEC"
                 << endl;
        
            file << string(58, '=') << endl;

            Student* temp = head;
            while (temp) {
                file << left
                    << setw(12) << temp->studentID
                    << setw(4)  << static_cast<int>(temp->lecture.summativeScore[0])
                    << setw(4)  << static_cast<int>(temp->lecture.summativeScore[1])
                    << setw(4)  << static_cast<int>(temp->lecture.summativeScore[2])
                    << setw(4)  << static_cast<int>(temp->lecture.summativeScore[3])
                    << setw(4)  << static_cast<int>(temp->lecture.m_ProjectScore)
                    << setw(4)  << static_cast<int>(temp->lecture.f_ProjectScore)
                    << setw(4)  << static_cast<int>(temp->lecture.m_ExamScore)
                    << setw(4)  << static_cast<int>(temp->lecture.f_ExamScore)
                    << setw(6)  << fixed << setprecision(1) << temp->lecture.midtermLectureGrade
                    << setw(6)  << fixed << setprecision(1) << temp->lecture.finalLectureGrade
                    << endl;
            
                temp = temp->next;
            }
            
            file.close();
        }

        void saveLaboratoryToFile() {
            ofstream file("Laboratory Grades.txt");
        
            if (!file) {
                cout << "Error opening file for writing!" << endl;
                return;
            }

            file << left 
                 << setw(12) << "ID"
                 << setw(4)  << "TA1"
                 << setw(4)  << "TA2"
                 << setw(4)  << "TA3"
                 << setw(4)  << "TA4"
                 << setw(4)  << "TA5"
                 << setw(4)  << "TA6"
                 << setw(4)  << "TA7"
                 << setw(4)  << "TA8"
                 << setw(4)  << "ME"
                 << setw(4)  << "FE"
                 << setw(6)  << "MLAB"
                 << setw(6)  << "FLAB"
                 << endl;
        
            file << string(63, '=') << endl;
        
            Student* temp = head;
        
            while (temp) {
                file << left
                     << setw(12) << temp->studentID;

                for (int i = 0; i < 8; i++) {
                    file << setw(4) << static_cast<int>(temp->laboratory.technicalScore[i]);
                }

                file << setw(4) << static_cast<int>(temp->laboratory.m_lab_examScore)
                     << setw(4) << static_cast<int>(temp->laboratory.f_lab_examScore);

                file << setw(6) << fixed << setprecision(1) << temp->laboratory.midtermLabGrade
                     << setw(6) << fixed << setprecision(1) << temp->laboratory.finalLabGrade
                     << endl;
        
                temp = temp->next;
            }
        
            file.close();
        }
};
    
void Menu1(StudentManager &sm);
void Menu2(StudentManager &sm);
void Menu3(StudentManager &sm);
void Menu6(StudentManager &sm);
void Menu4(StudentManager &sm);
void Menu5(StudentManager &sm);
void Quit(StudentManager &sm);

int getValidatedInput(string prompt, int min, int max);
int getValidStudentID(StudentManager &sm);
Student* findStudent(StudentManager &sm, int id);
void getStudentScore(double &score, string label);

void Header();
void Display_Menu();
string toUpperCase(string str);
/*----------------------------------------------------------------------------------------------------------*/
int main() {
    StudentManager sm;

    sm.loadFromFile();

    int again, Menu_Choice = 0;

    do {
        bool valid = false;

        while (!valid) {
            system("cls");
            Display_Menu();
            cout << "--[";            
            cin >> Menu_Choice;
    
            if (cin.fail()) { 
                cin.clear();
                cin.ignore(10000, '\n'); 
                continue;
            }
    
            if (Menu_Choice >= 1 && Menu_Choice <= 7) {
                valid = true; 
            }
        }

        switch (Menu_Choice) {
            case 1: Menu1(sm); break;
            case 2: Menu2(sm); break;
            case 3: Menu3(sm); break;
            case 4: Menu4(sm); break;
            case 5: Menu5(sm); break;
            case 6: Menu6(sm); break;
            case 7: Quit(sm); break;
        }

        valid = false;

        cin.clear();
        cin.ignore(10000, '\n');

        cout << "\n\n";
        Horline('-', 71);
        Center_Text("[1] BACK TO MENU ", 70);
        Center_Text("[2] EXIT         ", 70);
        Horline('=', 71);
        cout << "--[";
        cin >> again;

        if (again != 1) Quit(sm);

    } while (again == 1);
    
    return 0;
}
/*----------------------------------------------------------------------------------------------------------*/

void Menu1(StudentManager &sm) {
    while (true) {

        system("cls");
        Header();
        Horline('-', 71);
        Center_Text("INPUT LECTURE DATA ", 70);
        Horline('-', 71);

        int id = getValidStudentID(sm);
        string fn, ln, mi, sec;

        cout << "Enter First Name     : ";
        cin.ignore();
        getline(cin, fn);
        cout << "Enter Last Name      : ";
        getline(cin, ln);
        cout << "Enter Middle Initial : ";
        getline(cin, mi);
        cout << "Enter Section        : ";
        cin >> sec;

        fn  = toUpperCase(fn);
        ln  = toUpperCase(ln);
        mi  = toUpperCase(mi);
        sec = toUpperCase(sec);

        sm.addStudent(id, fn, ln, mi, sec);
        Student* student = sm.searchStudent(id);
        if (!student) return;

        cout << endl;
        for (int i = 0; i < 4; i++) {
            getStudentScore(student->lecture.summativeScore[i],  "Summative Assessment " + to_string(i + 1) + " [Score]  : ");
            getStudentScore(student->lecture.summativePoints[i], "                       [Points] : ");
        }

        getStudentScore(student->lecture.m_ProjectScore , "Midterm Project        [Score]  : ");
        getStudentScore(student->lecture.m_ProjectPoints, "                       [Points] : ");
        getStudentScore(student->lecture.f_ProjectScore , "Final Project          [Score]  : ");
        getStudentScore(student->lecture.f_ProjectPoints, "                       [Points] : ");
        getStudentScore(student->lecture.m_ExamScore    , "Midterm Exam           [Score]  : ");
        getStudentScore(student->lecture.m_ExamPoints   , "                       [Points] : ");
        getStudentScore(student->lecture.f_ExamScore    , "Final Exam             [Score]  : ");
        getStudentScore(student->lecture.f_ExamPoints   , "                       [Points] : ");

        student->lecture.calculateMidtermLectureGrade();
        student->lecture.calculateFinalLectureGrade();

        sm.saveToFile();
        sm.saveLectureToFile();

        system("cls");
        Header();
        Horline('-', 71);
        Center_Text(fn + " SUCCESSFULLY ADDED", 70);
        Horline('-', 71);
        sm.displaySingleStudentInfo(student);
        Center_Text("LECTURE GRADES", 70);
        Center_Text(" ", 70);
        
        cout << left;
        cout << "| TASK                      [SCORE]    /    [POINTS]                   |\n";
        cout << "| -------------------------------------------------------------------- |\n";
        for (int i = 0; i < 4; i++) {
        cout << "| Summative Assessment "<<to_string(i + 1)<<" :    " << setw(3) << student->lecture.summativeScore[i] << "      /      " << setw(3) << student->lecture.summativePoints[i] << "                      |" << endl;
        }
        cout << "| Midterm Project        :    " << setw(3) << student->lecture.m_ProjectScore << "      /      " << setw(3) << student->lecture.m_ProjectPoints << "                      |" << endl;
        cout << "| Final Project          :    " << setw(3) << student->lecture.f_ProjectScore << "      /      " << setw(3) << student->lecture.f_ProjectPoints << "                      |" << endl;
        cout << "| Midterm Exam           :    " << setw(3) << student->lecture.m_ExamScore    << "      /      " << setw(3) << student->lecture.m_ExamPoints    << "                      |" << endl;
        cout << "| Final Exam             :    " << setw(3) << student->lecture.f_ExamScore    << "      /      " << setw(3) << student->lecture.f_ExamPoints    << "                      |" << endl;
        Center_Text(" ", 70);
        Horline('-', 71);

        int choice = getValidatedInput("\nEnter [1] to ADD another student [2] to EXIT --[", 1, 2);
        if (choice != 1) return;
    }
}

void Menu2(StudentManager &sm) {
    
    while (true) {
        system("cls");
        
        int id = getValidatedInput("Enter Student ID to Update Lab Data: ", 1, 999999999);
        Student* student = findStudent(sm, id);
        if (!student) return;

        system("cls");
        Header();
        sm.displaySingleStudentInfo(student);

        Horline    ('-', 71);
			Center_Text("Input Laboratory Data", 70);
			Center_Text("" , 70);

        for (int i = 0; i < 8; i++) {
            getStudentScore(student->laboratory.technicalScore[i],  "Technical Assessment " + to_string(i + 1) + "  [Score]  : ");
            getStudentScore(student->laboratory.technicalPoints[i], "                        [Points] : ");
        }

        getStudentScore(student->laboratory.m_lab_examScore    , "Midterm Laboratory Exam [Score]  : ");
        getStudentScore(student->laboratory.m_lab_examPoints   , "                        [Points] : ");
        getStudentScore(student->laboratory.f_lab_examScore    , "Final Laboratory Exam   [Score]  : ");
        getStudentScore(student->laboratory.f_lab_examPoints   , "                        [Points] : ");  

        student->laboratory.calculateMidtermLabGrade();
        student->laboratory.calculateFinalLabGrade();

        sm.saveLaboratoryToFile();

        system("cls");
        Header();
        Horline('-', 71);
        Center_Text(to_string(id) + " SUCCESSFULLY ADDED", 70);
        Horline('-', 71);
        sm.displaySingleStudentInfo(student);
        Center_Text("LABORATORY GRADES", 70);
        Center_Text(" ", 70);
        
        cout << left;
        cout << "| TASK                      [SCORE]    /    [POINTS]                   |\n";
        cout << "| -------------------------------------------------------------------- |\n";
        for (int i = 0; i < 4; i++) {
        cout << "| Technical Assessment "<<to_string(i + 1)<<" :    " << setw(3) << student->laboratory.technicalScore[i] << "      /      " << setw(3) << student->laboratory.technicalPoints[i] << "                      |" << endl;
        }
        cout << "| Midterm Lab Exam       :    " << setw(3) << student->laboratory.m_lab_examScore    << "      /      " << setw(3) << student->laboratory.m_lab_examPoints << "                      |" << endl;
        cout << "| Final Lab Exam         :    " << setw(3) << student->laboratory.f_lab_examScore    << "      /      " << setw(3) << student->laboratory.f_lab_examPoints << "                      |" << endl;
        Center_Text(" ", 70);
        Horline('-', 71);

        int choice = getValidatedInput("\nEnter [1] to ADD another student [2] to EXIT --[", 1, 2);
        if (choice != 1) return;
    }
}


void Menu3(StudentManager &sm) {
    while (true) {
        system("cls");
        Header();
        Horline('-', 71);
        Center_Text("STUDENT GRADE REPORT", 70);
        Horline('-', 71);

        int id = getValidatedInput("Enter Student ID to View Grades: ", 1, 999999999);
        Student* student = sm.searchStudent(id);

        if (!student) {
            cout << "Warning: Student with ID " << id << " not found!\n";
            cout << "Please go to Menu 1 first to add this student.\n";
            return;
        }

        bool hasLectureGrades = student->lecture.m_ProjectPoints > 0 && student->lecture.f_ProjectPoints > 0;
        bool hasLabGrades = student->laboratory.m_lab_examPoints > 0 && student->laboratory.f_lab_examPoints > 0;

        if (!hasLectureGrades) cout << "Warning: No recorded lecture grades for this student!\n";
        if (!hasLabGrades) cout << "Warning: No recorded laboratory grades for this student!\n";

        student->calculateMidtermCourseGrade();
        student->calculateFinalCourseGrade();

        if (isnan(student->lecture.midtermLectureGrade) || isinf(student->lecture.midtermLectureGrade))
            student->lecture.midtermLectureGrade = 0;
        if (isnan(student->lecture.finalLectureGrade) || isinf(student->lecture.finalLectureGrade))
            student->lecture.finalLectureGrade = 0;
        if (isnan(student->laboratory.midtermLabGrade) || isinf(student->laboratory.midtermLabGrade))
            student->laboratory.midtermLabGrade = 0;
        if (isnan(student->laboratory.finalLabGrade) || isinf(student->laboratory.finalLabGrade))
            student->laboratory.finalLabGrade = 0;
        if (isnan(student->lecture.finalCourseGrade) || isinf(student->lecture.finalCourseGrade))
            student->lecture.finalCourseGrade = 0;

        double finalCourse_Grade = student->lecture.finalCourseGrade;
        double numEquivalent;
        string equivalent;

        if (finalCourse_Grade >= 97 && finalCourse_Grade <= 100) {
            numEquivalent = 4.0;
            equivalent = "Excellent";
        } else if (finalCourse_Grade >= 93) {
            numEquivalent = 3.5;
            equivalent = "Superior";
        } else if (finalCourse_Grade >= 89) {
            numEquivalent = 3.0;
            equivalent = "Very Good";
        } else if (finalCourse_Grade >= 85) {
            numEquivalent = 2.5;
            equivalent = "Good";
        } else if (finalCourse_Grade >= 80) {
            numEquivalent = 2.0;
            equivalent = "Satisfactory";
        } else if (finalCourse_Grade >= 75) {
            numEquivalent = 1.5;
            equivalent = "Fair";
        } else if (finalCourse_Grade >= 70) {
            numEquivalent = 1.0;
            equivalent = "Passed";
        } else {
            numEquivalent = 0.5;
            equivalent = "Failed";
        }

        system("cls");
        Header();
        Horline('-', 71);
        Center_Text("STUDENT GRADE REPORT", 70);
        Horline('-', 71);
        Center_Text("Student Information", 70);
        cout << left;
        cout << "| " << setw(30) << "Student Name"      << ": " << setw(36) << student->getFullName()   << " |\n";
        cout << "| " << setw(30) << "Student ID Number" << ": " << setw(36) << student->studentID      << " |\n";
        cout << "| " << setw(30) << "Course"            << ": " << setw(36) << "CCS0007/CCS0007L"      << " |\n";
        cout << "| " << setw(30) << "Section"           << ": " << setw(36) << student->studentSection << " |\n";
        Horline('-', 71);

        cout << "\n LECTURE GRADES\n -------------------------------\n";
        cout << " SA1  SA2  SA3  SA4  MP   FP   ME   FE   MLEC  FLEC\n";
        cout << " ==== ==== ==== ==== ==== ==== ==== ==== ===== =====\n";

        cout <<" "
             << setw(4) << static_cast<int>(student->lecture.summativeScore[0]) << " "
             << setw(4) << static_cast<int>(student->lecture.summativeScore[1]) << " "
             << setw(4) << static_cast<int>(student->lecture.summativeScore[2]) << " "
             << setw(4) << static_cast<int>(student->lecture.summativeScore[3]) << " "
             << setw(4) << static_cast<int>(student->lecture.m_ProjectScore) << " "
             << setw(4) << static_cast<int>(student->lecture.f_ProjectScore) << " "
             << setw(4) << static_cast<int>(student->lecture.m_ExamScore)    << " "
             << setw(4) << static_cast<int>(student->lecture.f_ExamScore)    << " "
             << setw(6) << fixed << setprecision(1) << student->lecture.midtermLectureGrade << " "
             << setw(6) << student->lecture.finalLectureGrade << endl;

        cout << "\n LABORATORY GRADES\n -------------------------------\n";
        cout << " TA1  TA2  TA3  TA4  TA5  TA6  TA7  TA8  ME   FE   MLAB  FLAB\n";
        cout << " ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ===== =====\n ";

        for (int i = 0; i < 8; i++) {
            cout << setw(4) << static_cast<int>(student->laboratory.technicalScore[i]) << " ";
        }
        cout <<" "<< setw(4) << static_cast<int>(student->laboratory.m_lab_examScore) << " "
             << setw(4) << static_cast<int>(student->laboratory.f_lab_examScore) << " "
             << setw(6) << fixed << setprecision(1) << student->laboratory.midtermLabGrade << " "
             << setw(6) << student->laboratory.finalLabGrade << endl;

        cout << "\n COURSE GRADES\n -------------------------------\n";
        cout << " MCG   FCG   EQV   REMARKS\n";
        cout << " ===== ===== ===== =========\n ";
        cout << fixed << setprecision(1)
             << setw(5) << student->lecture.midtermCourseGrade << " "
             << setw(5) << student->lecture.finalCourseGrade << " "
             << setw(5) << numEquivalent << "  "
             << equivalent << endl << endl;

        Horline('-', 71);

        int choice = getValidatedInput("\nEnter [1] to view another student [2] to EXIT --[", 1, 2);
        if (choice != 1) return;
    }
}

void Menu4(StudentManager &sm) {

    system("cls");
    Header();
    Horline('-', 71);
    Center_Text("List of Students", 70);
    Horline('-', 71);
        
    Student* temp = sm.getHead();
    int studentCount = 0;

    while (temp) { 
        studentCount++;
        temp = temp->next;
    }

    if (studentCount == 0) {
        cout << "⚠ Warning: No students listed in the system!\n";
        cout << "➡ Please add students first in Menu 1.\n";
        cout << "\nPress any key to return to the main menu...";
        cin.ignore();
        cin.get();
        return;
    }

    Horline('-', 71);

    cout << left;
    cout << "| " << setw(40) << "Total Number of Students Listed" << ": " << setw(26) << studentCount << " |\n";
    cout << "| " << setw(40) << "Course"                          << ": " << setw(26) << "CCS0007/CCS0007L" << " |\n";
    cout << "| " << setw(40) << "Section"                         << ": " << setw(26) << "TN05" << " |\n";
    
    Horline('-', 71);

    Horline('-', 71);

    cout << "| " << setw(4) << "No." 
         << "| " << setw(35) << "Student Name" 
         << "| " << setw(25) << "Student ID No." << " |\n";
    
    Horline('-', 71);

    temp = sm.getHead();
    int count = 1;

    while (temp) {
        cout << "| " << setw(4) << count 
             << "| " << setw(35) << temp->getFullName() 
             << "| " << setw(25) << temp->studentID << " |\n";
        
        temp = temp->next;
        count++;
    }

    Horline('-', 71);
  
}

void Menu5(StudentManager &sm) {
    system("cls");

    Student* temp = sm.getHead();

    if (!temp) {
        cout << "⚠ Warning: No students listed in the system!\n";
        cout << "➡ Please add students first in Menu 1.\n";
        cout << "\nPress any key to return to the main menu...";
        cin.ignore();
        cin.get();
        return;
    }

    Horline('=', 107);
    Center_Text("CCS0007/CCS0007L COURSE GRADING COMPUTATION MENU", 106);
    Horline('=', 107);
    Horline('-', 107);
    
    Center_Text("Lecture Grades of Listed Students", 106);
    Center_Text("", 106);
    Center_Text("Course    : CCS0007L                                           Section   : TN05", 106);
    Horline('-', 107);
    Horline('-', 107);

    cout << left;
    cout << "| " << setw(3) << "No." 
         << " " << setw(28) << "Student Name"
         << "  " << setw(12) << "ID No."
         << "  " << setw(4) << "SA1"
         << "  " << setw(4) << "SA2"
         << "  " << setw(4) << "SA3"
         << "  " << setw(4) << "SA4"
         << "  " << setw(4) << "MP"
         << " " << setw(4) << "FP"
         << " " << setw(4) << "ME"
         << " " << setw(4) << "FE"
         << " " << setw(6) << "MLEC"
         << " " << setw(6) << "FLEC"
         << "|\n";
    
    Horline('-', 107);

    int count = 1;
    while (temp) {
        bool noGrades = (temp->lecture.midtermLectureGrade == 0 && temp->lecture.finalLectureGrade == 0);
        
        cout << "| " << setw(3) << count 
             << " " << setw(28) << temp->getFullName()
             << "  " << setw(12) << temp->studentID;

        for (int j = 0; j < 4; j++) {
            cout << "  " << setw(4) << static_cast<int>(temp->lecture.summativeScore[j]);
        }

        cout << "  " << setw(4) << static_cast<int>(temp->lecture.m_ProjectScore)
             << " " << setw(4) << static_cast<int>(temp->lecture.f_ProjectScore)
             << " " << setw(4) << static_cast<int>(temp->lecture.m_ExamScore)
             << " " << setw(4) << static_cast<int>(temp->lecture.f_ExamScore)
             << " " << setw(6) << fixed << setprecision(1) << temp->lecture.midtermLectureGrade
             << " " << setw(6) << fixed << setprecision(1) << temp->lecture.finalLectureGrade
             << (noGrades ? "   ⚠ No Grades Recorded!" : "")
             << "|\n";

        temp = temp->next;
        count++;
    }

    Horline('-', 107);

}


void Menu6(StudentManager &sm) {
    system("cls");

    Student* temp = sm.getHead();

    if (!temp) {
        cout << "⚠ Warning: No students listed in the system!\n";
        cout << "➡ Please add students first in Menu 1.\n";
        cout << "\nPress any key to return to the main menu...";
        cin.ignore();
        cin.get();
        return;
    }

    Horline('=', 121);
    Center_Text("CCS0007/CCS0007L COURSE GRADING COMPUTATION MENU", 120);
    Horline('=', 121);
    Horline('-', 121);
    
    Center_Text("Laboratory Grades of Listed Students", 120);
    Center_Text("", 120);
    Center_Text("Course    : CCS0007                                            Section   : TN05", 120);
    Horline('-', 121);
    Horline('-', 121);

    cout << left;
    cout << "| " << setw(3) << "No." 
         << " " << setw(28) << "Student Name"
         << " " << setw(12) << "ID No."
         << "  " << setw(4) << "TA1"
         << "  " << setw(4) << "TA2"
         << "  " << setw(4) << "TA3"
         << "  " << setw(4) << "TA4"
         << "  " << setw(4) << "TA5"
         << "  " << setw(4) << "TA6"
         << "  " << setw(4) << "TA7"
         << "  " << setw(4) << "TA8"
         << "   " << setw(4) << "ME"
         << " " << setw(4) << "FE"
         << " " << setw(6) << "MLAB"
         << " " << setw(6) << "FLAB"
         << "|\n";
    
    Horline('-', 121);

    int count = 1;
    while (temp) {
        bool noLabGrades = (temp->laboratory.midtermLabGrade == 0 && temp->laboratory.finalLabGrade == 0);
        
        cout << "| " << setw(3) << count 
             << " " << setw(28) << temp->getFullName()
             << " " << setw(12) << temp->studentID;

        for (int j = 0; j < 8; j++) {
            cout << "  " << setw(4) << static_cast<int>(temp->laboratory.technicalScore[j]);
        }

        cout << "   " << setw(4) << static_cast<int>(temp->laboratory.m_lab_examScore)
             << " " << setw(4) << static_cast<int>(temp->laboratory.f_lab_examScore)
             << " " << setw(6) << fixed << setprecision(1) << temp->laboratory.midtermLabGrade
             << " " << setw(6) << fixed << setprecision(1) << temp->laboratory.finalLabGrade
             << (noLabGrades ? "   ⚠ No Grades Recorded!" : "")
             << "|\n";

        temp = temp->next;
        count++;
    }

    Horline('-', 121);

}

void Quit(StudentManager &sm) {
    system("cls");

    sm.saveToFile();
    sm.saveLectureToFile();
    sm.saveLaboratoryToFile();

    Header();
    Center_Text(" ", 70);
    Center_Text("Saving all student data...", 70);
    Center_Text("Thank you for using the system!", 70);
    Center_Text(" ", 70);
    Horline('-', 71);
    
    exit(0);
}

int getValidatedInput(string prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < min || value > max) {
            cout << " Invalid input! Please enter a number between " << min << " and " << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return value;
        }
    }
}

int getValidStudentID(StudentManager &sm) {
    int id;
    while (true) {

        cout << "Enter Student ID     : ";
        cin >> id;

        if (cin.fail() || id < 0) {  
            cout << "Error: Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (sm.searchStudent(id)) {
            cout << "Error: Student ID already exists!\n";
        } else {
            return id;
        }
    }
}

Student* findStudent(StudentManager &sm, int id) {

    Student* student = sm.searchStudent(id);

    if (!student) {

        Horline('-', 71);
        Center_Text(" ", 70);
        Center_Text("Warning: Student with ID " + to_string(id) + " not found!", 70);
        Center_Text("Please go to Menu 1 first to add this student.", 70);
        Center_Text(" ", 70);
        Horline('-', 71);

        return nullptr;
    }
    return student;
}

void getStudentScore(double &score, string label) {
    do {
        cout << label;
        cin >> score;

        if (cin.fail() || score < 1 || score > 100) {
            cout << "Error: Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);
}

	
void Horline(char symbol='-', int count=71){
    for (int i=0; i<=count; i++){
        cout << symbol;  
    }
    cout << endl;
}

void Header(){

    Horline('=');
    Center_Text("COURSE GRADE CALCULATOR", 70);
    Horline('=');
}

void Center_Text(const string& text, int totalLength) {
    int textLength = text.length();
    int paddingLeft = (totalLength - textLength) / 2;
    int paddingRight = totalLength - textLength - paddingLeft;

    cout << "|" << string(paddingLeft, ' ') << text << string(paddingRight, ' ') << "|" << endl;
}

void Display_Menu(){
    Header();
    Center_Text(" ", 70);
    Center_Text("[1] INPUT LECTURE DATA                              ", 70);
    Center_Text("[2] INPUT LABORATORY DATA                           ", 70);
    Center_Text("[3] GET STUDENT LECTURE, LABORATORY, & COURSE GRADE ", 70);
    Center_Text("[4] GET NUMBER OF STUDENTS LISTED                   ", 70);
    Center_Text("[5] GET POSTED LECTURE GRADES OF LISTED STUDENTS    ", 70);
    Center_Text("[6] GET POSTED LABORATORY GRADES OF LISTED STUDENTS ", 70);
    Center_Text("[7] EXIT                                            ", 70);
    Center_Text(" ", 70);
    Horline();	
}

string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
	}
    