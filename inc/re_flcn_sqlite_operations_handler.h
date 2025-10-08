//
// Created by revolver-ocelot on 9/22/25.
//

#ifndef FALCON_V2_RE_FLCN_SQLITE_OPERATIONS_HANDLER_H
#define FALCON_V2_RE_FLCN_SQLITE_OPERATIONS_HANDLER_H

#define FLCN_SQLITE_OPEN_RW SQLITE_OPEN_READWRITE
#define FLCN_SQLITE_OPEN_CR SQLITE_OPEN_CREATE

#define FLCN_SQL_REQUEST "SELECT f_name, f_hash FROM flcn_hashes WHERE f_name = ?"
#define FLCN_SQLITE_CREATE_TABLE "CREATE TABLE IF NOT EXISTS flcn_hashes (f_name TEXT PRIMARY KEY, f_hash TEXT NOT NULL)"
#define FLCN_SQLITE_INSERT_TABLE "REPLACE INTO flcn_hashes (f_name, f_hash) VALUES (?, ?)"

#include <sqlite3.h>

typedef enum
{
    FLCN_DB_ROW,    //this dont work and its useless. Remove ASAP
    FLCN_DB_DONE,
    FLCN_DB_ERROR
}flcn_db_stat;

int flcn_dboperations_open_db(const char *db_path, sqlite3 **db, int flags);

int flcn_dboperations_prepare_db(sqlite3 *db, const char *request, sqlite3_stmt **stmt);

int flcn_dboperations_db_bind_text(sqlite3_stmt *stmt, int pos,const char *file_name);

int flcn_dboperations_step_db(sqlite3_stmt *stmt);

int flcn_dboperations_finalize_db_stmt(sqlite3_stmt *stmt);

int flcn_dboperations_close_db(sqlite3 *db);

char *flcn_dboperations_column_strdup(sqlite3_stmt *stmt, int column);
//O meu maior medo é o futuro. E se eu nunca conseguir as coisas que sempre desejei?
//isso é o de menos, e se eu nunca conseguir nada e viver uma vida miserável?
//Talvez eu seja burro demais para seguir numa carreira intelectual
//Mas preguiçoso demais para trabalhar num sub-emprego(que ja trabahlo atualmente, mas é """tranquilo""")
//Não sei a quem atribuir a culpa. Pode ser culpa do meu pai que me criou assim,
//pode ser culpa minha que sou preguiçoso e burro, pode ser o ambiente em que cresci
//e me proporcionou.
//Escrever aqui me parece um lugar segroo. Ninguém vai ver esse repositório mesmo, quem dirá parar para analisar os arquivos
#endif //FALCON_V2_RE_FLCN_SQLITE_OPERATIONS_HANDLER_H