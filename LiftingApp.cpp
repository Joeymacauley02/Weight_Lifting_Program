/*


*/

#include "LiftingApp.h"

//ExerciseList Class Functions ------------------------------------------------------------------------------------------------------------
ExerciseList::ExerciseList()
{
	frontPtr = nullptr; 
	rearPtr = nullptr;
	numItems = 0;  
}

ExerciseList::~ExerciseList()
{
}

bool ExerciseList::isEmpty()
{
	if (frontPtr == nullptr)
		return true;
	else
		return false; 
}

void ExerciseList::clear()
{
	while (frontPtr != nullptr)
	{
		removeFromFront(); 
	}
}

void ExerciseList::addToFront(string n, int w, int sets, int reps, string tgt)
{
	ExerciseNode* temp = new ExerciseNode; 

	temp->name = n; 
	temp->weight = w;
	temp->numSets = sets; 
	temp->numReps = reps; 
	temp->target = tgt; 

	temp->nextPtr = nullptr; 
	temp->prevPtr = nullptr; 

	if (isEmpty())
	{
		frontPtr = temp; 
		rearPtr = temp; 
	}
	else
	{
		frontPtr->prevPtr = temp; 
		temp->nextPtr = frontPtr; 
		frontPtr = temp; 
	}

	numItems++; 
}

void ExerciseList::addToRear(string n, int w, int sets, int reps, string tgt)
{
	ExerciseNode* temp = new ExerciseNode;

	temp->name = n;
	temp->weight = w;
	temp->numSets = sets;
	temp->numReps = reps;
	temp->target = tgt;

	temp->nextPtr = nullptr;
	temp->prevPtr = nullptr;

	if (isEmpty())
	{
		frontPtr = temp;
		rearPtr = temp;
	}
	else
	{
		rearPtr->nextPtr = temp;
		temp->prevPtr = rearPtr;
		rearPtr = temp;
	}

	numItems++;
}

void ExerciseList::addAtIndex(string n, int w, int sets, int reps, string tgt, int index)
{
	ExerciseNode* temp = new ExerciseNode;
	ExerciseNode* traverse = frontPtr; 

	temp->name = n;
	temp->weight = w;
	temp->numSets = sets;
	temp->numReps = reps;
	temp->target = tgt;

	temp->nextPtr = nullptr;
	temp->prevPtr = nullptr;

	if (numItems < index)
	{
		addToRear(n, w, sets, reps, tgt);
	}
	else if (index == 0)
	{
		addToFront(n, w, sets, reps, tgt); 
	}
	else
	{
		for (int i = 1; i < index; i++)
		{
			traverse = traverse->nextPtr; 
		}
		temp->nextPtr = traverse->nextPtr; 
		temp->prevPtr = traverse; 
		traverse->nextPtr->prevPtr = temp;
		traverse->nextPtr = temp;
		
	}

	numItems++;
}

void ExerciseList::removeFromFront()
{
	ExerciseNode* deleteNode = frontPtr; 
	
	frontPtr = frontPtr->nextPtr; 
	if (frontPtr == nullptr) 
	{
		rearPtr = nullptr;
	}
	else
	{
		frontPtr->prevPtr = nullptr;
	}
	
	numItems--; 
	delete deleteNode; 
}

void ExerciseList::removeFromRear()
{
	ExerciseNode* deleteNode = rearPtr;
	rearPtr = rearPtr->prevPtr;

	if (rearPtr == nullptr)
	{
		frontPtr = nullptr;
	}
	else
	{
		rearPtr->nextPtr = nullptr;
	}

	numItems--; 
	delete deleteNode;
}

void ExerciseList::removeAtIndex(int index)
{
	ExerciseNode* deleteNode = nullptr; 
	deleteNode = frontPtr; 
	
	if (numItems < index || numItems == (index+1))
	{
		removeFromRear(); 
	}
	else if (index == 0)
	{
		removeFromFront(); 
	}
	else
	{
		for (int i = 0; i < index; i++)
		{
			deleteNode = deleteNode->nextPtr;
		}

		deleteNode->prevPtr->nextPtr = deleteNode->nextPtr; 
		deleteNode->nextPtr->prevPtr = deleteNode->prevPtr; 

		delete deleteNode;
		numItems--;
		
	}
}

