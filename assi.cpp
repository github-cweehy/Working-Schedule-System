//admin system 

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<string>
#include<cmath>

// new library
#include<sstream>
#include<cctype>
#include<ctime>
#include <cstdlib>
using namespace std;

struct UserDetails
{
	string contact;
	string pw;
	string name;
	string email;
	string ID;
	string role;
	string startTime;
	string endTime;
	string fulldate;
	string ClockIn_time;
	string ClockOut_time;
	int date;
	int month;
	float total_hour;
	float monthly_hour[12]; 
	float monthly_salary[12];
}s[100],r[100],schedule[100],clocking[100],clockout[100];

void interface();

class file
{
	private:
		int total_emp, total_resign_emp, total_schedule, total_clock,total_clock_out;
		float hourlyRate,BasicSalary;
	public:
		file() : total_schedule(0),hourlyRate(9),BasicSalary(1800){}
		friend void interface();
		
		//save schedule file with new schedule 
		void saveSchedule();
		
		//save schedule file after edit, the total schedule unchanged
		void saveSchedule2();
		
		//save schedule with delete one of the schedule by delete function
		void saveSchedule3();
		
		//read the schedule file and load into struct UserDetails schedule
		void loadSchedule();
		
		//save new employee details into file
		void SaveToFile();
		
		//save employee details after editing, total employee number unchanged
		void SaveToFile2();
		
		//save employee details when remove the selecting employee
		void SaveToFile3();
		
		//save removed employee to this file
		void SaveToResignFile(int i);

  		//read employee file and load into struct UserDetails s
  		void LoadFromFile();
  		
  		//read removed employee file and load into struct UserDetails r
  		void LoadResignEmployee();
  		
  		//save salary into file based on the working hour from schedule
  		void saveSalary();
		
		//read salary from file and load to struct UserDetails s
		void loadSalaryfile();
				
		//save clock in timing into file with current time
		void saveClockingfile(int i,int j)
		{
			ofstream clockFile("clocking_file.txt", ios::app);
	        if (clockFile.is_open()) 
			{
				clocking[total_clock].ID = s[i].ID;
	            clockFile << "ID :" << s[i].ID << endl;
	            clockFile << "Role :" << schedule[j].role << endl;
	            clockFile << "Clock In Date :" << getCurrentDate() << " (" << getDayOfWeek2() << ")" << endl;
	            clockFile << "Clock In Time :" << getCurrentTime() << endl;
	            total_clock++;
	            clockFile.close();
	            
	            cout<<"====================================="<<endl;
	            cout<<"          Clock in record"<<endl;
	            cout<<"====================================="<<endl;
	            cout << "\nID: " << s[i].ID << endl;
	            cout << "Role: " << schedule[j].role << endl;
	            cout << "Clock In Date: " << getCurrentDate() << " (" << getDayOfWeek2() << ")" << endl;
	            cout << "Clock In Time: " << getCurrentTime() << endl;
	            cout << "\nClock In recorded successfully." << endl<<endl;        
	        } 
			else 
			{
	            cerr << "Unable to open clocking_file.txt for writing." << endl;
	        }
		}
		
		//save clock out timing into file with current time 
		void saveClockingfile2(int i, int j)
		{
			ofstream clockFile("clock_out_file.txt", ios::app);
	        if (clockFile.is_open()) 
			{
				clockout[total_clock_out].ID = s[i].ID;
				clockout[total_clock_out].fulldate = getCurrentDate() + " (" + getDayOfWeek2() + ")";
	            clockFile << "ID :" << clockout[total_clock_out].ID << endl;
	            clockFile << "Role :" << schedule[j].role << endl;
	            clockFile << "Clock Out Date :" << getCurrentDate() << " (" << getDayOfWeek2() << ")" << endl;
	            clockFile << "Clock Out Time :" << getCurrentTime() << endl;
	            total_clock_out++;
	            clockFile.close();
	            
	            cout<<"====================================="<<endl;
	            cout<<"          Clock out record"<<endl;
	            cout<<"====================================="<<endl;
	            cout << "\nID: " << s[i].ID << endl;
	            cout << "Role: " << schedule[j].role << endl;
	            cout << "Clock Out Date: " << getCurrentDate() << " (" << getDayOfWeek2() << ")" << endl;
	            cout << "Clock Out Time: " << getCurrentTime() << endl;
	            cout << "\nClock Out recorded successfully." << endl<<endl;       
	        }
			else 
			{
	            cerr << "Unable to open clocking_file.txt for writing." << endl;
	        }
		}
		
		//read clock out file and load into struct UserDetails clockout
		void loadClockingfile2()
		{
			string line, key;
	        int i=0;
	        
		    ifstream file5;
		    file5.open("clock_out_file.txt");
		
		    while (getline(file5, line)) 
			{
		        istringstream ss(line);
		        getline(ss, key, ':');
				
				if (key == "ID ")
				{
		            ss >> clockout[i].ID;
		        } 
				else if (key == "Role ") 
				{
		            ss >> clockout[i].role;
		        }
		        else if (key == "Clock Out Date ") 
				{
		            getline(ss, clockout[i].fulldate);
		        }     
				else if (key == "Clock Out Time ") 
				{
		            ss >> clockout[i].ClockOut_time;
		            i++;
		        }
		    }
		    total_clock_out = i;
		}
		
		//read clock in file and load into struct UserDetails clocking
		void loadClockingfile()
		{
			string line, key;
	        int i=0;
	        
		    ifstream file5;
		    file5.open("clocking_file.txt");
		
		    while (getline(file5, line)) 
			{
		        istringstream ss(line);
		        getline(ss, key, ':');
				
				if (key == "ID ")
				{
		            ss >> clocking[i].ID;
		        } 
				else if (key == "Role ") 
				{
		            ss >> clocking[i].role;
		        }
		        else if (key == "Clock In Date ") 
				{
		            getline(ss, clocking[i].fulldate);
		        }     
				else if (key == "Clock In Time ") 
				{
		            ss >> clocking[i].ClockIn_time;
		            i++;
		        }
		    }
		    total_clock = i;
		}
		
		//Use to make ascending order when display schedule
		bool compareByDate(const UserDetails &a, const UserDetails &b)
		{
		    if (a.month < b.month) 
			{
		        return true;
		    }
			else if (a.month == b.month) 
			{
		        return a.date < b.date;
		    }
		    return false;
		}
		
		//To check whether the date is weekday or weekend
		bool isWeekend(int day, int month, int year)
		{
		    tm timeinfo = {0, 0, 0, day, month - 1, year - 1900};
		    mktime(&timeinfo);
		    
		    return (timeinfo.tm_wday == 0 || timeinfo.tm_wday == 6); // 0 is Sunday, 6 is Saturday
		}
		
		//To check the date is which day and return the day
		string getDayOfWeek(int i,int m, int Date[])
		{
			int month = m;
	        // Set the date
	        tm date = {};
	        date.tm_mday = Date[i];        // Selected date
	        date.tm_mon = month - 1;      // January (month is 0-indexed)
	        date.tm_year = 2024 - 1900;  // Year 2024
	
	        // Use mktime to convert the tm structure to time_t
	        time_t time = mktime(&date);
	
	        // Use localtime to get a tm structure for the specified time
	        tm* date_info = localtime(&time);
	
	        // Array of days of the week
	        const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};  
	        
		    return days[date_info->tm_wday];
		}
		
		//return current full date like 23 Jan 2024 (Tuesday)
		string getCurrentDate() 
		{
	        time_t now = time(0);
	        tm *currentTime = localtime(&now);
	        char date[20];
	        sprintf(date, "%02d %s %d", currentTime->tm_mday, getMonthName(currentTime->tm_mon).c_str(), currentTime->tm_year + 1900);
	        return date;
	    }
	    
	    //return current date number
	    int getCurrentDateNum()
	    {
	    	time_t now = time(0);
	        tm *currentTime = localtime(&now);
	        return currentTime->tm_mday;
		}
		
		//return current month number
		int getCurrentMonthNum()
	    {
	    	time_t now = time(0);
	        tm *currentTime = localtime(&now);
	        return currentTime->tm_mon;
		}
		
		//return current time
	    string getCurrentTime() 
		{
	        time_t now = time(0);
	        tm *currentTime = localtime(&now);
	        char time[10];
	        sprintf(time, "%02d:%02d:%02d", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
	        return time;
	    }
		
		//based on month number to return month name
	    string getMonthName(int month) 
		{
	        const char *monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	                                    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	        return monthNames[month];
	    }
	    
	    //return day depend on the current date
	    string getDayOfWeek2() 
		{
	        const char *dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	        time_t now = time(0);
	        tm *currentTime = localtime(&now);
	        return dayNames[currentTime->tm_wday];
	    }
		
  		//return total employee number
  		int GetTotalEmployee()
  		{
  			return total_emp;
		}
		
		//return total removed employee number
		int GetTotal_resign_emp()
		{
			return total_resign_emp;
		}
		
		//return total schedule number
		int GetTotal_schedule()
		{
			return total_schedule;
		}
		
		//return total clock in number
		int GetTotal_clock()
		{
			return total_clock;
		}
		
		//return total clock out number
		int GetTotal_clock_out()
		{
			return total_clock_out;
		}
};

//save schedule file with new schedule 
void file :: saveSchedule()
{
    ofstream file3("schedule.txt", ios::out | ios::trunc); // Open in truncation mode
    if (file3.is_open())
    {
    	total_schedule++; 
        for (int j = 0; j < total_schedule; j++)
        {
            file3 << "ID:"         << schedule[j].ID << endl;
            file3 << "Month:"      << schedule[j].month << endl;
            file3 << "Date:"       << schedule[j].date << endl;
            file3 << "Role:"       << schedule[j].role << endl;
            file3 << "Start Time:" << schedule[j].startTime << endl;
            file3 << "End Time:"   << schedule[j].endTime << endl << endl;
        }
    }
    else
    {
        cout << "Unable to open the file." << endl;
    }
    file3.close(); // Close the file
}

