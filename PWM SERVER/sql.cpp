#include "include.h"
#include "includeSQL.h"

const string server = "127.0.0.1:3306";
const string username = "root";
const string password = "RppTl018!";
sql::Driver* driver;
sql::Connection* con;
sql::Statement* stmt;
sql::PreparedStatement* pstmt;

void insertData(string key, string data, string info)
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);

		con->setSchema("db");

		pstmt = con->prepareStatement("INSERT INTO user(username, password, info) VALUES(?,?,?)");
		pstmt->setString(1, key);
		pstmt->setString(2, data);
		pstmt->setString(3, info);
		pstmt->execute();

		delete pstmt;
		delete con;
	}
	catch (sql::SQLException e)
	{
		answer = "SUCCESS";
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}

string readData(string key)
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);


		con->setSchema("db");

		//select  
		pstmt = con->prepareStatement("SELECT * FROM USER WHERE username = ?");
		pstmt->setString(1, key);
		sql::ResultSet* result = pstmt->executeQuery();
		result->next();
		delete pstmt;
		delete con;
		return result->getString(2) + "&" + result->getString(3);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}

void updateData(string key, string data, string info)
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);



		con->setSchema("db");

		//update
		if (data.size() > 0)
		{
			pstmt = con->prepareStatement("UPDATE user SET password = ? WHERE username = ?");
			pstmt->setString(1, data);
			pstmt->setString(2, key);
			pstmt->executeQuery();
		}

		if (info.size() > 0)
		{
			pstmt = con->prepareStatement("UPDATE user SET info = ? WHERE username = ?");
			pstmt->setString(1, info);
			pstmt->setString(2, key);
			pstmt->executeQuery();
		}
		delete con;
		delete pstmt;
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}

void deleteData(string key, string data)
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);



		con->setSchema("db");

		pstmt = con->prepareStatement("DELETE FROM user WHERE username = ? AND WHERE data = ?");
		pstmt->setString(1, key);
		pstmt->setString(2, data);
		pstmt->executeQuery();

		delete pstmt;
		delete con;
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}

void deleteAcc(string key)
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);



		con->setSchema("db");

		pstmt = con->prepareStatement("DELETE FROM user WHERE username = ?");
		pstmt->setString(1, key);
		pstmt->executeQuery();

		delete pstmt;
		delete con;
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}
