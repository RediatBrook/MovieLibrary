# Movie Library
A basic movie library that efficiently browses and catalogs a given movie database. It accepts two commandline arguments that correspond
to a database file and a query file. These are text files that should be formatted similar to the dbfile1.txt and query.txt files in the
repository. 

## Running the Queries
There are two kinds of queries for a movie database in this library. The first is a query by movie name that requests
all the actors that starred in a given movie. And, the second is a query by actor name that searches for all the movies 
that an actor has taken part in. Both kinds of queries can be added as single new line entries in a text file (*.txt) 
whose name is entered as the second command line argument for the program. 
<br/><br/>
Sample query file format below:


```
Fly Boy (1999)
Snitch (1998)
Janssen, Famke
Kenny, Al
Dedicato a una stella (1976)
Boyden, Sally
Any Time, Any Play (1989)
Rimmer, Shane

```
The first command line argument is used to enter the name of the database file from which the queries are run. It should be formatted
identically to the dbfile1.txt or dbfile2.txt sample files in the repo. After both the query file and database file are in the same 
directory as the movielibrary, compile the program and run. 
<br/><br/>

Sample compilation command (Assuming you use GNU's compiler): 
```
g++ movielibrary.cpp

```
<br/>
Sample Run Command:


```
./a dbfile1.txt query.txt

```
Run Command Template: 
```
./a <db file> <query file>

```
