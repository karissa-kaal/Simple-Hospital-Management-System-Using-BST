#include"20L-0956.h"

//---------------------------------------------------------------------------------------------------------------
//class PatientRecord

//class members
//int PatientID;
//string PatientName, Disease;
//bool Status; // false = admitted, true = discharged
//Date* AdmissionDate;


PatientRecord::PatientRecord() {
	//constructor
	PatientID = 0;
	PatientName = Disease = "";
	Status = false;
	AdmissionDate = new Date();
}

PatientRecord::~PatientRecord() {
	//destructor
	if (AdmissionDate)
		delete AdmissionDate;
}

void PatientRecord::Input(int size) {
	//takes inout of patient
	cin.ignore();
	cout << "\nPlease enter the full name of Patient:\t";
	getline(cin, PatientName);
	cout << "\nPlease enter the disease of patient:\t";
	getline(cin, Disease);
	cout << "\nIf the patient is admitted then enter 0 if dischareged enter 1:\t";
	int x; cin >> x;
	if (x == 1)
		Status = true;
	else if (x == 0)
		Status = false;
	else{
		cout << "\nIncorrect option. But currently the status is set to be admitted. \nIf you want to discharge the patient, please use main menu.";
		Status = false;
	}
	AdmissionDate->InputDate();
	cout << "\nPatient Id:\t";
	cin >> PatientID;
	//PatientID = 111111 + size;
}
	
void PatientRecord::ChangeStatus() {
	//changes the status of patient
	if (Status)
		Status = false;
	else
		Status = true;
}
	
void PatientRecord::Display() {
	//displays the patient
	cout << "\n---------------------------------------------------------------------------------------------------------------\n";
	cout << "\n\tPatient ID:\n\t\t\t" << PatientID << "\n\tPatient Name:\n\t\t\t" << PatientName << "\n\tDisease:\n\t\t\t" << Disease;
	cout << "\n\tStatus of Patient:\n\t\t\t";
	(!Status) ? cout << "Admitted" : cout << "Discharged";
	cout << "\n\tDate of Admission:\n\t\t\t"; 
	AdmissionDate->DisplayDate();
}

int PatientRecord::GetID() {
	//return ID
	return PatientID;
}

bool PatientRecord::GetStatus() {
	//return status
	return Status;
}

PatientRecord* PatientRecord::CopyRecord() {
	//deep copy of the patient record
	PatientRecord* Temp = new PatientRecord;
	Temp->PatientID = PatientID;
	Temp->PatientName = PatientName;
	Temp->Disease = Disease;
	Temp->Status = Status;
	AdmissionDate->CopyDate(Temp->AdmissionDate);
	return Temp;
}

void PatientRecord::ReadPatient(ifstream& fin) {
	//reading patient from file
	fin >> PatientID;
	fin.ignore();
	getline(fin, PatientName);
	getline(fin, Disease);
	int x;
	fin >> x;
	Status = x;
	AdmissionDate->ReadDate(fin);
	//fin >> PatientID;
}

//---------------------------------------------------------------------------------------------------------------
//class TNode

//class members
//PatientRecord* Rec;
//TNode* LChild;
//TNode* RChild;


TNode::TNode() {
	//constructor
	Rec = NULL;
	LChild = NULL;
	RChild = NULL;
}

TNode::~TNode() {
	//destructor
	if (Rec)
		delete Rec;
}

TNode::TNode(PatientRecord* TempRec, TNode* Left, TNode* Right) {
	//overloaded constructor
	Rec = TempRec;
	LChild = Left;
	RChild = Right;
}

//---------------------------------------------------------------------------------------------------------------
//class HospitalData 

//class members
//TNode* Root;
//int Size;


HospitalData::HospitalData() {
	//constructor
	Root = NULL;
	Size = 0;
}

void HospitalData::Destroy(TNode*& curr) {
	//deleting recursively
	if (curr) {
		Destroy(curr->LChild);
		Destroy(curr->RChild);
		delete curr;
	}
}

