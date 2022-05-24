#ifndef PROJECT_INCLUDE_DATABASE_H
#define PROJECT_INCLUDE_DATABASE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <sqlite3.h>

enum DB_FUNC_EXIT_CODES{
	DB_FUNC_ERR_OPEN = (-3),
	DB_FUNC_ERR_SQL_EXEC, 
	DB_FUNC_ERR_CLOSE, 
	DB_FUNC_CODE_SUCCESS
};

/*CОСТОЯНИЯ СЛОВ ОТ ВЛАДА

1. ещё не изучается: то есть пользователь вообще ещё не выбирал изучать категорию, в котором есть это слово
2. выбрано для изучения: слово есть в какой-то из выбранных категорий, но пока ни разу не выпадало пользователю
3. повторяется: это когда слово хотя бы один раз выпадало пользователю
4. изучено

*/

/* ФУНКЦИИ ОТ ВЛАДА


1)
void learn_category(int user_id, int category_id);
она должна у данного пользователя для каждого слова из данной категории проставить состояние выбрано для изучения.
2)
void update_word(Word word);
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

/* ФУНКЦИИ ПО МОИМ ТРЕБОВАНИЯМ 
* создать таблицы
* таблица ->  json
* json -> таблица

*/

bool createDB(const char * pathname);
int createTable(const char * pathname);

int insertInitialWordsCategs(const char * pathname);

bool auth(std::string login, std::string password);

struct Word {
	size_t id;
	std::string endlish_word;
	std::string translation;
	std::string transcription;
	int learning_status;
};


class ManagerDB {
 public: 
    ManagerDB();
    ~ManagerDB();
 private:
  sqlite3* db;
	struct Word;
};

#endif  // PROJECT_INCLUDE_DATABASE_H
