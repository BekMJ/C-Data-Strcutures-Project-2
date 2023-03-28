# C-Data-Strcutures-Project-2
In this project you will implement the tableClass class along with the all the methods that are
given in the class definition (boilerplate_project2.cpp). You are required to read a csv file, do
operations on the data stored and display the queried contents from the tableClass. TableClass is
a table of data (all stored as strings) with rows and columns.
To perform operations on the data, there is something that we would need to discuss about. You
can see in the class given that we are going to be storing the data (categorical and numeric) as
strings. So, before we calculate the min of a given column, we need to check if that is a column
whose values are in fact of a numeric data type for which we can calculate the requested statistic.
And if it is a column of numbers for which we can calculate each of the requested statistic, we
would have to convert the string to a numeric data type as and when we are using the value as a
number for calculation purposes. This is referred to as late binding when we convert the stored
data to a desired data type as and when required. The data types of each of the columns are also
given in the
If asked to calculate min for a column that is not of a numeric data type, an exception is to be
thrown. You are required to write an exception class and a set of exceptions for any and each of
these cases. Please refer to the book for examples on exception throwing.
