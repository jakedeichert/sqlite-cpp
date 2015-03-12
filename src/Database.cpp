#include "Database.h"



Database::Database() {
	isConnected = false;
}



Database::~Database() {
	Disconnect();
}



// Open a database connection.
// param:tableName-> The table to open.
// param:primaryKeyColumnName-> The primary key column used within the specified table.
int Database::Connect(std::string tableName, std::string primaryKeyColumnName) {
	currentTable = tableName;
	currentPrimaryKeyColumn = primaryKeyColumnName;

	// attempt to connect to the database
	// TODO make the database filename a paramter.
	//		for some reason, I never did that?!
	int resultCode = sqlite3_open("game.db", &db);

	// if there is a result code, connection failed
	// else, connection was successful
	if (resultCode) {
		sqlite3_close(db);
		return DB_CANNOT_CONNECT;
	} else {
		// try to load all existing tables in this database
		resultCode = LoadTableNames();
		if (resultCode) return resultCode;

		// test if the specified table exists
		resultCode = CheckTableExists(currentTable);
		if (resultCode) return resultCode;

		// load column names and make sure the specified primary key column exists
		LoadColumnNames();
		resultCode = CheckColumnExists(primaryKeyColumnName);
		if (resultCode) return resultCode;

		// load primary keys
		LoadPrimaryKeys();
	}
	isConnected = true;
	return DB_SUCCESS;
}



// Close the database connection.
int Database::Disconnect() {
	// if the database is connected, disconnect it
	if (isConnected) {
		isConnected = false;
		sqlite3_close(db);
		return DB_SUCCESS;
	}
	return DB_CANNOT_DISCONNECT;
}



// Get data from a cell in the format of an int.
// param:primaryKeySearchValue-> The primary key used to find the row to grab info from.
// param:columnNameSearch-> The column to grab info from.
int Database::GetCellInt(std::string primaryKeySearchValue, std::string columnNameSearch) {
	// if data isn't found, it will be null
	int data = NULL;

	// if the specified column and primary key search value exist
	if (!CheckColumnExists(columnNameSearch) && !CheckPrimaryKeyValueExists(primaryKeySearchValue)) {
		// create the statement
		sqlite3_stmt *statement;
		// select the row with the specified primary key search value
		std::string statementString = "SELECT * FROM " + currentTable + " WHERE " + currentPrimaryKeyColumn + "='" + primaryKeySearchValue + "';";

		// if the statement is valid
		if (sqlite3_prepare_v2(db, statementString.c_str(), -1, &statement, 0) == SQLITE_OK) {
			// go to the row
			int result = sqlite3_step(statement);

			// if the result is a row, set the return data
			if (result == SQLITE_ROW) data = sqlite3_column_int(statement, tableColumns[columnNameSearch]);
		}
		// statement is finished
		sqlite3_finalize(statement);
	}
	return data;
}



// Get data from a cell in the format of a double.
// param:primaryKeySearchValue-> The primary key used to find the row to grab info from.
// param:columnNameSearch-> The column to grab info from.
double Database::GetCellDouble(std::string primaryKeySearchValue, std::string columnNameSearch) {
	// if data isn't found, it will be null
	double data = NULL;

	// if the specified column and primary key search value exist
	if (!CheckColumnExists(columnNameSearch) && !CheckPrimaryKeyValueExists(primaryKeySearchValue)) {
		// create the statement
		sqlite3_stmt *statement;
		// select the row with the specified primary key search value
		std::string statementString = "SELECT * FROM " + currentTable + " WHERE " + currentPrimaryKeyColumn + "='" + primaryKeySearchValue + "';";

		// if the statement is valid
		if (sqlite3_prepare_v2(db, statementString.c_str(), -1, &statement, 0) == SQLITE_OK) {
			// go to the row
			int result = sqlite3_step(statement);

			// if the result is a row, set the return data
			if (result == SQLITE_ROW) data = sqlite3_column_double(statement, tableColumns[columnNameSearch]);
		}
		// statement is finished
		sqlite3_finalize(statement);
	}
	return data;
}



