#include "sqlite3.h"
#include <iostream>

using namespace std;

extern "C" int runevtest();

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	cout<<"db action done"<<endl;
	   int i;
	      for(i = 0; i<argc; i++) {
		            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
			       }
	         printf("\n");
		    return 0;
}

int main(int argc, char **argv){
	
	sqlite3* db;
	char *errMsg = 0;
	const char *sql;
	

	int res = sqlite3_open("db_1.db", &db);
	if(res){
	    //database failed to open
	    cout << "Database failed to open" << endl;
	}else{
		//your database code here
	    cout << "Database opened" << endl;
	    sql="INSERT INTO nodes (password,type,tags) VALUES('hof','url','la la')";
	    res = sqlite3_exec(db,sql, callback,0,&errMsg);
	    
	    if( res != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", errMsg);
			sqlite3_free(errMsg);
		} else{
			fprintf(stdout, "Records created successfully\n");
	
		}
	}


	
	sqlite3_close(db);
	runevtest();
	return 0;
}