void ExerciseList::displayList(void) const
{
	int count = 1; 
	displayList(frontPtr, count); 
	cout << endl; 
}

void ExerciseList::displayList(ExerciseNode* nodePtr, int count) const
{
	
	if (nodePtr != nullptr)
	{
		cout << setw(2) << count << ") Exercise: " << setw(15) << nodePtr->name << " | Weight: " << setw(3) << nodePtr->weight << " lbs. | Sets : ";
		cout << setw(3) << nodePtr->numSets << " | Reps : " << setw(2) << nodePtr->numReps << " | Target : " << nodePtr->target << endl;
		displayList(nodePtr->nextPtr, (count + 1));
	}
}

void ExerciseList::saveData(ofstream& outfile) const
{
	saveData(outfile, frontPtr);
	cout << endl; 
}

void ExerciseList::saveData(ofstream& outfile, ExerciseNode* nodePtr) const
{
	if (nodePtr != nullptr)
	{
		outfile << nodePtr->name << "," << nodePtr->weight << "," << nodePtr->numSets << "," << nodePtr->numReps << "," << nodePtr->target << endl; 
		saveData(outfile, nodePtr->nextPtr); 
	}
}
//End of ExerciseList Class functions ------------------------------------------------------------------------------------------------------

WeightLifter::WeightLifter()
{
}

WeightLifter::~WeightLifter()
{
}

//Opening Files
bool openInFile(ifstream& infile, string inFilename)
{
	infile.open(inFilename);

	if (!infile.is_open())
	{
		return false;
	}
	else if (infile.fail())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void openOutFile(ofstream& outfile, string outFilename)
{
	outfile.open(outFilename);

}

//Loading Data 
void loadLoginInfo(ifstream& infile, vector<string>& usernames, vector<string>& passwords)
{
	string lineParse = "", temp = ""; 
	stringstream ss; 
	while (!infile.eof())
	{
		if (infile.good())
		{
			getline(infile, lineParse);
			if (!infile.fail())
			{
				ss.clear();
				ss.str(lineParse);
				getline(ss, temp, ',');
				usernames.push_back(temp);
				getline(ss, temp);
				passwords.push_back(temp);
			}
		}
	}
 }

//Loging in functions
void saveLoginInfo(ofstream& outfile, vector<string> usernames, vector<string> passwords)
{
	for (int i = 0; i < usernames.size(); i++)
	{
		outfile << usernames.at(i) << "," << passwords.at(i) << endl; 
	}
}

bool doesUserExist(vector<string> usernames, string username, int& currIdx)
{
	if (usernames.size() == 0)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < usernames.size(); i++)
		{
			if (username == usernames.at(i))
			{
				currIdx = i; 
				return true; 
			}
		}
	}
	return false;
}

bool correctPassword(vector<string> passwords, string password, int currIdx)
{
	if (passwords.at(currIdx) == password)
	{
		return true; 
	}
	else
	{
		return false; 
	}
}

void addLogInInfo(vector<string>& usernames, vector<string>& passwords, string username, string password)
{
	usernames.push_back(username); 
	passwords.push_back(password); 
}

//Validating user input functions
char checkInput(char ck1, char ck2, char input) //Invalid input when selecting user
{
	while (input != ck1 && input != ck2)
	{
		cout << "                        *   INVALID INPUT   *                        " << endl;
		cout << "             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "             | NEW User ----------------- SELECT \'" << ck1 << "\' |               " << endl;
		cout << "             | RETURNING User ----------- SELECT \'" << ck2 << "\' |              " << endl;
		cout << "             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "             Selection: ";
		cin >> input;
		toUpperCase(input);
		cout << endl; 
	}
	return input;
}

