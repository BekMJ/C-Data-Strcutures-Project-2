// Spring 2023
// Data Structures
// Project 2
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>

using namespace std;
// Exception class
class Exception {

    public:
        Exception(const string& msg) : msg_(msg) {}
        ~Exception() {}

        string getMessage() const {
            return(msg_);
        }
    private:
        string msg_;
    };
// if the string is not able to be convertede into numerical values, throw this
    void I() {
        throw(Exception("not numeric data type"));
// if there is no such record/name in the table, throw this
    }
    void F() {
        throw(Exception("Record not found"));
    }



class tableClass {
protected:
    string** myTable; // 2D string array to store all values (strings and numbers)
    string* DTarray; // 1D array to store the data types of each column
    string* rowArr; //1d array to store each lines as a string (further used for sorting the table)
    int noRows, noCols; // number of rows and columns

public:
//Constructors
    tableClass();
    tableClass(int rows, int cols){
        noRows = rows;
        noCols = cols;
        myTable = new string*[rows];
        for(int i =0; i < rows; i++)
        {
            myTable[i] = new string [cols];
        }


    };

// Overload the [] operator to access a row in myTable
    string* operator[](int i) {

        string array[noCols] ;
        for(int a =0; a < noCols; a++)
        {
            array[a] = myTable[i][a];
        }
        return array;
    };

//File reading Method
    void readCSV(string filename){
        ifstream myfile;
        // it wasnt reading the file, therefore I added the directory path to the file "C:\\Users\\askub\\CLionProjects\\project2\\", but I had to delete it when submitting it
        string fullfilename = "C:\\Users\\askub\\CLionProjects\\project2\\" + filename;
        rowArr = new string [noRows]; // first read the file as a 1d array to store the rows as a line in it
        myfile.open(fullfilename);
        string line; // each lines in the csv file
        // initializing the 2d array


        if(myfile.is_open())
            for(int i =0; i < noRows; i++)
            {
                getline(myfile, line); // first read the file line by line and seperate the line using string stream later
                rowArr[i] = line;
                stringstream input(line);

                for(int j = 0; j < noCols; j++)
                {
                    getline(input, myTable[i][j], ',');
                }

            }
        else
            cout << "cant open file"<<endl; // to check whether the file was opening or not


    };

//Fill DTarray
    void dataTypeArray(string* array, int size){
        DTarray = new string [size];
        for(int i = 0; i < size; i++){
            DTarray[i] = array[i];
        }
    };
//Output Method
    void display()
    {
        for (int i =0; i < noCols; i++)
            cout << DTarray[i] << " ";
        cout << endl;
        for(int i = 0; i < noRows; i++)
        {
            for(int j = 0; j < noCols; j++)
            {
                cout << myTable[i][j] << "\t";
            }
            cout << endl;
        }
    };

//Sort the table
    void sortTable()
    {
        string temp;
        int i, j, a;
        for(i =1; i < noRows; i++)
        {
            temp = rowArr[i];
            j= i -1;

            while(j >= 0 && (rowArr[j].compare(temp) >0))
            {
                rowArr[j+1] = rowArr[j];
                j--;
            }
            rowArr[j+1] =temp;
        }

        for(int i =0; i < noRows; i++)
        {

            stringstream input(rowArr[i]);

            for(int j = 0; j < noCols; j++)
            {
                getline(input, myTable[i][j], ',');
            }

        }


    };

