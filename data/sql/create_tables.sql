CREATE TABLE user (
	userid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	name TEXT NOT NULL
);
CREATE TABLE file (
	fileid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	filename TEXT NOT NULL,
	md5hash TEXT NOT NULL
);
CREATE TABLE gpsdata (
	gpsdataid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	location INTEGER UNSIGNED NOT NULL,
	user INTEGER UNSIGNED NOT NULL,
	latitude REAL NOT NULL,
	longitude REAL NOT NULL,
	time NUMERIC NOT NULL,
	elevation REAL NOT NULL,
	segment INTEGER UNSIGNED NOT NULL,
	file INTEGER UNSIGNED NOT NULL,
	FOREIGN KEY (user) REFERENCES user (userid),
	FOREIGN KEY (location) REFERENCES location (locationid),
	FOREIGN KEY (file) REFERENCES file (fileid),
	UNIQUE (user, latitude, longitude, time)
);
CREATE TABLE location (
	locationid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	city TEXT NOT NULL,
	country TEXT NOT NULL,
	longitude REAL,
	latitude REAL,
	radius REAL,
    radiuskm REAL,
    polygon TEXT,
    upperleftlon REAL,
    upperleftlat REAL,
    bottomrightlon REAL,
    bottomrightlat REAL,
	UNIQUE (city, country)
);