//save schedule file after edit, the total schedule unchanged
void file :: saveSchedule2()
{
    ofstream file3("schedule.txt", ios::out | ios::trunc); // Open in truncation mode
    if (file3.is_open())
    {
        for (int j = 0; j < total_schedule; j++)
        {
            file3 << "ID:"         << schedule[j].ID << endl;
            file3 << "Month:"      << schedule[j].month << endl;
            file3 << "Date:"       << schedule[j].date << endl;
            file3 << "Role:"       << schedule[j].role << endl;
            file3 << "Start Time:" << schedule[j].startTime << endl;
            file3 << "End Time:"   << schedule[j].endTime << endl << endl;
        }
    }
    else
    {
        cout << "Unable to open the file." << endl;
    }
    file3.close(); // Close the file
}

//save schedule with delete one of the schedule by delete function
void file :: saveSchedule3()
{
    ofstream file3("schedule.txt", ios::out | ios::trunc); // Open in truncation mode
    if (file3.is_open())
    {
    	total_schedule--;
        for (int j = 0; j < total_schedule; j++)
        {
            file3 << "ID:"         << schedule[j].ID << endl;
            file3 << "Month:"      << schedule[j].month << endl;
            file3 << "Date:"       << schedule[j].date << endl;
            file3 << "Role:"       << schedule[j].role << endl;
            file3 << "Start Time:" << schedule[j].startTime << endl;
            file3 << "End Time:"   << schedule[j].endTime << endl << endl;
        }
    }
    else
    {
        cout << "Unable to open the file." << endl;
    }
    file3.close(); // Close the file
}

//read the schedule file and load into struct UserDetails schedule
void file :: loadSchedule()
{
	string line, key;
    int i=0;
    
    ifstream file3;
    file3.open("schedule.txt");

    while (getline(file3, line)) 
	{
        istringstream ss(line);
        getline(ss, key, ':');

		if (key == "ID") 
		{
            getline(ss, schedule[i].ID);
        }
        else if (key == "Role") 
		{
            getline(ss, schedule[i].role);
        } 
		else if (key == "Start Time") 
		{
            getline(ss, schedule[i].startTime);
        }
        else if (key == "Date") 
		{
            ss >> schedule[i].date;
        }
        else if (key == "Month") 
		{
            ss >> schedule[i].month;
        }
        else if (key == "End Time") 
		{
            getline(ss, schedule[i].endTime);
            i++; 
        }
        
    }
    total_schedule = i;
}

//save new employee details into file
void file :: SaveToFile() 
{
    ofstream file("employee.txt", ios::app); // Open the file in append mode
    if (file.is_open()) 
    {
        // Write employee details to the file
        file << "ID:" << s[total_emp].ID << endl;
        file << "Name:" << s[total_emp].name << endl;
        file << "Password:" << s[total_emp].pw << endl;
        file << "Contact:" << s[total_emp].contact << endl;
        file << "Email:" << s[total_emp].email << endl << endl; // Add an extra newline for better readability
        total_emp++;
    } 
    else
    {
        cout << "Unable to open the file." << endl;
    }
    file.close(); // Close the file
}

//save employee details after editing, total employee number unchanged
void file :: SaveToFile2()
{
    ofstream file("employee.txt", ios::out | ios::trunc);
    if(file.is_open())
	{
		for(int i=0;i<total_emp;i++)
		{
		// Write employee details to the file
        file << "ID:" << s[i].ID << endl;
        file << "Name:" << s[i].name << endl;
        file << "Password:" << s[i].pw << endl;
        file << "Contact:" << s[i].contact << endl;
        file << "Email:" << s[i].email << endl << endl; // Add an extra newline for better readability
        }
	}
	else
    {
        cout << "Unable to open the file." << endl;
    }
    file.close(); // Close the file
}

//save employee details when remove the selecting employee
void file :: SaveToFile3()
{
	ofstream file("employee.txt", ios::out | ios::trunc);
	if(file.is_open())
	{
		total_emp--;
		for(int i=0;i<total_emp;i++)
		{
		// Write employee details to the file
        file << "ID:" << s[i].ID << endl;
        file << "Name:" << s[i].name << endl;
        file << "Password:" << s[i].pw << endl;
        file << "Contact:" << s[i].contact << endl;
        file << "Email:" << s[i].email << endl << endl; // Add an extra newline for better readability
        }
	}
	else
    {
        cout << "Unable to open the file." << endl;
    }
    file.close(); // Close the file
}

//save removed employee to this file
void file :: SaveToResignFile(int i)
{
	ofstream ResignFile("ResignEmployee.txt", ios::app);
	if (ResignFile.is_open()) 
    {
        // Write resign employee details to the file
        ResignFile << "ID:" << s[i].ID << endl;
        ResignFile << "Name:" << s[i].name << endl;
        ResignFile << "Password:" << s[i].pw << endl;
        ResignFile << "Contact:" << s[i].contact << endl;
        ResignFile << "Email:" << s[i].email << endl << endl; // Add an extra newline for better readability

        total_resign_emp++;
    } 
    else
    {
        cout << "Unable to open the file." << endl;
    }
    ResignFile.close(); // Close the file
}

//read employee file and load into struct UserDetails s
void file :: LoadFromFile() 
{
    string line, key;
    int i = 0;
    total_emp = 0;
    
    ifstream file;
    file.open("employee.txt");

    if (!file) 
	{
        cout << "Error opening file!" << endl;
        exit(0);
    }

    while (getline(file, line)) //reads each line from the file until the end of the file is reached
	{	
		//creates an input string stream obejct 'ss' to process the current line
        istringstream ss(line);

		//parses the line using ':' as a delimeter and stores the key part in the 'key' variable
        //delimeter: marks the boundaries between separate, independent regions of data in a sequence
		getline(ss, key, ':');

		//check the value of 'key' and assigns the corresponding value to the appropriate member of the 'UserDetails' struct 's[i]'		
        if (key == "Password") 
		{
            getline(ss, s[i].pw); //reads the value into s[i].pw
        } 
		else if (key == "Name") 
		{
            getline(ss, s[i].name);
        }
        else if (key == "Email") 
		{
            getline(ss, s[i].email);
            i++;
            total_emp++;
        }
        else if (key == "Contact") 
		{
            getline(ss, s[i].contact);
        }
        else if (key == "ID") 
		{
            getline(ss, s[i].ID);
        }
    }

}

//read removed employee file and load into struct UserDetails r
void file :: LoadResignEmployee()
{
    string line, key;
    int i = 0;
    
    ifstream ResignFile;
    ResignFile.open("ResignEmployee.txt");

    while (getline(ResignFile, line)) 
	{
        istringstream ss(line);
        getline(ss, key, ':');

		
        if (key == "Password") 
		{
            getline(ss, r[i].pw);
        } 
		else if (key == "Name") 
		{
            getline(ss, r[i].name);
        }
        else if (key == "Email") 
		{
            getline(ss, r[i].email);
            i++;
        }
        else if (key == "Contact") 
		{
            getline(ss, r[i].contact);
        }
        else if (key == "ID") 
		{
            getline(ss, r[i].ID);
        }
    }
    total_resign_emp=i;
}

//save salary into file based on the working hour from schedule
void file :: saveSalary()
{
	ofstream file4("Salary.txt",ios::out | ios::trunc);
	
	//reset the monthly hour
	for(int i=0;i<total_emp;i++)
	{
		for(int j=0;j<12;j++)
		{
			s[i].monthly_hour[j] = 0;
		}
	}
	for (int i = 0; i < total_emp; i++) 
	{
        s[i].total_hour = 0; // Initialize total hours for each employee

        for (int j = 0; j < total_schedule; j++) 
		{
            for (int k = 0; k < 12; k++) 
			{
                if (schedule[j].ID == s[i].ID && schedule[j].month == 1 + k) 
				{
                    stringstream ed(schedule[j].endTime);
                    stringstream st(schedule[j].startTime);
                    int start, end;
                    ed >> end;
                    st >> start;

                    float HourPerDay = (end / 100.0) - (start / 100.0);

                    // Accumulate total hours and monthly hours for the current employee
                    s[i].total_hour += HourPerDay;
                    s[i].monthly_hour[k] += HourPerDay;
                    break; // Remove this break statement if you want to process all schedules for the month
                }
            }
        }
    }
    
	for (int i = 0; i < total_emp; i++) 
	{
	    file4 << "Total hours:" << s[i].total_hour << endl;
	
	    for (int month = 0; month < 12; month++) 
		{
	        file4 << "Month hours:" << s[i].monthly_hour[month] << endl;
	    }
	
	    for (int month = 0; month < 12; month++) 
		{
	        if(s[i].monthly_hour[month] < 180)
	        {
	        	s[i].monthly_salary[month] = s[i].monthly_hour[month] * hourlyRate;
			}
			else
			{
				hourlyRate = 12;
				s[i].monthly_salary[month] = BasicSalary + ((s[i].monthly_hour[month] - 180) * hourlyRate);
			}
	        file4 << "Month Salary:" << s[i].monthly_salary[month] << endl;
	    }
	
	    // Output a separator line between employee entries
	    file4 << "====================" << endl;
	}

	file4.close();
	
}

