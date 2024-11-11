#include "Property.h"

                                                   // Record Existence By ID (completed)  
                                                   //___________________________________

bool Property::operator == (const Property& temp) {

	for (int i = 0; i < 9; i++) {
		if (this->ID[i] != temp.ID[i]) {
			return false;
		}
	}
	return true;
}

                                                   // Record Existence By ID (completed)
                                                   //-----------------------

bool Property::operator != (const Property& temp) {
	return !(*this == temp);
}

                                                   // Record Existence (Duplicate Avoid)
                                                   //__________________________

bool Property::isRecordExist(std::string fileName) {
	std::ifstream infile;
	infile.open(fileName, std::ios::binary | std::ios::ate);
	if (!infile.is_open()) {
		std::cout << "File could not open";
		return false;
	}

	auto size = infile.tellg();
	infile.seekg(0, std::ios::beg);

	int num = size / sizeof(Property);
	Property* AllProperties = new Property[num];

	infile.read((char*)AllProperties, size);
	infile.close();

	for (int i = 0; i < num; i++) {
		if (*this == AllProperties[i]) {
			delete[] AllProperties;  
			return true;
		}
	}

	delete[] AllProperties;  
	return false;
}

                                                   // Adding Property (completed)
                                                   //_______________________________

void Property::AddProperty(std::string fileName) {
	std::cout << "\nPlease Enter Property Details\n"
		      << "-----------------------------\n";
	Property p;
	std::cin >> p;

	std::ofstream outfile;
	outfile.open(fileName, std::ios::binary | std::ios::app);

	if (outfile.is_open()) {
		if (!p.isRecordExist(fileName)) {

			outfile.write((char*)&p, sizeof(Property));
			std::cout << "Successfully Added.\n";
			outfile.close();

		}

		else {
			std::cout << "\n-------\n"
				<< "WARNING:  Record Already exists!\n"
				<< "_______\n\n";
			outfile.close();

		}

	}

	else {
		std::cout << "\n-------\n"
			<< "WARNING: The File could not opened!\n"
			<< "_______\n\n";

	}

}

                                                   // Property Deletion (completed)
                                                   // _____________________________

void Property::deleteProperty(std::string fileName) {
	std::string str;
	std::cout << "\nEnter Property ID: ";
	std::cin >> str;
	Property temp, stemp;
	strcpy_s(temp.ID, sizeof(temp.ID), str.c_str());

	std::ifstream f(fileName, std::ios::binary);
	
	if (f.is_open()) {
		f.seekg(0, std::ios::end);
		long check = f.tellg();
		f.seekg(0, std::ios::beg);

		if (check != 0) {
			std::ofstream of("Temp.dat", std::ios::binary);
			bool flag = true;

			while (f.read((char*)&stemp, sizeof(Property))) {

				if (stemp != temp) {
					of.write((char*)&stemp, sizeof(Property));

				}

				else {
					flag = false;

				}

			}

			f.close();
			of.close();


			if (!flag) {
				remove(fileName.c_str());
				rename("Temp.dat", fileName.c_str());
				std::cout << "Successfully deleted\n";

			}

			else {
				std::cout << "\n-------\n"
					<< "WARNING:  No Record exist!\n"
					<< "_______\n\n";
			}

		}
		else {
			std::cout << "\n-------\n"
				<< "WARNING: The File is empty!\n"
				<< "_______\n\n";
		}
	}
	else {
		std::cout << "\n-------\n"
			<< "WARNING:  The File could not be opened!\n"
			<< "_______\n\n";
		
	}

}

                                                   // Display All Properties (completed)
                                                   // ----------------------

void Property::DisplayAllProperties(std::string fileName) {
	std::ifstream infile(fileName, std::ios::binary);

	if (infile.is_open()) {
		Property temp;
		infile.seekg(0, std::ios::end);
		long curr = infile.tellg();
		infile.seekg(0, std::ios::beg);
		if (curr != 0) {

			std::cout <<"\n\t\t\t\t__________________________\n"
				      <<"\t\t\t\t Display of All Properties\n"
				      <<"\t\t\t\t__________________________\n\n";
			while (infile.read((char*)&temp, sizeof(Property))) {
				std::cout <<"\n"<<temp << std::endl;
				std::cout << "\n____________________________________________\n";
			}
			infile.close();
			
		}
		else {
			std::cout << "\n-------\n"
				<< "WARNING: The File is empty!\n"
				<< "_______\n\n";
			infile.close();
		}
	}

	else {
		std::cout << "\n-------\n"
			<< "WARNING:  The File could not be opened!\n"
			<< "_______\n\n";

	}

}

                                                   // Display Single Property Based On ID
                                                   //________________________

