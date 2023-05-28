#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class PatientRecord;
class TNode;
class HospitalData;
class Date;
 

class PatientRecord {
private:
	int PatientID;
	string PatientName, Disease;
	bool Status; //true = admitted, false = discharged
	Date* AdmissionDate;
public:
	friend class TNode;
	PatientRecord();
	~PatientRecord();
	void Input(int);
	void ChangeStatus();
	void Display();
	int GetID();
	bool GetStatus();
	PatientRecord* CopyRecord();
	void ReadPatient(ifstream&);
};

class TNode {
private:
	PatientRecord* Rec;
	TNode* LChild;
	TNode* RChild;
public:
	friend class HospitalData;
	TNode();
	~TNode();
	TNode(PatientRecord*, TNode*, TNode*);
};

class HospitalData {
private:
	TNode* Root;
	int Size;
public:
	HospitalData();
	~HospitalData();
	void Destroy(TNode*&);
	void Insert(PatientRecord*, TNode*&);
	void Insert();
	void Remove(int);
	void Remove(TNode*&, int);
	void deleteNode(TNode*&);
	PatientRecord* getPred(TNode*);
	void Print(int);
	void Print(TNode*, int);
	void PrintAdmitted();
	void PrintAdmitted(TNode*);
	void SearchNode(TNode*&, PatientRecord*&, int, int, int&, bool&);
	PatientRecord* Search(int, int);
	PatientRecord* Search(int);
	void LeftRotation(TNode*&);
	void RightRotation(TNode*&);
	void Split(HospitalData*&, HospitalData*&);
	void Split();
	TNode* CopyTree(TNode*);
	TNode* MedianNode();
	TNode* MedianNode(TNode*, int&);
	void print2DUtil(TNode*, int = 5);
	void print2DUtil();
	void ReadFile();
};

class Date {
private:
	int Day, Month, Year;
public:
	Date();
	void InputDate();
	bool CheckDate();
	void DisplayDate();
	void CopyDate(Date*&);
	void ReadDate(ifstream&);
};