//read salary from file and load to struct UserDetails
void file :: loadSalaryfile()
{
	string line, key;
    int i=0,month =0,month2=0;
    
    ifstream file4;
    file4.open("Salary.txt");

    while (getline(file4, line)) 
	{
        istringstream ss(line);
        getline(ss, key, ':');
		
		if (key == "Total hours")
		{
            ss >> s[i].total_hour;
            month = 0;
            month2 = 0;
        } 
		else if (key == "Month hours") 
		{
            ss >> s[i].monthly_hour[month];
            month++;
        }
        else if (key == "Month Salary") 
		{
            ss >> s[i].monthly_salary[month2];
            month2++;
            if(month2 == 12)
            {
            	i++;
			}
        }        
    }
}

//inheritance from class file
class Admin : public file
{
	private:
		string name, contact, password, email,ID,role,startTime,endTime;
		int choice,i;
		int total_emp, total_resign_emp, total_schedule;
		float total_salary;
		float total_hour;
		float HourPerDay;
		float hourlyRate;
		
	public:
		// Constructor to set initial values
		Admin() : startTime("0900"), endTime("1800") {}
		
		// Destructor
		~Admin()
		{
			cout<<"Have a nice day!"<<endl;
		}
		
		//friend function
		friend void interface();
		
		void Admin_login()
		{
			string Admin_ID;
			bool valid = true;
			system("CLS");
			cout<<"============================================================"<<endl;
			cout<<"\t             Admin Login"<<endl;
			cout<<"============================================================"<<endl;
			do
			{
				fflush(stdin);
				cout<<"Enter Admin ID : ";
				getline(cin,Admin_ID);
				
				if(Admin_ID == "1221204416" || Admin_ID == "1221205257" || Admin_ID == "1221204572" || Admin_ID == "1221204995")
				{
					LoadFromFile();
					LoadResignEmployee();
					loadSchedule();
					loadSalaryfile();
					loadClockingfile();
					loadClockingfile2();
					valid = false;
					cout << ("\nLogin successful") << endl;
					system("pause");
					system("CLS");
			        display();
				}
				else if (Admin_ID == "back") //back to interface based on user need
				{
					return;
				}
				else
				{
			    	cout<<"\nIncorrect Admin ID, please try again. (Enter 'back' in ID will back to main menu)"<<endl;
				}
			}while(valid);
		}
		
		
		void display()
		{
			int choice;
			
			total_emp = GetTotalEmployee();
			total_resign_emp = GetTotal_resign_emp();
			total_schedule = GetTotal_schedule();
			cout<<"=================================================="<<endl;
			cout<<"                 Menu"<<endl;
			cout<<"=================================================="<<endl;
			cout<<"1. Adding new employee"<<endl;
			cout<<"2. Update employee details"<<endl;
			cout<<"3. Employee list"<<endl;
			cout<<"4. Assign work to employees"<<endl;
			cout<<"5. Edit schedule"<<endl;
			cout<<"6. Display Working Schedule"<<endl;
			cout<<"7. Check working hours & salary"<<endl;
			cout<<"8. Clocking timing"<<endl;
			cout<<"9. Logout"<<endl;
			do
			{
				cout<<"\nEnter your choice : ";
				cin>>choice;
				switch(choice)
				{
					case 1:
						AddEmployee();
						break;
					case 2:
						EditEmployee();
						break;
					case 3:
						Employee_list();
						break;
					case 4:
						AddSchedule();
						break;
					case 5:
						editSchedule();
						break;
					case 6:
						displaySchedule();
						break;
					case 7:
						displayWorkingHoursAndSalary();		
						break;
					case 8:
						ClockingMenu();
						break;
					case 9:
						return;
					default:
						cout<<"\nInvalid value! Please re-enter your choice !"<<endl;
				}
			}while(choice > 9 || choice < 1);
		}
		
		void AddEmployee()
		{
			char choice;
			bool valid=0;
			
			ID = GetEmployeeID();

			fflush(stdin);
			cout<<"Enter New employee name : ";
			getline(cin,name);
			cout<<"Enter New employee password : ";
			getline(cin,password);
			
			do
		    {
		    	valid = 1;
		        fflush(stdin);
		        cout << "Enter New employee contact number: ";
		        getline(cin, contact);
		
		        // Validate contact
		        for (int i = 0; i < total_emp; ++i)
		        {
		            if (s[i].contact == contact)
		            {
		                cout << "Contact already exists. Please enter another contact." << endl;
		                valid = 0;
		                break;
			        }
			    }
			} while (valid == 0);
				
			
		    do
		    {
		    	valid = 1;
		        cout << "Enter New employee email : ";
		        getline(cin, email);
		
		        // Validate email
		        for (int i = 0; i < total_emp; ++i)
		        {
		            if (s[i].email == email)
		            {
		                cout << "\nEmail already exists. Please enter another email." << endl <<endl;
		                valid = 0;
		                break;
		            }
		        }
		    } while (valid == 0);

			
			do
			{
				cout<< "==============================================================================================================" << endl;
			    cout<< "| No. | ID   | Employee                    | Password             | Contact       | Email                    |" << endl;
			    cout<< "--------------------------------------------------------------------------------------------------------------" << endl;
		        cout<< "| " << setw(4)  << left << "1"
		       		<< "| " << setw(5)  << left << ID
		            << "| " << setw(28) << left << name
		            << "| " << setw(21) << left << password
		            << "| " << setw(14) << left << contact
		            << "| " << setw(25) << left << email
		            << "| " << endl;
			    cout<< "==============================================================================================================" << endl<<endl;
				cout<<"Confirmation [Y|N] : ";
				cin>>choice;
				if(choice == 'y'|| choice == 'Y')
				{
				s[total_emp].ID = ID;
				s[total_emp].name = name;
				s[total_emp].pw = password;
				s[total_emp].contact = contact;
				s[total_emp].email = email;
				
				SaveToFile();
				cout << "\n---Employee successfully added---." << endl<<endl;
				system("pause");
				system("CLS");
				display();
				}
				else if(choice == 'n'|| choice == 'N')
				{
					cout<<"---Employee creation cancelled---"<<endl;
					system("pause");
					system("CLS");
					display();
				}
				else
				{
					cout<<"Invalid input"<<endl;
				}
			}while(choice != 'y'&& choice != 'Y' && choice != 'n' && choice != 'N');

		}
		
		
		void EditEmployee()
		{
			bool valid=0;
			int choice,i;
			string confirmation;
			char choice2;
			cout << "\n========================================" << endl;
		    cout << "| No | ID    | Employee                |" << endl;
		    cout << "========================================" << endl;
			for(int i=0;i<total_emp;i++)
			{
				cout<<"| " << setw(3) << left<< i+1<< "| " << setw(5) << left << s[i].ID <<" |" << setw(24) << left << s[i].name<<" |"<<endl;
				cout<<"----------------------------------------"<<endl;
			}
			
			do
			{
				fflush(stdin);
				cout<<"\nEnter employee ID for edit (Enter 'back' to menu) : ";
				getline(cin,ID);
				for(i=0;i<total_emp;i++)
				{
					if(ID == s[i].ID)
					{
						valid = 1;
						break;
					}
					else if(ID == "back")
					{
						display();
						return;
					}
				}
				if(!valid)
				{
					cout<<"No employee was found."<<endl<<endl;
				}
			}while(!valid);
			
			if(valid)
			{
				cout<< "\n==============================================================================================================" << endl;
			    cout<< "| No. | ID   | Employee                    | Password             | Contact       | Email                    |" << endl;
			    cout<< "--------------------------------------------------------------------------------------------------------------" << endl;
		        cout<< "| " << setw(4)  << left << i+1
		       		<< "| " << setw(5)  << left << s[i].ID
		            << "| " << setw(28) << left << s[i].name
		            << "| " << setw(21) << left << s[i].pw
		            << "| " << setw(14) << left << s[i].contact
		            << "| " << setw(25) << left << s[i].email
		            << "| " << endl;
			    cout<< "==============================================================================================================" << endl<<endl;
			    cout<<"1. Name"<<endl;
			    cout<<"2. Password"<<endl;
			    cout<<"3. Contact Number"<<endl;
			    cout<<"4. Email"<<endl;
			    cout<<"5. Remove employee"<<endl;
			    cout<<"6. Back"<<endl;
			    do
			    {
				    cout<<"Enter your choice (eg, '2'): ";
				    cin>>choice;
				    if(choice == 1)
				    {
				    	fflush(stdin); 
				    	cout<<"\nEnter New name : ";
				    	getline(cin,s[i].name);
					}
					else if(choice == 2)
				    {
				    	fflush(stdin); 
				    	cout<<"\nEnter New password : ";
				    	getline(cin,s[i].pw);
					}
					else if(choice == 3)
				    {
				    	fflush(stdin); 
				    	cout<<"\nEnter New contact number : ";
				    	getline(cin,s[i].contact);
					}
					else if(choice == 4)
				    {
				    	fflush(stdin);
				    	cout<<"\nEnter New email : ";
				    	getline(cin,s[i].email);
					}
					else if(choice == 5)
				    {
				    	do
						{
					    	fflush(stdin);
					    	cout<<"Enter 'yes' to confirm remove the employee  ("<<s[i].ID<<") or 'no' back to menu: ";
					    	getline(cin,confirmation);
						    
						    for (size_t j = 0; j < confirmation.length(); ++j) 
							{
						        confirmation[j] = tolower(confirmation[j]);
						    }
						    
					    	if(confirmation == "yes")
					    	{
					    		SaveToResignFile(i);
					    		for(i;i<total_emp-1;i++)
					    		{
					    			s[i] = s[i+1];
								}
								total_emp--;
								SaveToFile3();
								cout<<"\n--- Employee had removed ---"<<endl<<endl;
								system("pause");
								system("CLS");
								display();
								return;
								
							}
							else if(confirmation == "no")
							{
								cout<<"\n---Cancel removing the employee---"<<endl<<endl;
								system("pause");
								system("CLS");
								display();
								return;
							}
							else
							{
								cout<<"Invalid input"<<endl;
							}
						}while(confirmation !="yes" && confirmation != "no");
					}
					else if(choice == 6)
					{
						display();
						return;
					}
					else
					{
						cout<<"Invalid selection, please try again."<<endl<<endl;
					}
				}while(choice > 6 || choice < 1);
				
				cout<<"Enter Y for confirmation or N back to menu : ";
				cin>>choice2;
				if(choice2 == 'y' || choice2 == 'Y')
				{
					SaveToFile2();
					cout << "\nEmployee details updated." << endl<<endl;
    				system("pause"); // Keeps the console window open
    				system("CLS");
					display();
				}
				else if(choice2 == 'n' || choice2 == 'N')
				{
					display();
				}
				else
				{
					cout<<"Invalid input, please try again.";
				}
			}
		}
		
