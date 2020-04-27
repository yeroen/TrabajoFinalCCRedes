#include <iostream>
#include <string.h>
#include <sqlite3.h>

using namespace std;

    void execSELECT(sqlite3* connDB, string table, string columns = " *")
    {
        sqlite3_stmt *stmt;
        string query = "SELECT " + columns + " FROM " + table;
        const char *sql = query.c_str();
        if (sqlite3_prepare_v2(connDB, sql , strlen(sql), &stmt, NULL) == SQLITE_OK)
        {
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                int id = sqlite3_column_int(stmt, 0);
                cout << id << " ";
                for (int i = 1; i < sqlite3_column_count(stmt); i++ )
                {
                    const unsigned char* dato = sqlite3_column_text(stmt, i);
                    cout << dato << " ";
                }
                cout << endl;
            }
            cout << "successfully query \n";
        }
        else
            cout << "Error execSelect: " << sqlite3_errmsg(connDB) << endl;
        sqlite3_finalize(stmt);
    }

    void exec(sqlite3* connDB, const char* sql)
    {
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(connDB, sql, strlen(sql), &stmt, NULL) == SQLITE_OK)
        {
            sqlite3_step(stmt);
        }
        else
            cout << "Error exec: " << sqlite3_errmsg(connDB) << endl;
        sqlite3_finalize(stmt);
    }


int main(){
    sqlite3 *connDB;
    sqlite3_stmt *stmt;

    if (sqlite3_open("./test.db", &connDB) == SQLITE_OK)
    {
        //exec(connDB,"update into nodo2 values(5,'alexander','pinto')");
        //exec(connDB,"update nodo2 set dni='felix' where id = 3");
        //exec(connDB,"delete from nodo2 where id = 5");
        execSELECT(connDB,"nodo2");
    }
    else
        cout << "Failed to open db\n";

    /*if (sqlite3_exec(db, "insert into nodo values (3,'jorge')", 0, 0, 0) == SQLITE_OK) cout << "query1 successfully\n";
    else cout << "query1 failed \n";*/
    
    //sqlite3_finalize(stmt);
    sqlite3_close(connDB);

    return 0;
}