    //Search record
    string* searchRecord(string str)
    {
        int count = 0; //increment this if found record
        string* row = new string [noCols];
        for(int i =0; i < noRows; i++){
            if(myTable[i][0] == str)
            {
                count++;
                for(int j =0; j < noCols; j++){
                    row[j] = myTable[i][j];
                }
            }
        }
        try {
            if (count==0){
                F();
            }
            else {
                cout<<"Record found: " << endl << "\t";
                for(int i =0; i <noCols; i++){
                    cout << row[i] << "\t";
                }
                cout<<endl;
            }

        }
        catch(Exception& e) {
            cout << e.getMessage() << endl; // throws out the message Record not found
        }



        return row;
    }; // str will be from the first column


//Search value from table
    void searchValue(string str)
    {
        cout << "Searching for " << str << endl;

        int count =0; // increment this if found the value, if the value not found count stays zero
        for(int i =0; i < noRows; i++){
            for(int j =0; j < noCols; j++)
            {
                if(myTable[i][j] == str)
                {
                    count++;
                    cout<< " found in (" << i << ", " << j << ")" << endl;
                }


            }
        }
        if (count == 0)
            cout<< "Value not found" << endl;
    };

// returns the number of rows
    int getNumberRows()
    {
        return noRows;
    };
// returns the number of columns
    int getNumberCols()
    {
        return noCols;
    };


// returns a tableClass with a set of columns from colLeft to colRight indices
    tableClass* getColumns(int colLeft, int colRight)
    {
        int num = colRight - colLeft;
        tableClass* t = new tableClass(noRows, num);
        t->dataTypeArray(DTarray, num); // initializes the t tableclass's table and DTarray


        for (int i =colLeft; i < colRight; i++)
            cout << DTarray[i] << " ";
        cout << endl;
        for(int i = 0; i < noRows; i++)
        {
            for(int j = colLeft; j < colRight; j++)
            {

                cout << myTable[i][j] << "\t";
            }
            cout << endl;
        }
        // prints out the values of the table in the tableclass
        return t;


    };
// returns a tableClass with a set of rows from rowTop to rowBottom indices
    tableClass* getRows(int rowTop, int rowBottom)
    {
        tableClass* t = new tableClass(rowBottom - rowTop, noCols);
        t->dataTypeArray(DTarray, noCols);

        for (int i =0; i < noCols; i++)
            cout << DTarray[i] << " ";
        cout << endl;
        for(int i = rowTop; i < rowBottom; i++)
        {
            for(int j = 0; j < noCols; j++)
            {
                cout << myTable[i][j] << "\t";
            }
            cout << endl;
        }
        return t;
    };
    tableClass* getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom)
    {
        tableClass* t = new tableClass(rowBottom-rowTop, colRight - colLeft);
        t->dataTypeArray(DTarray, colRight - colLeft);

        for (int i =colLeft; i < colRight; i++)
            cout << DTarray[i] << " ";
        cout << endl;
        for(int i = rowTop; i < rowBottom; i++)
        {
            for(int j = colLeft; j < colRight; j++)
            {
                cout << myTable[i][j] << "\t";
            }
            cout << endl;
        }
        return t;
    }; // returns a tableClass with the data between the cols and rows given
//Find info of a given column
    void findMin(int colNumber){
        if (colNumber > (noCols - 1) || colNumber < 0)  {
            cout << "Column number " << colNumber << " out of bounds" << endl;
            // prints when the column number out of bounds
            return;
        }
        try {
            if (DTarray[colNumber] == "string" || DTarray[colNumber] == "char"){
                I(); //exception when the column is not of a numerical data type
            }
            else if(DTarray[colNumber] == "int" && (colNumber == 3 || colNumber == 4))
            {
                int num;
                int min = stoi(myTable[0][colNumber]);
                for(int i =1; i < noRows; i++)
                {
                    num = stoi(myTable[i][colNumber]);
                    if(num < min)
                        min = num;
                }
                cout << "Min of " << colNumber << " is " << min << endl;
            }

            else if (DTarray[colNumber] == "float")
            {
                float num;
                float min = stof(myTable[0][colNumber]);
                for(int i =1; i < noRows; i++)
                {
                    num = stof(myTable[i][colNumber]);
                    if(num < min)
                        min = num;
                }
                cout << "Min of " << colNumber << " is " << min << endl;
            }


        }
        catch(Exception& e) {
            cout  << e.getMessage() << endl;
            // catches the exception and prints out the message
        }

    }; // returns the min of the given column
//Destructor
    ~tableClass();
};

int main()
{
    int numRows, numCols;
    string fileName;
    char option;
    cin >> numRows >> numCols >> fileName;
    cout << "NumRows: " << numRows << endl;
    cout << "NumCols: " << numCols << endl;
    cout << "FileName: " << fileName << endl;
    tableClass* d = new tableClass(numRows, numCols);
    // TODO: read the file input name and call readCSV()
    d->readCSV(fileName); // reading file


    // TODO: read the data types and store in DTarray of d
    string* array = new string[numCols];
    string datatype;
    for(int i=0; i <numCols; i++){ // initializing the array with data types read from the file
        cin >> datatype;
        array[i] = datatype;
    }

    d->dataTypeArray(array, numCols); // created my own method to initialize DTarray
    d->sortTable();


    string p; // it will read the characters from the file
    // TODO: start reading the options till the end of the file


    while(cin >> p){ // i did a while loop because the input sizes were different


        if (p == "F")
        {
            string f;
            cin >> f;
            d->searchRecord(f);
        }
        else if (p == "V")
        {
            string v;
            cin >> v;
            d->searchValue(v);
        }
        else if (p == "D"){
            d->display();
        }
        else if (p == "I"){
            int i;
            cin >> i;
            d->findMin(i);
        }
        else if ( p == "C"){
            int a,b;
            cin >> a >> b;
            d->getColumns(a, b);
        }
        else if (p == "R"){
            int a,b;
            cin >> a >> b;
            d->getRows(a,b);
        }
        else if (p == "S"){
            int a,b,c,e;
            cin >> a >> b >> c >> e;
            d->getRowsCols(a, b, c, e);
        }
    }
    return 0;
}