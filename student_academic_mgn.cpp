#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <iomanip>

using namespace std;

string recent = "You just came in 🤝\n";

void rg_student();
void cr_course();
void delete_student();
void delete_course();
void enroll_student();
void unenroll_student();
void record_marks();
void display_available_courses();
void virtual_mark();
bool check_file_existence(string file);
int count_files(string dir);


void space(int x)
{
    for (int i = 0; i < x; i++)
    {
        cout << endl;
    }
}


int main()
{
    if (recent == "You just came in 🤝\n")
        system("clear");

    int main_choice;
    space(2);
    cout << setw(70) << "WELCOME TO UMaT ACADEMIC RECORDS SPACE\n";
    virtual_mark();

    system("python3 course_records.py numbers");
    space(1);
    cout << "RECENT ACTIVITY ⚙️" << endl;
    cout << recent << endl;

    cout << "Please enter an interger beside your preferd action as below.\n";
    cout << "0. Exit [Or any other character]\n";
    cout << "1. Create a new course\n";
    cout << "2. Register a student\n";
    cout << "3. Record marks\n";
    cout << "4. Enroll a student to a course\n";
    cout << "5. Unenroll a student from a course\n";
    system("python3 course_records.py option_6"); // Delete student option
    system("python3 course_records.py option_7_8"); // See available courses option
    cout<< "Enter a number-> ";
   
    cin >> main_choice;
    cin.ignore(1000, '\n');

    main_choice = int(main_choice);
    
    switch (main_choice)
    {
        case 0:
            space(1);
            cout << "Bye👋  See you next time.\n Closing...\n";
            exit(0);

        case 1:
            cr_course();
        
        case 2:
            rg_student();   

        case 3:
            record_marks();

        case 4:
            enroll_student();

        case 5:
            unenroll_student();

        case 6:
            delete_student();
    
        case 7:
            delete_course();

        case 8:
            space(1);
            display_available_courses();

        default:
            return 0;
    }
}

void cr_course()
{
    string cr_name, cr_code, cr_instructor, credit_hours;
    int confirm;
    space(1);
    cout << "Enter name of Course: ";
    getline(cin, cr_name);
    cout << "Enter course code: ";
    getline(cin, cr_code);
    cout << "Enter course instructors name: ";
    getline(cin, cr_instructor);
    cout << "Enter total credit hours of course: ";
    cin >> credit_hours;

    cout << "Are you sure of the details?\n";
    cout << "1. Yes\t 2.Return to main menu\t [Any other char to re-enter values]\n";
    cin >> confirm;
    cin.clear();
    space(1);

    if (int(confirm)== 1)
    {
        ofstream ofile("cr_details.txt");
        ofile << cr_name << "\n"
        << cr_instructor << "\n" 
        << cr_code << "\n"
        << credit_hours << "\n";
        space(1);
        cout << "Creating course...\n";
        space(1);
    }
    else if (int(confirm) == 2)
    {
        cout << "Arborted! Returning to main menu...\n";
        recent = "You just aborted Course[" +cr_code + "] registration\n";
    }
    else
    {
        cout << "Arborted: Re-enter details\n";
        cin.ignore(100000, '\n');
        cr_course();   
    }

    if (int(confirm) == 1)
    {
        system("python3 course_records.py cr_course");

        bool cr_created_suc = check_file_existence("./cr_code_taken.txt");
        if (cr_created_suc)
        {
            system("rm ./cr_code_taken.txt");
            recent = "You just entered an course code and couldn't register course⭕️\n";
            system("rm cr_details.txt");
            cr_course();
        }
    

        system("rm cr_details.txt");
        recent = "You just created a Course[" + cr_code + "]\n";
    }
    sleep(1);
    space(1);
    main();
}

