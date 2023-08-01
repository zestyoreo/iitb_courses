#!/usr/bin/python
# -*- coding: utf-8 -*-

import psycopg2

con = psycopg2.connect(database='lab2db', user='postgres',
                       password='s$cret')

with con:

    cur = con.cursor()

    cur.execute('SELECT * FROM cars')

    desc = cur.description

    print(desc)