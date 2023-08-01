#!/usr/bin/python
# -*- coding: utf-8 -*-

import psycopg2

con = psycopg2.connect(database='lab2db', user='postgres',
                    password='s$cret')

with con:

    cur = con.cursor()
    cur.execute("SELECT * FROM cars")

    rows = cur.fetchall()       #tuple of tuples

    for row in rows:
        print(f"{row[0]} {row[1]} {row[2]}")