		void Employee_list() 
		{
			int i;
		    cout << "==============================================================================================================" << endl;
		    cout << setw(74) << left<<"\t\t\t\t\tEmployee List" << "|"<<endl;
		    cout << "==============================================================================================================" << endl;
		    cout << "| No. | ID   | Employee                    | Password             | Contact       | Email                    |" << endl;
		    cout << "==============================================================================================================" << endl;
		
		    for (i = 0; i < total_emp; i++) 
			{
		        cout << "| " << setw(4)  << left << i+1
		       		 << "| " << setw(5)  << left << s[i].ID
		             << "| " << setw(28) << left << s[i].name
		             << "| " << setw(21) << left << s[i].pw
		             << "| " << setw(14) << left << s[i].contact
		             << "| " << setw(25) << left << s[i].email
		             << "| " << endl;           
		        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
		    }
		    cout << "==============================================================================================================" << endl<<endl;
		    system("pause");
			system("CLS");
		    display();
		}
		
	    string GetEmployeeID()
		{
        stringstream ss;
        ss << "E" << setw(3) << setfill('0') << total_emp + total_resign_emp + 1; // Format the employee number
        return ss.str();
   		}
   		
   		void setRole()
   		{
   			for(int i=0;i<total_emp;i++)
   			{
	   			if (s[i].role != "Producer" && s[i].role != "Packer")
	   			{
	   				s[i].role = "None";
	   				s[i].startTime = "0";
					s[i].endTime = "0";
				}
			}
		}
		
