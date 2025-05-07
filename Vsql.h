#pragma once
#include <iostream>
#include <sstream>
#include <sqlite3.h>
#include <string>
#include <map>
#include <vector>
#define CreateTableSIGNAL unsigned short int
#define Def_var "none_def"
class Vsql
{
public:
	Vsql(std::string DBname);
	~Vsql();
	// enum Field type
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
	// functional
	std::string Connection_Test();
	std::string Empty_status();
	void show_All_TableName();
	std::vector<std::string> get_All_TableName();
	CreateTableSIGNAL Add_Field(std::string table_name, std::string field_name, FieldType typeSQL, std::string default_var = Def_var, int len = 0);


	

private:
	// Variable
	sqlite3* db;
	std::vector<std::string> AllTableName;
	sqlite3_stmt* stmt;
	char* errMsg = nullptr;
	int ControlerDB;
	bool connection_status;
	bool empty; // if false in not empty
	int tableCount = 0;
	// functional
	void GetTableName();
	void ErrorDetector(std::string);
	std::string GetAllField_in_thisTable(std::string);
	static int callback_GETallField_name(void* data, int argc, char** argv, char** azColName);


	// enum and map from sql command
	enum SQLcommand {
		Get_all_table_name_command,
		Add_Field_Command,
		Default_Value,
		Get_All_Field_in_this_Table,

	};
	
	std::map<SQLcommand, const char*> commands = {
		{Get_all_table_name_command, "SELECT name FROM sqlite_master WHERE type='table';"},
		{Add_Field_Command , "ALTER TABLE tn_dev ADD COLUMN fn_dev type_dev;"},
		{Default_Value , " DEFAULT default_value;"},
		{Get_All_Field_in_this_Table , "PRAGMA table_info(tn_dev);"},

	};

	// map from field type
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

