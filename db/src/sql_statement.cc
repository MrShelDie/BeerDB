//  Author: dennetki@21-school.ru (Elmanov Alexander)

#include "sql_statement.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

#include "commons.h"
#include "exceptions.h"

using namespace std;
std::ostream &operator<<(std::ostream &out, const SQLWhere &where) {
  switch (where.sign_type) {
    case SIGN_EQ:
      cout << "where: " << where.key << " = " << where.value << endl;
      return out;
    case SIGN_NE:
      cout << "where: " << where.key << " != " << where.value << endl;
      return out;
    case SIGN_LT:
      cout << "where: " << where.key << " < " << where.value << endl;
      return out;
    case SIGN_GT:
      cout << "where: " << where.key << " > " << where.value << endl;
      return out;
    case SIGN_LE:
      cout << "where: " << where.key << " <= " << where.value << endl;
      return out;
    case SIGN_GE:
      cout << "where: " << where.key << " >= " << where.value << endl;
      return out;
    default:
      return out;
  }
  return out;
}

std::ostream &operator<<(std::ostream &out, const TKey &object) {
  switch (object.key_type_) {
    case 0: {
      int a;
      memcpy(&a, object.key_, object.length_);
      cout << setw(9) << left << a;
    } break;
    case 1: {
      float a;
      memcpy(&a, object.key_, object.length_);
      cout << setw(9) << left << a;
    } break;
    case 2: {
      cout << setw(9) << left << object.key_;
    } break;
  }

  return out;
}

void SQLSelect::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 90;
  unsigned int pos = 1;

  if (sql_vector.size() <= pos) {
    throw SyntaxErrorException();
  }

  if (strcasecmp(sql_vector[pos].c_str(), "*")) {
    throw SyntaxErrorException();
  }
  pos++;
  if (strcasecmp(sql_vector[pos].c_str(), "from")) {
    throw SyntaxErrorException();
  }
  pos++;

  std::cout << "TABLE NAME: " << sql_vector[pos] << std::endl;
  tb_name_ = sql_vector[pos];
  pos++;

  if (sql_vector.size() == pos) {
    return;
  }

  if (strcasecmp(sql_vector[pos].c_str(), "where")) {
    throw SyntaxErrorException();
  }
  pos++;

  while (true) {
    SQLWhere where;

    where.key = sql_vector[pos];
    pos++;

    if (!strcasecmp(sql_vector[pos].c_str(), "=")) {
      where.sign_type = SIGN_EQ;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "<")) {
      where.sign_type = SIGN_LT;
    } else if (!strcasecmp(sql_vector[pos].c_str(), ">")) {
      where.sign_type = SIGN_GT;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "<=")) {
      where.sign_type = SIGN_LE;
    } else if (!strcasecmp(sql_vector[pos].c_str(), ">=")) {
      where.sign_type = SIGN_GE;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "<>")) {
      where.sign_type = SIGN_NE;
    }
    pos++;

    where.value = sql_vector[pos];
    pos++;

    if (where.value.at(0) == '\'' || where.value.at(0) == '\"') {
      where.value.assign(where.value, 1, where.value.length() - 2);
    }

    wheres_.push_back(where);
    cout << where;

    if (sql_vector.size() == pos) {
      break;
    }

    if (strcasecmp(sql_vector[pos].c_str(), "and")) {
      throw SyntaxErrorException();
    }
    pos++;
  }
}

void SQLExec::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 80;
  if (sql_vector.size() <= 1) {
    throw SyntaxErrorException();
  } else {
    std::cout << "FILE NAME: " << sql_vector[1] << std::endl;
    file_name_ = sql_vector[1];
  }
}

void SQLCreateDatabase::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 30;
  if (sql_vector.size() <= 2) {
    throw SyntaxErrorException();
  } else {
    std::cout << "DB NAME: " << sql_vector[2] << std::endl;
    db_name_ = sql_vector[2];
  }
}

void SQLDropDatabase::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 50;
  if (sql_vector.size() <= 2) {
    throw SyntaxErrorException();
  } else {
    std::cout << "DB NAME: " << sql_vector[2] << std::endl;
    db_name_ = sql_vector[2];
  }
}

void SQLDropTable::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 51;
  if (sql_vector.size() <= 2) {
    throw SyntaxErrorException();
  } else {
    std::cout << "TB NAME: " << sql_vector[2] << std::endl;
    tb_name_ = sql_vector[2];
  }
}

void SQLDropIndex::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 52;
  if (sql_vector.size() <= 2) {
    throw SyntaxErrorException();
  } else {
    std::cout << "IDX NAME: " << sql_vector[2] << std::endl;
    idx_name_ = sql_vector[2];
  }
}

void SQLUse::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 60;
  if (sql_vector.size() <= 1) {
    throw SyntaxErrorException();
  } else {
    std::cout << "DB NAME: " << sql_vector[1] << std::endl;
    db_name_ = sql_vector[1];
  }
}

