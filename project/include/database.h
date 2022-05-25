#ifndef PROJECT_INCLUDE_DATABASE_H
#define PROJECT_INCLUDE_DATABASE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <sqlite3.h>

namespace database {
enum DB_FUNC_EXIT_CODES{
	DB_FUNC_ERR_OPEN = (-3),
	DB_FUNC_ERR_SQL_EXEC, 
	DB_FUNC_ERR_CLOSE, 
	DB_FUNC_CODE_SUCCESS
};

/*CОСТОЯНИЯ СЛОВ ОТ ВЛАДА

1. ещё не изучается: то есть пользователь вообще ещё не выбирал изучать категорию, в котором есть это слово
2. выбрано для изучения: слово ест
обновить все поля в бд для слова с id равным word.id
3)
Word get_word_to_learn(int user_id);
Возвращает случайное слово среди слов с состоянием выбрано для изучения для данного пользователя
4)
Word get_word_to_revise(int user_id);
Возвращает случайное слово среди слов с состоянием повторяется для данного пользователя
5)
int auth(std::string login, std::string password);
Возвращает -1, если вход не удался (нет такого логина или неправильный пароль).  Иначе возвращает id пользователя
6)
int register(std::string login, std::string password);
Возвращает -1, если такой логин уже зарегистрирован. Иначе создаёт новую учётную запись и возвращает id
*/

/*
Вот итоговый вариант функций, которые требуют изменений в бд на сервере.
Все они возвращают int, чтобы была возможность показать неуспех

1. int register(std::string login, std::string password);
2. int set_category_status(int user_id, int category_id, bool status) - если статус true, то нужно, чтобы эта категория была изучаемой, а если false, то неизучаемой
3-4. int set_word_status(int user_id, int word_id, int status);
5. int set_notes(int user_id, int word_id, std::string notes)
6 = 2 со статусом false
7 = 3-4 с разными статусами.
Так что по сути есть 4 функции, которые требуют изменений в бд на сервереИ есть ещё одна функция, которая требует считать информацию именно с бд, а не с клиента
int auth(std::string login, std::string password);
*/

bool createDB(const char* pathname);
int createTable(const char* pathname);
int insertInitialWordsCategs(const char* pathname);

struct Word {
	size_t id;
	std::string endlish_word;
	std::string translation;
	std::string transcription;
	int learning_status;
};

struct Hookup {
	size_t hookup_id; 
	std::string user_id;
	std::string word_id;
	std::string state; 
	std::string notes; 
};

class ManagerDB {
 public: 
    ManagerDB(const char * pathname);
    ~ManagerDB();

		int signUp(std::string login, std::string password); // регистрация insert
		int auth(std::string login, std::string password); // select

		int setCategoryStatus(int user_id, int category_id, bool status); // update
		int setWordStatus(int user_id, int word_id, int status); // update
		int setNotes(int user_id, int word_id, std::string notes); // update

		struct Word getWordLearn(int user_id); // select
		struct Word getWordRevise(int user_id); // select



 private:
  sqlite3* db_;
	int insertInitialHookups(int user_id);  // insert

};
} // namespace database

#endif  // PROJECT_INCLUDE_DATABASE_H
