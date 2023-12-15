#include "database.h"
#include <bcrypt.h>
#include <iostream>

Database::Database(const char* dbName) : db(nullptr), dbName(dbName) {}

Database::~Database() {
    close();
}

bool Database::open() {
    int n = sqlite3_open(dbName, &db) == SQLITE_OK;
    if (db != NULL) {
        std::cout << "Database connected successfully" << std::endl;
    }
    return n;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

int Database::addUser(const std::string& username, const std::string& password) {
    if (!db) {
        // Handle error, database not open
        std::cerr << "Cannot open database" << std::endl;
        return -1;
    }
    int checkUser = userExists(username);

    if (checkUser == 0) {
        std::string encrytedPassword = encryptPassword(password); // Encrypt password before adding to database
        if (encrytedPassword == "") {
            // Error occurred in encryptPassword
            return -1;
        }
        sqlite3_stmt *stmt = nullptr;
        const char *query = "INSERT INTO USER (NAME, PASSWORD) VALUES (?, ?)";

        // Prepare and bind parameters
        if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, encrytedPassword.c_str(), -1, SQLITE_TRANSIENT);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                sqlite3_finalize(stmt);
                std::cout << "Added successfully" << std::endl;
                return 1;
            }
        }
    } else {
        return checkUser;
    }
    
    // Handle error
    std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
    return -1;
}

int Database::userExists(const std::string& username) {
    if (!db) {
        // Handle error, database not open
        std::cerr << "Cannot open database" << std::endl;
        return -1;
    }

    const char* query = "SELECT COUNT(*) FROM USER WHERE NAME = ?;";
    sqlite3_stmt* stmt = nullptr;
    int result = 0;

    // Prepare and bind parameters
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        // Execute the statement and retrieve the result
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }

        // Finalize the statement
        sqlite3_finalize(stmt);
    } else {
        // Handle error
        std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    // If the user is registered, query will return 1, otherwise 0
    return result;
}

int Database::validateUser(const std::string& username, const std::string& password) {
    if (!db) {
        // Handle error, database not open
        std::cerr << "Cannot open database" << std::endl;
        return -1;
    }

    if (userExists(username)) {
        const char* query = "SELECT PASSWORD FROM USER WHERE NAME = ?;";
        sqlite3_stmt* stmt = nullptr;
        std::string result = "";

        // Prepare and bind parameters
        if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

            // Execute the statement and retrieve the result
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                result = (const char*)sqlite3_column_text(stmt, 0);
            }

            // Finalize the statement
            sqlite3_finalize(stmt);
        } else {
            // Handle error
            std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
            return -1;
        }
        return bcrypt_checkpw(password.c_str(), result.c_str()) == 0? 1 : 0;  
    } else {
        // User not found
        return 0;
    }
}

int Database::addMatch(const std::string& whiteID, const std::string& blackID,
                              int result, const std::string& moves) {
    if (!db) {
        // Handle error, database not open
        std::cerr << "Cannot open database" << std::endl;
        return -1;
    }
    int checkW = userExists(whiteID), checkB = userExists(blackID);
    if (checkW < 1 || checkB < 1) {
        return checkW < 1 ? checkW : checkB;
    }

    const char* query = "INSERT INTO HISTORY (WID, BID, RESULT, MOVES) VALUES "
        "((SELECT UID FROM USER WHERE NAME = ?), (SELECT UID FROM USER WHERE NAME = ?), ?, ?)";
    sqlite3_stmt* stmt = nullptr;

    // Prepare and bind statement
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, whiteID.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, blackID.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, result);
        sqlite3_bind_text(stmt, 4, moves.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return true;
        } else {
            // Handle error
            std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
            return -1;
        }
    } else {
        // Handle error
        std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    return -1;
}

