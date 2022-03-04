/*


*/

#include "LiftingApp.h"

int main(void)

{
	//Variables, Vectors, Files
	ifstream infile, inRecords; 
	ofstream outfile, records;
	string loginDataBase = "userLoginData.txt"; 

	vector<string> usernames, passwords, planTitles; 
	vector<WeightLifter> plans;
	char user = '\0', wrongPass = '\0', menuSelect = '\0', plan = '\0';
	string username = "", password = "", newPassword = "";
	int currIdx = 0; 
	bool userExists = false, correctPass = false, fileExists = false;

	//INTRO/HEADER
	cout << "*********************************************************************" << endl;
	cout << "*                              WELCOME!                             *" << endl; 
	cout << "*                     THIS IS JOEY'S FITNESS APP                    *" << endl; 
	cout << "*********************************************************************" << endl;
	
	//Load in existing login data
	fileExists = openInFile(infile, loginDataBase);
	if (fileExists)
	{
		loadLoginInfo(infile, usernames, passwords);
	}

	//Defining the type of user
	cout << "             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl; 
	cout << "             | New Users ---------------- SELECT 'N' |               " << endl; 
	cout << "             | Returning Users ---------- SELECT 'R' |               " << endl;
	cout << "             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
	cout << "             Selection: "; 
	cin >> user; 
	cout << endl; 
	toUpperCase(user);
	user = checkInput('N', 'R', user); 
	
	//Must select "NEW USER" when first opening application
	if (user == 'R' && fileExists == 0)
	{
		cout << "         [NO users exist yet... Please CREATE a NEW account]         " << endl << endl;
		user = 'N'; 
	}
	
	//RETURNING user login
	if (user == 'R') 
	{
		cout << "*********************************************************************" << endl;
		cout << "                           * SIGN IN  *                             " << endl;
		cout << "*********************************************************************" << endl;
		cout << "			Username: "; 
		cin >> username; 
		userExists = doesUserExist(usernames, username, currIdx); 
		while (userExists == false)
		{
			cout << "\n                    *   INCORRECT USERNAME   *                       \n" << endl;
			cout << "			Username: ";
			cin >> username;
			userExists = doesUserExist(usernames, username, currIdx);
		}
		
		cout << "			Password: ";
		cin >> password;
		cout << endl; 
		correctPass = correctPassword(passwords, password, currIdx); 
		while (correctPass == false)
		{
			cout << "                    *   INCORRECT PASSWORD   *                       \n" << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~              " << endl;
			cout << "              |  Forgot Password --------- SELECT 'F' |              " << endl;
			cout << "              |  TRY AGAIN --------------- SELECT 'T' |              " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~              " << endl;
			cout << "              Selection: ";
			cin >> wrongPass;
			toUpperCase(wrongPass);
			wrongPass = checkInput2('F', 'T', wrongPass); 
			cout << endl; 
			if (wrongPass == 'T')
			{
				cout << "*********************************************************************" << endl;
				cout << "			Username: " << username << endl; 
				cout << "			Password: ";
				cin >> password;
				cout << endl; 
				correctPass = correctPassword(passwords, password, currIdx);
			}
			else
			{
				cout << "*********************************************************************" << endl;
				cout << "               [Please enter a NEW and UNIQUE password]              " << endl; 
				cout << "			Username: " << username << endl;
				cout << "			Password: ";
				cin >> newPassword;
				passwords.at(currIdx) = newPassword;
				correctPass = true;
			}
		}
	}

	//NEW user account creation/login
	if (user == 'N')
	{
		cout << "*********************************************************************" << endl;
		cout << "                        *  CREATE ACCOUNT  *                         " << endl;
		cout << "*********************************************************************" << endl;
		cout << "	Please enter a Username: ";
		cin >> username; 
		userExists = doesUserExist(usernames, username, currIdx);
		while (userExists == true)
		{
			cout << "\n                     *  USER ALREADY EXISTS  *                       \n" << endl;
			cout << "*********************************************************************" << endl;
			cout << "	Please enter a DIFFERENT Username: ";
			cin >> username;
			userExists = doesUserExist(usernames, username, currIdx);
		}
		cout << "	Please enter a UNIQUE Password: "; 
		cin >> password; 
		addLogInInfo(usernames, passwords, username, password); 
		cout << "*********************************************************************" << endl;
	}
	
	//Update loginDataBase
	openOutFile(outfile, loginDataBase);
	saveLoginInfo(outfile, usernames, passwords); 
	
	//load in existing records
	loadRecords(inRecords, username, planTitles, plans);
	while (menuSelect != 'Q')
	{
		cout << "*********************************************************************" << endl;
		cout << "                             [MAIN MENU]                             " << endl;
		cout << "*********************************************************************" << endl;
		cout << "             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "             |  VIEW PLAN -------------- SELECT 'V'  |               " << endl;
		cout << "             |  ADD NEW ---------------- SELECT 'A'  |               " << endl;
		cout << "             |  EDIT ------------------- SELECT 'E'  |               " << endl;
		cout << "             |  SAVE/QUIT -------------- SELECT 'Q'  |               " << endl;
		cout << "             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "             Selection: ";
		cin >> menuSelect;
		cout << endl; 
		toUpperCase(menuSelect);
		menuSelect = checkInput3('V', 'A', 'E', 'Q', menuSelect);
		if (menuSelect == 'V')
		{
			displayAvailablePlans(planTitles); 
			cout << "Please select the # associated with the plan you would like to view: ";
			cin >> plan; 
			cout << endl; 
			displayPlan(plans, plan); 
			displayMenu4(menuSelect);
		}
		else if (menuSelect == 'A')
		{
			newWorkoutPlan(planTitles, plans);
			displayMenu4(menuSelect);
		}
		else if (menuSelect == 'E')
		{
			displayMenu4(menuSelect);
		}
	}
	savePlans(records, username, planTitles, plans);
	infile.close(); 
	outfile.close();

	return 0; 
}