void rg_student()
{
    space(1);
    string s_name, f_name, l_name, index_num, program;
    cout << "To Register Student:\n";
    cout << "Enter student's Surname: ";
    cin >> s_name;
    cout << "Enter student's First name: ";
    cin >> f_name;
    cout << "Enter student's Last name: ";
    cin >> l_name;
    cout << "Enter student's index number: ";
    cin >> index_num;
    cout << "Enter student's Program: ";
    cin.ignore();
    getline(cin, program);
    
    int confirm;
    cout << "Are you sure of the details?\n";
    cout << "1. Yes\t 2. Abort and return to main menu\t  [Any other char to re-enter details]\n";

    cin >> confirm;
    cin.clear();

    if (int(confirm) == 1)
    {
        ofstream file("st_details.txt");
        file << f_name << " " << l_name << " " << s_name << "\n";
        file << index_num << "\n";
        file << program << "\n";
        cout << "Registering student\n";
        space(1);
    }
    else if (int(confirm) == 2)
    {   
        cout << "Aborted!  Returning to main menu...\n";
        recent = "You just aborted student[" + index_num + "] registration\n";
    }
    else
    {
        cout << "Aborted: Re-enter details\n";
        cin.ignore(100000, '\n');
        rg_student();    
    }
    if (int(confirm == 1))
    {
        system("python3 course_records.py rg_student");
    
        bool st_registered_suc = check_file_existence("./index_num_taken.txt");
        if (st_registered_suc)
        {
            system("rm ./index_num_taken.txt");
            recent = "You just entered an existing ined number and couldn't register student⭕️\n";
            system("rm st_details.txt");
            rg_student();
        }
    
        system("rm st_details.txt");
        recent = "🌈You just registered a student[" + index_num + "]\n";
    }

    sleep(1);
    space(1);
    main();
}

void delete_student()
{
    system("python3 course_records.py delete_student");

    if (!check_file_existence("./courses.txt"))
    {
        recent = "You just entered a wrong❌ index number for student deletion\n";
        system("rm ./confirm_index_num.txt");
        main();
    }

    string index_num;
    cout << "Enter Index number of student again: ";
    cin >> index_num;

    string previous_index_num;
    ifstream index_num_file("confirm_index_num.txt");
    index_num_file >> previous_index_num;
    index_num_file.close();

    if (index_num != previous_index_num)
    {
        system("rm ./confirm_index_num.txt");
        system("rm ./courses.txt");
        recent = "Deletion of student just failed🛑 due to unmatched index numbers\n";
        main();
    }

    cout << "Checking and unenrolling [" << index_num << "] from courses..." << endl;
    string course;
    ifstream fin("courses.txt");
    while (getline(fin, course))
    {
        ofstream fout("st_and_cr_details.txt");
        fout << index_num << endl << course << endl;
        system("python3 course_records.py deleting_unenrollment");
        system("rm st_and_cr_details.txt");
        fout.close();
    }
    system("rm ./confirm_index_num.txt");
    system("rm ./courses.txt");

    cout << "Now deleting student's files..." << endl;
    ofstream st_file("st_file.txt"); // for python to get index num to delete st file
    st_file << index_num << endl;
    system("python3 course_records.py delete_st_files");
    system("rm ./st_file.txt");
    cout << "Done ✅" << endl;
    recent = "🌈You just successfully deleted a student with index number " + index_num + "\n";
    main();
}

void delete_course()
{
    system("python3 course_records.py delete_course");

    if (!check_file_existence("./students.txt"))
    {
        recent = "You just entered a wrong❌ course code for course deletion\n";
        system("rm ./confirm_cr_code.txt");
        main();
    }

    string cr_code;
    cout << "Enter course code again(Note: It's case sensitive): ";
    cin >> cr_code;

    string previous_cr_code;
    ifstream cr_code_file("confirm_cr_code.txt");
    cr_code_file >> previous_cr_code;
    cr_code_file.close();

    if (cr_code != previous_cr_code)
    {
        system("rm ./confirm_cr_code.txt");
        system("rm ./students.txt");
        recent = "Deletion of course just failed🛑 due to unmatched course codes\n";
        main();
    }

    cout << "Checking and deleting course[" << cr_code << "] data from active students..." << endl;
    string students;
    ifstream fin("students.txt");
    while (getline(fin, students))
    {
        ofstream fout("st_and_cr_details.txt");
        fout << students << endl << cr_code << endl;
        system("python3 course_records.py deleting_unenrollment");
        system("rm st_and_cr_details.txt");
        fout.close();
    }

    system("rm ./confirm_cr_code.txt");
    system("rm ./students.txt");

    cout << "Now deleting course files..." << endl;
    ofstream cr_file("cr_file.txt"); // for python to get cr_code/index_ num to delete st file/cr file
    cr_file << cr_code << endl;
    system("python3 course_records.py delete_cr_files");
    system("rm ./cr_file.txt");
    cout << "Done ✅" << endl;
    recent = "🌈You just successfully deleted a course with code" + cr_code + "\n";
    main();
}

