#!/usr/bin/python
# -*- coding: utf-8 -*-

import psycopg2

uid = 3

con = psycopg2.connect(database='lab2db', user='postgres',
                    password='s$cret')

with con:

    cur = con.cursor()

    cur.execute("SELECT * FROM cars WHERE id=%(id)s", {'id': uid } )

    row = cur.fetchone()

    print(f'{row[0]} {row[1]} {row[2]}')