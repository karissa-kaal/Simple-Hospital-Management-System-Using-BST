#include"20L-0956.h"

void main() {
	bool check = false;
	HospitalData* Hospital = new HospitalData();

	Hospital->ReadFile();

	do {
		cout << "\n\n\n\tEnter your choice:"
			<< "\n\t1:\tEnter a new Patient"
			<< "\n\t2:\tSearch a Patient by ID"
			<< "\n\t3:\tSearch a Patient by ID under a certain level"
			<< "\n\t4:\tDisplay the Patient Record of given ID"
			<< "\n\t5:\tRemove a Patient by ID"
			<< "\n\t6:\tPrint All Patients"
			<< "\n\t7:\tPrint All Admitted Patients"
			<< "\n\t8:\tSplit Data and Display"
			<< "\n\t9:\tChange Status of a Patient"
			<< "\n\t10:\tLeave Program\n\n";
		int x;
		cin >> x;
		int tempid;
		PatientRecord* TempPatient;

		switch(x) {
		case 1:
			Hospital->Insert();
			break;
		case 2:
			cout << "\n\n\tPlease enter ID you want to search:\t"; cin >> tempid;
			TempPatient = Hospital->Search(tempid);
			if (TempPatient)
				TempPatient->Display();
			else
				cout << "\n\n!!No Patient found\n\n";
			break;
		case 3:
			cout << "\n\n\tPlease enter ID you want to search:\t"; cin >> tempid;
			cout << "\n\n\tPlease enter level you want to search from:\t"; cin >> x;

			TempPatient = Hospital->Search(tempid, x);
			if (TempPatient)
				TempPatient->Display();
			else
				cout << "\n\n!!No Patient found\n\n";
			break;
		case 4:
			cout << "\n\n\tPlease enter ID you want to display:\t"; cin >> tempid;
			Hospital->Print(tempid);
			break;
		case 5:
			cout << "\n\n\tPlease enter ID you want to remove:\t"; cin >> tempid;
			Hospital->Remove(tempid);
			break;
		case 6:
			cout << "\n\n\n\t\t!!Following is the whole record of Hospital!!\n\n\n";
			Hospital->print2DUtil();
			break;
		case 7:
			Hospital->PrintAdmitted();
			break;
		case 8:
			Hospital->Split();
			break;
		case 9:
			cout << "\n\n\tPlease enter ID you want to change status of:\t"; cin >> tempid;
			TempPatient = Hospital->Search(tempid);
			if (TempPatient) {
				TempPatient->ChangeStatus();
				cout << "\n\n\tSTATUS CHANGED\n\n";
				TempPatient->Display();
			}
			else
				cout << "\n\n!!No Patient found\n\n";
			break;
		case 10:
			cout << "\n\n\t\t\tMay everyone get well soon. To all the souls we lost, may they rest in peace.\n\n\n";
			check = true;
			break;
		default:
			cout << "\n\n\t!!Invalid Entry!!\n\n";
			break;
		}
	} while (!check);
}