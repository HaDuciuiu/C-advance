#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "207.148.67.107", "tuyenld", "LDTpro@2001",
          "ql_pakn", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  // if (mysql_query(con, "DROP TABLE IF EXISTS cars")) {
  //     finish_with_error(con);
  // }

  // if (mysql_query(con, "CREATE TABLE cars(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), price INT)")) {
  //     finish_with_error(con);
  // }

  // if (mysql_query(con, "INSERT INTO cars VALUES(1,'Audi',52642)")) {
  //     finish_with_error(con);
  // }

  // if (mysql_query(con, "INSERT INTO cars VALUES(2,'Mercedes',57127)")) {
  //     finish_with_error(con);
  // }

  // if (mysql_query(con, "INSERT INTO cars VALUES(3,'Skoda',9000)")) {
  //     finish_with_error(con);
  // }

  // if (mysql_query(con, "INSERT INTO cars VALUES(4,'Volvo',29000)")) {
  //     finish_with_error(con);
  // }

  // if (mysql_query(con, "INSERT INTO cars VALUES(5,'Bentley',350000)")) {
  //     finish_with_error(con);
  // }

  // if (mysql_query(con, "INSERT INTO cars VALUES(6,'Citroen',21000)")) {
  //     finish_with_error(con);
  // }

  // if (mysql_query(con, "INSERT INTO cars VALUES(7,'Hummer',41400)")) {
  //     finish_with_error(con);
  // }

  // if (mysql_query(con, "INSERT INTO cars VALUES(8,'Volkswagen',21600)")) {
  //     finish_with_error(con);
  // }

if (mysql_query(con, "SELECT * FROM cars WHERE price > 40000"))
  {
      finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  MYSQL_FIELD *field;

  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          if (i == 0)
          {
             while(field = mysql_fetch_field(result))
             {
                printf("%s ", field->name);
             }

             printf("\n");
          }

          printf("%s  ", row[i] ? row[i] : "NULL");
      }
  }

  printf("\n");

  mysql_close(con);
  exit(0);
}