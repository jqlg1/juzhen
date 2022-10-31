/**
 * @file juzhen
 * @author QianliJia
 * StudentNumber:210320728
 * e-mail:741492060@qq.com
 * @brief 编写矩阵类，实现矩阵初始化、求逆、转置、访问等功能
 * 基于运算符重载，实现矩阵的加减乘除、输入输出的操作
 * @version 0.1
 * @date 2022-09-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <math.h>
using namespace std;
#define length 4
class Matrix_4x4
{
private:
    double matrix[length][length];
public:
    Matrix_4x4();                                   //默认构造函数，初始化矩阵为单位阵
    Matrix_4x4(double a[length][length]);           //带参数构造函数，用一个4*4的二维数组初始化
    Matrix_4x4(const Matrix_4x4 &b);                //复制构造函数
    Matrix_4x4 &operator=(const Matrix_4x4 &a);     //重载 = 运算符 ，参数为矩阵对象
    Matrix_4x4 operator=(double a[length][length]); //重载 = 运算符，参数为一个4*4的二维数组
    Matrix_4x4 operator+(Matrix_4x4 &a);
    Matrix_4x4 operator-(Matrix_4x4 &a);
    Matrix_4x4 operator*(const Matrix_4x4 &a);
    Matrix_4x4 operator^(int x);
    const double *operator[](const int i) const { return matrix[i]; }
    double *operator[](const int i) { return matrix[i]; }
    friend istream &operator>>(istream &, Matrix_4x4 &);
    friend ostream &operator<<(ostream &, Matrix_4x4 &);
    double determinant();   //矩阵求行列式
    Matrix_4x4 inverse();   //矩阵求逆，不改变当前矩阵值，返回逆矩阵
    Matrix_4x4 transpose(); //矩阵转置，不改变当前矩阵值，返回转置矩阵

    ~Matrix_4x4();
};
Matrix_4x4::Matrix_4x4()
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
        }
    }
}
Matrix_4x4::Matrix_4x4(const Matrix_4x4 &b)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            matrix[i][j] = b.matrix[i][j];
        }
    }
}
Matrix_4x4::Matrix_4x4(double a[4][4])
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            matrix[i][j] = a[i][j];
        }
    }
}
Matrix_4x4::~Matrix_4x4() {}
//重载 = 运算符 ，参数为矩阵对象
Matrix_4x4 &Matrix_4x4::operator=(const Matrix_4x4 &a)
{

    if (this != &a)
    {
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                matrix[i][j] = a.matrix[i][j];
            }
        }
    }
    return *this;
}
//重载 = 运算符，参数为一个4*4的二维数组
Matrix_4x4 Matrix_4x4::operator=(double a[length][length])
{
    Matrix_4x4 b;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            b.matrix[i][j] = a[i][j];
        }
    }
    return b;
}
Matrix_4x4 Matrix_4x4::operator+(Matrix_4x4 &a)
{
    Matrix_4x4 b;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            b.matrix[i][j] = matrix[i][j] + a.matrix[i][j];
        }
    }
    return b;
}
Matrix_4x4 Matrix_4x4::operator-(Matrix_4x4 &a)
{
    Matrix_4x4 b;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            b.matrix[i][j] = matrix[i][j] - a.matrix[i][j];
        }
    }
    return b;
}
Matrix_4x4 Matrix_4x4::operator*(const Matrix_4x4 &a)
{
    Matrix_4x4 b;
    double temp = 0;
    for (int i = 0; i < length; i++)
    {
        for (int k = 0; k < length; k++)
        {
            for (int j = 0; j < length; j++)
            {
                temp += matrix[i][j] * a.matrix[j][k];
            }
            b.matrix[i][k] = temp;
            temp = 0;
        }
    }
    return b;
}
Matrix_4x4 Matrix_4x4::operator^(int x)
{
    Matrix_4x4 b, c;
    if (x >= 1)
    {
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                b.matrix[i][j] = matrix[i][j];
                c.matrix[i][j] = matrix[i][j];
            }
        }
        for (int i = 1; i < x; i++)
        {
            b = (b * c);
        }
    }
    else if (x <= -1)
    {
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                b.matrix[i][j] = matrix[i][j];
                c.matrix[i][j] = matrix[i][j];
            }
        }
        b = c.inverse();
        c = c.inverse();
        for (int i = 1; i < fabs(x); i++)
        {
            b = (b * c);
        }
    }
    return b;
}
double Matrix_4x4 ::determinant()
{
    Matrix_4x4 t;
    int k, x = 1;
    double max;
    double output = 1;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            t[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < length; i++)
    {
        max = t[i][i];
        k = i;
        for (int j = i + 1; j < length; j++)
        {
            if (fabs(t[j][i]) > fabs(max))
            {
                max = t[j][i];
                k = j;
            }
        }
        if (k != i)
        {
            x = -x;
            double temp;
            for (int j = 0; j < length; j++)
            {
                temp = t[k][j];
                t[k][j] = t[i][j];
                t[i][j] = t[k][j];
            }
        }
        for (int j = i + 1; j < length; j++)
        {
            for (int m = 0; m < length; m++)
            {
                t[j][m] = t[j][m] - (t[j][i] / t[i][i]) * t[i][m];
            }
        }
    }
    for (int i = 0; i < length; i++)
    {
        output = t[i][i] * output * x;
    }
    return output;
}
//矩阵求逆，不改变当前矩阵值，返回逆矩阵
Matrix_4x4 Matrix_4x4::inverse()
{
    Matrix_4x4 t;
    // a's ni
    Matrix_4x4 b;
    int k = 0;
    double max = 0;
    double output = 1;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            t[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < length; i++)
    {
        max = t[i][i];
        k = i;
        for (int j = i + 1; j < length; j++)
        {
            if (fabs(t[j][i]) > fabs(max))
            {
                max = t[j][i];
                k = j;
            }
        }
        if (max == 0)
        {
            cout << "No inverse." << endl;
            // exit(0);
        }
        if (k != i)
        {
            double temp;
            for (int j = 0; j < length; j++)
            {
                temp = t[k][j];
                t[k][j] = t[i][j];
                t[i][j] = temp;

                temp = b[k][j];
                b[k][j] = b[i][j];
                b[i][j] = temp;
            }
        }
        double temp = t[i][i];
        for (int j = 0; j < length; j++)
        {
            t[i][j] = t[i][j] / temp;
            b[i][j] = b[i][j] / temp;
        }
        for (int j = 0; j < length; j++)
        {
            double temp = t[j][i] / t[i][i];
            for (int m = 0; m < length; m++)
            {
                if (j != i)
                {
                    // t[j][m] = t[j][m] - (t[j][i] / t[i][i]) * t[i][m];
                    // b[j][m] = b[j][m] - (b[j][i] / b[i][i]) * b[i][m];
                    t[j][m] = t[j][m] - temp * t[i][m];
                    b[j][m] = b[j][m] - temp * b[i][m];
                }
            }
        }
    }
    return b;
}
//矩阵转置，不改变当前矩阵值，返回转置矩阵
Matrix_4x4 Matrix_4x4::transpose()
{
    Matrix_4x4 b;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            b.matrix[i][j] = matrix[j][i];
        }
    }
    return b;
}
//  重载输入 >>
istream &operator>>(istream &input, Matrix_4x4 &a)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            input >> a.matrix[i][j];
        }
    }
    return input;
}
//重载输出<<
ostream &operator<<(ostream &output, Matrix_4x4 &a)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            output << a.matrix[i][j] << "   ";
        }
        output << "\n";
    }
    return output;
}

int main(void)
{
    // double m[length][length] = {{1,2,3,5},{6,3,2,1},{4,3,5,2},{6,1,3,8}};
    // Matrix_4x4 a;//
    // Matrix_4x4 b(a);//1
    // Matrix_4x4 c(m);//1
    // Matrix_4x4 d;
    // for (int i = 0; i < length; i++)
    // {
    //     for (int j = 0; j < length; j++)
    //     {
    //         d[i][j] = m[i][j];
    //     }
    // }//1
    // cout << "a : \n"<<a<<endl;
    // cout << "b(a) : \n"<<b<<endl;
    // cout << "c(m) : \n"<<c<<endl;
    // cout << "d : \n"<<d<<endl;

    // d = a + c ;//1
    // cout << "d = a + c :\n"<<d<<endl;
    // d = d - a ;//1
    // cout << "d = d - a  :\n"<<d<<endl;
    // d = d * d.inverse();
    // cout << "d = d * d.inverse()  :\n"<<d<<endl;
    // d = a^3;//1
    // cout << "d = a^3 :\n"<<d<<endl;
    // d = c.transpose();//1
    // cout << "d = c.transpose() :\n"<< d <<endl<< "c : \n"<< c ;
    // double m[length][length] = {{1, 2, 3, 5}, {6, 3, 2, 1}, {4, 3, 5, 2}, {6, 1, 3, 8}};
    // Matrix_4x4 c(m);
    // Matrix_4x4 d = c ^ 3;
    // cout << d << endl;
    // c = c^(-2);
    // cout << c;
    double m[length][length] = {{0,2,0,1},{3,3,2,1},{3,2,4,0},{2,2,1,1}};
    Matrix_4x4 a(m);
    a = a.inverse();
    cout << a<<endl;
}
