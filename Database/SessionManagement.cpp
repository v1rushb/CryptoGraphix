#ifndef SESSIONMANAGEMENT_CPP
#define SESSIONMANAGEMENT_CPP

#include <iostream>
#include <mysql/mysql.h>
#include "DatabaseConnection.cpp"
#include <memory>

using namespace std;

#define ll long long int

class SessionManagement {
private:
    DatabaseConnection& dbConnection;

public:
    SessionManagement(DatabaseConnection& dbConnection) : dbConnection(dbConnection) {}

    bool CreateSession(int userID) {
        string query = "INSERT INTO Session (user_id) VALUES (" + to_string(userID) + ")";
        try {
            if (mysql_query(dbConnection.getConnection(), query.c_str())) { 
               throw runtime_error(mysql_error(dbConnection.getConnection()));
            }
        } catch(const exception &ex) {
            cout << ex.what() << endl;
            return false;
        }
        return true;
    }

    bool IsValidSession(long long userID) {
        string query = "SELECT session_id FROM Session WHERE user_id = " + to_string(userID) + 
                       " AND TIMESTAMPDIFF(MINUTE, start_time, NOW()) < 1";
        if (mysql_query(dbConnection.getConnection(), query.c_str())) {
            cout << "SQL Query Error: " << mysql_error(dbConnection.getConnection()) << endl;
            return false;
        }

        MYSQL_RES *result = mysql_use_result(dbConnection.getConnection());
        bool isValid = (mysql_fetch_row(result) != NULL);
        mysql_free_result(result);
        return isValid;
    }

    bool ClearAllSessions() {
        const char* query = "DELETE FROM Session";
        if (mysql_query(dbConnection.getConnection(), query)) {
            cerr << "SQL Query Error: " << mysql_error(dbConnection.getConnection()) << endl;
            return false;
        }
        cout << "All sessions cleared.\n";
        return true;
    }
};


#endif