char checkInput2(char ck1, char ck2, char input) //Invalid input when fixing an incorrect password
{
	while (input != ck1 && input != ck2)
	{
		cout << "                        *   INVALID INPUT   *                        " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~              " << endl;
		cout << "              |  Forgot Password --------- SELECT \'" << ck1 << "\' |              " << endl;
		cout << "              |  TRY AGAIN --------------- SELECT \'" << ck2 << "\' |              " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~              " << endl;
		cout << "              Selection: ";
		cin >> input;
		toUpperCase(input);
		cout << endl; 
	}
	return input;
}

char checkInput3(char ck1, char ck2, char ck3, char ck4, char input)
{
	while (input != ck1 && input != ck2 && input != ck3 && input != ck4)
	{
		cout << "                       *   INVALID INPUT   *                         " << endl;
		cout << "             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "             |  VIEW PLAN -------------- SELECT \'" << ck1 << "\'  |             " << endl;
		cout << "             |  ADD NEW ---------------- SELECT \'" << ck2 << "\'  |             " << endl;
		cout << "             |  EDIT ------------------- SELECT \'" << ck3 << "\'  |             " << endl;
		cout << "             |  SAVE/QUIT -------------- SELECT \'" << ck4 << "\'  |             " << endl;
		cout << "             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "             Selection: ";
		cin >> input;
		cout << endl; 
		toUpperCase(input);
	}
	return input;
}

char checkInput4(char ck1, char ck2, char ck3, char input)
{
	while (input != ck1 && input != ck2 && input != ck3)
	{
		cout << "                        *   INVALID INPUT   *                        " << endl;
		cout << "                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~             " << endl;
		cout << "                |  ADD to FRONT ---------- SELECT \'" << ck1 << "\'  |             " << endl;
		cout << "                |  ADD to BACK ----------- SELECT \'" << ck2 << "\'  |             " << endl;
		cout << "                |  ADD ELSEWHERE --------- SELECT \'" << ck3 << "\'  |             " << endl;
		cout << "                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~             " << endl;
		cout << "                Selection: ";
		cin >> input;
		toUpperCase(input);
	}
	return input;
}

char displayMenu4(char& input)
{
	cout << "*********************************************************************" << endl;
	cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
	cout << "              |  RETURN TO MENU -------- SELECT 'M'  |               " << endl;
	cout << "              |  SAVE/QUIT ------------- SELECT 'Q'  |               " << endl;
	cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
	cout << "              Selection: ";
	cin >> input;
	cout << endl; 
	toUpperCase(input);

	while (input != 'M' && input != 'Q')
	{
		cout << "                       *   INVALID INPUT   *                         " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              |  RETURN TO MENU -------- SELECT 'M'  |               " << endl;
		cout << "              |  SAVE/QUIT ------------- SELECT 'Q'  |               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Selection: ";
		cin >> input;
		toUpperCase(input);
		cout << endl; 
	}

	return input;
}

