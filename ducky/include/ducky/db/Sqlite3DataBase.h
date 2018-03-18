/*
 * Sqlite3DataBase.h
 *
 *  Created on: 2017年9月27日
 *      Author: liyawu
 */

#ifndef DUCKY_DB_SQLITE3dATABASE_H_
#define DUCKY_DB_SQLITE3dATABASE_H_

#include <ducky/ducky_config.h>

#ifdef __USE_SQLITE3_DB__

#include <sqlite3.h>
#include <string>
#include <list>
#include <set>
#include <ducky/exception/Exception.h>
#include <ducky/variant/Variant.h>
#include <ducky/buffer/Buffer.h>

using std::string;
using std::list;
using std::set;
using ducky::variant::Variant;
using ducky::buffer::Buffer;

namespace ducky{
namespace db {

EXCEPTION_DEF(Sqlite3Exception)

class Statment {
public:
	Statment();
	virtual ~Statment();

	operator sqlite3_stmt*();
	operator sqlite3_stmt**();

	int getDataCount() const;
	int getColumnCount() const;
	int getColumnType(int col) const;
	string getColumnName(int col) const;
	list<string> getColumns() const;
	int indexOfColumn(const string& columnName) const;
	Variant getColumnValue(int col) const;
	Variant getColumnValue(const string& columnName) const;
	string getTableName(int col) const;

	string getSql();
	int reset();
	int clearbindings();
	int bindNull(int index);
	int bind(int index, const string& value);
	int bind(int index, int value);
	int bind(int index, double value);
	int bind(int index, const void* data, int size);
	int bindNull(const string& paramName);
	int bind(const string& paramName, const string& value);
	int bind(const string& paramName, int value);
	int bind(const string& paramName, double value);
	int bind(const string& paramName, const void* data, int size);
	int bindParamCount() const;
	string bindParamName(int index) const;
	int bindParamIndex(const string& paramName) const;

	int step();
	bool isReadOnly();
	bool isBusy();

private:
	sqlite3_stmt* stmt;
};

class ColumnInfo{
public:
	ColumnInfo();
	ColumnInfo(const string& columnName, const string& dataType, bool primaryKey = false,
			bool notNull = false, bool autoInc = false, const string& tableName = "",
			const string& collate = "");

	bool isAutoInc() const;
	void setAutoInc(bool autoInc);
	const string& getCollate() const;
	void setCollate(const string& collate);
	const string& getColumnName() const;
	void setColumnName(const string& columnName);
	const string& getDataType() const;
	void setDataType(const string& dataType);
	bool isNotNull() const;
	void setNotNull(bool notNull);
	bool isPrimaryKey() const;
	void setPrimaryKey(bool primaryKey);
	const string& getTableName() const;
	void setTableName(const string& tableName);

	bool operator==(const ColumnInfo& colInfo) const;
	bool operator<(const ColumnInfo& colInfo) const;

private:
	string tableName;
	string columnName;
	bool notNull;
	bool primaryKey;
	bool autoInc;
	string collate;
	string dataType;
};

class TableInfo{
public:
	TableInfo();
	TableInfo(const string& tableName);

	set<ColumnInfo> getColumns() const;
	const string& getTableName() const;
	void addColumn(const ColumnInfo& colInfo);
	const ColumnInfo& getColumn(const string& columnName) const;
	const ColumnInfo& operator[](const string& columnName) const;

	void setTableName(const string& tableName);

private:
	string tableName;
	set<ColumnInfo> columns;
};

class Sqlite3DataBase {
public:
	Sqlite3DataBase();
	virtual ~Sqlite3DataBase();

	void open(const string& dbFilePath, bool createIfNotExists = false);
	void close();
	Statment prepare(const string& sql);
	string errorMsg() const;
	int errorCode() const;
	int beginTransaction();
	int beginExclusiveTransaction();
	int commitTransaction();
	int rollbackTransaction();
	int getChanges();

	list<string> getTables();
	TableInfo getTableInfo(const string& tableName);

	typedef int (*ExecCallback)(void*, int, char**, char**);
	int exec(const string& sql, ExecCallback callbackFunc = NULL, void* callbackParam = NULL);

	static string GetVersion();
	static int GetVersionNumber();
	static string GetSouceId();
	static bool IsValidSqlStatement(const string& sql);
private:
	sqlite3* db;
	string dbFile;
};

} /* namespace db */
} /* namespace ducky */

#endif /* __USE_SQLITE3_DB__ */
#endif /* DUCKY_DB_SQLITE3dATABASE_H_ */