void Property::DisPropertyID(std::string fileName, std::string id) {
	std::ifstream infile(fileName, std::ios::binary);
	Property stemp;
	strcpy_s(stemp.ID, sizeof(stemp.ID), id.c_str());
	if (infile.is_open()) {
		infile.seekg(0, std::ios::end);
		long check = infile.tellg();
		infile.seekg(0, std::ios::beg);

		if (check != 0) {
			Property temp;
			while (infile.read((char*)&temp, sizeof(Property))) {
				if (stemp == temp) {
					std::cout << temp << std::endl;
					infile.close();
					return;
				}
			}
			infile.close();
			std::cout << "\n-------\n"
				<< "WARNING:  No Record exist!\n"
				<< "_______\n\n";
		}
		else {
			std::cout << "\n-------\n"
				<< "WARNING: The File is empty!\n"
				<< "_______\n\n";
		}
	}

	else {
		std::cout << "\n-------\n"
			<< "WARNING:  The File could not be opened!\n"
			<< "_______\n\n";

	}

}

                                                   // Display All Property Based On Status (Sold/Unsold)
                                                   //________________________

void Property::DisPropertyStatus(std::string fileName, std::string status) {
	std::ifstream infile(fileName, std::ios::binary);
	Property temp;
	if (infile.is_open()) {
		infile.seekg(0, std::ios::end);
		long curr = infile.tellg();
		infile.seekg(0, std::ios::beg);
		if (curr != 0) {
			bool flag = false;
			while (infile.read((char*)&temp, sizeof(Property))) {
				if (temp.status[0] == status[0]) {
					std::cout << temp << std::endl;
					std::cout << "\n\n____________________________________________\n";
					flag = true;
				}
			}
			infile.close();
			if (flag == false) {
				std::cout << "\n-------\n"
					<< "WARNING:  No Record exist!\n"
					<< "_______\n\n";
			}
		}
		else {
			std::cout << "\n-------\n"
				<< "WARNING: The File is empty!\n"
				<< "_______\n\n";
			infile.close();
		}
	}
	else {
		std::cout << "\n-------\n"
			<< "WARNING:  The File could not be opened!\n"
			<< "_______\n\n";

	}
}

                                                   // Update Property (Price/Status) (completed)
                                                   // __________________________________________

                                                    // Displaying Sales Revenue
                                                    //_________________________

void Property:: dispSalesRevenue(const char* fileName) {
	std::ifstream infile;
	infile.open(fileName, std::ios::binary);
	if (infile.is_open()) {
		infile.seekg(0, std::ios::end);
		auto check = infile.tellg();
		infile.seekg(0, std::ios::beg);

		if (check != 0) {
			Property temp;
			double total = 0;

			while (infile.read((char*)&temp, sizeof(temp))){
				if (temp.status[0]=='S') {
					total += temp.price;

				}

			}

			infile.close();
			std::cout << "\n-------\n"
				<<"Sales Revenue: "  <<total<<"\n"
				<< "_______\n\n";
			

		}
		else {
			std::cout << "\n-------\n"
				<< "WARNING: The File is empty!\n"
				<< "_______\n\n";
		}
	}
	else {
		std::cout << "\n-------\n"
			<< "WARNING:  The File could not be opened!\n"
			<< "_______\n\n";

	}
}


                                                   // Update Property
                                                   //________________

