#include <iostream>
#include <fstream>

using namespace std;

void blockWriteFile(const char*, int, int, int);
void displayFile(const char*, int, int);
void workFile(const char* ,const char*, int, int);
void displayMatrix(int*, int, int);
//void simpleMatrix(int*, int, int);
//int sumElemMatrix(int*, int, int);
int** mapTo(int*, int, int);
int* initMatrix(int, int);
long long  actionWithMatrix(int**, int, int);

int main()
{
    blockWriteFile("test", 5, 8, 9);
    displayFile("test" ,3,4);
    workFile("test1.txt", "test", 8, 9);
    
}

void blockWriteFile(const char* fileName, int count, int row, int column) // записывает в бинарный файл count матриц с row строками и column столбцами, значения матриц рандомные
{
    ofstream fout(fileName, ios::out | ios::binary);
    if (!fout.is_open())
    {
        throw std::exception();
    }
    int size = sizeof(int) * row * column;
    int* matrix = nullptr;
    for (int i = 0; i < count; i++)
    {
        matrix = initMatrix(row, column);
        displayMatrix(matrix, row, column);
        cout << endl;
        fout.write((char*)matrix, size);
    }
    delete[] matrix;
    fout.close();
}


void displayFile(const char* filename , int row , int column)
{
    ifstream fin(filename, ios::binary);
    if (!fin.is_open())
    {
        throw std::exception();
    }
    int size = sizeof(int) * row * column;
    int* matrix = new int [row*column];
    while(fin.read((char*)matrix, size))
    {
        displayMatrix(matrix, row, column);
    }
    delete[] matrix;
    fin.close();
}

void workFile(const char* fileTextName, const char* fileBinaryName, int row, int column)
{
    ofstream fOut(fileTextName);
    ifstream fin(fileBinaryName, ios::binary);
    if (!fOut.is_open())
    {
        throw std::exception();
    }
    if (!fin.is_open())
    {
        throw std::exception();
    }
    int size = sizeof(int) * row * column;
    int* array = new int[row * column];

    while (fin.read((char*)array, size))
    {
       int** matrix = mapTo(array, row, column);
      int temp = actionWithMatrix(matrix, row, column);
      fOut.width(10);
      fOut << temp << endl;
    }
    fOut.close();
    delete[] array;
    fin.close();
}



void displayMatrix(int* matrix, int row, int column)
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            cout.width(4);
            cout << matrix[i * column + j];
        }
        cout << endl;
    }
}

int** allocateMemory(int width, int heigth)
{
    if (heigth <= 0)
    {
        throw std::out_of_range("Count of elements must be positive.");
    }
    int** matrix = new int* [heigth];
    for (size_t i = 0; i < heigth; i++)
    {
        matrix[i] = new int[width] ;
    }
    return matrix;
}

int** mapTo(int* source, int row, int column)
    {
      if (row <= 0 || column <= 0)
        {
            throw std::out_of_range("Count of elements must be positive.");
        }
        if (source == nullptr)
        {
            throw std::invalid_argument("nullptr pointer.");
        }
        int** matrix = allocateMemory(row, column);
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < column; j++)
            {
                int k = i * column + j;
                matrix[i][j] = source[k];
            }
        }
        return matrix;
    }


int* initMatrix(int row, int column)
{
    int dimension = row * column;
    int* matrix = new int[dimension];
    for (size_t i = 0; i < dimension; i++)
    {
        matrix[i] = rand() % 100;
    }
    return matrix;
}

long long actionWithMatrix(int** matrix, int row, int column)
{
    int sum = 0;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            sum += matrix[i][j];
            cout.width(5);
            cout << matrix[i][j];
        }
        
        cout << endl;
    }
    return sum;
}