void newWorkoutPlan(vector<string>& planTitles, vector<WeightLifter>& plans)
{
	WeightLifter temp;
	string title = "", moveOn = "", exercise = "", target = "";
	char add = '\0', choice = '\0';
	int weight = 0, sets = 0, reps = 0, index = 0;

	cout << "*********************************************************************" << endl;
	getline(cin, moveOn);
	cout << "	Please enter a title for this plan: ";
	getline(cin, title);
	cout << endl;

	cout << "	[Press ENTER to begin]" << endl;
	getline(cin, moveOn);

	cout << "	Enter an EXERCISE: ";
	getline(cin, exercise);
	cout << "	Enter the WEIGHT that will be used: ";
	cin >> weight;
	cout << "	Enter the number of SETS: ";
	cin >> sets;
	cout << "	Enter the number of REPS: ";
	cin >> reps;
	getline(cin, moveOn);
	cout << "	Enter the TARGETED MUSCLE: ";
	getline(cin, target);
	cout << endl;
	temp.EL.addToFront(exercise, weight, sets, reps, target);
	cout << "	Add another exercises? Press \'Y\' if YES, otherwise press any OTHER KEY: "; 
	cin >> add;
	toUpperCase(add);

	while (add == 'Y')
	{
		cout << "*********************************************************************" << endl;
		cout << "                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~             " << endl;
		cout << "                |  ADD to FRONT ---------- SELECT 'F'  |             " << endl;
		cout << "                |  ADD to BACK ----------- SELECT 'B'  |             " << endl;
		cout << "                |  ADD ELSEWHERE --------- SELECT 'E'  |             " << endl;
		cout << "                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~             " << endl;
		cout << "                Selection: ";
		cin >> choice;
		cout << endl; 
		toUpperCase(choice);
		choice = checkInput4('F', 'B', 'E', choice);
		getline(cin, moveOn);
		cout << "	Enter an EXERCISE: ";
		getline(cin, exercise);
		cout << "	Enter the WEIGHT that will be used: ";
		cin >> weight;
		cout << "	Enter the number of SETS: ";
		cin >> sets;
		cout << "	Enter the number of REPS: ";
		cin >> reps;
		getline(cin, moveOn);
		cout << "	Enter the TARGETED MUSCLE: ";
		getline(cin, target);
		cout << endl;
		if (choice == 'F')
		{
			temp.EL.addToFront(exercise, weight, sets, reps, target);
		}
		else if (choice == 'B')
		{
			temp.EL.addToRear(exercise, weight, sets, reps, target);
		}
		else
		{
			cout << "	Enter an existing list number to place this exercise: ";
			cin >> index;
			temp.EL.addAtIndex(exercise, weight, sets, reps, target, index);
		}
		cout << "	Add another exercise? Press \'Y\' if YES, otherwise press any OTHER KEY: "; 
		cin >> add;
		cout << endl; 
		toUpperCase(add); 
	} 
	planTitles.push_back(title);
	plans.push_back(temp);
}

void savePlans(ofstream& records, string username, vector<string> planTitles, vector<WeightLifter> plans)
{
	string filename = { username + "_Records.txt" };
	openOutFile(records, filename);
	for (int i = 0; i < planTitles.size(); i++)
	{
		records << planTitles.at(i) << endl;
	}

	cout << endl;

	for (int j = 0; j < plans.size(); j++)
	{
		plans.at(j).EL.saveData(records); 
	}
	records.close(); 
}

void loadRecords(ifstream& infile, string username, vector<string>& planTitles, vector<WeightLifter>& plans)
{
	string filename = { username + "_Records.txt" };
	bool fileExists = false; 
	fileExists = openInFile(infile, filename); 
	string lineParse = "", exercise = "", target = "", trash = ""; 
	int weight = 0, sets = 0, reps = 0; 
	WeightLifter temp; 
	stringstream ss;

	if (fileExists)
	{

		getline(infile, lineParse);
		while (lineParse != "")
		{
			planTitles.push_back(lineParse);
			getline(infile, lineParse);
		}

		while (!infile.eof())
		{
			getline(infile, lineParse);
			if (lineParse != "")
			{
				ss.clear();
				ss.str(lineParse);
				getline(ss, exercise, ',');
				ss >> weight;
				getline(ss, trash, ',');
				ss >> sets;
				getline(ss, trash, ',');
				ss >> reps;
				getline(ss, trash, ',');
				getline(ss, target);
				temp.EL.addToRear(exercise, weight, sets, reps, target);
			}
			else
			{
				plans.push_back(temp);
			}
		}
	}
}
void displayPlan(vector<WeightLifter> plan, int index)
{
	int actualIdx = index - 1; 
	plan.at(actualIdx).EL.displayList();
}
void displayAvailablePlans(vector<string> planTitles)
{
	cout << "************************************************************" << endl;
	cout << "                 [PLANS AVAILABLE TO EDIT]                  " << endl; 
	for (int i = 0; i < planTitles.size(); i++)
	{
		cout << "*" << i + 1 << ") " << setw(15) << planTitles.at(i) << "*" << endl;
	}
	cout << "************************************************************" << endl;
}

void toUpperCase(char& val)
{
		if (val > 96)
		{
			val = val - 32; 
		}
}

