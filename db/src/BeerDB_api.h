//  Author: mrsheldie@mail.ru (Ivchenko Nikolay)

#ifndef BeerDB_BeerDB_API_H_
#define BeerDB_BeerDB_API_H_

#include <string>

#include "buffer_manager.h"
#include "catalog_manager.h"
#include "sql_statement.h"

class BeerDBAPI {
 private:
  std::string path_;
  CatalogManager *cm_;
  BufferManager *hdl_;
  std::string curr_db_;

 public:
  BeerDBAPI(std::string p);
  ~BeerDBAPI();
  void Quit();
  void Help();
  void CreateDatabase(SQLCreateDatabase &st);
  void ShowDatabases();
  void DropDatabase(SQLDropDatabase &st);
  void DropTable(SQLDropTable &st);
  void DropIndex(SQLDropIndex &st);
  void Use(SQLUse &st);
  void CreateTable(SQLCreateTable &st);
  void ShowTables();
  void Insert(SQLInsert &st);
  void Select(SQLSelect &st);
  void CreateIndex(SQLCreateIndex &st);
  void Delete(SQLDelete &st);
  void Update(SQLUpdate &st);
};

#endif /* BeerDB_BeerDB_API_H_ */