void SQLCreateTable::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 31;
  unsigned int pos = 2;
  bool is_attr = true;

  if (sql_vector.size() <= pos) {
    throw SyntaxErrorException();
  }

  std::cout << "TABLE NAME: " << sql_vector[pos] << std::endl;
  tb_name_ = sql_vector[pos];
  pos++;

  if (strcasecmp(sql_vector[pos].c_str(), "(")) {
    throw SyntaxErrorException();
  }
  pos++;

  bool has_pk = false;

  while (is_attr) {
    is_attr = false;
    if (!strcasecmp(sql_vector[pos].c_str(), "primary")) {
      pos++;
      if (strcasecmp(sql_vector[pos].c_str(), "key")) {
        throw SyntaxErrorException();
      }
      pos++;

      if (has_pk) {
        throw SyntaxErrorException();
      }

      if (strcasecmp(sql_vector[pos].c_str(), "(")) {
        throw SyntaxErrorException();
      }
      pos++;
      for (unsigned int i = 0; i < attrs_.size(); ++i) {
        if (attrs_[i].attr_name() == sql_vector[pos]) {
          attrs_[i].set_attr_primary();
          std::cout << "PRIMARY KEY: " << sql_vector[pos] << std::endl;
        }
      }
      pos++;
      if (strcasecmp(sql_vector[pos].c_str(), ")")) {
        throw SyntaxErrorException();
      }
      has_pk = true;
    } else {
      std::cout << "COLUMN: " << sql_vector[pos] << std::endl;
      Attribute attr;
      attr.set_attr_name(sql_vector[pos]);
      pos++;

      pos = ParseDataType(sql_vector, attr, pos);

      attrs_.push_back(attr);

      if (strcasecmp(sql_vector[pos].c_str(), ")")) {
        is_attr = true;
      }
    }
  }
}

void SQLCreateIndex::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 32;
  unsigned int pos = 2;
  if (sql_vector.size() <= pos) {
    throw SyntaxErrorException();
  }

  std::cout << "INDEX NAME: " << sql_vector[pos] << std::endl;
  index_name_ = sql_vector[pos];
  pos++;
  if (strcasecmp(sql_vector[pos].c_str(), "on")) {
    throw SyntaxErrorException();
  }
  pos++;

  std::cout << "TABLE NAME: " << sql_vector[pos] << std::endl;
  tb_name_ = sql_vector[pos];
  pos++;
  if (strcasecmp(sql_vector[pos].c_str(), "(")) {
    throw SyntaxErrorException();
  }
  pos++;

  std::cout << "COLUMN NAME: " << sql_vector[pos] << std::endl;
  col_name_ = sql_vector[pos];
  pos++;
  if (strcasecmp(sql_vector[pos].c_str(), ")")) {
    throw SyntaxErrorException();
  }
  pos++;
}

void SQLInsert::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 70;
  unsigned int pos = 1;
  bool is_attr = true;
  if (strcasecmp(sql_vector[pos].c_str(), "into")) {
    throw SyntaxErrorException();
  }
  pos++;
  cout << "TABLE NAME: " << sql_vector[pos] << endl;
  tb_name_ = sql_vector[pos];
  pos++;
  if (strcasecmp(sql_vector[pos].c_str(), "values")) {
    throw SyntaxErrorException();
  }
  pos++;
  if (strcasecmp(sql_vector[pos].c_str(), "(")) {
    throw SyntaxErrorException();
  }
  pos++;
  while (is_attr) {
    is_attr = false;
    SQLValue sql_value;
    std::string value = sql_vector[pos];
    if (value.at(0) == '\'' || value.at(0) == '\"') {
      value.assign(value, 1, value.length() - 2);
      sql_value.data_type = 2;
    } else {
      if (value.find(".") != string::npos) {
        sql_value.data_type = 1;
      } else {
        sql_value.data_type = 0;
      }
    }
    sql_value.value = value;
    cout << sql_value.data_type << " : " << value << endl;
    pos++;
    values_.push_back(sql_value);
    if (strcasecmp(sql_vector[pos].c_str(), ")")) {
      is_attr = true;
    }
    pos++;
  }
}

int SQL::ParseDataType(std::vector<std::string> sql_vector, Attribute &attr,
                       unsigned int pos) {
  // std::algorithm::to_lower(sql_vector[pos]);
  if (!strcasecmp(sql_vector[pos].c_str(), "int")) {
    std::cout << "TYPE: "
              << "int" << std::endl;
    attr.set_data_type(T_INT);
    attr.set_length(4);
    pos++;
    if (!strcasecmp(sql_vector[pos].c_str(), ",")) {
      pos++;
    }
  } else if (!strcasecmp(sql_vector[pos].c_str(), "float")) {
    std::cout << "TYPE: "
              << "float" << std::endl;
    attr.set_data_type(T_FLOAT);
    attr.set_length(4);
    pos++;
    if (!strcasecmp(sql_vector[pos].c_str(), ",")) {
      pos++;
    }
  } else if (!strcasecmp(sql_vector[pos].c_str(), "char")) {
    attr.set_data_type(T_CHAR);
    pos++;
    if (!strcasecmp(sql_vector[pos].c_str(), "(")) {
      pos++;
    }
    attr.set_length(atoi(sql_vector[pos].c_str()));
    pos++;
    if (!strcasecmp(sql_vector[pos].c_str(), ")")) {
      pos++;
    }
    if (!strcasecmp(sql_vector[pos].c_str(), ",")) {
      pos++;
    }
  } else {
    throw SyntaxErrorException();
  }

  return pos;
}