   		void AddSchedule()
		{
		    bool valid;
		    string role;
		    char choice;
		    int selection, i, month, date,date1,maxDays;
		    setRole();
		    
		    	
			cout << "\n========================================" << endl;
		    cout << "| No | ID    | Employee                |" << endl;
		    cout << "========================================" << endl;
			for(int i=0;i<total_emp;i++)
			{
				cout<<"| " << setw(3) << left<< i+1<< "| " << setw(5) << left << s[i].ID <<" |" << setw(24) << left << s[i].name<<" |"<<endl;
				cout<<"----------------------------------------"<<endl;
			}
			
			do{
				fflush(stdin);
				cout << "\nEnter employee ID to assign position (Enter 'back to menu') : ";
			    getline(cin,ID);
			    
			    if(ID == "back")
			    {
			    	display();
			    	return;
				}
			
			    for (i = 0; i < total_emp; i++)
			    {
			        if (ID == s[i].ID)
			        {
			            valid = 1;
			            break;
			        }
			        else
			        {
			            valid = 0;
			        }
			    }
			
			    if (valid)
			    {
			    	do
			    	{
				        cout << "\nSelect month (1-12) : ";
				        cin >> month;
				
				        switch (month)
				        {
					        case 1:
					        case 3:
					        case 5:
					        case 7:
					        case 8:
					        case 10:
					        case 12:
					            maxDays = 31;
					            break;
					        case 4:
					        case 6:
					        case 9:
					        case 11:
					            maxDays = 30;
					            break;
					        case 2:
					            maxDays = 28;
					            break;
					        default:
					            cout << "Invalid month. Please enter a value between 1 and 12." << endl;
					    }
				    }while(month < 1 || month > 12);
					
					do
					{
				        cout << "\nEnter date (1-" << maxDays << ") : ";
				        cin >> date;
				        date1 = date;
				
				        if (date < 1 || date > maxDays)
				        {
				            cout << "Invalid date. Please enter a value between 1 and " << maxDays << "." << endl;
				        }
			        }while(date < 1 || date > maxDays);
			        
			        for(int j=0;j<total_schedule;j++)
					{
						if(s[i].ID == schedule[j].ID && date1 == schedule[j].date && month == schedule[j].month)
						{
							cout<<"\nEmployee already assigned work on the day"<<endl<< endl;
							system("pause");
							system("CLS");
							display();
							return;
						}
					}
					
					// Convert input to tm structure
				    tm dateStruct = {0, 0, 0, date, month - 1, 2024 - 1900}; // Month is 0-indexed
				
				    // Convert tm structure to time_t
				    time_t date = mktime(&dateStruct);
				
				    // Convert time_t to tm structure to get the day of the week
				    tm* dateInfo = localtime(&date);
				
				    // Array to store day names
				    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
					cout << "\n== Role selection =="<<endl;
			        cout << "1. Producer" << endl;
			        cout << "2. Packer" << endl;
					do
					{
						cout << "\nSelect the position [1 or 2]: ";
			        	cin >> selection;
						if (selection == 1)
				        {
				            role = "Producer";
				        }
				        else if (selection == 2)
				        {
				            role = "Packer";
				        }
				        else
				        {
				            cout << "Invalid selection." << endl;
				        }
					}while(selection != 1 && selection != 2);   
			        
			        stringstream dateStream;
					dateStream << date1 << "/" << month << "/2024 " << "(" << days[dateInfo->tm_wday] << ")";
			        cout << "\n===============================================================================" << endl;
			        cout << "| No. | ID   | Employee                    | Role      | Day                  |"<< endl;
			        cout << "-------------------------------------------------------------------------------" << endl;
			        cout << "| " << setw(4) << left << i + 1
			             << "| " << setw(5) << left << s[i].ID
			             << "| " << setw(28) << left << s[i].name
			             << "| " << setw(10) << left << role
						 << "| " << setw(21) << left << dateStream.str()
			             << "| " << endl;
			        cout << "===============================================================================" << endl
			             << endl;
			        do
			        {
			        	cout<<"Enter y to confirm schedule or n to cancel schedule : ";
			    		cin>>choice;
			    	
			    		if(choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y')
			    		{
			    			cout<<"Invalid input, please enter y or n."<<endl;
						}
						
						if(choice == 'Y' || choice == 'y')
						{
							break;
						}
						
						if(choice == 'n' || choice == 'N')
						{
							cout<<"\nschedule cancelled."<<endl<<endl;
							system("pause");
							system("CLS");
							display();
							return;
						}
					}while(choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
			    	
			        
			        schedule[total_schedule].ID = ID;
			        schedule[total_schedule].startTime = startTime;
			        schedule[total_schedule].endTime = endTime;
			        schedule[total_schedule].role = role;
			        schedule[total_schedule].month = month;
			        schedule[total_schedule].date = date1;
			        
			        saveSchedule();
					saveSalary();
			        cout << "\nSuccessfully scheduled." << endl << endl;
			        system("pause");
					system("CLS");
			        display();
			        
			    }
			    else
			    {
			        cout << "No employee was found. (Enter 'back to menu')" << endl;
			    }
			}while(!valid);
		}
		
		
		void editSchedule()
		{
			cout<<"=================================================="<<endl;
			cout<<"                 Edit Schedule"<<endl;
			cout<<"=================================================="<<endl;
			cout<<"1. update schedule"<<endl;
			cout<<"2. remove schedule"<<endl;
			cout<<"3. back"<<endl;
			do
			{
				cout<<"\nEnter your choice : ";
				cin>>choice;
				switch(choice)
				{
					case 1:
						UpdateSchedule();
						break;
					case 2:
						RemoveSchedule();
						break;
					case 3:
						system("CLS");
						display();
						break;
					default:
						cout<<"Invalid value!"<<endl;
				}
			}while(choice > 3 || choice < 1);
			
		}

		void UpdateSchedule()
		{
			int array[100],i,j=0,k,month,num,selection;
			char choice;
			bool valid=0;
			
			cout << "\n========================================" << endl;
		    cout << "| No | ID    | Employee                |" << endl;
		    cout << "========================================" << endl;
			for(int i=0;i<total_emp;i++)
			{
				cout<<"| " << setw(3) << left<< i+1<< "| " << setw(5) << left << s[i].ID <<" |" << setw(24) << left << s[i].name<<" |"<<endl;
				cout<<"----------------------------------------"<<endl;
			}
			do
			{
				fflush(stdin);
				cout<<"\nEnter employee ID (enter back to menu): ";
				getline(cin,ID);
				if(ID == "back")
				{
					editSchedule();
					return;
				}
				for(k=0;k<total_emp;k++)
				{
					if(ID == s[k].ID)
					{
						valid = 1;
						break;
					}
				}
				if(!valid)
				{
					cout<<"no employee was found."<<endl;
				}
			}while(!valid);
			
			do
			{
				cout<<"Enter the month to check schedule: ";
				cin>>month;
				
				if(month<1 || month >12)
				{
					cout<<"Invalid input, please enter input within 1 - 12.";
				}
			}while(month<1 || month >12);

			cout << "\n=======================================================================" << endl;
		    cout << "\t\t   Schedule for "<<s[k].name <<" ("<< s[k].ID << ") \t\t      " << endl;
		    cout << "=======================================================================" << endl;
		    cout << "| No | Date          | Role           | Start Time    | End Time      |" << endl;
		    cout << "=======================================================================" << endl;
			for (int i = 0; i < total_schedule; i++) 
			{
			    for (int j = i + 1; j < total_schedule; j++) 
				{
			        if (!compareByDate(schedule[i], schedule[j])) 
					{
			            UserDetails temp = schedule[i];
			            schedule[i] = schedule[j];
			            schedule[j] = temp;
			        }
			    }
			}
		    for(int i=0;i<total_schedule;i++)
		    {
		    	stringstream dateStream;
				dateStream << schedule[i].date << "/" << schedule[i].month << "/2024";
		        if(ID == schedule[i].ID && month == schedule[i].month)
		        {
		        	array[j] = i;
		        	j++;        	
		            cout << "| " << setw(3) << left << j << "| "
		                 << setw(13) << left << dateStream.str() << " |  "
		                 << setw(14) << left << schedule[i].role << "| "
		                 << setw(14) << left << schedule[i].startTime << "| "
		                 << setw(14) << left << schedule[i].endTime << "|" << endl;
		            cout << "-----------------------------------------------------------------------" << endl;
		        }
		    }
		    if(j == 0)
		    {
		    	cout<<"No schedule was found in this month"<<endl;
		    	editSchedule();
		    	return;
			}
			
			do
			{
				cout<<"Enter the number of schedule to edit : ";
				cin>>num;
				if(num < 1 || num > j)
				{
					cout<<"Please enter number between 1 to "<<j<<"."<<endl<<endl;
				}
			}while(num < 1 || num > j);
			num--;
			
			cout << "\n== Role selection =="<<endl;
			cout << "1. Producer" << endl;
	        cout << "2. Packer" << endl;
			do
			{
		        cout << "\nSelect the position [1 or 2]: ";
		        cin >> selection;
				if (selection == 1)
		        {
		            role = "Producer";
		        }
		        else if (selection == 2)
		        {
		            role = "Packer";
		        }
		        else
		        {
		            cout << "\nInvalid selection." << endl<<endl;
		        }
			}while(selection != 1 && selection != 2);
			
			fflush(stdin);
			cout<<"Enter start time (e.g. 0900) : ";
			getline(cin,startTime);
			
			cout<<"Enter end time (e.g. 1800) : ";
			getline(cin,endTime);
		    
		    tm dateStruct = {0, 0, 0, schedule[array[num]].date, schedule[array[num]].month - 1, 2024 - 1900}; // Month is 0-indexed	
		    // Convert tm structure to time_t
		    time_t date = mktime(&dateStruct);
		    // Convert time_t to tm structure to get the day of the week
		    tm* dateInfo = localtime(&date);
		    // Array to store day names
		    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
		    
			cout << "==========================================================================================" << endl;
	        cout << "| ID   | Employee                    | Role      |  Start Time  |  End Time  | Day       |"<< endl;
	        cout << "==========================================================================================" << endl;
	        cout << "| " << setw(5) << left << schedule[array[num]].ID
	             << "| " << setw(28) << left << s[k].name
	             << "| " << setw(10) << left << role
	             << "| " << setw(13) << left << startTime
	             << "| " << setw(11) << left << endTime
				 << "| " << setw(10) << left << days[dateInfo->tm_wday]
	             << "| " << endl;
	        cout << "==========================================================================================" << endl
	             << endl;
	        do
	        {
	        	cout<<"Enter y to confirm schedule or n to cancel schedule : ";
	    		cin>>choice;
	    	
	    		if(choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y')
	    		{
	    			cout<<"Invalid input, please enter y or n."<<endl;
				}
				
				if(choice == 'Y' || choice == 'y')
				{
					break;
				}
				
				if(choice == 'n' || choice == 'N')
				{
					cout<<"\nschedule edit cancelled."<<endl<<endl;
					system("pause");
					system("CLS");
					display();
					return;
				}
			}while(choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
			schedule[array[num]].role = role;
			schedule[array[num]].startTime = startTime;
			schedule[array[num]].endTime = endTime;
			
			saveSchedule2();
			saveSalary();
			cout<<"\nemployee schedule successful edited."<<endl<<endl;
			system("pause");
			system("CLS");
			display();
		}
		
		void RemoveSchedule()
		{
			int k,month,array[100],j=0,num;
			char choice;
			bool valid=0;
			cout << "\n========================================" << endl;
		    cout << "| No | ID    | Employee                |" << endl;
		    cout << "========================================" << endl;
			for(int i=0;i<total_emp;i++)
			{
				cout<<"| " << setw(3) << left<< i+1<< "| " << setw(5) << left << s[i].ID <<" |" << setw(24) << left << s[i].name<<" |"<<endl;
				cout<<"----------------------------------------"<<endl;
			}
			do
			{
				fflush(stdin);
				cout<<"Enter employee ID (enter back to menu): ";
				getline(cin,ID);
				if(ID == "back")
				{
					display();
					return;
				}
				for(k=0;k<total_emp;k++)
				{
					if(ID == s[k].ID)
					{
						valid = 1;
						break;
					}
				}
				if(!valid)
				{
					cout<<"no employee was found."<<endl;
				}
			}while(!valid);
			
			do
			{
				cout<<"Enter the month to check schedule: ";
				cin>>month;
				
				if(month<1 || month >12)
				{
					cout<<"Invalid input, please enter input within 1 - 12.";
				}
			}while(month<1 || month >12);

		cout << "\n=======================================================================" << endl;
		    cout << "\t\t   Schedule for "<<s[k].name <<" ("<< s[k].ID << ") \t\t      " << endl;
		    cout << "=======================================================================" << endl;
		    cout << "| No | Date          | Role           | Start Time    | End Time      |" << endl;
		    cout << "=======================================================================" << endl;
			for (int i = 0; i < total_schedule; i++) 
			{
			    for (int j = i + 1; j < total_schedule; j++) 
				{
			        if (!compareByDate(schedule[i], schedule[j])) 
					{
			            UserDetails temp = schedule[i];
			            schedule[i] = schedule[j];
			            schedule[j] = temp;
			        }
			    }
			}
		    for(int i=0;i<total_schedule;i++)
		    {
		    	stringstream dateStream;
				dateStream << schedule[i].date << "/" << schedule[i].month << "/2024";
		        if(ID == schedule[i].ID && month == schedule[i].month)
		        {
		        	array[j] = i;
		        	j++;
		            cout << "| " << setw(3) << left << j << "| "
		                 << setw(13) << left << dateStream.str() << " |  "
		                 << setw(14) << left << schedule[i].role << "| "
		                 << setw(14) << left << schedule[i].startTime << "| "
		                 << setw(14) << left << schedule[i].endTime << "|" << endl;
		            cout << "-----------------------------------------------------------------------" << endl;
		        }
		    }
		    if(j == 0)
		    {
		    	cout<<"No schedule was found in this month"<<endl<<endl;
		    	editSchedule();
		    	return;
			}
			
			do
			{
				cout<<"Enter the number of schedule to remove : ";
				cin>>num;
				if(num < 1 || num > j)
				{
					cout<<"Please enter number between 1 to "<<j<<"."<<endl;
				}
			}while(num < 1 || num > j);
			num--;
			
			tm dateStruct = {0, 0, 0, schedule[array[num]].date, schedule[array[num]].month - 1, 2024 - 1900}; // Month is 0-indexed	
		    // Convert tm structure to time_t
		    time_t date = mktime(&dateStruct);
		    // Convert time_t to tm structure to get the day of the week
		    tm* dateInfo = localtime(&date);
		    // Array to store day names
		    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
		    
			cout << "==========================================================================================" << endl;
		    cout << "|\t\t          "<<s[k].name <<" ("<< s[k].ID << ") \t\t\t\t\t\t |" << endl;	    
			cout << "==========================================================================================" << endl;
	        cout << "| ID   | Employee                    | Role      |  Start Time  |  End Time  | Day       |"<< endl;
	        cout << "==========================================================================================" << endl;
	        cout << "| " << setw(5) << left << schedule[array[num]].ID
	             << "| " << setw(28) << left << s[k].name
	             << "| " << setw(10) << left << schedule[array[num]].role
	             << "| " << setw(13) << left << schedule[array[num]].startTime
	             << "| " << setw(11) << left << schedule[array[num]].endTime
				 << "| " << setw(10) << left << days[dateInfo->tm_wday]
	             << "| " << endl;
	        cout << "==========================================================================================" << endl
	             << endl;
	        do
	        {
	        	cout<<"Enter y to remove schedule or n to cancel action : ";
	    		cin>>choice;
	    	
	    		if(choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y')
	    		{
	    			cout<<"Invalid input, please enter y or n."<<endl;
				}
				
				if(choice == 'Y' || choice == 'y')
				{
					break;
				}
				
				if(choice == 'n' || choice == 'N')
				{
					cout<<"schedule cancel from removing."<<endl;
					display();
					return;
				}
			}while(choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
			
			for(j=0;j<total_schedule;j++)
			{
				if(schedule[j].ID == schedule[array[num]].ID && schedule[j].month == schedule[array[num]].month && schedule[j].date == schedule[array[num]].date)
				{
					break;
				}
			}
			for(j;j<total_schedule-1;j++)
    		{
    			schedule[j] = schedule[j+1];
			}
			total_schedule--;
			saveSchedule3();
			saveSalary();
			cout<<"Successful remove the schedule."<<endl;
			display();
			
		}

		
		void displaySchedule()
		{
			bool valid;
			int numOfDay, Date[7], month, day,j=0,k=0;
			cout<<"============================================================"<<endl;
			cout<<"\t             Working Schedule"<<endl;
			cout<<"============================================================"<<endl;
			do
			{
				cout<<"Month (1-12) : ";
				cin>>month;
				
				if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{			
					cout<<"\n----------------"<<endl;
					cout<<"| No | DATE    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 1  | 1-7     |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 2  | 8-14    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 3  | 15-21   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 4  | 22-28   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 5  | 29-31   |"<<endl;
					cout<<"----------------"<<endl;
					do
					{
						cout<<"\nEnter your choice (e.g : 1) : ";
						cin>>day;
						if(day > 5 || day < 1)
						{
							cout<<"Invalid input, please try again."<<endl; 
						}
					}while(day > 5 || day < 1);
				}
				else if(month == 4 || month == 6 || month == 9 || month == 11)
				{
					cout<<"\n----------------"<<endl;
					cout<<"| No | DATE    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 1  | 1-7     |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 2  | 8-14    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 3  | 15-21   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 4  | 22-28   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 5  | 29-30   |"<<endl;
					cout<<"----------------"<<endl;
					do
					{
						cout<<"\nEnter your choice (e.g : 1) : ";
						cin>>day;
						if(day > 5 || day < 1)
						{
							cout<<"Invalid input, please try again."<<endl; 
						}
					}while(day > 5 || day < 1);
				}
				else if(month == 2)
				{	
					cout<<"\n----------------"<<endl;
					cout<<"| No | DATE    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 1  | 1-7     |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 2  | 8-14    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 3  | 15-21   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 4  | 22-28   |"<<endl;
					cout<<"----------------"<<endl;
					do
					{
						cout<<"\nEnter your choice (e.g : 1) : ";
						cin>>day;
						if(day > 4 || day < 1)
						{
							cout<<"Invalid input, please try again."<<endl; 
						}
					}while(day > 4 || day < 1);
				}
				else
				{
					cout<<"Invalid input."<<endl<<endl;
				}
				
			}while(month > 12 || month < 1);
			
			
			
			
			switch (day)
		    {
			    case 1:
			        numOfDay = 7;
			        for (int i = 0; i < numOfDay; i++)
			        {
			            Date[i] = i + 1;
			        }
			        break;
			
			    case 2:
			        numOfDay = 7;
			        for (int i = 0; i < numOfDay; i++)
			        {
			            Date[i] = i + 8;
			        }
			        break;
			
			    case 3:
			        numOfDay = 7;
			        for (int i = 0; i < numOfDay; i++)
			        {
			            Date[i] = i + 15;
			        }
			        break;
			
			    case 4:
			        numOfDay = 7;
			        for (int i = 0; i < numOfDay; i++)
			        {
			            Date[i] = i + 22;
			        }
			        break;
			
			    case 5:
			        numOfDay = 3;
			        if(month == 4 || month == 6 || month == 9 || month == 11)
			        {
			        	numOfDay = 2;
			        	for (int i = 0; i < numOfDay; i++)
				        {
				            Date[i] = i + 29;
				        }
					}
					else
					{
				        for (int i = 0; i < numOfDay; i++)
				        {
				            Date[i] = i + 29;
				        }
			    	}
			        break;
			    default:
			    	cout<<"Invalid selection!"<<endl;
		    }
			
		    cout << "\n=======================================================================================================================================================================" << endl;
		    cout << "|\t\t\t\t\t\t\t\t\t   Week "<<day<<" schedule                                                                            |" << endl;
		    cout << "=======================================================================================================================================================================" << endl;
		    cout << "| ID   |  Employee         | ";
		    for(int i=0;i<numOfDay;i++)
		    {
				stringstream dateStream;
				dateStream << Date[i] << "/" << month << "/2024";
				cout << setw(16) << left << dateStream.str() << " |  ";
			}
			
			cout << "\n|      |                   | ";
			for(int i=0;i<numOfDay;i++)
		    {
		    	cout<<setw(16)<<left<<getDayOfWeek(i,month,Date)<<" |  ";
			}
		    cout << "\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		
		    for (int i = 0; i < total_emp; i++) 
			{
		        cout << "| " << setw(5) << left << s[i].ID << "| " << setw(18) << left << s[i].name << "| " ;
				for(j=0;j<numOfDay;j++)
				{
			        for (k=0; k < total_schedule; k++)
					{
						if(schedule[k].ID == s[i].ID && schedule[k].month == month && schedule[k].date == Date[j])
						{
							valid = 1;
							break;
						}
						else
						{

							valid = 0;
						}
						
						
			        }
				        if(valid)
						{
							cout << setw(17) << left << schedule[k].role << "|  ";
						}
						else if(isWeekend(Date[j], month, 2024))
						{
							cout << setw(17) << left << "OFF DAY" << "|  ";
						}
						else
						{
							cout << setw(17) << left << "None" << "|  ";
						}
		        }
		        cout << "\n" << setw(7) << "| " << setw(20)<< "| " << "|";
		        
		        
		        for(int j=0;j<7;j++)
				{
					for(k=0;k<total_schedule;k++)
			        {
			        	if(schedule[k].ID == s[i].ID && schedule[k].month == month && schedule[k].date == Date[j])
						{
							valid = 1;
							break;
						}
						else
						{
							valid = 0;
						}
					}
					if(valid)
					{
						cout<<setw(18) << left << " " + schedule[k].startTime + "hrs-" + schedule[k].endTime + "hrs"<< "| ";
					}
					else
					{
						cout<<setw(18) << left << " " << "| ";
					}		
				}
		
		    	cout <<"\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
		    }
		    system("pause");
		    system("CLS");
		    display();
		}	
		
		void displayWorkingHoursAndSalary() 
		{
		    bool valid = false;
		    int i;
		
			cout << "\n========================================" << endl;
		    cout << "| No | ID    | Employee                |" << endl;
		    cout << "========================================" << endl;
			for(int i=0;i<total_emp;i++)
			{
				cout<<"| " << setw(3) << left<< i+1<< "| " << setw(5) << left << s[i].ID <<" |" << setw(24) << left << s[i].name<<" |"<<endl;
				cout<<"----------------------------------------"<<endl;
			}
			
		    do 
		    {
		        fflush(stdin);
		        cout << "\nEnter employee ID for details (Enter 'back' to menu): ";
		        getline(cin, ID);
		        
		        for (i = 0; i < total_emp; i++) 
		        {
		            if (ID == s[i].ID) 
		            {
		                valid = true;
		                break;
		            } 
		            else if (ID == "back") 
		            {
		                display();
		                return;
		            } 
		            else if (i == total_emp - 1) 
		            {
		                cout << "No employee was found (Enter 'back' to menu)" << endl;
		            }
		        }
		    } while (!valid);
		
		    // Display monthly details
		    stringstream dateStream;
			dateStream << s[i].name << " (" << s[i].ID << ")";
		    cout << "\n============================================" << endl;
		    cout << "| Monthly Details for " << setw(20)<< dateStream.str() << " |" <<endl;
		    cout << "============================================" << endl;
		    cout << "| Month\t| Hours Worked\t| Salary           |" << endl;
		    cout << "|-------|---------------|-------------------" << endl;
		
		    for (int month = 0; month < 12; month++) 
		    {
		        cout << "| " << setw(6) << left << month + 1 
		             << "| " << setw(6) << fixed << setprecision(2) << s[i].monthly_hour[month] << setw(8) <<" hours"
		             << "| RM " << setw(14) << fixed << setprecision(2) << s[i].monthly_salary[month] << "|"<<endl;
		    	cout<<"--------------------------------------------"<<endl;
		    }
		
		    // Calculate and display total salary using DMA
		    double *totalSalary = new double(0.0);

		    for (int month = 0; month < 12; month++) 
		    {
		        *totalSalary += s[i].monthly_salary[month];
		    }
		
		    cout << "============================================" << endl;
		    cout << "| Total Hours : " << setw(27) << fixed << setprecision(2) << s[i].total_hour << "|"<<endl;
		    cout << "| Total Salary: RM " << setw(24) << fixed << setprecision(2) << *totalSalary << "|"<<endl;
		    cout << "============================================" << endl;
		    system("pause");
			system("CLS");
		
		    // Deallocate memory
		    delete totalSalary;
		
		    display(); // Display the menu again
		}

		void ClockingMenu()
		{
			int choice;
			cout<<"=================================================="<<endl;
			cout<<"                Clocking Menu"<<endl;
			cout<<"=================================================="<<endl;
			cout<<"1. Check Clocking timing today"<<endl;
			cout<<"2. Check Clocking timing in specific date"<<endl;
			cout<<"3. back"<<endl;
			do
			{
				cout<<"\nEnter your choice : ";
				cin>>choice;
				switch(choice)
				{
					case 1:
						displayClocking();
						break;
					case 2:
						displayClocking2();
						break;
					case 3:
						display();
						return;
					default:
						cout<<"\nInvalid value! Please re-enter your choice !"<<endl;
				}
			}while(choice > 3 || choice < 1);
		}
		
		void displayClocking()
		{
			bool valid;
			cout << "\n=============================================================================" << endl;
		    cout << "|\t\t   "<<getCurrentDate() + " (" + getDayOfWeek2() + ")"<<"\t\t\t\t    |" << endl;
		    cout << "=============================================================================" << endl;
	   		cout << "| ID   |  Employee         |    Role    | Clock In Time  |  Clock Out Time  |"<<endl;
	   		cout << "============================================================================="<<endl;
	   		for (int i = 0; i < total_emp; i++) 
			{
				valid = 0;
		        cout << "| " << setw(5) << left << s[i].ID << "| " << setw(18) << left << s[i].name << "| " ;
		        
		        for(int j=0;j<total_schedule;j++)
			    {
			    	if(s[i].ID == schedule[j].ID && schedule[j].month == getCurrentMonthNum() + 1 && schedule[j].date == getCurrentDateNum())
			    	{
			    		valid = 1;
			    		cout << setw(11) << schedule[j].role << "|  ";
					}
				}
				if(!valid)
				{
					cout << setw(11) << "" << "|  ";
				}
				
		        for (int j=0; j < GetTotal_clock(); j++)
				{
					valid = 0; 
					if(clocking[j].ID == s[i].ID && clocking[j].fulldate == getCurrentDate() + " (" + getDayOfWeek2() + ")")
					{
						cout << setw(14) << left << clocking[j].ClockIn_time << "|  ";
						valid = 1;
						break;
					}
			    }
			    if(!valid)
			    {
			    	cout << setw(14) << left << "" << "|  ";
				}
				
			    for (int j=0; j < GetTotal_clock_out(); j++)
				{
					valid = 0;
					if(clockout[j].ID == s[i].ID && clockout[j].fulldate == getCurrentDate() + " (" + getDayOfWeek2() + ")")
					{
						cout << setw(16) << clockout[j].ClockOut_time << "|  ";
						valid = 1;
						break;
					}
			    }
			    if(!valid)
			    {
			    	cout << setw(16) << left << "" << "|  ";
				}
			    cout << "\n-----------------------------------------------------------------------------"<<endl;
			}
			system("pause");
			system("CLS");
			display();
		}
		
		void displayClocking2()
		{
			bool valid;
			int month,date;
			int monthNumber=1;
			int day,year;
			string month2, dayOfWeek;
			const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
			
			do
			{
				cout<<"Enter Month (1-12) : ";
				cin>>month;
				
				if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					do
					{
						cout<<"Enter date (1-31) : ";
						cin>>date;
						if(date > 31 || date < 1)
						{
							cout<<"Invalid input, please try again."<<endl; 
						}
					}while(date > 31 || date < 1);
				}
				else if(month == 4 || month == 6 || month == 9 || month == 11)
				{
					do
					{
						cout<<"Enter date (1-30) : ";
						cin>>date;
						if(date > 30 || date < 1)
						{
							cout<<"Invalid input, please try again."<<endl; 
						}
					}while(date > 30 || date < 1);
				}
				else if(month == 2)
				{
					do
					{
						cout<<"Enter date (1-28) : ";
						cin>>date;
						if(date > 28 || date < 1)
						{
							cout<<"Invalid input, please try again."<<endl; 
						}
					}while(date > 28 || date < 1);
				}
				else
				{
					cout<<"Invalid input."<<endl<<endl;
				}
			}while(month > 12 || month < 1);
			
			stringstream dateStream;
			dateStream << date << "/" << month << "/2024";				
				
			cout << "\n=============================================================================" << endl;
		    cout << "|\t\t\t      "<<setw(30)<<left<<dateStream.str()<<"\t\t    |" << endl;
		    cout << "=============================================================================" << endl;
	   		cout << "| ID   |  Employee         |    Role    | Clock In Time  |  Clock Out Time  |"<<endl;
	   		cout << "============================================================================="<<endl;
	   		int i;
	   		for (i = 0; i < total_emp; i++) 
			{
				valid = 0;
				//if there is a schedule for this employee, display the employee id and name
				cout << "| " << setw(5) << left << s[i].ID << "| " << setw(18) << left << s[i].name << "| " ;
			    
			    for(int j=0;j<total_schedule;j++)
			    {
			    	if(s[i].ID == schedule[j].ID && schedule[j].month == month && schedule[j].date == date)
			    	{
			    		valid = 1;
			    		cout << setw(11) << schedule[j].role << "|  ";
					}
				}
				if(!valid)
				{
					cout << setw(11) << "" << "|  ";
				}
		        //if the clocking time was found, display it, else display nothing.
		        for (int j=0; j < GetTotal_clock(); j++)
				{
					valid = 0;
					istringstream iss(clocking[j].fulldate);
			    	iss >> day >> month2 >> year >> dayOfWeek;
			    	
			    	for (int k = 0; k < 12; ++k) 
					{
				        if (month2 == months[k])
						{
				            monthNumber = k + 1;
				            break;
				        }
				    }
				    
					if(clocking[j].ID == s[i].ID && monthNumber == month && day == date)
					{
						cout  << setw(14) << left << clocking[j].ClockIn_time << "|  ";
						valid = 1;
						break;
					}
			    }
			    if(!valid)
			    {
			    	cout << setw(14) << left << "" << "|  ";
				}
		    
			    
			    for (int j=0; j < GetTotal_clock_out(); j++)
				{
					valid = 0;
					istringstream is(clockout[j].fulldate);
				    is >> day >> month2 >> year >> dayOfWeek;
	
				    for (int k = 0; k < 12; ++k) 
					{
				        if (month2 == months[k])
						{
				            monthNumber = k + 1;
				            break;
				        }
				    }
					if(clockout[j].ID == s[i].ID && monthNumber == month && day == date)
					{
						cout << setw(16) << clockout[j].ClockOut_time << "|  ";
						cout << "\n-----------------------------------------------------------------------------"<<endl;
						valid = 1;
						break;
					}
			    }
			    if(!valid)
			    {
			    	cout << setw(16) << left << "" << "|  ";
			    	cout << "\n-----------------------------------------------------------------------------"<<endl;
				}
			    
			    
			}
			system("pause");
			system("CLS");
			display();
		}
		
};

//Inherit from class file
class user : public file
{
	private:
		string entered_name,entered_password;
		int emp;
		
	public:
		//Declare friend function
		friend void interface();
		
		//User login function
		void login()
		{
			system("CLS");
			cout<<"============================================================"<<endl;
			cout<<" \t              Employee Login"<<endl;
			cout<<"============================================================"<<endl;
			// Prompt the user to enter employee name
			fflush(stdin);
			cout<<"Enter Employee name : ";
			getline(cin,entered_name);
			
			// Check if the user wants to go back to the interface
			if (entered_name == "back") //back to interface based on user need
			{
				// Go back to the main interface
				return;
			}
			
			// Prompt the user to enter password
			cout<<"Enter password : ";
			getline(cin,entered_password);
			// Login validation to ensure name and password is true
			login_val(*this,entered_name, entered_password); 
		}
		
		
		
		//Function to display the schedule
		void DisplaySchedule()
		{
			bool valid;
			int numOfDay, Date[7], month, day,j=0,k=0;
			
			//get user input for month and display the following date to choose based on the month chosen.
			cout<<"============================================================"<<endl;
			cout<<"\t             Working Schedule"<<endl;
			cout<<"============================================================"<<endl;
			do
			{
				cout<<"Month (1-12) : ";
				cin>>month;
				
				if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{			
					cout<<"\n----------------"<<endl;
					cout<<"| No | DATE    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 1  | 1-7     |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 2  | 8-14    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 3  | 15-21   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 4  | 22-28   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 5  | 29-31   |"<<endl;
					cout<<"----------------"<<endl;
					do
					{
						cout<<"\nEnter your choice (e.g : 1) : ";
						cin>>day;
						if(day > 5 || day < 1)
						{
							cout<<"Invalid input, please try again."<<endl; 
						}
					}while(day > 5 || day < 1);
				}
				else if(month == 4 || month == 6 || month == 9 || month == 11)
				{
					cout<<"\n----------------"<<endl;
					cout<<"| No | DATE    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 1  | 1-7     |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 2  | 8-14    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 3  | 15-21   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 4  | 22-28   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 5  | 29-30   |"<<endl;
					cout<<"----------------"<<endl;
					do
					{
						cout<<"\nEnter your choice (e.g : 1) : ";
						cin>>day;
						if(day > 5 || day < 1)
						{
							cout<<"Invalid input, please try again."<<endl; 
						}
					}while(day > 5 || day < 1);
				}
				else if(month == 2)
				{
					cout<<"\n----------------"<<endl;
					cout<<"| No | DATE    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 1  | 1-7     |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 2  | 8-14    |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 3  | 15-21   |"<<endl;
					cout<<"----------------"<<endl;
					cout<<"| 4  | 22-28   |"<<endl;
					cout<<"----------------"<<endl;
					do
					{
						cout<<"\nEnter your choice (e.g : 1) : ";
						cin>>day;
						if(day > 4 || day < 1)
						{
							cout<<"Invalid input, please try again."<<endl; 
						}
					}while(day > 4 || day < 1);
				}
				else
				{
					cout<<"Invalid input."<<endl<<endl;
				}
				
			}while(month > 12 || month < 1);
				
			//display the specific date based on user input for day
			switch (day)
		    {
			    case 1:
			        numOfDay = 7;
			        for (int i = 0; i < numOfDay; i++)
			        {
			            Date[i] = i + 1;
			        }
			        break;
			
			    case 2:
			        numOfDay = 7;
			        for (int i = 0; i < numOfDay; i++)
			        {
			            Date[i] = i + 8;
			        }
			        break;
			
			    case 3:
			        numOfDay = 7;
			        for (int i = 0; i < numOfDay; i++)
			        {
			            Date[i] = i + 15;
			        }
			        break;
			
			    case 4:
			        numOfDay = 7;
			        for (int i = 0; i < numOfDay; i++)
			        {
			            Date[i] = i + 22;
			        }
			        break;
			
			    case 5:
			        numOfDay = 3;
			        if(month == 4 || month == 6 || month == 9 || month == 11)
			        {
			        	numOfDay = 2;
			        	for (int i = 0; i < numOfDay; i++)
				        {
				            Date[i] = i + 29;
				        }
					}
					else
					{
				        for (int i = 0; i < numOfDay; i++)
				        {
				            Date[i] = i + 29;
				        }
			    	}
			        break;
			    default:
			    	cout<<"Invalid selection."<<endl;
		    }
			
		    cout << "=======================================================================================================================================================================" << endl;
		    cout << "|\t\t\t\t\t\t\t\t\t   Week "<<day<<" schedule                                                                            |" << endl;
		    cout << "=======================================================================================================================================================================" << endl;
		    cout << "| ID   |  Employee         | ";
		    
		    //convert date and month into string and combine them as a string to display it with setw.
		    for(int i=0;i<numOfDay;i++)
		    {
				stringstream dateStream;
				dateStream << Date[i] << "/" << month << "/2024";
				cout << setw(16) << left << dateStream.str() << " |  ";
			}
			
			cout << "\n|      |                   | ";
			
			//display the day like Monday based on the month, date and date chosen.
			for(int i=0;i<numOfDay;i++)
		    {
		    	cout<<setw(16)<<left<<getDayOfWeek(i,month,Date)<<" |  ";
			}
		    cout << "\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			
			// Loop through employees to display schedule details
		    for (int i = 0; i < GetTotalEmployee(); i++) 
			{
				//display the employee ID and name
		        cout << "| " << setw(5) << left << s[i].ID << "| " << setw(18) << left << s[i].name << "| " ;
				for(j=0;j<numOfDay;j++)
				{
					//Validate the employee ID, date and role 
			        for (k=0; k < GetTotal_schedule(); k++)
					{
						if(schedule[k].ID == s[i].ID && schedule[k].month == month && schedule[k].date == Date[j])
						{
							valid = 1;
							break;
						}
						else
						{

							valid = 0;
						}
						
						
			        }
			        	//display schedule role
				        if(valid)
						{
							cout << setw(17) << left << schedule[k].role << "|  ";
						}
						//display OFF DAY
						else if(isWeekend(Date[j], month, 2024))
						{
							cout << setw(17) << left << "OFF DAY" << "|  ";
						}
						//display None for no work
						else
						{
							cout << setw(17) << left << "None" << "|  ";
						}
		        }
		        cout << "\n" << setw(7) << "| " << setw(20)<< "| " << "|";
		        
		        //display the start time and end time
		        for(int j=0;j<7;j++)
				{
					for(k=0;k<GetTotal_schedule();k++)
			        {
			        	if(schedule[k].ID == s[i].ID && schedule[k].month == month && schedule[k].date == Date[j])
						{
							valid = 1;
							break;
						}
						else
						{
							valid = 0;
						}
					}
					if(valid)
					{
						cout<<setw(18) << left << " " + schedule[k].startTime + "hrs-" + schedule[k].endTime + "hrs"<< "| ";
					}
					else
					{
						cout<<setw(18) << left << " " << "| ";
					}		
				}
		
		    	cout <<"\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
		    }
		    system("pause");
			system("CLS");
		    Display();
		}
		
		// Display clocking menu options
		void ClockingMenu()
		{
			int choice;
			
			cout<<"=================================================="<<endl;
			cout<<"                 Clocking"<<endl;
			cout<<"=================================================="<<endl;
			cout<<"1. Clock in"<<endl;
			cout<<"2. Clock out"<<endl;
			cout<<"3. back"<<endl;
			do
			{			
				cout<<"\nEnter your choice : ";
				cin>>choice;
				if(choice > 3 || choice < 1)
				{
					cout<<"Invalid choice."<<endl;
				}
			}while(choice > 3 || choice < 1);
			
			switch(choice)
			{
				case 1:
					clockIn();
					break;
				case 2:
					clockOut();
					break;
				case 3:
					Display();
					return;
				default:
					cout<<"Invalid number."<<endl;
			}
		}

		
		void clockIn() 
		{
			int i,j;
	        
	        //this for loop using name and password check for the employee ID
	        for(i=0;i<GetTotalEmployee();i++)
	        {
	        	if(s[i].name == entered_name && s[i].pw == entered_password)
	        	{
	        		break;
				}
			}
			
			//this for loop check whether the employee working today or not
			bool valid = false;
			for(j=0;j<GetTotal_schedule();j++)
			{
				if(s[i].ID == schedule[j].ID && schedule[j].date == getCurrentDateNum() && schedule[j].month == getCurrentMonthNum()+1)
				{
					valid = true;
					break;
				}
			}
			// If no schedule is found, return to the main menu
			if(!valid)
			{
				cout<<"\nNo schedule work for today"<<endl<<endl;
				system("pause");
				system("CLS");
	            ClockingMenu();
				return;
			}
			
			// Check if the employee has already clocked in today
			for(int k=0;k<GetTotal_clock();k++)
			{
				if(clocking[k].ID == schedule[j].ID && clocking[k].fulldate == getCurrentDate() + " (" + getDayOfWeek2() + ")")
				{
					cout<<"\nYou already clock in today."<<endl<<endl;
					system("pause");
					system("CLS");
	            	ClockingMenu();
					return;
				}
			}
			
			//save the clock in details and return to menu
			clocking[GetTotal_clock()].fulldate = getCurrentDate() + " (" + getDayOfWeek2() + ")";
			saveClockingfile(i,j);
			system("pause");
			system("CLS");
			ClockingMenu();
	    }
	    
	    // Method to validate clock in based on the schedule
	    bool clockin_val(int j)
	    {
	    	for(int i=0;i<GetTotal_clock();i++)
	    	{
	    		// Create input string stream from the given date
			    istringstream iss(clocking[i].fulldate);
			
			    // Parse day, month, year, and day of the week
			    int day, year;
			    string month, dayOfWeek;
			    iss >> day >> month >> year >> dayOfWeek;
			
			    // Convert month abbreviation to numeric value
			    const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
			    int monthNumber = 1; // Default to January
			    for (int i = 0; i < 12; ++i) 
				{
			        if (month == months[i]) 
					{
			            monthNumber = i + 1;
			            break;
			        }
			    }
		
			    // Get the current date
			    time_t currentTime = time(0);
			    tm* currentDate = localtime(&currentTime);
			    
			    // Compare ID, year, month, and day components
			    for(int i=0;i<GetTotal_clock();i++)
			    {
			    	if((2024 == currentDate->tm_year + 1900) && (monthNumber == currentDate->tm_mon + 1) && (day == currentDate->tm_mday) && schedule[j].ID == clocking[i].ID)
				    {
				    	return 1;
					}
				}
			    
			}
		    return 0;
		}
	
	    void clockOut() 
		{
			int i,j,num=0;
	        
	        //this for loop check for employee id using name and password
	        for(i=0;i<GetTotalEmployee();i++)
	        {
	        	if(s[i].name == entered_name && s[i].pw == entered_password)
	        	{
	        		break;
				}
			}
			//look for the exact schedule in schedule file and store it position in j
			for(j=0;j<GetTotal_schedule();j++)
			{
				if(s[i].ID == schedule[j].ID && schedule[j].date == getCurrentDateNum() && schedule[j].month == getCurrentMonthNum()+1)
				{
					break;
				}
			}
			//if employee did not clock in then he cant clock out
			if (!clockin_val(j))
			{
	            cout << "\nYou has not clocked in. Cannot clock out." << endl<<endl;
	            system("pause");
				system("CLS");
	            ClockingMenu();
	            return;
        	}
        	for(int k=0;k<GetTotal_clock_out();k++)
			{
				if(clockout[k].ID == schedule[j].ID && clockout[k].fulldate == getCurrentDate() + " (" + getDayOfWeek2() + ")")
				{
					cout<<"\nYou already clock out today."<<endl<<endl;
					system("pause");
					system("CLS");
	         	    ClockingMenu();
					return;	
				}
			}
			
			//save into clock out file and go to menu
        	saveClockingfile2(i,j);
        	system("pause");
			system("CLS");
        	ClockingMenu();
	    }
		
		//user menu function
		void Display()
		{
		 	int choice;
		 	system("CLS");
			cout<<"=================================================="<<endl;
			cout<<"                 Menu"<<endl;
			cout<<"=================================================="<<endl;
			cout<<"1. Clocking system"<<endl;
			cout<<"2. Work Schedule"<<endl;
			cout<<"3. Logout"<<endl;
			do
			{
				cout<<"\nEnter your choice : ";
				cin>>choice;
				switch(choice)
				{
					case 1:
						ClockingMenu();
						break;
					case 2:
						DisplaySchedule();
						break;
					case 3:
						return;
					default:
						cout<<"Invalid value!!"<<endl;
				}
			}while(choice > 3 || choice < 1);
		}
		friend void login_val(user& ob, const string& entered_name, const string& entered_password);
};

void interface()
{
	int choice;
	Admin adm;
	user us;
	do
	{
		system("CLS");
		cout<<"============================================================"<<endl;
		cout<<"               Working Schedule System"<<endl;
		cout<<"============================================================"<<endl;
		cout<<"1. Employee Login"<<endl;
		cout<<"2. Admin Login"<<endl;
		cout<<"3. Exit"<<endl;
		cout<<"\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				us.login();
				break;
			case 2:
				adm.Admin_login();
				break;
			case 3:
				return;
			default:
				cout<<"Invalid value!!!"<<endl;
		}
	}while(choice != 3);
}

//Login validation function
void login_val(user& ob, const string& entered_name, const string& entered_password)
{
	bool valid;
	// Load employee data from file for checking 
    ob.LoadFromFile();
    
    // Iterate through the list of employees and check for a match
    for(int i=0;i<ob.GetTotalEmployee();i++)
    {
        if (s[i].name == entered_name && s[i].pw == entered_password)
        {
            valid = 1;
            break; // Break the loop when a match is found
        }   		    	
	}

	//if employee data match, load all neccessary file and display main menu
    if (valid == 1)
    {
        cout << ("\nLogin successful") << endl << endl;
        ob.LoadFromFile();
		ob.LoadResignEmployee();
		ob.loadSchedule();
		ob.loadSalaryfile();
		ob.loadClockingfile();
		ob.loadClockingfile2();
		system("pause");
		system("CLS");
		ob.Display();
	}
	// Display error message for unmatch data and let user go back to login function
	else
	{
    	//Display an error message
		cout<<"\nIncorrect ID or Password, please try again. (Enter 'back' in ID will back to menu)"<<endl;
    	system("pause");

		//call again to allow the user to try logging in again
    	ob.login();
	}
}

int main()
{
	interface();
	
	return 0;
} 
