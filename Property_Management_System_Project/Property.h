#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Property {
private:
	char ID[10];
	char Address[75];
	int price;
	double size;
	char type[15];
	char status[10];

public:

	// Record Existence by ID
	bool operator==(const Property&);

	// != Operator
	bool operator!=(const Property&);

	// Record checking confirmation to avoid duplicate record
	bool isRecordExist(std::string);

	// Property Adding to the List
	void AddProperty(std::string);

	// Property deletion
	void deleteProperty(std::string);

	// Display All Properties
	void DisplayAllProperties(std::string);

	// Display Single Property Based On ID searched
	void DisPropertyID(std::string , std::string);

	// Display All Property Based on status
	void DisPropertyStatus(std::string , std::string);

	// Display Sales Revenue
	void dispSalesRevenue(const char* fileName);

	// Update Record
	void updateProperty(std::string);

	// Export to a CSV File
	void exportToCSV(std::string);

	void importFromCSV(const char* , std::string );


	// Record Input  
	friend std::istream& operator>>(std::istream&, Property&);

	// Record Display
	friend std::ostream& operator<<(std::ostream&, const Property&);

};


