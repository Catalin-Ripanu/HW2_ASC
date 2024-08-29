/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"
#include "cblas.h"

/* Se alocă memorie în mod dinamic pentru matricele implicate în operație */

void matrix_allocation(int N, double **Matrix)
{
	*Matrix = (double *)calloc(N * N, sizeof(**Matrix));
	if (!*Matrix)
		exit(EXIT_FAILURE);
}

/*
 * Add your BLAS implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	double *C;

	/* BA_t reține rezultatul intermediar BA_t = B * A', unde A' este transpusa lui A */

	double *BA_t;

	matrix_allocation(N, &C);
	matrix_allocation(N, &BA_t);

	/* Se folosește funcția BLAS cblas_dtrmm() astfel încât BA_t = B * A' */

	cblas_dcopy(N * N, B, 1, BA_t, 1);

	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper,
				CblasTrans, CblasNonUnit, N, N, 1.0, A, N, BA_t, N);

	/* Se folosește funcția BLAS cblas_dtrmm() astfel încât BA_t = A * BA_T = A * B * A' */

	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper,
				CblasNoTrans, CblasNonUnit, N, N, 1.0, A, N, BA_t, N);

	/* Se folosește funcția BLAS cblas_dgemm() astfel încât C = B' * B' */

	cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans,
				N, N, N, 1.0, B, N, B, N, 0, C, N);

	/* Se folosește funcția BLAS cblas_dgemm() astfel încât C = BA_t + C = A * B * A' + B' * B' */

	cblas_daxpy(N * N, 1, BA_t, 1, C, 1);

	free(BA_t);
	return C;
}