void enroll_student()
{
    string course_code, index_num;
    space(1);
    cout << "Enrol Student to which cause?\n";
    cout << "Enter course code to continue action or 0 to return to main menu: ";
    cin >> course_code;
    space(1);

    if (course_code == "0")
    {
        cout << "Returning to main Menu...\n";
        recent = "You just aborted a student[" + index_num + "] enrollment to course[" + course_code + "]\n";
        sleep(1);
        main();
    }

    string course_loc = "./files/courses/" + course_code + ".xlsx";
    bool course_exist = check_file_existence(course_loc);
    bool st_exist = false;

    if (course_exist)
    {
        while (true)
        {
            cout << "Enter students index number to proceed or 0 to return to main menu\n";
            cout << "Not registered student? Then enter r/R to register student now...\n";
            cout << "Index number / r/R / 0: ";
            cin >> index_num;

            string st_loc = "./files/students/" + index_num + ".xlsx";
            st_exist = check_file_existence(st_loc);

            if (index_num == "r")
            {
                rg_student();
            }
            else if (index_num == "0")
            {
                cout << "Returning to Main Menu\n";
                recent = "You just aborted a student[" + index_num + "] enrollment to course[" + course_code + "]\n";
                sleep(1);

                main();
            }
            else if (st_exist)
            {
                ofstream ofile("st_and_cr_details.txt");
                ofile << index_num <<endl<< course_code <<endl;

                space(1);
                cout << "Enrolling Student\n";
                cout << "######################\n";
                space(1);
                break;
            }
            else
            {
                space(1);
                cout << "No student available with index number "<< index_num<<"\n";
            }
        }
    }
    else
    {
        space(1);
        cout << "No registered course with code " << course_code << " available."
             << "\n";
        enroll_student();
    }
    if (st_exist)
    {
        system("python3 course_records.py enroll_student");
        system("rm ./st_and_cr_details.txt");
        sleep(1);
        recent = "You just enrolled a student[" + index_num + "] to course[" + course_code + "]\n";
        main();
    }
}

void unenroll_student()

{
    string course_code, index_num;
    space(1);
    cout << "Unenroll Student from which cause?\n";
    cout << "Enter course code to proceed or 0 to return to main menu: ";
    cin >> course_code;

    if (course_code == "0"){
        cout << "Returning to Main Menu\n";
        recent = "You just aborted a student[" + index_num + "] unenrollment from course[" + course_code + "]\n";
        sleep(1);
        main();
    }

    string course_loc = "./files/courses/" + course_code + ".xlsx";
    bool course_exist = check_file_existence(course_loc);

    if (course_exist)
    {
        cout << "Enter students index number: ";
        cin >> index_num;

        string st_loc = "./files/students/" + index_num + ".xlsx";
        bool st_exist = check_file_existence(st_loc);


        while (!st_exist)
        {
            space(1);

            cout << "No registered student with index number " << index_num << " available⭕️" << endl;
            cout << "Enter the correct index number to proceed or 0 to return to main menu: ";
            cin >> index_num;

            st_loc = "./files/students/" + index_num + ".xlsx";
            st_exist = check_file_existence(st_loc);

            if (index_num == "0")
            {
                cout << "Returning to Main Menu\n";
                sleep(1);
                recent = "You just aborted a student[" + index_num + "] unenrollment to course[" + course_code + "]\n";
                main();
            }
        }

        space(1);
        ofstream ofile("st_and_cr_details.txt");
        ofile << index_num <<endl<< course_code <<endl;
        cout << "Unenrolling Student\n";
        space(1);
    }
    else
    {
        space(1);
        cout << "No registered course with code " << course_code << " available."
             << "\n";
        unenroll_student();
    }

    if(course_exist)
    {
        system("python3 course_records.py unenroll_student");
        system("rm ./st_and_cr_details.txt");

        if(check_file_existence("./aborted_unenrollment.txt"))
        {
            recent = "You just aborted unenrolling a student[" + index_num + "] from course[" + course_code + "]⭕️\n";
            system("rm ./aborted_unenrollment.txt");
        }
        else
        {
            recent = "You just unenrolled a student[" + index_num + "] from course[" + course_code + "]\n";
        }
    }
    sleep(1);
    main();
}

