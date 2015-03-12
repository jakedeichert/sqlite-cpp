# ﻿SQLite3 Cheat Sheet

open database
-------------
```
sqlite3.exe game.db
```


create a table
--------------
```
CREATE TABLE players (
    username        TEXT    NOT NULL    PRIMARY KEY,
    password        TEXT    NOT NULL,
    total_kills     INT     NOT NULL
);
```

insert values
-------------
```
INSERT INTO players (username, password, total_kills, total_deaths, total_assists, logged_in)
VALUES ('username', 'password', 0, 0, 0, 'false');
```

run script in txt file
----------------------
```
.read script.txt
```


output table
------------
```
SELECT * FROM players;
```


show table info
---------------
```
pragma table_info(tableName);
```


show table create sql statement
-------------------------------
```
.schema players
```


update syntax
-------------
```
UPDATE players
SET total_kills = 4, total_deaths = 2, total_assists = 1
WHERE username='jake'
```


delete a player from the table
------------------------------
```
DELETE FROM players
WHERE username = 'jake';
```


change table settings in ~/.swliterc
------------------------------------
```
.show
.header on
.mode column
```


create a lib file from a def file
---------------------------------
```
lib /DEF:"C:\...\sqlite\sqlite3.def" /OUT:"C:\...\sqlite\sqlite3.lib"
```
