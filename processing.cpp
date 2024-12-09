#include <iostream>
#include <unordered_map>
#include <string>
#include <optional>
#include <stdexcept>
using namespace std;
class InMemoryDB{

public:
    optional<int> get(const string &key) const{
        auto it = active.find(key);
        if(it != active.end()){
            return it->second;
        }
        return nullopt;
    }

    void put(const string &key, int val){
        if(!current){
            throw runtime_error("put called without an active transaction");
        }
        transactions[key] = val;
    }
    
    void begin_transaction(){
        if(current){
            throw runtime_error("a transaction is already in progress!");
        }
        current = true;
        transactions.clear();
    }

    void commit(){
        if(!current){
            throw runtime_error("commit called without an active transaction");
        }
        for(const auto &it: transactions){
            active[it.first] = it.second;
        }
        transactions.clear();
        current = false;
    }

    void rollback(){
        if(!current){
            throw runtime_error("rollback called without an active transaction");
        }
        transactions.clear();
        current = false;
    }

private:
    bool current = false;
    unordered_map<string, int> transactions;
    unordered_map<string, int> active;

};

int main() {
    InMemoryDB db;
    {
        auto val = db.get("A");
        std::cout << "db.get(\"A\") before transaction: "
                  << (val.has_value() ? std::to_string(val.value()) : "null") << "\n";
    }
    try {
        db.put("A", 5);
    } catch (const std::runtime_error &e) {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }
    db.begin_transaction();
    db.put("A", 5);
    {
        auto val = db.get("A");
        std::cout << "db.get(\"A\") after put in transaction (uncommitted): "
                  << (val.has_value() ? std::to_string(val.value()) : "null") << "\n";
    }
    db.put("A", 6);
    db.commit();
    {
        auto val = db.get("A");
        std::cout << "db.get(\"A\") after commit: "
                  << (val.has_value() ? std::to_string(val.value()) : "null") << "\n";
    }
    try {
        db.commit();
    } catch (const std::runtime_error &e) {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }
    try {
        db.rollback();
    } catch (const std::runtime_error &e) {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }
    {
        auto val = db.get("B");
        std::cout << "db.get(\"B\") before setting: "
                  << (val.has_value() ? std::to_string(val.value()) : "null") << "\n";
    }
    db.begin_transaction();
    db.put("B", 10);
    db.rollback();
    {
        auto val = db.get("B");
        std::cout << "db.get(\"B\") after rollback: "
                  << (val.has_value() ? std::to_string(val.value()) : "null") << "\n";
    }
    return 0;
}