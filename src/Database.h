#pragma once 
#include <iostream>
#include <pqxx/pqxx>
#include <future>
#include <sstream>
#include <thread>
#include <fstream>


using namespace std;

const string host = "aws-0-us-east-1.pooler.supabase.com";
const string port = "6543";
const string dbname = "postgres";
const string user = "postgres.acobuhpfnokxtrpwqhmw";
string pass;

class Database {
public:
    Database() : connection(nullptr) {
        pass = readPassword("db_password.txt");
        connect();
        cout << executeQueryAsync("SELECT version();").get() << endl;
        cout << "Connected to: " << connection -> dbname() << endl;
    }
    ~Database() {
        if (!connection) return;
        cout << "Disconnected" << endl;
        delete connection;
        connection = nullptr;
    }
private:
    pqxx::connection* connection;

    string readPassword(const std::string& filename) {
        std::ifstream file(filename);
        std::string password;
        if (file.is_open()) {
            std::getline(file, password);
            file.close();
        } else throw std::runtime_error("Unable to open password file");
        return password;
    }
    
    void connect() {
        try {
            connection = new pqxx::connection("host=" + host + " port=" + port + " dbname=" + dbname + " user=" + user + " password=" + pass);
            if (!(connection -> is_open())) cout << "I can't connect" << endl;
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
    }
public:

    string executeQuery(const string& query) {
        stringstream result;
        if (!connection || !connection -> is_open()) {
            cerr << "Database connection is not open!" << endl;
            return result.str();
        }

        try {
            pqxx::nontransaction N(*connection);
            pqxx::result R(N.exec(query));

            for (int i = 0; i < R.size(); i++) {
                for (auto field : R[i]) result << field.c_str() << " ";
                if (i < R.size() - 1) result << endl;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
        return result.str();
    }

    future<string> executeQueryAsync(const string& query) {
        return async(launch::async, &Database::executeQuery, this, query);
    }

};