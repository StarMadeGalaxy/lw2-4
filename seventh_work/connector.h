#pragma once

#include "stdafx.h"
#include <mysql.h>
#include <stdio.h>


struct ConnectCreate
{
	MYSQL* connection = NULL;

	const char* host = "localhost";
	const char* username = "root";
	const char* password = "password";
	const char* database = "tariff_database";

	const char* unix_socket = NULL;
	uint32_t port = 3306;
	unsigned long clientflag = 0;

	ConnectCreate()
	{
		connection = mysql_init(NULL);

		if (connection == NULL)
		{
			fprintf(stderr, "\nFailed to init database: Error: %s\n", mysql_error(connection));
			exit(EXIT_FAILURE);
		}

		if (mysql_real_connect(connection, host, username, password, database, port, unix_socket, clientflag) == NULL)
		{
			fprintf(stderr, "\nFailed to init database: Error: %s\n", mysql_error(connection));
			exit(EXIT_FAILURE);
		}
	}

	~ConnectCreate()
	{
		mysql_close(connection);
	}
};