// Get data from a cell in the format of a string.
// param:primaryKeySearchValue-> The primary key used to find the row to grab info from.
// param:columnNameSearch-> The column to grab info from.
std::string Database::GetCellString(std::string primaryKeySearchValue, std::string columnNameSearch) {
	// if data isn't found, it will be null
	std::string data = "";

	// if the specified column and primary key search value exist
	if (!CheckColumnExists(columnNameSearch) && !CheckPrimaryKeyValueExists(primaryKeySearchValue)) {
		// create the statement
		sqlite3_stmt *statement;
		// select the row with the specified primary key search value
		std::string statementString = "SELECT * FROM " + currentTable + " WHERE " + currentPrimaryKeyColumn + "='" + primaryKeySearchValue + "';";

		// if the statement is valid
		if (sqlite3_prepare_v2(db, statementString.c_str(), -1, &statement, 0) == SQLITE_OK) {
			// go to the row
			int result = sqlite3_step(statement);

			// if the result is a row, set the return data
			if (result == SQLITE_ROW) data = (char *)sqlite3_column_text(statement, tableColumns[columnNameSearch]);
		}
		// statement is finished
		sqlite3_finalize(statement);
	}
	return data;
}



// Update a cell in the database.
// param:primaryKeySearchValue-> The primary key used to find the row to update.
// param:columnNameSearch-> The column to update.
// param:newValue-> The new value for that cell.
int Database::UpdateCell(std::string primaryKeySearchValue, std::string columnNameSearch, std::string newValue) {
	// default result code
	int resultCode = DB_CANNOT_UPDATE_VALUE;

	// if the specified column and primary key search value exist
	if (!CheckColumnExists(columnNameSearch) && !CheckPrimaryKeyValueExists(primaryKeySearchValue)) {
		// select the row with the specified primary key search value
		std::string statementString = "UPDATE " + currentTable + " SET " + columnNameSearch + "='" + newValue + "' WHERE " + currentPrimaryKeyColumn + "='" + primaryKeySearchValue + "';";

		// if the statement is valid, then success
		if (sqlite3_exec(db, statementString.c_str(), NULL, NULL, NULL) == SQLITE_OK) resultCode = DB_SUCCESS;
	}
	return resultCode;
}



// Update a cell in the database.
// param:primaryKeySearchValue-> The primary key used to find the row to update.
// param:columnNameSearch-> The column to update.
// param:newValue-> The new value for that cell.
int Database::UpdateCell(std::string primaryKeySearchValue, std::string columnNameSearch, int newValue) {
	// default result code
	int resultCode = DB_CANNOT_UPDATE_VALUE;

	// convert number to string for sql
	std::stringstream newValueString;
	newValueString << newValue;

	// if the specified column and primary key search value exist
	if (!CheckColumnExists(columnNameSearch) && !CheckPrimaryKeyValueExists(primaryKeySearchValue)) {
		// select the row with the specified primary key search value
		std::string statementString = "UPDATE " + currentTable + " SET " + columnNameSearch + "=" + newValueString.str() + " WHERE " + currentPrimaryKeyColumn + "='" + primaryKeySearchValue + "';";

		// if the statement is valid, then success
		if (sqlite3_exec(db, statementString.c_str(), NULL, NULL, NULL) == SQLITE_OK) resultCode = DB_SUCCESS;
	}
	return resultCode;
}



// Update a cell in the database.
// param:primaryKeySearchValue-> The primary key used to find the row to update.
// param:columnNameSearch-> The column to update.
// param:newValue-> The new value for that cell.
int Database::UpdateCell(std::string primaryKeySearchValue, std::string columnNameSearch, double newValue) {
	// default result code
	int resultCode = DB_CANNOT_UPDATE_VALUE;

	// convert number to string for sql
	std::stringstream newValueString;
	newValueString << newValue;

	// if the specified column and primary key search value exist
	if (!CheckColumnExists(columnNameSearch) && !CheckPrimaryKeyValueExists(primaryKeySearchValue)) {
		// select the row with the specified primary key search value
		std::string statementString = "UPDATE " + currentTable + " SET " + columnNameSearch + "=" + newValueString.str() + " WHERE " + currentPrimaryKeyColumn + "='" + primaryKeySearchValue + "';";

		// if the statement is valid, then success
		if (sqlite3_exec(db, statementString.c_str(), NULL, NULL, NULL) == SQLITE_OK) resultCode = DB_SUCCESS;
	}
	return resultCode;
}



