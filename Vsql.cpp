#include "Vsql.h"


Vsql::Vsql(std::string DBname)
{
	ControlerDB = sqlite3_open("test1.db", &db);
	if (ControlerDB != SQLITE_OK) {
		connection_status = false;
	}
	else
	{
		connection_status = true;
	}
	GetTableName();
}
//---------------------------------------------------

CreateTableSIGNAL Vsql::Add_Field(std::string table_name , std::string field_name , FieldType typeSQL , std::string default_var, int len) {
	SQLcommand command = Add_Field_Command;
	std::string temp_str_type = SQLtype[typeSQL];
	std::string SQLc = commands[command];
	
	CreateTableSIGNAL pos = SQLc.find("tn_dev");
	SQLc.replace(pos , 6, table_name);
	
	pos = SQLc.find("fn_dev");
	SQLc.replace(pos, 6, field_name);
	
	pos = SQLc.find("type_dev");
	if (typeSQL == vChar or typeSQL == Char or typeSQL == nChar) {
		if (len == 0) {
			ErrorDetector("We need to know the lenth !");
			return 1;
		}
		CreateTableSIGNAL type_pos = SQLtype[typeSQL].find("(n)");
		std::ostringstream oss;
		oss << "(" << len << ")";
		std::string tempstr1 = oss.str();
		temp_str_type = SQLtype[typeSQL].replace(type_pos,3 ,tempstr1);
	}
	SQLc.replace(pos, 8, temp_str_type);

	if (default_var != Def_var) {
		std::string def = commands[SQLcommand::Default_Value];
		if (typeSQL == vChar or typeSQL == Char or typeSQL == nChar or typeSQL == text or typeSQL == date or typeSQL == time or typeSQL == dateANDtime or typeSQL == Ntext or typeSQL == year)
		{
			default_var = "\"" + default_var + "\"";
		}
		def.replace(def.find("default_value"), 13, default_var);
		SQLc.replace(SQLc.find(";"), 1, def);
	}

	const char* cStr = SQLc.c_str();
	//std::cout << SQLc << std::endl;
	ControlerDB = sqlite3_exec(db, cStr, nullptr , nullptr, &errMsg);
	if (ControlerDB != SQLITE_OK) {
		if (GetAllField_in_thisTable(table_name).find(field_name) != std::string::npos) {
			ErrorDetector("Field Name is a duplicate !");
			sqlite3_free(errMsg);
			return 2;
		}
		ErrorDetector("Error in make to Field !");
		sqlite3_free(errMsg);
		return 3;
	}
	return 0;
}

std::string Vsql::GetAllField_in_thisTable(std::string tn_dev) {

	std::string temp = commands[SQLcommand::Get_All_Field_in_this_Table];
	temp = temp.replace(temp.find("tn_dev"), 6, tn_dev);
	const char* cStr = temp.c_str();


	std::string resultStr;
	ControlerDB = sqlite3_exec(db, cStr, callback_GETallField_name, &resultStr, &errMsg);
	if (ControlerDB != SQLITE_OK) {
		ErrorDetector("problem from GetAllField_in_thisTable !");
		sqlite3_free(errMsg);
	}
	return resultStr;
}

int Vsql::callback_GETallField_name(void* data, int argc, char** argv, char** azColName) {
	std::string* outStr = static_cast<std::string*>(data); // تبدیل اشاره‌گر عمومی به string

	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "name" && argv[i]) {
			*outStr += argv[i]; // اضافه کردن مقدار به رشته
			*outStr += "\t";    // جداکننده برای خوانایی بیشتر
		}
	}
	return 0;
}

void Vsql::ErrorDetector(std::string namePlace) {
	std::cout << "Your error is in the section: " << namePlace << std::endl;
}

void Vsql::GetTableName() {
	SQLcommand command = Get_all_table_name_command;
	ControlerDB = sqlite3_prepare_v2(db, commands[command], -1, &stmt, nullptr);
	if (ControlerDB != SQLITE_OK) {
		ErrorDetector("The command to get table names failed");
	}
	const unsigned char* tableName;
	while ((ControlerDB = sqlite3_step(stmt)) == SQLITE_ROW) {
		tableName = sqlite3_column_text(stmt, 0);
		AllTableName.push_back(reinterpret_cast<const char*>(tableName));
		tableCount++;
	}
	if (tableCount == 0) {
		empty == true;
	}
	else {
		empty == false;
	}

}

void Vsql::show_All_TableName() {
	std::cout << "---------------------------------------" << std::endl;
	std::cout << "your tables : " << std::endl;
	for (int i = 0; i < this->AllTableName.size(); i++) {
		std::cout << " - " << this->AllTableName.at(i) << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}

std::vector<std::string> Vsql::get_All_TableName() {
	return AllTableName;
}


std::string Vsql::Connection_Test() {
	if (connection_status == true){
		return "True";
	}
	else
	{
		return "False";
	}
}

std::string Vsql::Empty_status() {
	if (empty == true) {
		return "True";
	}
	else
	{
		return "False";
	}
}


//---------------------------------------------------
Vsql::~Vsql()
{
	sqlite3_finalize(stmt);
	sqlite3_close(this->db);
}