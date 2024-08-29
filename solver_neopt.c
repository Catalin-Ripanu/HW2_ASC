/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

/* Funcția care efectuează produsul dintre matricea 'left' și
   matricea 'right', ambele transpuse */

void matrix_tran_multiply(int N, double *left,
						  double *right, double *res)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				res[i * N + j] += left[k * N + i] * right[j * N + k];
			}
		}
	}
}

/* Funcția care efectuează suma dintre matricea 'left' și matricea 'right' */

void matrix_sum(int N, double *left,
				double *right, double *res)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			res[i * N + j] += left[i * N + j] + right[i * N + j];
		}
	}
}

/* Funcția care efectuează produsul dintre matricea 'left' și matricea 'right'
   Se ține cont de faptul că 'left' este o matrice superior triunghiulară */

void matrix_left_triangular_multiply(int N, double *left,
									 double *right, double *res)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			/* Iteratorul k pornește de la i întrucât matricea
			   'left' are 0-uri sub diagonala principală */

			for (int k = i; k < N; k++)
			{
				res[i * N + j] += left[i * N + k] *
								  right[k * N + j];
			}
		}
	}
}

/* Funcția care efectuează produsul dintre matricea 'left' și matricea 'right'
   Se ține cont de faptul că 'right' este o matrice superior triunghiulară
   De asemenea, și de faptul că 'right' se transpune */

void matrix_right_triangular_tran_multiply(int N, double *left,
										   double *right, double *res)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			/* Iteratorul k pornește de la j întrucât matricea
			   'right' are 0-uri sub diagonala principală */

			for (int k = j; k < N; k++)
			{
				res[i * N + j] += left[i * N + k] *
								  right[j * N + k];
			}
		}
	}
}

/* Se alocă memorie în mod dinamic pentru matricele implicate în operație */

void matrix_allocation(int N, double **Matrix)
{
	*Matrix = (double *)calloc(N * N, sizeof(**Matrix));
	if (!*Matrix)
		exit(EXIT_FAILURE);
}

/*
 * Add your unoptimized implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	double *C;
	double *BA_t;
	double *ABA_t;
	double *B_tB_t;

	matrix_allocation(N, &C);
	matrix_allocation(N, &BA_t);
	matrix_allocation(N, &ABA_t);
	matrix_allocation(N, &B_tB_t);

	/* Se formează produsul B * A' */

	matrix_right_triangular_tran_multiply(N, B, A, BA_t);

	/* Se formează produsul A * B * A' */

	matrix_left_triangular_multiply(N, A, BA_t, ABA_t);

	/* Se formează produsul B' * B' */

	matrix_tran_multiply(N, B, B, B_tB_t);

	/* Se formează suma A * B * A' + B' * B' */

	matrix_sum(N, ABA_t, B_tB_t, C);

	free(BA_t);
	free(ABA_t);
	free(B_tB_t);

	return C;
}
