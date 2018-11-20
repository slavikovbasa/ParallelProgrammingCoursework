using System;
using System.Text;

namespace PRG1
{
    //Vector class. Containing all necessary methods to perform operations with vectors
    class Vector
    {
        //Returns vector that is a sum of this and vector2 vectors for elements from i1 to i2
        static public void Add(int[] vector, int[] vector2, int[] sum, int i1, int i2)
        {
            for (int i = i1; i < i2; i++)
                sum[i] = vector[i] + vector2[i];
        }

        //Returns a vector that is a product of this vector and matrix matrix
        static public void Multiply(int[] vector, int[][] matrix, int[] product, int i1, int i2)
        {
            for (int i = i1; i < i2; i++)
            {
                product[i] = 0;
                for (int j = 0; j < vector.Length; j++)
                    product[i] += vector[j] * matrix[i][j];
            }
        }

        //Returns a vector that is a product of this vector and number num
        static public void Multiply(int[] vector, int num, int[] res, int i1, int i2)
        {
            for (int i = i1; i < i2; i++)
                res[i] = vector[i] * num;
        }

        //Returns string representation of vector
        static public String ToString(int[] vector)
        {
            StringBuilder str = new StringBuilder();
            for (int i = 0; i < vector.Length; i++)
            {
                str.Append(vector[i]).Append(" ");
            }
            return str.ToString();
        }

        //Fills vector with number n
        static public void Fill(int[] vector, int n)
        {
            for (int i = 0; i < vector.Length; i++)
                vector[i] = n;
        }

        //Fills vector with decreasing number n
        static public void FillSequence(int[] vector)
        {
            for (int i = 0; i < vector.Length; i++)
                vector[i] = vector.Length - i;
        }

        //Returns deep copy of this vector
        static public int[] GetCopy(int[] vector)
        {
            int[] cpVector = new int[vector.Length];

            for (int i = 0; i < vector.Length; i++)
                    cpVector[i] = vector[i];

            return cpVector;
        }

        //Insertion sort
        static public void Sort(int[] vector, int i1, int i2)
        {
            for (int i = i1; i < i2 - 1; i++)
            {
                int j = i + 1;

                while (j > i1)
                {
                    if (vector[j - 1] > vector[j])
                    {
                        int temp = vector[j - 1];
                        vector[j - 1] = vector[j];
                        vector[j] = temp;

                    }
                    j--;
                }
            }
        }

        //Merge sort
        static public void Merge(int[] input, int low, int middle, int high)
        {
            int left = low;
            int right = middle + 1;
            int[] tmp = new int[(high - low) + 1];
            int tmpIndex = 0;

            while ((left <= middle) && (right <= high))
            {
                if (input[left] < input[right])
                {
                    tmp[tmpIndex] = input[left];
                    left = left + 1;
                }
                else
                {
                    tmp[tmpIndex] = input[right];
                    right = right + 1;
                }
                tmpIndex = tmpIndex + 1;
            }


            while (left <= middle)
            {
                tmp[tmpIndex] = input[left];
                left = left + 1;
                tmpIndex = tmpIndex + 1;
            }

            while (right <= high)
            {
                tmp[tmpIndex] = input[right];
                right = right + 1;
                tmpIndex = tmpIndex + 1;
            }

            for (int i = 0; i < tmp.Length; i++)
            {
                input[low + i] = tmp[i];
            }

        }
    }
}
