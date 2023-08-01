import argparse, psycopg2, sys, csv
from psycopg2.extras import execute_values

edges = None
toposort = None
visited = None

def main(args):
    connection = psycopg2.connect(host = args.host, port = args.port, database = args.name, user = args.user, password = args.pswd)
    cursor = connection.cursor()
    
    if(args.import_table_data):
        cursor.execute("SELECT * FROM {}".format(args.table))
        with open(args.path, 'r') as f:
            next(f)
            reader = csv.reader(f)
            values = []
            for line in reader:
                values.append(line)
            query = "INSERT INTO {} ({}) VALUES %s".format(args.table, ','.join([col[0] for col in cursor.description]))
            # print(values)
            execute_values(cursor, query, values)
        connection.commit()
    
    if(args.export_table_data):
        cursor.execute("SELECT * FROM {}".format(args.table))
        if args.path:

            if args.format == 'csv':
                with open(args.path, 'w') as f:
                    writer = csv.writer(f)
                    writer.writerow([col[0] for col in cursor.description])
                    writer.writerows(cursor.fetchall())
                    
            elif args.format == 'sql':
                with open(args.path, 'w') as f:
                    for row in cursor.fetchall():
                        f.write("INSERT INTO {} ({}) VALUES ({})\n".format(args.table, ','.join([col[0] for col in cursor.description]), ','.join(row)))
        
        else:
            if args.format == 'csv':
                writer = csv.writer(sys.stdout)
                writer.writerow([col[0] for col in cursor.description])
                writer.writerows(cursor.fetchall())
                    
            elif args.format == 'sql':
                for row in cursor.fetchall():
                    sys.stdout.write("INSERT INTO {} ({}) VALUES ({})\n".format(args.table, ','.join([col[0] for col in cursor.description]), ','.join(row)))

    if(args.show_tables):
        pass

    if(args.show_table_schema):
        pass

    if(args.import_sql):
        pass

    if(args.export_database_schema):
        pass
    
    if(args.testing):
        cursor.execute("DROP TABLE IF EXISTS test;")
        cursor.execute("CREATE TABLE test (id serial PRIMARY KEY, num integer, data varchar);")
        cursor.execute("INSERT INTO test (num, data) VALUES (%s, %s)", (100, "abc'def"))
        cursor.execute("INSERT INTO test (num, data) VALUES (%s, %s)", (200, "abc'def"))
        cursor.execute("INSERT INTO test (num, data) VALUES (%s, %s)", (100, "abc'def"))
        
        cursor.execute("SELECT * FROM test;")
        row = cursor.fetchone()
        while row != None:
            print(row)
            row = cursor.fetchone()
        
        cursor.execute("SELECT * FROM test where num = 100;")
        print(cursor.fetchall())

        cursor.execute("SELECT * FROM test;")
        print(cursor.fetchmany(3))

    if connection:
        cursor.close()
        connection.close()
    

        

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--name")
    parser.add_argument("--user")
    parser.add_argument("--pswd")
    parser.add_argument("--host")
    parser.add_argument("--port")
    parser.add_argument("--import-table-data", action='store_true')
    parser.add_argument("--export-table-data", action='store_true')
    parser.add_argument("--show-tables", action='store_true')
    parser.add_argument("--show-table-schema", action='store_true')
    parser.add_argument("--table")
    parser.add_argument("--format")
    parser.add_argument("--import-sql", action='store_true')
    parser.add_argument("--path")
    parser.add_argument("--export-database-schema", action='store_true')
    parser.add_argument("--testing", action = 'store_true')

    args = parser.parse_args()
    main(args)