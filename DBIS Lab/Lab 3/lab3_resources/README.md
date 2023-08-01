# Lab3 - Interfacing Python to Postgres and Metadata handling

This directory contains a set of sample inputs and outputs for this week's problem statement, detailed description below.

1. ``./ipl.ddl`` - This is a DDL file for the sample IPL database.
2. ``./csvs/`` - This directory contains appropriately named CSVs containing data for each table defined in the DDL file.
3. ``./outs/`` - This directory contains sample outputs for various parts of the problem statement.
    - Inlab part (b): File ``iB_player_sql.out`` contains output with flags``--export-table-data --table-name "player" --format "sql"``. CSV samples are same as files in ``./csvs/``.
    - Outlab part (b) : File ``oB_tables.out`` contains output with flags ``--show-tables``.
    - Outlab part (c): File ``oC_venue_schema.out`` contains output with flags ``--show-table-schema --table-name "venue"``.
    - Outlab part (d): File ``oD_dump.out`` contains output with flags ``--export-database-schema``.