HospitalData::~HospitalData() {
	//destructor
	Destroy(Root);
}

void HospitalData::Insert(PatientRecord* TempRec, TNode*& curr) {
	//This function takes a patient record as an input parameter, 
	//inserts it in the BST based on the patient  id, 
	//and moves the newly inserted node to the root. 
	//It is assumed that the newly inserted node will be  accessed shortly
	if (curr == NULL) {
		curr = new TNode(TempRec, NULL, NULL);
		Size++;
		int currlevel = 0;
		bool flag = false;
		SearchNode(Root, TempRec, curr->Rec->GetID(), 0, currlevel, flag); //searching and bringing at root
		cout << "\nPatient data successfully stored under the patient ID:\t" << TempRec->GetID()
			 << "\n---------------------------------------------------------------------------------------------------------------\n";
		if (Root == NULL)
			Root = curr;
	}
	else if (curr->Rec->GetID() == TempRec->GetID()) {
		cout << "\n\n\t!!ERROR!!\tCannot enter user as the ID already exists!!";
		return;
	}
	else if (curr->Rec->GetID() > TempRec->GetID())
		Insert(TempRec, curr->LChild);
	else if (curr->Rec->GetID() < TempRec->GetID())
		Insert(TempRec, curr->RChild);

}
	
void HospitalData::Insert() {
	//call this function when new patient is to be added
	PatientRecord* NewP = new PatientRecord();
	NewP->Input(Size);	//to take the patient details
	Insert(NewP, Root);	//inserting in tree
}

void HospitalData::Remove(int id) {
	//This function takes a patient id as an input parameter and 
	//removes the patient record from the  tree
	//wrapper
	Remove(Root, id);
}

void HospitalData::Remove(TNode*& curr, int id) {
	//This function takes a patient id as an input parameter and 
	//removes the patient record from the  tree

	if (curr) {
		if (id == curr->Rec->GetID()) {
			deleteNode(curr);
			cout << "\n\n\n\t!!Patient Deleted!!\n\n\n";
		}
		else if (id > curr->Rec->GetID())
			Remove(curr->RChild, id);
		else if (id < curr->Rec->GetID())
			Remove(curr->LChild, id);
		else
			cout << "\n\n\n~~~~~~~~!!Patient Not Found!!~~~~~~~~\n\n\n";
	}
	else
		cout << "\n\n\n~~~~~~~~!!Patient Not Found!!~~~~~~~~\n\n\n";
}

PatientRecord* HospitalData::getPred(TNode* curr) {
	//to replace a deleting record
	while (curr->RChild != NULL)
		curr = curr->RChild;
	return curr->Rec;
}

void HospitalData::deleteNode(TNode*& curr) {
	//delete a record
	TNode* temp = curr;

	if (curr->LChild == NULL) {
		curr = curr->RChild;
		delete temp;
	}
	else if (curr->RChild == NULL) {
		curr = curr->LChild;
		delete temp;
	}

	else {
		PatientRecord* Pred = getPred(curr->LChild);
		curr->Rec = Pred;
		Remove(curr->LChild, Pred->GetID());
	}
}

void HospitalData::Print(TNode* curr, int id) {
	//searching and displaying
	if (curr) {
		if (id == curr->Rec->GetID())
			curr->Rec->Display();
		else if (id > curr->Rec->GetID())
			Print(curr->RChild, id);
		else if (id < curr->Rec->GetID())
			Print(curr->LChild, id);
		else
			cout << "\n\n\n~~~~~~~~!!Patient Not Found!!~~~~~~~~\n\n\n";
	}
	else
		cout << "\n\n\n~~~~~~~~!!Patient Not Found!!~~~~~~~~\n\n\n";
}

void HospitalData::Print(int id) {
	//This function takes patient id (pid) as input parameter and outputs the record
	//wrapper
	Print(Root, id);
}

