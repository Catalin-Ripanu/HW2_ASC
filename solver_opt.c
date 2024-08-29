/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

/* Funcția care efectuează suma dintre matricea 'left' și matricea 'right' */

void matrix_sum(register int N, double *left,
				double *right)
{
	register double result;
	for (register int i = 0; i != N; ++i)
	{
		register double *C_ptr = left + i * N;
		register double *B_t_left_copy = right + i;
		for (register int j = 0; j != N; ++j, ++C_ptr)
		{
			result = 0.0;
			register double *B_t_ptr = B_t_left_copy;

			register double *B_ptr = right + j * N;

			for (register int k = 0; k != N; k++)
			{
				result += *B_t_ptr * *B_ptr;
				B_t_ptr += N;
				B_ptr++;
			}

			*C_ptr += result;
		}
	}
}

/* Funcția care efectuează produsul dintre matricea 'left' și matricea 'right'
   Se ține cont de faptul că 'left' este o matrice superior triunghiulară */

void matrix_left_triangular_multiply(const register int N, double *left,
									 double *right)
{
	register double result;
	for (register int i = 0; i != N; ++i)
	{
		register double *ABA_t_ptr = right + i * N;
		register double *A_copy = left + i * N;
		for (register int j = 0; j != N; ++j, ++ABA_t_ptr)
		{
			result = 0.0;
			register double *A_ptr = A_copy + i;

			register double *BA_ptr = right + j + i * N;

			for (register int k = i; k != N; k++)
			{
				result += *A_ptr * *BA_ptr;
				BA_ptr += N;
				A_ptr++;
			}

			*ABA_t_ptr = result;
		}
	}
}

/* Funcția care efectuează produsul dintre matricea 'left' și matricea 'right'
   Se ține cont de faptul că 'right' este o matrice superior triunghiulară
   De asemenea, și de faptul că 'right' se transpune */

void matrix_right_triangular_tran_multiply(const register int N, double *left,
										   double *right, double *res)
{
	register double result;
	for (register int i = 0; i != N; ++i)
	{
		register double *BA_t_ptr = res + i * N;
		register double *B_copy = left + i * N;
		for (register int j = 0; j != N; ++j, ++BA_t_ptr)
		{
			result = 0.0;
			register double *A_t_ptr = right + N * j + j;

			register double *B_ptr = B_copy + j;

			for (register int k = j; k != N; k++)
			{
				result += *A_t_ptr * *B_ptr;
				B_ptr++;
				A_t_ptr++;
			}

			*BA_t_ptr = result;
		}
	}
}

/* Se alocă memorie în mod dinamic pentru matricele implicate în operație */

void matrix_allocation(const register int N, double **Matrix)
{
	register int size = N * N * sizeof(**Matrix);
	*Matrix = (double *)malloc(size);
	if (!*Matrix)
		exit(EXIT_FAILURE);
}

/*
 * Add your optimized implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	double *C;

	matrix_allocation(N, &C);

	/* Se formează produsul B * A' */

	matrix_right_triangular_tran_multiply(N, B, A, C);

	/* Se formează produsul A * B * A' */

	matrix_left_triangular_multiply(N, A, C);

	/* Se formează suma A * B * A' + B' * B' */

	matrix_sum(N, C, B);

	return C;
}
