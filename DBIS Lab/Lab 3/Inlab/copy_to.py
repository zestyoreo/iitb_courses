#!/usr/bin/python
# -*- coding: utf-8 -*-

import psycopg2
import sys

con = None
fout = None

try:

    con = psycopg2.connect(database='lab2db', user='postgres',
                    password='s$cret')

    cur = con.cursor()
    fout = open('cars.csv', 'w')
    cur.copy_to(fout, 'cars', sep="|")

except psycopg2.DatabaseError as e:

    print(f'Error {e}')
    sys.exit(1)

except IOError as e:

    print(f'Error {e}')
    sys.exit(1)

finally:

    if con:
        con.close()

    if fout:
        fout.close()