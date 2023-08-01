#!/usr/bin/python
# -*- coding: utf-8 -*-

import psycopg2
import sys

con = None
f = None

try:

    con = psycopg2.connect(database='lab2db', user='postgres',
                    password='s$cret')

    cur = con.cursor()
    f = open('cars.csv', 'r')

    cur.copy_from(f, 'cars', sep="|")
    con.commit()

except psycopg2.DatabaseError as e:

    if con:
        con.rollback()

    print(f'Error {e}')
    sys.exit(1)

except IOError as e:

    if con:
        con.rollback()

    print(f'Error {e}')
    sys.exit(1)

finally:

    if con:
        con.close()

    if f:
        f.close()