void HospitalData::PrintAdmitted(TNode* curr) {
	//This function outputs all the records of patients whose status is admitted in sorted order  according to the pid
	//false = admitted , true = discharged
	if (curr) {
		PrintAdmitted(curr->LChild);
		if (curr->Rec->GetStatus() == false)
			curr->Rec->Display();
		PrintAdmitted(curr->RChild);
	}
}

void HospitalData::PrintAdmitted() {
	//This function outputs all the records of patients whose status is admitted in sorted order  according to the pid
	//wrapper
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\n\tFollowing are the currently admitted patients:\n\n";
	PrintAdmitted(Root);
}
	
void HospitalData::SearchNode(TNode*& curr, PatientRecord*& TempRec, int id, int Klevel, int& currlevel, bool& flag) {
	//for searching record and arranging the tree
	//flag is used for rotation indication
	//when flag = true, we need to rotate acc to level difference
	if (curr) {
		if (curr->Rec->GetID() == id) {
			flag = true;
			TempRec = curr->Rec;
		}
		else if (curr->Rec->GetID() < id) {
			SearchNode(curr->RChild, TempRec, id, Klevel, ++currlevel, flag);
			if (flag) {
				if (currlevel > Klevel) //rotate only when level is greater
					LeftRotation(curr);
				currlevel--;	//-- becuase level is now decreased
			}
		}
		else {
			SearchNode(curr->LChild, TempRec, id, Klevel, ++currlevel, flag);
			if (flag) {
				if (currlevel > Klevel)	//rotate only when level is greater
					RightRotation(curr);
				currlevel--;	//-- becuase level is now decreased
			}
		}

	}
	else {
		cout << "\n\n\t!!ERROR!!\tPatient under ID " << id << " not found!!";
		return;
	}
}

void HospitalData::LeftRotation(TNode*& X) {
	//simple left rotation
	TNode* Orphan = X->RChild->LChild;
	TNode* Y = X->RChild;

	Y->LChild = X;
	X->RChild = Orphan;
	X = Y;
}

void HospitalData::RightRotation(TNode*& X) {
	//simple right rotation
	TNode* Orphan = X->LChild->RChild;
	TNode* Y = X->LChild;

	Y->RChild = X;
	X->LChild = Orphan;
	X = Y;
}

PatientRecord* HospitalData::Search(int id, int level) {
	//This function takes a patient pid and level number k as input parameters. 
	//It searches the patient  with the given pid and returns the patient record if the patient exists. 
	//Otherwise, it must indicate that  patient does not exist. Moreover, if a patient record is found, 
	//then move it to level k
	PatientRecord* Patient = NULL;
	int currlevel = 0;
	bool flag = false;

	//searching and arranging - Patient passed by refernce for ease
	SearchNode(Root, Patient, id, level, currlevel, flag); 
	return Patient;
}

PatientRecord* HospitalData::Search(int id) {
	//in case level is not given, make it 1, next to root
	return Search(id, 1);	
}
	
void HospitalData::Split(HospitalData*& LeftTree, HospitalData*& RightTree) {
	//This function splits the given BST tree into two BST trees in linear time (O(n)) and returns the  second tree
	
	PatientRecord* Patient = NULL;
	int currlevel = 0;
	bool flag = false;

	//returns median Node 
	TNode* Median = MedianNode();	
	cout << "\n\nMEDIAN IS:\n\n";

	//display median
	Median->Rec->Display();	

	//arranges the tree
	SearchNode(Root, Patient, Median->Rec->GetID(), 0, currlevel, flag);	

	//check if the median is there and tree display
	print2DUtil();	

	//copy both trees
	LeftTree->Root = CopyTree(Root->LChild);	
	LeftTree->Size = Size / 2;
	RightTree->Root = CopyTree(Root->RChild);	
	RightTree->Size = Size / 2;
}

