#!/usr/bin/python
# -*- coding: utf-8 -*-

import psycopg2

con = psycopg2.connect(database='lab2db', user='postgres',
                    password='s$cret')
cur = None

with con:
    
    cur = con.cursor()     

    print(cur.mogrify("SELECT name, price FROM cars WHERE id=%s", (2,)))

    # cur.execute("SELECT name, price FROM cars WHERE id=%s", (2,) )
    # row = cur.fetchone()
    # print(f"{row[0]} {row[1]}")