std::vector<std::vector<std::string>> Database::getMatch(const std::string& username) {
    std::vector<std::vector<std::string>> matchList;
    
    if (!db) {
        // Handle error, database not open
        std::cerr << "Cannot open database" << std::endl;
        return matchList;
    }

    // If username not found, return empty list
    if (userExists(username) < 1) {
        return matchList;
    }

    // Fetch matches where the user is either the white or black player
    const char* query = "SELECT U1.NAME, U2.NAME, RESULT, MOVES, TIME, HID FROM HISTORY H JOIN "
        "USER U1 ON H.WID = U1.UID JOIN USER U2 ON H.BID = U2.UID WHERE WID = ? OR BID = ? ORDER "
        "BY H.HID DESC;";
    sqlite3_stmt* stmt = nullptr;

    // Prepare and bind parameters
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_TRANSIENT);

        // Execute the statement and retrieve the result
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Retrieve values from columns
            std::string whiteID = (const char*)sqlite3_column_text(stmt, 0);
            std::string blackID = (const char*)sqlite3_column_text(stmt, 1);
            int result = sqlite3_column_int(stmt, 2);
            std::string moves = (const char*)sqlite3_column_text(stmt, 3);
            std::string time = (const char*)sqlite3_column_text(stmt, 4);
            int hID = sqlite3_column_int(stmt, 5);

            // Pushing column values into the matrix
            std::vector<std::string> match;
            match.push_back(whiteID);
            match.push_back(blackID);
            match.push_back(std::to_string(result));
            match.push_back(moves);
            match.push_back(time);
            match.push_back(std::to_string(hID));

            matchList.push_back(match);
        }
    } else {
        // Handle error
        std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
    }

    return matchList;
}

std::vector<std::vector<std::string>> Database::getMatch(const std::string& username, const std::string& opponentName) {
    std::vector<std::vector<std::string>> matchList;
    
    if (!db) {
        // Handle error, database not open
        std::cerr << "Cannot open database" << std::endl;
        return matchList;
    }

    // If username not found, return empty list
    if (userExists(username) < 1) {
        return matchList;
    }

    // Fetch matches where the user is either the white or black player
    const char* query = "SELECT U1.NAME, U2.NAME, RESULT, MOVES, TIME, HID FROM HISTORY H JOIN "
        "USER U1 ON H.WID = U1.UID JOIN USER U2 ON H.BID = U2.UID WHERE (WID = ? AND BID = ?) OR "
        "(BID = ? AND WID = ?) ORDER BY H.HID DESC;";
    sqlite3_stmt* stmt = nullptr;

    // Prepare and bind parameters
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, opponentName.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, opponentName.c_str(), -1, SQLITE_TRANSIENT);

        // Execute the statement and retrieve the result
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Retrieve values from columns
            std::vector<std::string> match;
            std::string whiteID = (const char*)sqlite3_column_text(stmt, 0);
            std::string blackID = (const char*)sqlite3_column_text(stmt, 1);
            int result = sqlite3_column_int(stmt, 2);
            std::string moves = (const char*)sqlite3_column_text(stmt, 3);
            std::string time = (const char*)sqlite3_column_text(stmt, 4);
            int hID = sqlite3_column_int(stmt, 5);

            // Pushing column values into the matrix
            match.push_back(whiteID);
            match.push_back(blackID);
            match.push_back(std::to_string(result));
            match.push_back(moves);
            match.push_back(time);
            match.push_back(std::to_string(hID));

            matchList.push_back(match);
        }
    } else {
        // Handle error
        std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
    }
    
    return matchList;
}

std::string Database::encryptPassword(const std::string& password) {
    char salt[BCRYPT_HASHSIZE];
    char hashedPassword[BCRYPT_HASHSIZE];
    
    // Generate a random salt
    int ret = bcrypt_gensalt(12, salt);
    if (ret != 0) {
        // Handle error, print or log the error message
        std::cerr << "Error generating salt" << std::endl;
        return "";
    }

    // Hash the password with the salt
    ret = bcrypt_hashpw(password.c_str(), salt, hashedPassword);
    if (ret!= 0) {
        // Handle error, print or log the error message
        std::cerr << "Error hashing password" << std::endl;
        return "";
    }

    return hashedPassword;
}
