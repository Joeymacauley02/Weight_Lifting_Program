/*


*/

#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cctype>

#ifndef WL_APP
#define WL_APP

using namespace std; 

class ExerciseList
{
protected: 
	struct ExerciseNode
	{
		string name = "";
		int weight = 0; 
		int numSets = 0; 
		int numReps = 0; 
		string target = "";
		ExerciseNode* nextPtr = nullptr; 
		ExerciseNode* prevPtr = nullptr; 
	};

	ExerciseNode* frontPtr; 
	ExerciseNode* rearPtr; 
	int numItems; 

public: 
	ExerciseList(); 
	~ExerciseList(); 

	bool isEmpty(); 
	void clear(); 

	void addToFront(string, int, int, int, string);
	void addToRear(string, int, int, int, string);
	void addAtIndex(string, int, int, int, string, int);
	void removeFromFront(); 
	void removeFromRear(); 
	void removeAtIndex(int); 
	void displayList(void) const; 
	void displayList(ExerciseNode*, int) const;
	void saveData(ofstream&) const; 
	void saveData(ofstream&, ExerciseNode*) const;
	int getNumItems() { return numItems; }
};

class WeightLifter
{
public: 
	WeightLifter(); 
	~WeightLifter(); 
	ExerciseList EL; 
};

bool openInFile(ifstream&, string);
void openOutFile(ofstream&, string);
void loadLoginInfo(ifstream&, vector<string>&, vector<string>&);
void saveLoginInfo(ofstream&, vector<string>, vector<string>);
bool doesUserExist(vector<string>, string, int&); 
bool correctPassword(vector<string>, string, int); 
void addLogInInfo(vector<string>&, vector<string>&, string, string);
char checkInput(char, char, char);
char checkInput2(char, char, char);
char checkInput3(char, char, char, char, char);
char displayMenu4(char& input);
char checkInput4(char ck1, char ck2, char ck3, char input);
void displayAvailablePlans(vector<string> planTitles);
void toUpperCase(char& val);
void newWorkoutPlan(vector<string>& planTitles, vector<WeightLifter>& plans);
void savePlans(ofstream& outfile, string username, vector<string> planTitles, vector<WeightLifter> plans);
void loadRecords(ifstream& infile, string username, vector<string>& planTitles, vector<WeightLifter>& plans);
void displayPlan(vector<WeightLifter> plan, int index);
#endif