// Load all table names found in the database into a map.
int Database::LoadTableNames() {
	// default result code
	int dbResult = DB_NO_TABLES_EXIST;

	// clear any exisiting elements in the map
	tables.clear();

	// create the statement
	sqlite3_stmt *statement;
	// selects all table names from the master database
	std::string statementString = "SELECT name FROM sqlite_master WHERE type='table';";

	// if the statement was valid
	if (sqlite3_prepare_v2(db, statementString.c_str(), -1, &statement, 0) == SQLITE_OK) {
		bool loop = true;
		int index = 0;
		int result;

		// loop through all the rows
		while (loop) {
			// go to the next row
			result = sqlite3_step(statement);

			// if the result is a row, else, end the loop
			if (result == SQLITE_ROW) {
				// store table names in a map with their index
				tables[(char *)sqlite3_column_text(statement, 0)] = index++;
				dbResult = DB_SUCCESS;
			} else {
				loop = false;
			}
		}
	}
	// statement is finished
	sqlite3_finalize(statement);

	return dbResult;
}



// Load all column names found in the table into a map.
void Database::LoadColumnNames() {
	// clear any existing elements in the map
	tableColumns.clear();

	// create the statement
	sqlite3_stmt *statement;
	// selects everything in the table
	std::string statementString = "SELECT * FROM " + currentTable + ";";

	// if the statement was valid
	if (sqlite3_prepare_v2(db, statementString.c_str(), -1, &statement, 0) == SQLITE_OK) {
		// loop through the columns
		for (int i = 0; i < sqlite3_column_count(statement); i++) {
			// store column names in a map with their index
			tableColumns[sqlite3_column_name(statement, i)] = i;
		}
	}
	// statement is finished
	sqlite3_finalize(statement);
}



// Load all primary key values found in the primary key column into a map.
void Database::LoadPrimaryKeys() {
	// clear any exisiting elements in the map
	tablePrimaryKeys.clear();

	// create the statement
	sqlite3_stmt *statement;
	// selects all table names from the master database
	std::string statementString = "SELECT " + currentPrimaryKeyColumn + " FROM " + currentTable + ";";

	// if the statement was valid
	if (sqlite3_prepare_v2(db, statementString.c_str(), -1, &statement, 0) == SQLITE_OK) {
		bool loop = true;
		int index = 0;
		int result;

		// loop through all the rows
		while (loop) {
			// go to the next row
			result = sqlite3_step(statement);

			// if the result is a row, else, end the loop
			if (result == SQLITE_ROW) {
				// store primary key names in a map with their index
				tablePrimaryKeys[(char *)sqlite3_column_text(statement, 0)] = index++;
			} else {
				loop = false;
			}
		}
	}
	// statement is finished
	sqlite3_finalize(statement);
}



// Check if a table exists.
// param:tableName-> The table name to search for.
int Database::CheckTableExists(std::string tableName) {
	// if the specified table isn't in the map, table doesn't exist
	if (!tables.count(tableName)) return DB_CANNOT_FIND_TABLE;
	return DB_SUCCESS;
}



// Check if a column exists.
// param:columnName-> The column name to search for.
int Database::CheckColumnExists(std::string columnName) {
	// if the specified column isn't in the map, column doesn't exist
	if (!tableColumns.count(columnName)) return DB_CANNOT_FIND_COLUMN;
	return DB_SUCCESS;
}



// Check if a primary key value exists.
// param:primaryKeyName-> The value to search for.
int Database::CheckPrimaryKeyValueExists(std::string primaryKeyName) {
	// if the specified primary key value isn't in the map, the primary key doesn't exist
	if (!tablePrimaryKeys.count(primaryKeyName)) return DB_CANNOT_FIND_PRIMARY_KEY_VALUE;
	return DB_SUCCESS;
}



// Return whether the database is connected or not.
bool Database::GetIsConnected() {
	return isConnected;
}