void SQLDelete::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 100;
  unsigned int pos = 1;

  if (sql_vector.size() <= pos) {
    throw SyntaxErrorException();
  }

  if (strcasecmp(sql_vector[pos].c_str(), "from")) {
    throw SyntaxErrorException();
  }
  pos++;

  std::cout << "TABLE NAME: " << sql_vector[pos] << std::endl;
  tb_name_ = sql_vector[pos];
  pos++;

  if (sql_vector.size() == pos) {
    return;
  }

  if (strcasecmp(sql_vector[pos].c_str(), "where")) {
    throw SyntaxErrorException();
  }
  pos++;

  while (true) {
    SQLWhere where;

    where.key = sql_vector[pos];
    pos++;

    if (!strcasecmp(sql_vector[pos].c_str(), "=")) {
      where.sign_type = SIGN_EQ;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "<")) {
      where.sign_type = SIGN_LT;
    } else if (!strcasecmp(sql_vector[pos].c_str(), ">")) {
      where.sign_type = SIGN_GT;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "<=")) {
      where.sign_type = SIGN_LE;
    } else if (!strcasecmp(sql_vector[pos].c_str(), ">=")) {
      where.sign_type = SIGN_GE;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "<>")) {
      where.sign_type = SIGN_NE;
    }
    pos++;

    where.value = sql_vector[pos];
    pos++;

    if (where.value.at(0) == '\'' || where.value.at(0) == '\"') {
      where.value.assign(where.value, 1, where.value.length() - 2);
    }

    wheres_.push_back(where);
    cout << "where: " << where.key << " " << where.sign_type << " "
         << where.value << endl;

    if (sql_vector.size() == pos) {
      break;
    }

    if (strcasecmp(sql_vector[pos].c_str(), "and")) {
      throw SyntaxErrorException();
    }
    pos++;
  }
}

void SQLUpdate::Parse(std::vector<std::string> sql_vector) {
  sql_type_ = 110;
  unsigned int pos = 1;

  if (sql_vector.size() <= pos) {
    throw SyntaxErrorException();
  }

  std::cout << "TABLE NAME: " << sql_vector[pos] << std::endl;
  tb_name_ = sql_vector[pos];
  pos++;

  if (sql_vector.size() == pos) {
    return;
  }

  if (strcasecmp(sql_vector[pos].c_str(), "set")) {
    throw SyntaxErrorException();
  }
  pos++;

  while (true) {
    SQLKeyValue keyvalue;

    keyvalue.key = sql_vector[pos];
    pos++;

    if (strcasecmp(sql_vector[pos].c_str(), "=")) {
      throw SyntaxErrorException();
    }
    pos++;

    keyvalue.value = sql_vector[pos];
    pos++;
    if (keyvalue.value.at(0) == '\'' || keyvalue.value.at(0) == '\"') {
      keyvalue.value.assign(keyvalue.value, 1, keyvalue.value.length() - 2);
    }

    keyvalues_.push_back(keyvalue);
    cout << keyvalue.key << " " << keyvalue.value << endl;

    if (!strcasecmp(sql_vector[pos].c_str(), ",")) {
      pos++;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "where")) {
      break;
    } else {
      throw SyntaxErrorException();
    }
  }

  if (strcasecmp(sql_vector[pos].c_str(), "where")) {
    throw SyntaxErrorException();
  }
  pos++;

  while (true) {
    SQLWhere where;

    where.key = sql_vector[pos];
    pos++;

    if (!strcasecmp(sql_vector[pos].c_str(), "=")) {
      where.sign_type = SIGN_EQ;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "<")) {
      where.sign_type = SIGN_LT;
    } else if (!strcasecmp(sql_vector[pos].c_str(), ">")) {
      where.sign_type = SIGN_GT;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "<=")) {
      where.sign_type = SIGN_LE;
    } else if (!strcasecmp(sql_vector[pos].c_str(), ">=")) {
      where.sign_type = SIGN_GE;
    } else if (!strcasecmp(sql_vector[pos].c_str(), "<>")) {
      where.sign_type = SIGN_NE;
    }
    pos++;

    where.value = sql_vector[pos];
    pos++;

    if (where.value.at(0) == '\'' || where.value.at(0) == '\"') {
      where.value.assign(where.value, 1, where.value.length() - 2);
    }

    wheres_.push_back(where);
    cout << "where: " << where.key << " " << where.sign_type << " "
         << where.value << endl;

    if (sql_vector.size() == pos) {
      break;
    }

    if (strcasecmp(sql_vector[pos].c_str(), "and")) {
      throw SyntaxErrorException();
    }
    pos++;
  }
}
