#include <iostream>
#include <iomanip>
#include <string>
#include<limits>

using namespace std;

//Main Data Structure
struct lNode {
	int complaintID;
	string complaint_title;
	string complaint_body;
	string customer_name;
	string customer_address;
	int customer_contactno;
	int accNo;
	string complaint_date;
	struct lNode* nextPtr; /*pointer to next node*/
};

typedef struct lNode ListNode; /* Keyword for struct lNode */
typedef ListNode* ListNodePtr; /* Keyword for ListNode */

//Secondary Data Structure
struct sNode {
	int complaintID;
	string complaint_title;
	string complaint_body;
	string customer_name;
	string customer_address;
	int customer_contactno;
	int accNo;
	string complaint_date;
	struct sNode* nextPtr; /*pointer to next node*/
};

sNode* top = NULL;

//Queue Data Structure
struct qNode {
	int complaintID;
	string complaint_title;
	string complaint_body;
	string customer_name;
	string customer_address;
	int customer_contactno;
	int accNo;
	string complaint_date;
	string action_taken;
	int status;
	struct qNode* nextPtr; /*pointer to next node*/
};

typedef struct qNode qNode; /* Keyword for struct lNode */
typedef qNode* qNodePtr; /* Keyword for ListNode */

qNodePtr head = NULL;
qNodePtr tail = NULL;

