#include "sqlite3.h"
#include <iostream>
#include <algorithm>

using namespace std;

extern "C" int getGlobalKeyPress(); // Reach in to evtest c program

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	cout<<"db action done"<<endl;
	   int i;
	      for(i = 0; i<argc; i++) {
		            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
			       }
	         printf("\n");
		    return 0;
}

int run_ev_loop = 1;


// Returns true if x is in range [low..high], else false 
bool inRange(int low, int high, int x) 
{ 
    return  ((x-low) <= (high-low)); 
} 

void valuateGlobalCommand(int k_code){


	printf(":: COMMAND IS INTEGER %d \n",k_code);
	if(inRange(1,9, k_code)){
		printf("zesssss");

	}
}

void runloop(){

	while(run_ev_loop){
		int keycode = getGlobalKeyPress();
		printf("\nincomming->> %d\n", keycode);

		if(keycode != -1){

			valuateGlobalCommand(keycode);
			keycode = -1;
		}




	}


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
	

	runloop();
	return 0;
}
