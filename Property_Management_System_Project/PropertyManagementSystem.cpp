#include "Property.h"

// Dashboard
//__________
void mainMenu() {
	std::cout<<"\n\t\t\t\t__________________________\n"
		      << "\t\t\t\t*********DASHBOARD********\n"
		      << "\t\t\t\t__________________________\n\n";
	std::cout << "1. Add Property\n"
		      << "2. Update Property\n"
		      << "3. View Properties\n"
		      << "4. Delete Property\n"
		      << "5. Display Property\n"
		      << "6. Display Sales Revenue\n"                   
		      << "7. Export to a CSV File\n"
		      << "8. Import from a CSV File\n";
	int option;
	std::cout << "-------------------\n";
	std::cout << "Select Option: ";
	bool flag = true;
	do {
		flag = true;
		std::cin >> option;

		if (std::cin.fail()) {
			flag = false;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Please Enter a Number within range!: ";
		}
		else if (option < 1 || option>8) {
			flag = false;
			std::cout << "Please Select Option within range!: ";
		}

	} while (flag == false);
	Property caller;

	switch (option) {

	case 1:
		caller.AddProperty("Property.dat");
		break;

	case 2:
		caller.updateProperty("Property.dat");
		break;

	case 3:
		caller.DisplayAllProperties("Property.dat");
		break;

	case 4:
		caller.deleteProperty("Property.dat");
		break;

	case 5: {
		std::cout << "\nWant to Display\n"
			<< "\t1. Search Property By ID\n"
			<< "\t2. Display All Properties Based On Status\n";

		int option;
		std::cout << "----------------\n";
		std::cout << "Select Option: ";
		bool flag = true;
		do {
			flag = true;
			std::cin >> option;

			if (std::cin.fail()) {
				flag = false;
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "Please Enter a Number within range!: ";
			}
			else if (option < 1 || option>2) {
				flag = false;
				std::cout << "Please Select Option within range!: ";
			}

		} while (flag == false);

		switch (option) {
		case 1: {
			std::string id;
			std::cout << "Enter searching ID: ";
			std::cin >> id;
			caller.DisPropertyID("Property.dat", id);
			break;
		}
		case 2:
		{
			char op;
			std::cout<< "a.Sold\n"
				     << "b.Unsold\n";
			std::cout << "----------------\n";
			std::cout << "Select Option: ";
			bool flag = true;
			do {
				true;
				std::cin >> op;
				if (option != 'a' && option != 'b' && option != 'A' && option != 'B') {
					std::cout << "Enter a valid option (A/a/B/b): ";
					bool flag = false;
				}

			} while (flag == false);

			switch (op) {
			case 'A':
				caller.DisPropertyStatus("Property.dat", "Sold");
				break;
			case 'a':
				caller.DisPropertyStatus("Property.dat", "Sold");
				break;
			case 'B':
				caller.DisPropertyStatus("Property.dat", "Unsold");
				break;
			case 'b':
				caller.DisPropertyStatus("Property.dat", "Unsold");
				break;
			}
		}
		
		}

		}
	case 6:
		caller.dispSalesRevenue("Property.dat");
	case 7:
		caller.exportToCSV("Property.dat");
		break;
	case 8: {
		std::string f;
		std::cout << "Enter CSV File name: ";
		std::cin >> f;
		caller.importFromCSV("Property.dat", f);
		break;
	}
	}

}
int main() {

	std::cout << "\t\t\t Welcome To Property Management System\n"
		<< "\t\t\t___________________________________________\n\n";
	
	char ch;
	bool flag = true;
	do {
		mainMenu();
		std::cout << "\nWant to continue\n"
			<< "1.Y (Yes)\n"
			<< "2.N (No)\n"
			<<"----------------------";
		std::cout << "\nChoose Option (Enter Y/N): ";

		std::cin >> ch;
		
		while (ch != 'Y' && ch != 'N' && ch != 'y' && ch != 'n') {
			std::cout << "Please Enter Valid Option: ";
			std::cin >> ch;
		}

	} while (ch=='Y' || ch=='y');

}