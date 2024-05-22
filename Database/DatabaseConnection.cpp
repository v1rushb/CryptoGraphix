#ifndef DATABASECONNECTION_CPP
#define DATABASECONNECTION_CPP

#include <iostream>
#include <mysql/mysql.h>
#include <exception>

using namespace std;

class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    MYSQL* connection;
    const char* server;
    const char* user;
    const char* password;
    const char* database;

    DatabaseConnection(const char* server, const char* user, const char* password, const char* database)
        : server(server), user(user), password(password), database(database) {
        connection = mysql_init(NULL);
        if (!mysql_real_connect(connection, server, user, password, database, 0, NULL, 0)) {
            cerr << "Connection Error: " << mysql_error(connection) << endl;
            exit(1);
        }
    }

    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

public:
    ~DatabaseConnection() {
        if (connection) {
            mysql_close(connection);
        }
    }

    static DatabaseConnection* getInstance(const char* server, const char* user, const char* password, const char* database) {
        if (instance == nullptr) {
            instance = new DatabaseConnection(server, user, password, database);
        }
        return instance;
    }

    MYSQL* getConnection() {
        return connection;
    }
};

DatabaseConnection* DatabaseConnection::instance = nullptr;

#endif