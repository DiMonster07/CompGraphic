#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;


const int size_sys = 4;
float matrix[size_sys][size_sys] =
{
 {5.97, 3.33, -0.7, -7.38},
 {1.92, 4.54, -3.55, -0.01},
 {-2.57, -1.59, 5.84, -5.75},
 {-9.91, -5.66, -5.57, -1.24}
};

float vec_b[size_sys] = {98.7, 87.5, 86.2, 73.6};//1, 8, 5};
float vec_w[size_sys]{0};
float res_t[size_sys]{0};


void create_vec_w (float b, float u, int a);
void change_matrix ();
float get_b (int a);
float get_u (float b, int a);
float get_sum (int a);
void print_matrix();
void print_result();
float get_sum_res(int a);

int main()
{
	print_matrix();
	cout << endl;
    for (int i = 0; i < size_sys - 1; i++)
    {
        float b = get_b(i);
        float u = get_u(b, i);
        create_vec_w(b, u, i);
        change_matrix();
        print_matrix();
        cout << endl;
    }
    print_result();
    return 0;
}

void print_matrix()
{
    for (int i = 0; i < size_sys; i++)
    {
        for (int j = 0; j < size_sys; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void change_matrix ()
{
    float wwt [size_sys][size_sys]{0};
    for (int i = 0; i < size_sys; i++)
    {
        for (int j = 0; j < size_sys; j++)
        {
            wwt[i][j] = 2 * vec_w[i] * vec_w[j];
            if (i == j) wwt[i][j] = 1 - wwt[i][j];
            else wwt[i][j] = -wwt[i][j];
        }
    }
    float** temp = (float**)malloc(size_sys*sizeof(float*));
    for (int i = 0; i < size_sys; i++)
    {
        temp[i] = (float*)malloc(size_sys*sizeof(float));
        for (int j = 0; j < size_sys; j++)
        {
            float res = 0;
            for (int k = 0; k < size_sys; k++)
            {
                res += float(wwt[i][k] * matrix[k][j]);
            }
            temp[i][j] = round(res*1000)/1000;
        }
    }
    float vec_t[size_sys]{0};
    for (int i = 0; i < size_sys; i++)
    {
    	float res = 0;
    	for (int j = 0; j < size_sys; j++)
    	{
    		res += wwt[j][i]*vec_b[j];
    	}
    	vec_t[i] = round(res*1000)/1000;
    }
    for (int j = 0; j < size_sys; j++)
    {
    	vec_b[j] = vec_t[j];
        for (int k = 0; k < size_sys; k++)
        {
            matrix[j][k] = temp[j][k];
        }
    }
}

void create_vec_w (float b, float u, int a)
{
    for (int i = 0; i < size_sys; i++)
    {
        if (i < a)  vec_w[i] = 0;
        else if (i == a) vec_w[i] = u * (matrix[i][i] - b);
        else vec_w[i] = u * matrix[i][a];
    }
}

float get_b (int a)
{
	float b = float((-matrix[a][a])*sqrt(get_sum(a))/matrix[a][a]);
    return b;
}

float get_u (float b, int a)
{
    return float(1/sqrt(2*b*b - 2*b*matrix[a][a]));
}

float get_sum (int a)
{
    float res = 0;
    for (int i = a; i < size_sys; i++)
    {
        res += float(matrix[i][a] * matrix[i][a]);
    }
    return res;
}

float get_sum_res(int a)
{
	float temp = 0;
	for (int i = size_sys - 1; i > a; i--)
	{
		temp += float(matrix[a][i]*res_t[i]);
	}
	return temp;
}

void print_result()
{
	res_t[size_sys - 1] = vec_b[size_sys - 1]/matrix[size_sys - 1][size_sys - 1];
	res_t[size_sys - 1] = round(res_t[size_sys - 1]*1000)/1000;
	cout << "RES: \n" << res_t[size_sys - 1] << endl;
	for (int i = size_sys - 2; i >= 0; i--)
	{
		res_t[i] = float((vec_b[i] - get_sum_res(i))/(matrix[i][i]));
		res_t[i] = round(res_t[i]*1000)/1000;
		cout << res_t[i] << endl;
	}
}