void record_marks()
{
    space(1);
    int choice; string recording, cr_code, index_num;
    cout << "Choose from below what you wish to record\n";
    cout << "1. Exam\t 2. Quiz\t 3. Assignment\t 4. Attendance\t [Any other char to return to main menu]\n";
    cout << "Input: ";
    cin >> choice;
    cin.clear();
    cin.ignore(100000, '\n');
    space(1);

    switch (choice)
    {
    case 1:
        recording = "Exam";  
        break;
    
    case 2:
        recording = "Quiz";
        break;

    case 3:
        recording = "Assingment";
        break;

    case 4:
        recording = "Attendance";
        break;

    default:
        recent = "You just terminated recording of marks⁉️\n";
        main();
    }
     
    bool cr_exists = 0;
    while (!cr_exists)
    {
        cout << "Enter the code of the course you'll be recording to [Or 0 to return to previous menu]: ";
        cin >> cr_code;
        
        if (cr_code == "0")
        {
            cin.ignore(1000000, '\n');
            recent = "You just entered 0 when asked for course code and returned from recoding a/an " + recording + "\n";
            main();
        }

        string cr_path = "./files/courses/" + cr_code + ".xlsx";
        cr_exists = check_file_existence(cr_path);

        if (!cr_exists)
        {
            space(1);
            cout << "There is no available course with code "<< cr_code <<"\n";        
        }
    }
    space(1);

    bool st_exists = 0;
    while (!st_exists)
    {
        cout << "Enter the index number of the student you'll be recording for [Or 0 to return to previous menu]: ";
        cin >> index_num;
        
        if (index_num == "0")
        {
            cin.ignore(1000000, '\n');
            recent = "You just entered 0 when asked for index number and returned from recoding a/an " + recording + "\n";
            main();
        }

        string st_path = "./files/students/" + index_num + ".xlsx";
        st_exists = check_file_existence(st_path);

        if (!st_exists)
        {
            space(1);
            cout << "There is no available student with index number "<< index_num <<"\n";        
        }
    }
    space(1);

    ofstream fout("test_and_course_details.txt");
    fout << cr_code << endl << index_num << endl << recording << endl;

    system("python3 course_records.py record_marks");
    recent = "You recently visited marks recording for " + recording + "\n";
    system("rm test_and_course_details.txt");

    main();
}

void display_available_courses()
{
    cout << "Below is a list of all active courses\n";
    space(1);
    system("python3 course_records.py display_available_courses");
    space(1);
    cout << "Press any key to continue...";
    cin.get();
    system("clear");
    recent = "You just checked out available courses\n";
    main();
}

void virtual_mark()
{
    cout << setw(72) << "Created at Virtual World🌎💻💻\n";
    cout << setw(60) << "Brain behind:: Vadmin\n";
    space(1);
}

bool check_file_existence(string file_loc)
{
    ifstream file(file_loc);
    if (file)
    {
        return true;
    }
    return false;
}