void Property::updateProperty(std::string fileName) {
	std::string str;
	std::cout << "To update Enter Property ID: ";
	std::cin >> str;
	Property temp;
	strcpy_s(temp.ID, sizeof(temp.ID), str.c_str());

	std::fstream infile(fileName, std::ios::binary | std::ios::in | std::ios::out);

	if (infile.is_open()) {
		infile.seekg(0, std::ios::end);
		long check = infile.tellg();
		infile.seekg(0, std::ios::beg);
		
		if (check != 0) {
			Property setemp;
			bool flag = false;
			long int curr = 0;

			while (infile.read((char*)&setemp, sizeof(Property))) {
				if (setemp == temp) {
					curr = infile.tellg();
					flag = true;
					break;
				}
			}

			if (flag) {
				infile.seekp(curr - sizeof(Property), std::ios::beg);

				std::cout << "What you want to update\n\n\n"
					<< "\t1. Price\n"
					<< "\t2. Status\n"
					<< "\n\n_____________________\n"
					<< "Select option: ";

				int option;
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
					else if (option < 1 || option > 2) {
						flag = false;
						std::cout << "Please Select Option within range!: ";
					}
				} while (flag == false);

				switch (option) {

				case 1: {
					int pri;
					std::cout << "Enter New Price: ";
					std::cin >> pri;
					setemp.price = pri;
					infile.write((char*)&setemp, sizeof(Property));
					std::cout << "Successfully updatd the price to " << pri<<".\n";
					break;

				}

				case 2: {

					char ch = setemp.status[0];

					if (ch == 'S') {
						strcpy_s(setemp.status, sizeof(setemp.status), "Unsold");
						std::cout << "Successfully update status to Unsold.\n";

					}

					else if (ch == 'U') {
						strcpy_s(setemp.status, sizeof(setemp.status), "Sold");
						std::cout << "Successfully updated status to sold.\n";
					}

					infile.write((char*)&setemp, sizeof(Property));
					break;

				}

				}
				
				infile.close();

			}
			else {
				std::cout << "\n-------\n"
					<< "WARNING:  No Record exist!\n"
					<< "_______\n\n";

			}
		}
		else {
			std::cout << "\n-------\n"
				<< "WARNING: The File is empty!\n"
				<< "_______\n\n";
		}
	}

	else {
		std::cout << "\n-------\n"
			<< "WARNING:  The File could not be opened!\n"
			<< "_______\n\n";

	}

}

                                                   // Extraction Operator >> (completed)
                                                   //----------------------- 

std::istream& operator>>(std::istream& in, Property& temp) {


	std::string str;
	std::cout << "Enter Property ID: ";

	// Input Validity (Must Input 9 digits)
	do {
		std::cin >> str;
		if (str.length() != 9) {
			std::cout << "Please Enter 9 Digits ID!: ";

		}

	} while (str.length() != 9);		// Length != 9 then re-input from user

	strcpy_s(temp.ID, sizeof(temp.ID), str.c_str());



	std::cout << "Enter Property Address: ";
	in.ignore();
	getline(in, str, '\n');
	strcpy_s(temp.Address, sizeof(temp.Address), str.c_str());

	std::cout << "Enter Price: ";
	bool flag = true;

	do {
		flag = true;
		in >> temp.price;

		if (in.fail()) {
			flag = false;
			in.clear();
			in.ignore(100, '\n');
			std::cout << "Please Enter Number!: ";

		}

		else if (temp.price <= 0) {
			flag = false;
			std::cout << "Please Enter valid price!: ";

		}

	} while (flag == false);


	std::cout << "Enter Size: ";

	do {
		flag = true;
		in >> temp.size;

		if (in.fail()) {
			flag = false;
			in.clear();
			in.ignore(100, '\n');
			std::cout << "Please Enter Numbers!: ";

		}
		else if (temp.size <= 0) {
			flag = false;
			std::cout << "Please Enter valid size!: ";

		}

	} while (flag == false);



	std::cout << "\nEnter Property Type\n"
		<< "1) Commercial\n"
		<< "2) Residential";
	std::cout << "\n\n_____________________\n"
		<< "Select option: ";
	int option;

	do {
		flag = true;
		std::cin >> option;

		if (std::cin.fail()) {
			flag = false;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Please Enter a Number within range!: ";

		}

		else if (option < 1 || option > 2) {
			flag = false;
			std::cout << "Please Select Option within range!: ";

		}

	} while (flag == false);

	if (option == 1) {
		strcpy_s(temp.type, "Commercial");

	}

	else if (option == 2) {
		strcpy_s(temp.type, "Residential");

	}



	std::cout << "\nEnter Status\n"
		<< "1) Sold\n"
		<< "2) Unsold\n";
	std::cout << "_____________________\n"
		<< "Select option: ";

	do {
		flag = true;
		std::cin >> option;

		if (std::cin.fail()) {
			flag = false;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Please Enter a number within Range!: ";
		}
		else if (option < 1 || option > 2) {
			flag = false;
			std::cout << "Please Select Option within range!: ";
		}
	} while (flag == false);

	if (option == 1) {
		strcpy_s(temp.status, "Sold");

	}

	else if (option == 2) {
		strcpy_s(temp.status, "Unsold");

	}

	return in;
}

                                                   // Insertion Operator << (completed)
                                                   //-----------------------

