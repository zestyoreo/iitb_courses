#!/usr/bin/python
# -*- coding: utf-8 -*-

import psycopg2

con = psycopg2.connect(database='lab2db', user='postgres',
                       password='s$cret')

with con:

    cur = con.cursor()

    cur.execute("DROP TABLE IF EXISTS words")
    cur.execute("CREATE TABLE words(id SERIAL PRIMARY KEY, word VARCHAR(255))")
    cur.execute("INSERT INTO words(word) VALUES('forest') RETURNING id")
    cur.execute("INSERT INTO words(word) VALUES('cloud') RETURNING id")
    cur.execute("INSERT INTO words(word) VALUES('valley') RETURNING id")

    last_row_id = cur.fetchone()[0]

    print(f"The last Id of the inserted row is {last_row_id}")