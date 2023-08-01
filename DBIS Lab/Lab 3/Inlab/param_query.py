#!/usr/bin/python
# -*- coding: utf-8 -*-

import psycopg2

uId = 1
uPrice = 62300

con = psycopg2.connect(database='lab2db', user='postgres',
                    password='s$cret')

with con:

    cur = con.cursor()
    cur.execute("UPDATE cars SET price=%s WHERE id=%s", (uPrice, uId))

    print(f"Number of rows updated: {cur.rowcount}")