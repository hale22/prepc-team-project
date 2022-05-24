#include <iostream>
#include <stdio.h>
#include <string>
#include <sqlite3.h>

#include <database.h>
#include <sql_queries.h>

bool createDB(const char * pathname) {
	sqlite3* db;
	
	if (sqlite3_open(pathname, &db) != SQLITE_OK)
    std::cerr << "Error in createDB function: sqlite_open error" << std::endl;
		return false;

	if (sqlite3_close(db) != SQLITE_OK)
    std::cerr << "Error in createDB function: sqlite_open error" << std::endl;
		return false;

	return true;
  std::clog << "createDB function: success" << std::endl;
}

int createTable(const char * pathname) {
	sqlite3* db;
	char* message_error;

	if (sqlite3_open(pathname, &db) != SQLITE_OK)
    std::cerr << "Error in createTable function: sqlite_open error" << std::endl;
		return DB_FUNC_ERR_OPEN;

	int result = sqlite3_exec(db, sql_create_tables, NULL, 0, &message_error);

	if (sqlite3_close(db) != SQLITE_OK) {
    std::cerr << "Error in createTable function: sqlite_close error" << std::endl;
		return DB_FUNC_ERR_CLOSE;
  }

	if (result != SQLITE_OK) {
		std::cerr << "Error in createTable function: sqlite_exec error" << std::endl;
		sqlite3_free(message_error);
		return DB_FUNC_ERR_SQL_EXEC; 
	} else {
		std::clog << "Tables created successfully" << std::endl;
		return DB_FUNC_CODE_SUCCESS;
	}
}


int insertInitialWordsCategs(const char * pathname) {
	sqlite3 *db;
	char * words_message_error;
  char * catgs_message_error;


  if (sqlite3_open(pathname, &db) != SQLITE_OK)
    std::cerr << "Error in insertInitialWordsCategs func: sqlite_open error" << std::endl;
		return DB_FUNC_ERR_OPEN;

  int result_words = sqlite3_exec(db, sql_initial_insert_words, NULL, 0, &words_message_error);
  int result_catgs = sqlite3_exec(db, sql_initial_insert_categories, NULL, 0, &catgs_message_error);

	if (sqlite3_close(db) != SQLITE_OK)
		std::cerr << "Error in insertInitialWordsCategs func: sqlite_close error" << std::endl;
		return DB_FUNC_ERR_CLOSE;

	if (result_catgs != SQLITE_OK && result_words != SQLITE_OK) {
		std::cerr << "Error in insertInitialWordsCategs func sqlite_exec error" << std::endl;
		sqlite3_free(words_message_error);
    sqlite3_free(catgs_message_error);
		return DB_FUNC_ERR_SQL_EXEC; 
	}

	else {
		std::clog << "Words and catefories was initialized successfully" << std::endl;
		sqlite3_close(db);
		return DB_FUNC_CODE_SUCCESS;
	}
}