int instructions() {

	int choice;

	cout << "Select 1 - Add complaints " << endl;
	cout << "Select 2 - Remove complaints " << endl;
	cout << "Select 3 - Update complaints " << endl;
	cout << "Select 4 - View complaint details " << endl;
	cout << "Select 5 - View all complaints " << endl;
	cout << "Select 6 - Store complaint status " << endl;
	cout << "Select 7 - View closed complaints " << endl;
	cout << "Select 8 - View removed complaints " << endl;
	cout << "Select 0 - Exit " << endl;

	cout << "Enter choice : ";

	for (;;) {

		if (cin >> choice) {
			break;
		}
		else {
			cout << "Please enter a valid option (0-8) : " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		continue;
	}

	cout << endl;

	return choice;
}

string validDate() {

	char date[11]; // mm/dd/yyyy
	int mm, dd, yyyy;
	string vDate;

	for (;;) {

		cin >> date;

		if (strlen(date) < 10 || strlen(date) > 10)
		{
			cout << "Date should be in mm/dd/yyyy format : ";
		}
		else if (strlen(date) == 10)
		{
			char m[3], d[3], y[5];
			int i, j;

			for (i = 0; i < 2; i++)
				m[i] = date[i];

			for (i = 3, j = 0; i < 5; i++, j++) {
				d[j] = date[i];
			}
			for (i = 6, j = 0; i < 10; i++, j++)
				y[j] = date[i];

			mm = atoi(m);
			dd = atoi(d);
			yyyy = atoi(y);

			vDate = to_string(mm) + "/" + to_string(dd) + "/" + to_string(yyyy);

			break;
		}
		else
		{
			cout << "Date should be in mm/dd/yyyy format : ";
			cin.clear();
		}
		continue;
	}
	return vDate;
}

void insert(ListNodePtr* sPtr, int complaintID, string complaint_title, string complaint_body, string customer_name, string customer_address, int customer_contactno, int accNo, string complaint_date) {

	ListNodePtr newPtr = NULL;
	ListNodePtr previousPtr = NULL;
	ListNodePtr afterPtr = NULL;

	newPtr = new ListNode;

	if (newPtr != NULL) { //checking if newPtr is the first node -> If null it is the first node

		newPtr->complaintID = complaintID;
		newPtr->complaint_title = complaint_title;
		newPtr->complaint_body = complaint_body;
		newPtr->customer_name = customer_name;
		newPtr->customer_address = customer_address;
		newPtr->customer_contactno = customer_contactno;
		newPtr->accNo = accNo;
		newPtr->complaint_date = complaint_date;

		newPtr->nextPtr = NULL;
		previousPtr = NULL;
		afterPtr = *sPtr;

		while (afterPtr != NULL && complaintID > afterPtr->complaintID) { //Checks position -> Checks the two nodes on the sides

			previousPtr = afterPtr;
			afterPtr = afterPtr->nextPtr;
		}

		if (previousPtr == NULL) { // For only adding the front/ first node
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;

		}
		else {
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = afterPtr;
		}
	}
	else {
		cout << "Not inserted, no memory available" << complaintID << endl;

	}
}

ListNodePtr addComplaint(ListNodePtr startPtr, int complaintID) {

	string complaint_title;
	string complaint_body;
	string customer_name;
	string customer_address;
	int customer_contactno;
	int accNo;
	string complaint_date;

	int d, m, y = 0;

	cout << endl;
	cout << "Enter Complaint Details" << endl;

	cout << "Complaint ID: " << complaintID << endl;

	cin.ignore();

	cout << "Enter Complaint Title: ";
	getline(cin, complaint_title);

	cout << "Enter Complaint Description: ";
	getline(cin, complaint_body);
	cout << endl;

	cout << "Enter Customer Name: ";
	getline(cin, customer_name);

	cout << "Enter Customer Address: ";
	getline(cin, customer_address);

	cout << "Enter Customer Contact Number: ";

	for (;;) {

		if (cin >> customer_contactno) {
			break;
		}
		else {
			cout << "Please enter a valid contact number : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		continue;
	}

	cout << "Enter Customer Account Number: ";

	for (;;) {

		if (cin >> accNo) {
			break;
		}
		else {
			cout << "Please enter a valid account number : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		continue;
	}

	cout << "Enter Complaint Date (mm/dd/yyyy) : ";
	complaint_date = validDate();
	cout << endl;

	insert(&startPtr, complaintID, complaint_title, complaint_body, customer_name, customer_address, customer_contactno, accNo, complaint_date);

	return startPtr;
}


//Function to check if stack is empty or not
bool isEmpty() {

	if (top == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void printComplaint(ListNodePtr currentPtr) {

	cout << "Complaint ID: " << currentPtr->complaintID << endl;
	cout << "Complaint Title: " << currentPtr->complaint_title << endl;
	cout << "Complaint Description: " << currentPtr->complaint_body << endl;
	cout << "Customer Name: " << currentPtr->customer_name << endl;
	cout << "Customer Address: " << currentPtr->customer_address << endl;
	cout << "Contact Number: " << currentPtr->customer_contactno << endl;
	cout << "Account Number: " << currentPtr->accNo << endl;
	cout << "Complaint Date: " << currentPtr->complaint_date << endl;

}

void printList(ListNodePtr currentPtr, int compID) {

	/*If list is empty*/
	if (currentPtr != NULL) {

		if (compID == NULL) {

			/*While not the end of the list*/
			while (currentPtr != NULL) {

				printComplaint(currentPtr);
				cout << endl;
				currentPtr = currentPtr->nextPtr;
			}
		}
		else {

			while (currentPtr != NULL) {

				if (compID == currentPtr->complaintID) {

					printComplaint(currentPtr);

					cout << endl;

					return;

				}
				else {
					currentPtr = currentPtr->nextPtr;
				}
			}
		}

	}
	else {
		cout << "No enquiries made yet. List empty." << endl;


	}


}

void printRList() {

	if (isEmpty()) {
		cout << "Stack is empty." << endl;
	}

	else {
		while (top != NULL) {

			sNode* temp = top;

			while (temp != NULL) {

				cout << "Complaint ID: " << temp->complaintID << endl;
				cout << "Complaint Title: " << temp->complaint_title << endl;
				cout << "Complaint Description: " << temp->complaint_body << endl;
				cout << "Customer Name: " << temp->customer_name << endl;
				cout << "Customer Address: " << temp->customer_address << endl;
				cout << "Contact Number: " << temp->customer_contactno << endl;
				cout << "Account Number: " << temp->accNo << endl;
				cout << "Complaint Date: " << temp->complaint_date << endl;
				cout << endl;

				temp = temp->nextPtr;
			}

			return;
		}
	}
}

int update() {

	int ans = 0;

	cout << "1 - Update complaint title" << endl;
	cout << "2 - Update complaint description" << endl;
	cout << "3 - Update customer name" << endl;
	cout << "4 - Update customer address" << endl;
	cout << "5 - Update customer contact number" << endl;
	cout << "6 - Update account number" << endl;
	cout << "7 - Update lodge date" << endl;
	cout << "0 - Cancel" << endl;
	

	for (;;) {

		if (cin >> ans) {
			break;
		}
		else {
			cout << "Please enter a valid option (0-7) : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		continue;
	}

	return ans;

}

void updateComplaint(ListNodePtr currentPtr) {

	int ans = update();

	int customer_contactno;
	int accNo;

	while (ans != 0) {

		cin.ignore();

		switch (ans) {

		case 1:

			cout << "Enter Complaint Title: ";
			getline(cin, currentPtr->complaint_title);
			break;

		case 2:
			cout << "Enter Complaint Description: ";
			getline(cin, currentPtr->complaint_body);
			cout << endl;
			break;

		case 3:
			cout << "Enter Customer Name: ";
			getline(cin, currentPtr->customer_name);
			break;

		case 4:

			cout << "Enter Customer Address: ";
			getline(cin, currentPtr->customer_address);
			break;

		case 5:
			cout << "Enter Customer Contact Number: ";

			for (;;) {

				if (cin >> customer_contactno) {
					break;
				}
				else {
					cout << "Please enter a valid contact number : ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				continue;
			}

			currentPtr->customer_contactno = customer_contactno;

			break;

		case 6:
			cout << "Enter Customer Account Number: ";
			for (;;) {

				if (cin >> accNo) {
					break;
				}
				else {
					cout << "Please enter a valid account number : ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				continue;
			}

			currentPtr->customer_contactno = accNo;
			break;

		case 7:
			cout << "Enter Complaint Date (mm/dd/yyyy) : ";
			currentPtr->complaint_date = validDate();
			break;

		case 0:
			cout << "Exit";
			break;

		default:
			cout << "Invalid." << endl;
			break;

		}
		ans = update();
	}
}

//Function to insert an element in stack
bool push(ListNodePtr currentPtr) {

	sNode* rPtr = new sNode();

	rPtr->complaintID = currentPtr->complaintID;
	rPtr->complaint_title = currentPtr->complaint_title;
	rPtr->complaint_body = currentPtr->complaint_body;
	rPtr->customer_name = currentPtr->customer_name;
	rPtr->customer_address = currentPtr->customer_address; 
	rPtr->customer_contactno = currentPtr->customer_contactno;
	rPtr->accNo = currentPtr->accNo;
	rPtr->complaint_date = currentPtr->complaint_date;
	rPtr->nextPtr = top;
	top = rPtr;

	return true;
}


int removeComplaint(ListNodePtr* sPtr, int complaintID) {

	ListNodePtr previousPtr = NULL;
	ListNodePtr afterPtr = NULL;
	ListNodePtr tempPtr = NULL;

	if (complaintID == (*sPtr)->complaintID) {

		tempPtr = *sPtr;

		bool addSec = push(*sPtr);

		if (addSec) {

			*sPtr = (*sPtr)->nextPtr;
			delete(tempPtr);
			cout << "Added to secondary structure" << endl;
			return complaintID;

		}
		else {
			cout << "Error adding to secondary structure" << endl;
		}

	}
	else {
		previousPtr = *sPtr;
		afterPtr = (*sPtr)->nextPtr;

		//Loops until it finds the node with the complaint ID
		while (afterPtr != NULL && afterPtr->complaintID != complaintID) { // If after == NULL (1st) -> There is only one node in the list 
			previousPtr = afterPtr;
			afterPtr = afterPtr->nextPtr;

		}
		if (afterPtr != NULL) {
			tempPtr = afterPtr;
			bool addSec = push(tempPtr);

			if (addSec) {
				previousPtr->nextPtr = afterPtr->nextPtr;
				delete(tempPtr);
				cout << "Added to secondary data structure" << endl;
				return complaintID;

			}
			else {
				cout << "Error adding to secondary data structure" << endl;
			}

		}
	}
	return '\0';
}




void enqueue(ListNodePtr currentPtr) {

	qNode* ptr = new qNode();

	ptr->complaintID = currentPtr->complaintID;
	ptr->complaint_title = currentPtr->complaint_title;
	ptr->complaint_body = currentPtr->complaint_body;
	ptr->customer_name = currentPtr->customer_name;
	ptr->customer_address = currentPtr->customer_address; 
	ptr->customer_contactno = currentPtr->customer_contactno;
	ptr->accNo = currentPtr->accNo;
	ptr->complaint_date = currentPtr->complaint_date;
	ptr->action_taken = "NA";
	ptr->status = 1;
	ptr->nextPtr = NULL;

	if (head == NULL) {
		head = ptr;
		tail = ptr;
	}
	else {
		tail->nextPtr = ptr;
		tail = ptr;
	}

}

void viewQueue() {

	qNodePtr link = head;
	string status;

	while (link != NULL) {

		cout << "Complaint ID: " << link->complaintID << endl;
		cout << "Complaint Title: " << link->complaint_title << endl;
		cout << "Complaint Description: " << link->complaint_body << endl;
		cout << "Customer Name: " << link->customer_name << endl;
		cout << "Customer Address: " << link->customer_address << endl;
		cout << "Contact Number: " << link->customer_contactno << endl;
		cout << "Account Number: " << link->accNo << endl;
		cout << "Complaint Date: " << link->complaint_date << endl;
		cout << "Action taken: " << link->action_taken << endl;

		if (link->status == 1) {
			status = "Open";
		}
		else if (link->status == 2) {
			status = "Closed";
		}
		else {
			status = "Cannot address";
		}

		cout << "Status: " << status << endl;
		cout << endl;
		link = link->nextPtr;
	}

}

//Check whether queue is empty
bool qEmpty() {
	if (head == NULL && tail == NULL) {
		return true;
	}
	else {
		return false;
	}
}

int updateStatus() {

	int ans = 0;

	cout << endl;
	cout << "1 - Update action taken" << endl;
	cout << "2 - Update complaint status" << endl;
	cout << "3 - View stored complaint statuses" << endl;
	cout << "0 - Cancel" << endl;

	for (;;) {

		if (cin >> ans) {
			break;
		}
		else {
			cout << "Please enter a valid option (0-3) : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		continue;
	}


	return ans;

}

void storeStatus() {

	if (!(qEmpty())) {

		int ans = updateStatus();

		string action_taken;
		int status;

		while (ans != 0) {

			cin.ignore();

			switch (ans) {

			case 1:

				cout << "Enter Action Taken: ";
				getline(cin, tail->action_taken);
				break;

			case 2:
				cout << "Enter Complaint Status: " << endl;
				cout << "1 - Open" << setw(27) << "2 - Closed" << setw(27) << "3 - Cannot Address" << endl;
				cin >> tail->status;
				cout << endl;
				break;

			case 3:
				viewQueue();
				break;

			case 0:
				cout << "Exit";
				break;

			default:
				cout << "Invalid." << endl;
				break;

			}
			ans = updateStatus();
		}
	}
	else {
		cout << "No queue yet." << endl;
	}

}

void viewClosed() {

	if (!(qEmpty())) {

		qNodePtr link = head;
		string statusComp;

		while (link != NULL) {

			if (link->status == 2) {

				statusComp = "Closed";

				cout << "Complaint ID: " << link->complaintID << endl;
				cout << "Complaint Title: " << link->complaint_title << endl;
				cout << "Complaint Description: " << link->complaint_body << endl;
				cout << "Customer Name: " << link->customer_name << endl;
				cout << "Contact Number: " << link->customer_contactno << endl;
				cout << "Customer Address: " << link->customer_address << endl;
				cout << "Account Number: " << link->accNo << endl;
				cout << "Complaint Date: " << link->complaint_date << endl;
				cout << "Action taken: " << link->action_taken << endl;
				cout << "Status: " << statusComp << endl;
				cout << endl;
			}

			link = link->nextPtr;
		}

	}
	else {
		cout << "Queue is empty" << endl;
	}
}

void findStatus(int complaintID) {

	qNodePtr link = head;

	while (link != NULL) {

		if (link->complaintID == complaintID) {

			link->status = 3;
			link->complaintID = 000;

		}
		else {

			link = link->nextPtr;
		}
	}

}

ListNodePtr searchComplaintID(ListNodePtr currentPtr, int complaintID) {

	ListNodePtr tempPtr = currentPtr;

	if (tempPtr != NULL) {

		while (tempPtr != NULL) {

			if (complaintID == tempPtr->complaintID) {
				return tempPtr;
				break;
			}
			else {
				tempPtr = tempPtr->nextPtr;
			}
		}
		return NULL;

	}
	else {
		cout << "No enquires." << endl;
		return NULL;
	}

}

int checkValidID() {

	int complaintID;

	cout << "Enter complaint ID : ";

	for (;;) {

		if (cin >> complaintID) {
			break;
		}
		else {
			cout << "Please enter a valid complaint ID : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		
		continue;
	}

	return complaintID;
}

void main()
{
	ListNodePtr startPtr = NULL;

	int choice = 0;

	int complaintID;

	ListNodePtr complaintExists;

	choice = instructions();

	while (choice != 0) {

		switch (choice) {

		case 1:

			complaintID = checkValidID();

			complaintExists = searchComplaintID(startPtr, complaintID);

			if (complaintExists == NULL) {

				startPtr = addComplaint(startPtr, complaintID);

			}
			else {
				cout << "Enquiry is already registered." << endl;
			}
			break;

		case 2:

			complaintID = checkValidID();

			complaintExists = searchComplaintID(startPtr, complaintID);

			if (complaintExists != NULL) {

				int removedID = removeComplaint(&startPtr, complaintID);
				findStatus(removedID);
				cout << "Removed complaint ID : " << removedID << endl;

				cout << endl;

			}
			else {
				cout << "Complaint does not exist." << endl;
			}

			break;
		case 3:

			complaintID = checkValidID();

			complaintExists = searchComplaintID(startPtr, complaintID);

			if (complaintExists != NULL) {

				updateComplaint(complaintExists);

			}
			else {
				cout << "Complaint does not exist." << endl;
			}

			break;

		case 4:

			complaintID = checkValidID();

			complaintExists = searchComplaintID(startPtr, complaintID);

			if (complaintExists != NULL) {

				printList(startPtr, complaintID);

			}
			else {
				cout << "Complaint does not exist." << endl;
			}

			break;


		case 5:

			printList(startPtr, NULL);
			break;

		case 6:

			complaintID = checkValidID();

			complaintExists = searchComplaintID(startPtr, complaintID);

			if (complaintExists != NULL) {

				enqueue(complaintExists);
				storeStatus();

			}
			else {
				cout << "Complaint does not exist." << endl;
			}

			break;

		case 7:

			viewClosed();
			break;

		case 8:
			printRList();
			break;

		case 0:
			cout << "Exit" << endl;
			break;

		default:
			cout << "Invalid choice" << endl;
			break;
		}

		choice = instructions();
	}
}