#pragma once
#include <iostream>
#include <sstream>
#include <sqlite3.h>
#include <string>
#include <map>
#include <vector>

#define CreateTableSIGNAL unsigned short int  // return type for table creation status
#define Def_var "none_def"                    // default placeholder for default values

class Vsql
{
public:
	// Constructor & Destructor
	Vsql(std::string DBname);  // connect to database
	~Vsql();                   // close connection and cleanup

	// Types of fields for SQL table
	enum FieldType {
		Integer,
		FloatVar,
		SmalInteger,
		BigInteger,
		vChar,
		Char,
		nChar,
		text,
		Ntext,
		date,
		time,
		dateANDtime,
		year,
		boolean,
		bit,
	};


	// Public functions
	std::string Connection_Test();                      // check if DB is connected
	std::string Empty_status();                         // check if DB has tables
	void show_All_TableName();                          // print table names
	std::vector<std::string> get_All_TableName();       // return table names
	CreateTableSIGNAL Add_Field(std::string table_name, // add new column to table
		std::string field_name,
		FieldType typeSQL,
		int len = 0,
		std::string default_var = Def_var);
	CreateTableSIGNAL add_row(std::string&, std::map<std::string, std::string>&);
		
private:
	// SQLite database variables
	sqlite3* db;                     // database pointer
	std::vector<std::string> AllTableName; // all tables in DB
	sqlite3_stmt* stmt;             // for prepared statements
	char* errMsg = nullptr;         // store error messages
	int ControlerDB;                // store SQLite function return status
	bool connection_status;         // true if DB is connected
	bool empty;                     // true if DB has no tables
	int tableCount = 0;             // number of tables

	// Internal functions
	void GetTableName();                       // load table names from DB
	void ErrorDetector(std::string);           // print error message
	std::string GetAllField_in_thisTable(std::string); // get field names from a table
	static int callback_GETallField_name(void* data, int argc, char** argv, char** azColName); // for processing query result

	// SQL command identifiers
	enum SQLcommand {
		Get_all_table_name_command,
		Add_Field_Command,
		Default_Value,
		Get_All_Field_in_this_Table,
	};

	// SQL command templates
	std::map<SQLcommand, const char*> commands = {
		{Get_all_table_name_command, "SELECT name FROM sqlite_master WHERE type='table';"},
		{Add_Field_Command , "ALTER TABLE tn_dev ADD COLUMN fn_dev type_dev;"},
		{Default_Value , " DEFAULT default_value;"},
		{Get_All_Field_in_this_Table , "PRAGMA table_info(tn_dev);"},
	};

	// Mapping of FieldType to actual SQL types
	std::map<FieldType, std::string> SQLtype = {
		{Integer, "INT"},
		{FloatVar , "FLOAT"},
		{SmalInteger , "SMALLINT"},
		{BigInteger , "BIGINT"},
		{vChar , "VARCHAR(n)"},
		{Char , "CHAR(n)"},
		{nChar , "NCHAR(n)"},
		{text , "TEXT"},
		{Ntext , "NTEXT"},
		{date ,"DATE"},
		{time , "TIME"},
		{dateANDtime ,"DATETIME"},
		{year , "YEAR"},
		{boolean , "BOOL"},
		{bit , "BIT"},
	};
};
