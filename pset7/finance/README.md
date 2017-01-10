# C$50 - Finance
A paper trading app built as a solution to [problem set 7](http://docs.cs50.net/problems/finance/finance.html).
Built in the [CS50 online IDE](https://cs50.io)

## Technologies Used

* Flask - Python Micro Framework
* SQL
* Jinja templating language

## Database Schema (Implemented in using phpMyAdmin)

CREATE TABLE 'users' ('id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'username' TEXT NOT NULL, 'hash' TEXT NOT NULL, 'cash' NUMERIC NOT NULL DEFAULT 10000.00 )

CREATE TABLE 'transaction' ('transaction_id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'id' INTEGER, 'symbol' TEXT, 'volume'
INTEGER, 'share_price' NUMERIC, 'dtstamp' TEXT)

CREATE TABLE 'portfolio' ('id' INTEGER NOT NULL, 'symbol' TEXT NOT NULL,'num_shares' INTEGER NOT NULL DEFAULT 0 , PRIMARY KEY ('id', 'symbol'))
