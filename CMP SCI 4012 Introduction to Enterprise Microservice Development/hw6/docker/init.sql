CREATE TABLE IF NOT EXISTS student
(
    id SERIAL NOT NULL PRIMARY KEY,
    name VARCHAR(50),
    major VARCHAR(50),
    year INT
);

CREATE TABLE IF NOT EXISTS course
(
    id SERIAL NOT NULL PRIMARY KEY,
    name VARCHAR(50),
    number VARCHAR(50),
    capacity INT
);