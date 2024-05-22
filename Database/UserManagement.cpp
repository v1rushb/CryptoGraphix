#ifndef USERMANAGEMENT_CPP
#define USERMANAGEMENT_CPP

#include <iostream>
#include <mysql/mysql.h>
#include "DatabaseConnection.cpp"
#include <memory>
#include <cstring>

class UserManagement {
private:
    DatabaseConnection& dbConnection;

public:
    UserManagement(DatabaseConnection& dbConnection) : dbConnection(dbConnection) {}

    bool Register(const string& username, const string& password, const string& firstName, const string& secondName) {
        const char* query = "INSERT INTO User (Name, password, first_name, second_name) VALUES (?, ?, ?, ?)";
        MYSQL_STMT* stmt = mysql_stmt_init(dbConnection.getConnection());
        if (!stmt) {
            cerr << "Failed to initialize statement" << endl;
            return false;
        }

        if (mysql_stmt_prepare(stmt, query, strlen(query))) {
            cerr << "MySQL prepare error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return false;
        }

        MYSQL_BIND bind[4] = {};
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (char*)username.c_str();
        bind[0].buffer_length = username.length();

        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = (char*)password.c_str();
        bind[1].buffer_length = password.length();

        bind[2].buffer_type = MYSQL_TYPE_STRING;
        bind[2].buffer = (char*)firstName.c_str();
        bind[2].buffer_length = firstName.length();

        bind[3].buffer_type = MYSQL_TYPE_STRING;
        bind[3].buffer = (char*)secondName.c_str();
        bind[3].buffer_length = secondName.length();

        if (mysql_stmt_bind_param(stmt, bind)) {
            cerr << "MySQL bind param error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return false;
        }

        if (mysql_stmt_execute(stmt)) {
            cerr << "MySQL execute error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return false;
        }

        mysql_stmt_close(stmt);
        return true;
    }
    bool Login(const string& username, const string& password) {
        const char* query = "SELECT * FROM User WHERE Name = ? AND password = ?";
        MYSQL_STMT* stmt = mysql_stmt_init(dbConnection.getConnection());
        if (!stmt) {
            cerr << "Failed to initialize statement" << endl;
            return false;
        }

        if (mysql_stmt_prepare(stmt, query, strlen(query))) {
            cerr << "MySQL prepare error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return false;
        }

        MYSQL_BIND bind[2] = {};
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (char*)username.c_str();
        bind[0].buffer_length = username.length();

        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = (char*)password.c_str();
        bind[1].buffer_length = password.length();

        if (mysql_stmt_bind_param(stmt, bind)) {
            cerr << "MySQL bind param error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return false;
        }

        if (mysql_stmt_execute(stmt)) {
            cerr << "MySQL execute error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return false;
        }

        MYSQL_RES *result = mysql_stmt_result_metadata(stmt);
        bool isLoggedIn = false;
        if (result) {
            MYSQL_ROW row;
            if (mysql_stmt_store_result(stmt) == 0 && mysql_stmt_num_rows(stmt) > 0) {
                isLoggedIn = true;
            }
            mysql_free_result(result);
        }

        mysql_stmt_close(stmt);
        return isLoggedIn;
    }

    unique_ptr<ll> GetUserID(const string& username) {
        const string query = "SELECT ID FROM User WHERE Name = ?";
        unique_ptr<ll> user_id = nullptr;

        MYSQL_STMT* stmt = mysql_stmt_init(dbConnection.getConnection());
        if (!stmt) {
            cerr << "Failed to init statement" << endl;
            return nullptr;
        }

        if (mysql_stmt_prepare(stmt, query.c_str(), query.length())) {
            cerr << "MySQL prepare error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return nullptr;
        }

        MYSQL_BIND bind[1];
        memset(bind, 0, sizeof(bind));

        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (char*)username.c_str();
        bind[0].buffer_length = username.length();

        if (mysql_stmt_bind_param(stmt, bind)) {
            cerr << "MySQL bind param error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return nullptr;
        }

        if (mysql_stmt_execute(stmt)) {
            cerr << "MySQL execute error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return nullptr;
        }

        MYSQL_BIND result_bind[1];
        ll id;
        memset(result_bind, 0, sizeof(result_bind));

        result_bind[0].buffer_type = MYSQL_TYPE_LONGLONG;
        result_bind[0].buffer = (char*)&id;

        if (mysql_stmt_bind_result(stmt, result_bind)) {
            cerr << "MySQL bind result error: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return nullptr;
        }

        if (mysql_stmt_fetch(stmt) == 0) {
            user_id = make_unique<ll>(id);
        }

        mysql_stmt_close(stmt);
        return user_id;
    }
};

#endif