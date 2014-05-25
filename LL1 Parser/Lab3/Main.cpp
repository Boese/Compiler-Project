#include "cParser.h"

#include <iostream>
#include <fstream>

using namespace std;

#define fileOpenFailure_ 0;		// Execption Handler

void main()
{
	cParser parser;

	string tableFile, inputFile, startRule;

	// Have user input a file to be processed.
	cout << "Enter the name of table file: ";
	cin >> tableFile;
	//tableFile = "table1.txt";
	cout << endl;
	cout << "Enter the name of input file: ";
	cin >> inputFile;
	//inputFile = "input1.txt";
	cout << endl;
	cout << "Enter the start rule (1: Program): ";
	cin >> startRule;
	//startRule = "Program";
	cout << endl;

	try
	{
		/*******************Table File******************/

		// Open input file stream
		ifstream file( tableFile );

		// Oops something went wrong.
		if( !file )
			throw fileOpenFailure_;

		string buf;

		// While the file has more lines to consume...
		while ( !file.eof() )
		{
			getline( file, buf );
			parser.addTableEntry(buf);
		}

		file.close();

		/*************Input File******************/

		// Open input file stream
		ifstream inFile( inputFile );

		// Oops something went wrong.
		if( !inFile )
			throw fileOpenFailure_;

		string buff;

		// While the file has more lines to consume...
		while ( !inFile.eof() )
		{
			getline( inFile, buff );
			parser.addInputEntry(buff);
		}
		parser.addInputEntry("$");
		inFile.close();
	}
	// Oops something went wrong.
	catch (int e)
	{
		cout << "Error number: " << e << ", File not found" << endl;
	}

	parser.startRule(startRule);

	if (parser.parse())
		cout << "Parsed successfully." << endl;
	else
		cout << "Failed to Parse." << endl;

	system("pause");
}