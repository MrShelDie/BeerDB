# BeerDB: Mini Database in C++

Introduction to DBMS. Developing a simple BeerDB for your own.

The russian version of the task can be found in the repository.

## Contents

1. [Chapter I](#chapter-i) \
   1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
   2.1. [Information](#information) \
      2.1.1 [Database Management](#database-management) \
      2.1.2. [Table Management](#table-management) \
      2.1.3. [Index Management](#index-management) \
      2.1.4. [Data Manipulation](#data-manipulation) \
      2.1.5. [Other Features Implemented](#other-features-implemented) \
      2.1.6. [Unimplemented Features](#unimplemented-features)
3. [Chapter III](#chapter-iii)

## Chapter I

![MiniBD](misc/images/s21_containers.png)

Planet Earth, somewhere among the massive containers in the port, October 29, 1993.

*- Do you really think Bjarne will agree to add this to the standard?*

*-- Sure. Moreover, he was already interested in templates a couple of years ago, but then they could not achieve sufficient reliability of the program being developed.* - said a middle-aged man in a white shirt and an HP Labs badge with the inscription "A. Stepanov."

*- I saw your presentation on generalized programming. The idea is really impressive, but they wanted to release a new standard by the end of the year. This one will require a lot of adjustments...*

*-- I think this is exactly what they lacked to fully finalize the new standard. Moreover, as you said, the idea is impressive. However, it does need some adjustments. To be completely confident in the success of the presentation, we need to give some examples of how to use the approach and templates in general. Are you familiar with the structure of B+ trees?*

*- Yes, I think I'm beginning to understand your idea. Do you want to implement your own types of data storage?*

*-- And not only that. Imagine if all the data were contained together and managed by some kind of system. How much time, effort and resources it would save! Lists, maps, sets!" - the walk along the Embarcadero embankment was clearly getting more interesting.*

*- Queues and stacks... Damn it, it's brilliant.*

*-- That's right. After such examples, who will refuse to add a DBMS to their company?*

*- I'm in favor. We could even assemble a small team of guys who are interested in this. How much time do we have to implement these examples?*

*-- So, about two weeks before the presentation meeting in San Jose..*

### Introduction

As part of the project, you need to write your own program that implements the work of the DBMS and the basic standard SQL commands: `Create Database`, `Show Databases`, `Drop Database`, `Use`, `Create Table`, `Drop Table`, `Show Tables`, `Create Index`, `Drop Index`, `Drop Index`, `Insert`, `Select`, `Delete`, and `Update`. Implementations should provide a complete set of standard elements and methods for processing and indexing tables.

## Chapter II

### Information

A Database Management System (DBMS) is a software system that allows users to create, read, update, and delete data from a database. It provides a way to manage and manipulate databases. The DBMS interacts with end users, applications, and the database itself to capture and analyze data.

SQL (Structured Query Language) is a standard language for managing and manipulating databases. It is used to communicate with a database and perform tasks such as retrieving data, inserting records, updating records, deleting records, and creating and modifying database structures.

Here are common SQL commands:

#### Database Management

- Create Database

```SQL
Syntax:  CREATE DATABASE database_name;
Example: CREATE DATABASE abc;
```

- Drop Database

```SQL
Syntax:  DROP DATABASE database_name;
Example:  DROP DATABASE abc;
```

- Show Databases

```SQL
Syntax:  SHOW DATABASES;
Example:  SHOW DATABASES;
```

- Use

```SQL
Syntax:  USE database_name;
Example:  USE abc;
```

#### Table Management

- Create Table

```SQL
Syntax:  CREATE TABLE table_name
   (
   column_name1 data_type(size),
   column_name2 data_type(size),
   column_name3 data_type(size),
   ....,
   PRIMARY KEY (column_name)
   );
Example:  CREATE TABLE aaa
   (
   col1 int,
   col2 float,
   col3 char(8),
   PRIMARY KEY (col1)
   );
```

Note: Available data types include int, float and char(N). Only one primary key could be created.

- Drop Table

```SQL
Syntax:  DROP TABLE table_name;
Example: DROP TABLE aaa;
```

- Show Tables

```SQL
Syntax:  SHOW TABLES;
Example:  SHOW TABLES;
```

#### Index Management

- Create Index

```SQL
Syntax:  CREATE INDEX index_name
   ON table_name (column_name);
Example:  CREATE INDEX aaacol1 
   ON aaa (col1);
```

Note: Index can only be created on primary key. B+ tree manipulation is implemented in all data manipulation SQLs.

- Drop Index

```SQL
Syntax:  DROP INDEX index_name;
Example: DROP INDEX aaacol1;
```

#### Data Manipulation

- Insert

```SQL
Syntax:  INSERT INTO table_name
   VALUES (value1, value2, value3, ...);
Example:  INSERT INTO aaa
   VALUES (111, 222.2, 'xyz');
```

- Select

```SQL
Syntax:  SELECT * FROM table_name
   WHERE column1 = value1
   and column2 = value2
   and ...;
Example: SELECT * FROM aaa
   WHERE col1 = 111;
```

Note:  Only "and" logic is allowed. Only "*" is allowed.

- Delete

```SQL
Syntax:  DELETE FROM table_name 
   WHERE column1 = value1
   and column2 = value2
   and ...;
Example: DELETE FROM aaa
   WHERE col1 = 111;
```

Note:  Only "and" logic is allowed.

- Update

```SQL
Syntax:  UPDATE table_name
   SET column1 = value1, column2 = value2, ...
   WHERE column1 = value1
   and column2 = value2
   and ...;
Example: UPDATE aaa
   SET col2 = 555.5
   WHERE col1 = 1;
```

Note:  Only "and" logic is allowed.

#### Other Features Implemented

- Help

```SQL
Syntax:  HELP;
Example:  HELP;
```

- Quit

```SQL
Syntax:  EXIT
   or
   QUIT
Example: EXIT
   or
   QUIT
```

- Exec

```SQL
Syntax:  EXEC file_name;
Example:  EXEC input.txt;
```

#### Unimplemented Features

- Transaction Management
- User Management
- Authentication
- Join
- Foreign Keys
- Views
- Complex Select

## Chapter III

- The program must be developed in C++ language of C++17 standard using gcc compiler
- The program code must be located in the src folder
- When writing code it is necessary to follow the Google style
- Make sure to use iterators
- Classes must be template
- Prepare full coverage of container classes methods with unit-tests using the GTest library
- Copying of the Standard Template Library (STL) implementation is not allowed
- The logic of the Standard Template Library (STL) must be followed (in terms of checks, memory handling and behaviour in abnormal situations)