void HospitalData::Split() {
	//This function splits the given BST tree into two BST trees in linear time (O(n)) and returns the  second tree
	//wrapper
	//creating these two to pass in function
	HospitalData* Left = new HospitalData();
	HospitalData* Right = new HospitalData();


	Split(Left, Right);

	//display
	if (Left) {
		cout << "\n\n\n\tFollowing is the Left Split Tree:\n\n";
		Left->print2DUtil();
	}
		
	if (Right) {
		cout << "\n\n\n\tFollowing is the Right Split Tree:\n\n";
		Right->print2DUtil();
	}
}

TNode* HospitalData::CopyTree(TNode* other)
{	//deep copy tree

	//at null
	if (other == NULL)
		return NULL;

	TNode* newNode = new TNode;

	//copy
	if (other->Rec != NULL)
		newNode->Rec = other->Rec->CopyRecord();
	
	//children
	newNode->LChild = CopyTree(other->LChild);
	newNode->RChild = CopyTree(other->RChild);

	return newNode;
}

TNode* HospitalData::MedianNode(TNode* Curr, int& CurrCount) {
	//recursively finding median
	if (Curr) {
		//left
		TNode* Temp = MedianNode(Curr->LChild, CurrCount);

		//in case temp returns return temp
		if (Temp)
			return Temp;

		//continuosly checking the count, when it reaches mid, return the curr
		if (CurrCount == Size / 2)
			return Curr;

		//increment
		CurrCount++;

		//right
		return MedianNode(Curr->RChild, CurrCount);
	}
	else
		return NULL;
}

TNode* HospitalData::MedianNode() {
	//wrapper 
	int CurrCount = 0;
	return MedianNode(Root, CurrCount);
}

void HospitalData::print2DUtil(TNode* root, int space) {
	//Provided by TA

	const int COUNT = 10;
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->RChild, space);

	// Print current node after space
	// count
	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->Rec->GetID() << "\n";

	// Process left child
	print2DUtil(root->LChild, space);
}

void HospitalData::print2DUtil() {
	//wrapper
	print2DUtil(Root, Size);
}

void HospitalData::ReadFile() {
	//for my ease of input, so i dont have to add patients manually all the time
	ifstream fin;
	fin.open("HospitalData.txt");

	if (!fin.is_open()) {
		cout << "\n\n\n\n!!!!!!NO DATA FILE AVAILABLE!!!!!!\n\n\n\n";
	}
	else {
		while (!fin.eof()) {
			PatientRecord* NewPatient = new PatientRecord();
			NewPatient->ReadPatient(fin);
			Insert(NewPatient, Root);
			print2DUtil();
		}
	}
}

//---------------------------------------------------------------------------------------------------------------
//class Date

//class members
//int Day, Month, Year;

//a basic date class

Date::Date() {
	//constructor
	Day = Month = Year = 0;
}
	
void Date::InputDate() {
	//take input date
	int d, m, y;
	do {
		if(!CheckDate() && Day != 0 && Month != 0 && Year != 0)
			cout << "\n\tYou entered wrong date. Try Again.\n\n\n";
		cout << "\n\tEnter the day:\t"; cin >> d; Day = d;
		cout << "\n\tEnter the month:\t"; cin >> m; Month = m;
		cout << "\n\tEnter the year:\t"; cin >> y; Year = y;
	} while (!CheckDate());
	
}
	
bool Date::CheckDate() {
	//check if date is correct
	if (Day == 0 && Month == 0 && Year == 0)
		return false;
	if (Month > 12 || Month < 1)
		return false;
	if (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12)
		if (Day > 31 || Day < 1)
			return false;
	if (Year < 1999 || Year > 2021)
		return false;
	return true;
}
	
void Date::DisplayDate() {
	//display date
	cout << Day << "/" << Month << "/" << Year;
}

void Date::CopyDate(Date*& Temp) {
	//copy
	Temp->Day = Day;
	Temp->Month = Month;
	Temp->Year = Year;
}

void Date::ReadDate(ifstream& fin) {
	//reading from file
	fin >> Day;
	fin >> Month;
	fin >> Year;
}