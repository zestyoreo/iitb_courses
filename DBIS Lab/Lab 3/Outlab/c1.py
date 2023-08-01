import argparse
import psycopg2
import os

# Function to import SQL statements from a file
def import_sql(cursor, file_path):
    with open(file_path, 'r') as f:
        sql_statements = f.read()
    cursor.execute(sql_statements)

# Function to show the list of tables
def show_tables(cursor):
    cursor.execute("""
        SELECT table_name
        FROM information_schema.tables
        WHERE table_schema NOT LIKE 'pg_%'
        AND table_schema != 'information_schema'
        ORDER BY table_name
    """)
    tables = cursor.fetchall()
    for table in tables:
        print(table[0])

# Function to show the table schema
def show_table_schema(cursor, table_name):
    # Get column information
    cursor.execute("""
        SELECT column_name, data_type, character_maximum_length
        FROM information_schema.columns
        WHERE table_name = %s
        ORDER BY ordinal_position
    """, (table_name,))
    columns = cursor.fetchall()

    # Get primary key information
    cursor.execute("""
        SELECT kcu.column_name
        FROM information_schema.table_constraints tc
        JOIN information_schema.key_column_usage kcu
        ON tc.constraint_name = kcu.constraint_name
        WHERE tc.table_name = %s
        AND constraint_type = 'PRIMARY KEY'
        ORDER BY ordinal_position
    """, (table_name,))
    primary_keys = cursor.fetchall()

    # Get foreign key information
    cursor.execute("""
        SELECT kcu.column_name, ccu.table_name, ccu.column_name
        FROM information_schema.table_constraints tc
        JOIN information_schema.key_column_usage kcu
        ON tc.constraint_name = kcu.constraint_name
        JOIN information_schema.constraint_column_usage ccu
        ON ccu.constraint_name = tc.constraint_name
        WHERE tc.table_name = %s
        AND constraint_type = 'FOREIGN KEY'
        ORDER BY kcu.ordinal_position
    """, (table_name,))
    foreign_keys = cursor.fetchall()

    # Get unique constraint information
    cursor.execute("""
        SELECT column_name
        FROM information_schema.constraint_column_usage
        WHERE table_name = %s
        AND constraint_name LIKE '%_key'
        ORDER BY ordinal_position
    """, (table_name,))
    unique_constraints = cursor.fetchall()

    print(f"CREATE TABLE {table_name} (")
    for column in columns:
        print(f"    {column[0]} {column[1]}", end="")
        if column[2]:
            print(f"({column[2]})", end="")
        print(",")

    # Print primary keys
    if primary_keys:
        print("    PRIMARY KEY (", end="")
        for i, key in
