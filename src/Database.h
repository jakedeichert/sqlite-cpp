#pragma once
#include "sqlite3.h"
#include <string>
#include <map>
#include <sstream>

class Database
{
public:
	// Result codes used as return values.
	const enum Error {
		DB_SUCCESS,
		DB_CANNOT_CONNECT,
		DB_CANNOT_DISCONNECT,
		DB_CANNOT_FIND_TABLE,
		DB_CANNOT_FIND_COLUMN,
		DB_CANNOT_FIND_PRIMARY_KEY_VALUE,
		DB_CANNOT_UPDATE_VALUE,
		DB_NO_TABLES_EXIST
	};

	Database();
	~Database();


	// Open a database connection.
	// param:tableName-> The table to open.
	// param:primaryKeyColumnName-> The primary key column used within the specified table.
	int Connect(std::string tableName, std::string primaryKeyColumnName);


	// Close the database connection.
	int Disconnect();


	// Get data from a cell in the format of an int.
	// param:primaryKeySearchValue-> The primary key used to find the row to grab info from.
	// param:columnNameSearch-> The column to grab info from.
	int GetCellInt(std::string primaryKeySearchValue, std::string columnNameSearch);


	// Get data from a cell in the format of a double.
	// param:primaryKeySearchValue-> The primary key used to find the row to grab info from.
	// param:columnNameSearch-> The column to grab info from.
	double GetCellDouble(std::string primaryKeySearchValue, std::string columnNameSearch);


	// Get data from a cell in the format of a string.
	// param:primaryKeySearchValue-> The primary key used to find the row to grab info from.
	// param:columnNameSearch-> The column to grab info from.
	std::string GetCellString(std::string primaryKeySearchValue, std::string columnNameSearch);


	// Update a cell in the database.
	// param:primaryKeySearchValue-> The primary key used to find the row to update.
	// param:columnNameSearch-> The column to update.
	// param:newValue-> The new value for that cell.
	int UpdateCell(std::string primaryKeySearchValue, std::string columnNameSearch, std::string newValue);


	// Update a cell in the database.
	// param:primaryKeySearchValue-> The primary key used to find the row to update.
	// param:columnNameSearch-> The column to update.
	// param:newValue-> The new value for that cell.
	int UpdateCell(std::string primaryKeySearchValue, std::string columnNameSearch, int newValue);


	// Update a cell in the database.
	// param:primaryKeySearchValue-> The primary key used to find the row to update.
	// param:columnNameSearch-> The column to update.
	// param:newValue-> The new value for that cell.
	int UpdateCell(std::string primaryKeySearchValue, std::string columnNameSearch, double newValue);


	// Check if a table exists.
	// param:tableName-> The table name to search for.
	int CheckTableExists(std::string tableName);


	// Check if a column exists.
	// param:columnName-> The column name to search for.
	int CheckColumnExists(std::string columnName);


	// Check if a primary key value exists.
	// param:primaryKeyName-> The value to search for.
	int CheckPrimaryKeyValueExists(std::string primaryKeyName);


	// Return whether the database is connected or not.
	bool GetIsConnected();
private:
	// The sqlite3 database.
	sqlite3 *db;


	// Whether the database is connected or not.
	bool isConnected;


	// Maps used to store static data.
	std::map<std::string, int> tables;
	std::map<std::string, int> tableColumns;
	std::map<std::string, int> tablePrimaryKeys;


	// Current table and primary key column for this connection.
	std::string currentTable;
	std::string currentPrimaryKeyColumn;


	// Load all table names found in the database into a map.
	int LoadTableNames();


	// Load all column names found in the table into a map.
	void LoadColumnNames();


	// Load all primary key values found in the primary key column into a map.
	void LoadPrimaryKeys();
};
