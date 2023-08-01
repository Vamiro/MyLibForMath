#include <iostream>
#include <cmath>
#include <string>
#include <set>
#include "Matrix.h"
#include "Points.h"
#include "Vectors.h"
#include "BinaryTree.h"
#include "RBTree.h"


int main(int argc, char *argv[]) {
    if (argc == 1){
        std::cout << "-help: Options list";
    }

    std::set<std::string> options;

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);

        if (arg == "-help") {
            std::cout << "-b: BinaryTree edition\n"
                      << "-m: Matrix edition\t"
                      << "-d: with default matrix\n"
                      << "-p: Point edition\n"
                      << "-v: Vector edition\n";
        } else if (arg == "-m" || arg == "-d" || arg == "-p" || arg == "-v" || arg == "-b") {
            options.insert(arg);
        } else {
            std::cout << "unrecognized option: " << arg << std::endl;
            return 1;
        }
    }

    if(options.contains("-p")) {
        PointR2 a(1, 1);
        PointR3 b(2, 2, 2);
        a.PrintPoint();
        b.PrintPoint();
    }

    if(options.contains("-v")) {
        VectorR2 vec(PointR2(1, 1));
        vec.PrintVector();
        VectorR2 vec2(PointR2(-2, -2));
        vec2.PrintVector();
        vec += vec2;
        vec.PrintVector();
        vec2 = vec2.Normalize();
        vec2.PrintVector();
    }

    if(options.contains("-m")) {
        Matrix matrixDefault(3, 3);

        if(options.contains("-d")) {
            matrixDefault(0, 0) = 1;
            matrixDefault(0, 1) = 2;
            matrixDefault(0, 2) = 3;
            matrixDefault(1, 0) = 0;
            matrixDefault(1, 1) = 1;
            matrixDefault(1, 2) = 4;
            matrixDefault(2, 0) = 5;
            matrixDefault(2, 1) = 6;
            matrixDefault(2, 2) = 0;
        }
        else {
            for (int i = 0; i < matrixDefault.GetRows(); ++i) {
                for (int j = 0; j < matrixDefault.GetColumns(); ++j) {
                    matrixDefault(i, j) = rand() % 3;
                }
            }
        }
        Matrix matrix = matrixDefault;

        std::cout << "_______________________________________matrix created." << std::endl;
        matrix.PrintMatrix();

        Matrix matrix1(3, 3);
        for (int i = 0; i < matrix1.GetRows(); ++i) {
            for (int j = 0; j < matrix1.GetColumns(); ++j) {
                matrix1(i, j) = rand() % 3;
            }
        }
        std::cout << "_______________________________________matrix1 created." << std::endl;
        matrix1.PrintMatrix();
        std::cout << "_______________________________________Equals method" << std::endl;

        //Equals method

        bool eq = matrix.EqualMatrix(matrix1);
        std::cout << (eq ? "YES" : "NO") << std::endl;

        std::cout << "_______________________________________Sum  method" << std::endl;

        //Sum  method

        matrix.SumMatrix(matrix1);
        matrix.PrintMatrix();
        matrix = matrixDefault;

        std::cout << "_______________________________________Sub  method" << std::endl;

        //Sub  method

        matrix.SubMatrix(matrix1);
        matrix.PrintMatrix();
        matrix = matrixDefault;

        std::cout << "_______________________________________Multiply num  method" << std::endl;

        //Multiply num  method

        matrix.MultiplyNumber(2);
        matrix.PrintMatrix();
        matrix = matrixDefault;

        std::cout << "_______________________________________Multiply matrix  method" << std::endl;

        //Multiply matrix  method

        matrix.MultiplyMatrix(matrix1);
        matrix.PrintMatrix();
        matrix = matrixDefault;

        std::cout << "_______________________________________Transpose  method" << std::endl;

        //Transpose  method

        Matrix matrix2 = matrix.Transpose();
        matrix2.PrintMatrix();

        std::cout << "_______________________________________CalcComplements  method" << std::endl;

        //CalcComplements  method

        matrix2 = matrix.CalcComplements();
        matrix2.PrintMatrix();

        std::cout << "_______________________________________Determinant  method" << std::endl;

        //Determinant  method

        double det = matrix.Determinant();
        std::cout << det << std::endl;

        std::cout << "_______________________________________Inverse  method" << std::endl;

        //Inverse  method

        matrix2 = matrix.InverseMatrix();
        matrix2.PrintMatrix();

        std::cout << "_______________________________________operator +" << std::endl;

        //operator +

        matrix2 = matrix + matrix1;
        matrix2.PrintMatrix();

        std::cout << "_______________________________________operator -" << std::endl;

        //operator -

        matrix2 = matrix - matrix1;
        matrix2.PrintMatrix();

        std::cout << "_______________________________________operator * num" << std::endl;

        //operator * num

        matrix2 = matrix * 2;
        matrix2.PrintMatrix();

        std::cout << "_______________________________________operator * matrix" << std::endl;

        //operator * matrix

        matrix2 = matrix * matrix1;
        matrix2.PrintMatrix();

        std::cout << "_______________________________________operator ==" << std::endl;

        //operator ==

        std::cout << (matrix == matrix1 ? "YES" : "NO") << std::endl;

        std::cout << "_______________________________________operator =" << std::endl;

        //operator =

        matrix2 = matrix;
        matrix2.PrintMatrix();

        std::cout << "_______________________________________operator +=" << std::endl;

        //operator +=

        matrix += matrix1;
        matrix.PrintMatrix();
        matrix = matrixDefault;

        std::cout << "_______________________________________operator -=" << std::endl;

        //operator -=

        matrix -= matrix1;
        matrix.PrintMatrix();
        matrix = matrixDefault;

        std::cout << "_______________________________________operator *= num" << std::endl;

        //operator *= num

        matrix *= 2;
        matrix.PrintMatrix();
        matrix = matrixDefault;

        std::cout << "_______________________________________operator *= matrix" << std::endl;

        //operator *= matrix

        matrix *= matrix1;
        matrix.PrintMatrix();
        matrix = matrixDefault;

        std::cout << "_______________________________________set rows" << std::endl;

        //set rows

        matrix.SetRows(2);
        matrix.PrintMatrix();

        std::cout << "_______________________________________set columns" << std::endl;

        //set columns

        matrix.SetColumns(2);
        matrix.PrintMatrix();
    }

    if(options.contains("-b")){

        RBTree<int, int> tree;

        for (int i = 0; i <= 21; ++i) {
            tree.Insert(i, i);
        }

        // Print the tree using breadth-first traversal
        std::cout << "Breadth-First Traversal:" << std::endl;
        tree.PrintTree();
        std::cout << std::endl;

        // Search for a key in the tree
        int keyToSearch = 4;
        int *result = tree.Search(keyToSearch);
        if (result) {
            std::cout << "Value for key " << keyToSearch << ": " << *result << std::endl;
        } else {
            std::cout << "Key " << keyToSearch << " not found in the tree." << std::endl;
        }
    }

    return 0;
}


