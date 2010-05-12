#This is a comment
DROP DATABASE patty_library;
CREATE DATABASE patty_library;
USE patty_library;
CREATE TABLE books (bookid INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	author VARCHAR(255), title VARCHAR(255), text TEXT,
	active enum("ACTIVE","INACTIVE"), creation_date DATE,
	last_modified TIMESTAMP(14) );
CREATE TABLE users (userid INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	username VARCHAR(255), password VARCHAR(255), name VARCHAR(255),
	email VARCHAR(255), hometown VARCHAR(255), active enum("ACTIVE","INACTIVE"),
	creation_date DATE, last_modified TIMESTAMP(14) );
