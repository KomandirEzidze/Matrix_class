#include <iostream>


//------------------------------------------------------------------------------
// Описание класса Matrix

class Matrix
{
private:
  int rows; // количество строк
  int cols; // количество столбцов
  int** elements; // двумерный массив с элементами матрицы

public:
  Matrix(int m, int n, int** matrix);
  ~Matrix();

  inline int get_rows() const { return rows; } // Возвращает кол-во строк
  inline int get_cols() const { return cols; } // Возвращает кол-во столбцов
  inline int get_element(int i, int j) const { return elements[i][j]; }

  void show();

  Matrix operator+(const Matrix &matrix);
};

Matrix::Matrix(int m, int n, int** matrix) : rows(m), cols(n)
{
  elements = new int*[rows];
  for (int i=0;i<m;i++) {
    elements[i] = new int[cols];
    for (int j=0;j<n;j++) {
      elements[i][j] = matrix[i][j];
    }
  }
}

Matrix::~Matrix() {
  for (int i=0;i<rows;i++) {
    delete [] elements[i];
  }

  delete [] elements;
}

Matrix Matrix::operator+(const Matrix &matrix)
{
  if (rows != matrix.get_rows() || cols != matrix.get_cols()) {
    throw "Невозможно сложить матрицы разных размеров.";
  }

  int** sum_matrix = new int*[rows];
  for (int i=0;i<rows;i++) {
    sum_matrix[i] = new int[cols];
    for (int j=0;j<cols;j++) {
      sum_matrix[i][j] = elements[i][j] + matrix.get_element(i, j);
    }
  }

  return Matrix(rows, cols, sum_matrix);
}

void Matrix::show()
{
  for (int i=0;i<rows;i++) {
    std::cout << "[  ";
    for(int j=0;j<cols;j++) {
      std::cout << elements[i][j] << "  ";
    }
    std::cout << "]\n";
  }
}

//------------------------------------------------------------------------------

Matrix new_matrix()
{
  int m, n;
  std::cout << "Введите количество строк в матрице: ";
  std::cin >> m;
  std::cout << "Введите количество столбцов в матрице: ";
  std::cin >> n;

  int** matrix = new int*[m];
  std::cout << "Введите элементы матрицы:\n";
  for (int i=0;i<m;i++) {
    matrix[i] = new int[n];
    for (int j=0;j<n;j++) {
      std::cin >> matrix[i][j];
    }
  }

  return Matrix(m, n, matrix);
}

int main()
{
  Matrix matrix1 = new_matrix();
  Matrix matrix2 = new_matrix();

  Matrix matrix3 = matrix1 + matrix2;
  matrix3.show();

  return 0;
}