std::ostream& operator<<(std::ostream& out, const Property& temp) {

	out << "Property ID: " << temp.ID << std::endl
		<< "Property Address: " << temp.Address << std::endl
		<< "Property Price: " << temp.price << std::endl
		<< "Property Size: " << temp.size << std::endl
		<< "Property Type: " << temp.type << std::endl
		<< "Property Status: " << temp.status;

	return out;
}

                                                    // Export to a CSV File
                                                    //_____________________


void Property::exportToCSV(std::string fileName) {

	std::ifstream infile;
	infile.open(fileName, std::ios::binary);
	if (infile.is_open()) {
		infile.seekg(0, std::ios::end);
		long check = infile.tellg();
		infile.seekg(0, std::ios::beg);
		std::ofstream outfile("CSVFile.csv");
		Property temp;
		if (check != 0 ) {
			if (!outfile.is_open()) {
				std::cout << "\n-------\n"
					<< "WARNING:  A CSV File could not be opened!\n"
					<< "_______\n\n";
				return;
			}
			while (infile.read((char*)&temp, sizeof(Property))) {
				outfile << temp.ID << ","
					<< temp.Address << ","
					<< temp.price << ","
					<< temp.size << ","
					<< temp.type << ","
					<< temp.status << "\n";
			}
			std::cout << "Successfully Exported to a CSV file.\n";
			outfile.close();
			infile.close();
		}
		else {
			std::cout << "\n-------\n"
				<< "WARNING: The File is empty!\n"
				<< "_______\n\n";
			infile.close();
		}
	}
	else {
		std::cout << "\n-------\n"
			<< "WARNING:  The File could not be opened!\n"
			<< "_______\n\n";
	}
}

                                       // Import From CSV file
                                       // ____________________

void Property::importFromCSV(const char* FileName, std::string csvFileName) {
	std::ifstream FrCsv;
	FrCsv.open(csvFileName);
	if (!FrCsv.is_open()) {
		std::cout << "\n-------\n"
			<< "WARNING: A CSV File could not be opened!\n"
			<< "_______\n\n";
		return;
	}
	std::ofstream outfile;
	outfile.open(FileName, std::ios::binary | std::ios::app);
	if (!outfile.is_open()) {
		std::cout << "\n-------\n"
			<< "WARNING: " << FileName << "   could not be opened!\n"
			<< "_______\n\n";
		return;
	}

	FrCsv.seekg(0, std::ios::end);
	auto check = FrCsv.tellg();
	FrCsv.seekg(0, std::ios::beg);

	if (check == 0) {
		std::cout << "\n-------\n"
			<< "WARNING: The File is empty!\n"
			<< "_______\n\n";
		FrCsv.close();
		outfile.close();
		return;
	}

	Property temp;
	while (FrCsv.good()) {
		FrCsv.getline(temp.ID, 9, ',');
		FrCsv.ignore(100, ',');
		std::string str;
		FrCsv.getline(temp.Address, 75, ',');
		FrCsv.ignore(100, ',');
		getline(FrCsv, str, ',');
		temp.price = std::stoi(str);
		FrCsv.ignore(100, ',');
		getline(FrCsv, str, ',');
		temp.size = std::stoi(str);
		FrCsv.ignore(100, ',');
		getline(FrCsv, str, ',');
		strcpy_s(temp.type, sizeof(temp.type), str.c_str());
		FrCsv.ignore(100, ',');
		getline(FrCsv, str, '\n');
		strcpy_s(temp.status, sizeof(temp.status), str.c_str());
		outfile.write((char*)&temp, sizeof(Property));
	}

	std::cout << "Successfully Imported to a CSV file.\n";
	outfile.close();
	FrCsv.close();
}