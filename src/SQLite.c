// Fichero de muestra para conectar con la base de datos SQlite

// gcc main.c -lsqlite3

#include <stdio.h>
#include <sqlite3.h>    // Para trabajar con SQLite
  
int main (int argc, char **argv) {
  sqlite3 *db;          // Definimos un puntero a la base de datos
  char *errMsg = 0;     // Variable para el mensaje de error
  int rc;               // Variable para el retorno de la sentencia
  sqlite3_stmt *result; // Puntero a la respuesta de la consulta

  // Abro la conexión con la base de datos
  rc = sqlite3_open("BDPrueba.sqlite", &db);
  // Compruebo que no hay error
  if (rc != SQLITE_OK) {
    fprintf(stderr, "No se puede acceder a la base de datos: %s.\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }

  // Borro la tabla si no existe
  rc = sqlite3_exec(db, "DROP TABLE IF EXISTS Empresa", NULL, NULL, &errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Error al borrar la tabla: %s.\n", errMsg);
    sqlite3_free(errMsg);
    sqlite3_close(db);
    return(2);
  }
  // Creo la tabla Empresa
  rc = sqlite3_exec(db, "CREATE TABLE Empresa (IdEmpresa INTEGER PRIMARY KEY, Nombre CHAR[250])", NULL, NULL, &errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Error al crear la tabla: %s.\n", errMsg);
    sqlite3_free(errMsg);
    sqlite3_close(db);
    return(2);
  }
  // Inserto un par de registros
  rc = sqlite3_exec(db, "INSERT INTO Empresa VALUES( 1, 'Empresa A')", NULL, NULL, &errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Error al crear el primer registro: %s.\n", errMsg);
    sqlite3_free(errMsg);
    sqlite3_close(db);
    return(2);
  }
  rc = sqlite3_exec(db, "INSERT INTO Empresa VALUES( 2, 'Empresa B')", NULL, NULL, &errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Error al crear el segundo registro: %s.\n", errMsg);
    sqlite3_free(errMsg);
    sqlite3_close(db);
    return(2);
  }

  // Consulta a realizar sobre la tabla.
  // En este caso quiero los campos idEmpresa y Nombre de la tabla Empresa
  rc = sqlite3_prepare(db, "SELECT idEmpresa,Nombre FROM Empresa", -1, &result, NULL);
  // Compruebo que no hay error
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Error en la consulta: %s.\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(3);
  }

  // Bucle de presentación en pantalla del resultado de la consulta
  while ( sqlite3_step(result) == SQLITE_ROW) {
    fprintf(stderr, "El Id y nombre de la empresa son:  %i - %s.\n", sqlite3_column_int(result, 0)
                                                                   , sqlite3_column_text(result, 1));
  }

  // Cierro la conexión
  sqlite3_close(db);

  return 0;
}

