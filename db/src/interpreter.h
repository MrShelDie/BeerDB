//  Author: dennetki@21-school.ru (Elmanov Alexander)

#ifndef BeerDB_INTERPRETER_H_
#define BeerDB_INTERPRETER_H_

#include <string>
#include <vector>

#include "BeerDB_api.h"
#include "sql_statement.h"

class Interpreter {
 private:
  BeerDBAPI *api;
  std::string sql_statement_;
  std::vector<std::string> sql_vector_;
  int sql_type_;
  void TellSQLType();
  void FormatSQL();
  void Run();

 public:
  Interpreter();
  ~Interpreter();
  void ExecSQL(std::string statement);
};

#endif /* BeerDB_INTERPRETER_H_ */
