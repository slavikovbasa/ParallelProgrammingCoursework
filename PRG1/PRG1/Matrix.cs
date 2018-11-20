using System;
using System.Text;

namespace PRG1
{
    //Matrix class. Containing all necessary methods to perform operations with matrix
    class Matrix
    {
        //Returns matrix that is a product of this and matrix2 matrices for lines from i1 to i2
        static public void Multiply(int[][] matrix, int[][] matrix2, int[][] product, int i1, int i2)
        {
            for (int i = i1; i < i2; i++)
                for (int j = 0; j < matrix.Length; j++)
                {
                    product[i][j] = 0;
                    for (int k = 0; k < matrix.Length; k++)
                        product[i][j] += matrix[i][k] * matrix2[k][j];
                }
        }

        //Returns string representation of a matrix
        static public String ToString(int[][] matrix)
        {
            StringBuilder str = new StringBuilder();
            for (int i = 0; i < matrix.Length; i++)
            {
                for (int j = 0; j < matrix[i].Length; j++)
                {
                    str.Append(matrix[i][j]).Append(" ");
                }
                str.Append("\n");
            }
            return str.ToString();
        }

        //Fills matrix with number n
        static public void Fill(int[][] matrix, int n)
        {
            for (int i = 0; i < matrix.Length; i++)
                for (int j = 0; j < matrix[i].Length; j++)
                    matrix[i][j] = n;
        }

        //Returns deep copy of a matrix
        static public int[][] GetCopy(int[][] matrix)
        {
            int[][] cpMatrix = new int[matrix.Length][];

            for (int i = 0; i < matrix.Length; i++)
                cpMatrix[i] = new int[matrix.Length];
           
            for (int i = 0; i < matrix.Length; i++)
                for (int j = 0; j < matrix.Length; j++)
                    cpMatrix[i][j] = matrix[i][j];

            return cpMatrix;
        }
    }
}
