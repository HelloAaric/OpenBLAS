#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <complex.h>
#ifdef complex
#undef complex
#endif
#ifdef I
#undef I
#endif

#if defined(_WIN64)
typedef long long BLASLONG;
typedef unsigned long long BLASULONG;
#else
typedef long BLASLONG;
typedef unsigned long BLASULONG;
#endif

#ifdef LAPACK_ILP64
typedef BLASLONG blasint;
#if defined(_WIN64)
#define blasabs(x) llabs(x)
#else
#define blasabs(x) labs(x)
#endif
#else
typedef int blasint;
#define blasabs(x) abs(x)
#endif

typedef blasint integer;

typedef unsigned int uinteger;
typedef char *address;
typedef short int shortint;
typedef float real;
typedef double doublereal;
typedef struct { real r, i; } complex;
typedef struct { doublereal r, i; } doublecomplex;
#ifdef _MSC_VER
static inline _Fcomplex Cf(complex *z) {_Fcomplex zz={z->r , z->i}; return zz;}
static inline _Dcomplex Cd(doublecomplex *z) {_Dcomplex zz={z->r , z->i};return zz;}
static inline _Fcomplex * _pCf(complex *z) {return (_Fcomplex*)z;}
static inline _Dcomplex * _pCd(doublecomplex *z) {return (_Dcomplex*)z;}
#else
static inline _Complex float Cf(complex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex double Cd(doublecomplex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex float * _pCf(complex *z) {return (_Complex float*)z;}
static inline _Complex double * _pCd(doublecomplex *z) {return (_Complex double*)z;}
#endif
#define pCf(z) (*_pCf(z))
#define pCd(z) (*_pCd(z))
typedef int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char integer1;

#define TRUE_ (1)
#define FALSE_ (0)

/* Extern is for use with -E */
#ifndef Extern
#define Extern extern
#endif

/* I/O stuff */

typedef int flag;
typedef int ftnlen;
typedef int ftnint;

/*external read, write*/
typedef struct
{	flag cierr;
	ftnint ciunit;
	flag ciend;
	char *cifmt;
	ftnint cirec;
} cilist;

/*internal read, write*/
typedef struct
{	flag icierr;
	char *iciunit;
	flag iciend;
	char *icifmt;
	ftnint icirlen;
	ftnint icirnum;
} icilist;

/*open*/
typedef struct
{	flag oerr;
	ftnint ounit;
	char *ofnm;
	ftnlen ofnmlen;
	char *osta;
	char *oacc;
	char *ofm;
	ftnint orl;
	char *oblnk;
} olist;

/*close*/
typedef struct
{	flag cerr;
	ftnint cunit;
	char *csta;
} cllist;

/*rewind, backspace, endfile*/
typedef struct
{	flag aerr;
	ftnint aunit;
} alist;

/* inquire */
typedef struct
{	flag inerr;
	ftnint inunit;
	char *infile;
	ftnlen infilen;
	ftnint	*inex;	/*parameters in standard's order*/
	ftnint	*inopen;
	ftnint	*innum;
	ftnint	*innamed;
	char	*inname;
	ftnlen	innamlen;
	char	*inacc;
	ftnlen	inacclen;
	char	*inseq;
	ftnlen	inseqlen;
	char 	*indir;
	ftnlen	indirlen;
	char	*infmt;
	ftnlen	infmtlen;
	char	*inform;
	ftnint	informlen;
	char	*inunf;
	ftnlen	inunflen;
	ftnint	*inrecl;
	ftnint	*innrec;
	char	*inblank;
	ftnlen	inblanklen;
} inlist;

#define VOID void

union Multitype {	/* for multiple entry points */
	integer1 g;
	shortint h;
	integer i;
	/* longint j; */
	real r;
	doublereal d;
	complex c;
	doublecomplex z;
	};

typedef union Multitype Multitype;

struct Vardesc {	/* for Namelist */
	char *name;
	char *addr;
	ftnlen *dims;
	int  type;
	};
typedef struct Vardesc Vardesc;

struct Namelist {
	char *name;
	Vardesc **vars;
	int nvars;
	};
typedef struct Namelist Namelist;

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define dabs(x) (fabs(x))
#define f2cmin(a,b) ((a) <= (b) ? (a) : (b))
#define f2cmax(a,b) ((a) >= (b) ? (a) : (b))
#define dmin(a,b) (f2cmin(a,b))
#define dmax(a,b) (f2cmax(a,b))
#define bit_test(a,b)	((a) >> (b) & 1)
#define bit_clear(a,b)	((a) & ~((uinteger)1 << (b)))
#define bit_set(a,b)	((a) |  ((uinteger)1 << (b)))

#define abort_() { sig_die("Fortran abort routine called", 1); }
#define c_abs(z) (cabsf(Cf(z)))
#define c_cos(R,Z) { pCf(R)=ccos(Cf(Z)); }
#ifdef _MSC_VER
#define c_div(c, a, b) {Cf(c)._Val[0] = (Cf(a)._Val[0]/Cf(b)._Val[0]); Cf(c)._Val[1]=(Cf(a)._Val[1]/Cf(b)._Val[1]);}
#define z_div(c, a, b) {Cd(c)._Val[0] = (Cd(a)._Val[0]/Cd(b)._Val[0]); Cd(c)._Val[1]=(Cd(a)._Val[1]/Cd(b)._Val[1]);}
#else
#define c_div(c, a, b) {pCf(c) = Cf(a)/Cf(b);}
#define z_div(c, a, b) {pCd(c) = Cd(a)/Cd(b);}
#endif
#define c_exp(R, Z) {pCf(R) = cexpf(Cf(Z));}
#define c_log(R, Z) {pCf(R) = clogf(Cf(Z));}
#define c_sin(R, Z) {pCf(R) = csinf(Cf(Z));}
//#define c_sqrt(R, Z) {*(R) = csqrtf(Cf(Z));}
#define c_sqrt(R, Z) {pCf(R) = csqrtf(Cf(Z));}
#define d_abs(x) (fabs(*(x)))
#define d_acos(x) (acos(*(x)))
#define d_asin(x) (asin(*(x)))
#define d_atan(x) (atan(*(x)))
#define d_atn2(x, y) (atan2(*(x),*(y)))
#define d_cnjg(R, Z) { pCd(R) = conj(Cd(Z)); }
#define r_cnjg(R, Z) { pCf(R) = conjf(Cf(Z)); }
#define d_cos(x) (cos(*(x)))
#define d_cosh(x) (cosh(*(x)))
#define d_dim(__a, __b) ( *(__a) > *(__b) ? *(__a) - *(__b) : 0.0 )
#define d_exp(x) (exp(*(x)))
#define d_imag(z) (cimag(Cd(z)))
#define r_imag(z) (cimagf(Cf(z)))
#define d_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define r_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define d_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define r_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define d_log(x) (log(*(x)))
#define d_mod(x, y) (fmod(*(x), *(y)))
#define u_nint(__x) ((__x)>=0 ? floor((__x) + .5) : -floor(.5 - (__x)))
#define d_nint(x) u_nint(*(x))
#define u_sign(__a,__b) ((__b) >= 0 ? ((__a) >= 0 ? (__a) : -(__a)) : -((__a) >= 0 ? (__a) : -(__a)))
#define d_sign(a,b) u_sign(*(a),*(b))
#define r_sign(a,b) u_sign(*(a),*(b))
#define d_sin(x) (sin(*(x)))
#define d_sinh(x) (sinh(*(x)))
#define d_sqrt(x) (sqrt(*(x)))
#define d_tan(x) (tan(*(x)))
#define d_tanh(x) (tanh(*(x)))
#define i_abs(x) abs(*(x))
#define i_dnnt(x) ((integer)u_nint(*(x)))
#define i_len(s, n) (n)
#define i_nint(x) ((integer)u_nint(*(x)))
#define i_sign(a,b) ((integer)u_sign((integer)*(a),(integer)*(b)))
#define pow_dd(ap, bp) ( pow(*(ap), *(bp)))
#define pow_si(B,E) spow_ui(*(B),*(E))
#define pow_ri(B,E) spow_ui(*(B),*(E))
#define pow_di(B,E) dpow_ui(*(B),*(E))
#define pow_zi(p, a, b) {pCd(p) = zpow_ui(Cd(a), *(b));}
#define pow_ci(p, a, b) {pCf(p) = cpow_ui(Cf(a), *(b));}
#define pow_zz(R,A,B) {pCd(R) = cpow(Cd(A),*(B));}
#define s_cat(lpp, rpp, rnp, np, llp) { 	ftnlen i, nc, ll; char *f__rp, *lp; 	ll = (llp); lp = (lpp); 	for(i=0; i < (int)*(np); ++i) {         	nc = ll; 	        if((rnp)[i] < nc) nc = (rnp)[i]; 	        ll -= nc;         	f__rp = (rpp)[i]; 	        while(--nc >= 0) *lp++ = *(f__rp)++;         } 	while(--ll >= 0) *lp++ = ' '; }
#define s_cmp(a,b,c,d) ((integer)strncmp((a),(b),f2cmin((c),(d))))
#define s_copy(A,B,C,D) { int __i,__m; for (__i=0, __m=f2cmin((C),(D)); __i<__m && (B)[__i] != 0; ++__i) (A)[__i] = (B)[__i]; }
#define sig_die(s, kill) { exit(1); }
#define s_stop(s, n) {exit(0);}
#define z_abs(z) (cabs(Cd(z)))
#define z_exp(R, Z) {pCd(R) = cexp(Cd(Z));}
#define z_sqrt(R, Z) {pCd(R) = csqrt(Cd(Z));}
#define myexit_() break;
#define mycycle_() continue;
#define myceiling_(w) {ceil(w)}
#define myhuge_(w) {HUGE_VAL}
//#define mymaxloc_(w,s,e,n) {if (sizeof(*(w)) == sizeof(double)) dmaxloc_((w),*(s),*(e),n); else dmaxloc_((w),*(s),*(e),n);}
#define mymaxloc_(w,s,e,n) dmaxloc_(w,*(s),*(e),n)

/* procedure parameter types for -A and -C++ */

#define F2C_proc_par_types 1
#ifdef __cplusplus
typedef logical (*L_fp)(...);
#else
typedef logical (*L_fp)();
#endif
#if 0
static float spow_ui(float x, integer n) {
	float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static double dpow_ui(double x, integer n) {
	double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
#ifdef _MSC_VER
static _Fcomplex cpow_ui(complex x, integer n) {
	complex pow={1.0,0.0}; unsigned long int u;
		if(n != 0) {
		if(n < 0) n = -n, x.r = 1/x.r, x.i=1/x.i;
		for(u = n; ; ) {
			if(u & 01) pow.r *= x.r, pow.i *= x.i;
			if(u >>= 1) x.r *= x.r, x.i *= x.i;
			else break;
		}
	}
	_Fcomplex p={pow.r, pow.i};
	return p;
}
#else
static _Complex float cpow_ui(_Complex float x, integer n) {
	_Complex float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
#endif
#ifdef _MSC_VER
static _Dcomplex zpow_ui(_Dcomplex x, integer n) {
	_Dcomplex pow={1.0,0.0}; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x._Val[0] = 1/x._Val[0], x._Val[1] =1/x._Val[1];
		for(u = n; ; ) {
			if(u & 01) pow._Val[0] *= x._Val[0], pow._Val[1] *= x._Val[1];
			if(u >>= 1) x._Val[0] *= x._Val[0], x._Val[1] *= x._Val[1];
			else break;
		}
	}
	_Dcomplex p = {pow._Val[0], pow._Val[1]};
	return p;
}
#else
static _Complex double zpow_ui(_Complex double x, integer n) {
	_Complex double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
#endif
static integer pow_ii(integer x, integer n) {
	integer pow; unsigned long int u;
	if (n <= 0) {
		if (n == 0 || x == 1) pow = 1;
		else if (x != -1) pow = x == 0 ? 1/x : 0;
		else n = -n;
	}
	if ((n > 0) || !(n == 0 || x == 1 || x != -1)) {
		u = n;
		for(pow = 1; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static integer dmaxloc_(double *w, integer s, integer e, integer *n)
{
	double m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
static integer smaxloc_(float *w, integer s, integer e, integer *n)
{
	float m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
#endif
static inline void cdotc_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Fcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conjf(Cf(&x[i]))._Val[0] * Cf(&y[i])._Val[0];
			zdotc._Val[1] += conjf(Cf(&x[i]))._Val[1] * Cf(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conjf(Cf(&x[i*incx]))._Val[0] * Cf(&y[i*incy])._Val[0];
			zdotc._Val[1] += conjf(Cf(&x[i*incx]))._Val[1] * Cf(&y[i*incy])._Val[1];
		}
	}
	pCf(z) = zdotc;
}
#else
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i])) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i*incx])) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
#endif
static inline void zdotc_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Dcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conj(Cd(&x[i]))._Val[0] * Cd(&y[i])._Val[0];
			zdotc._Val[1] += conj(Cd(&x[i]))._Val[1] * Cd(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conj(Cd(&x[i*incx]))._Val[0] * Cd(&y[i*incy])._Val[0];
			zdotc._Val[1] += conj(Cd(&x[i*incx]))._Val[1] * Cd(&y[i*incy])._Val[1];
		}
	}
	pCd(z) = zdotc;
}
#else
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i])) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i*incx])) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}
#endif	
static inline void cdotu_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Fcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cf(&x[i])._Val[0] * Cf(&y[i])._Val[0];
			zdotc._Val[1] += Cf(&x[i])._Val[1] * Cf(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cf(&x[i*incx])._Val[0] * Cf(&y[i*incy])._Val[0];
			zdotc._Val[1] += Cf(&x[i*incx])._Val[1] * Cf(&y[i*incy])._Val[1];
		}
	}
	pCf(z) = zdotc;
}
#else
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i]) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i*incx]) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
#endif
static inline void zdotu_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Dcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cd(&x[i])._Val[0] * Cd(&y[i])._Val[0];
			zdotc._Val[1] += Cd(&x[i])._Val[1] * Cd(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cd(&x[i*incx])._Val[0] * Cd(&y[i*incy])._Val[0];
			zdotc._Val[1] += Cd(&x[i*incx])._Val[1] * Cd(&y[i*incy])._Val[1];
		}
	}
	pCd(z) = zdotc;
}
#else
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i]) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i*incx]) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}
#endif
/*  -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/



/* Common Block Declarations */

struct {
    integer infot, noutc;
    logical ok;
} infoc_;

#define infoc_1 infoc_

struct {
    char srnamt[12];
} srnamc_;

#define srnamc_1 srnamc_

/* Table of constant values */

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static integer c__1 = 1;
static integer c__65 = 65;
static integer c__2 = 2;
static doublereal c_b125 = 1.;
static integer c__6 = 6;
static logical c_true = TRUE_;
static integer c_n1 = -1;
static integer c__0 = 0;
static logical c_false = FALSE_;

/* Main program */ int main()
{
    /* Initialized data */

    static char snames[17][13] =  { "cblas_zgemv " , "cblas_zgbmv " , "cblas_zhemv ",
    "cblas_zhbmv ", "cblas_zhpmv ", "cblas_ztrmv " , "cblas_ztbmv " , "cblas_ztpmv ",
    "cblas_ztrsv ", "cblas_ztbsv ", "cblas_ztpsv " , "cblas_zgerc " , "cblas_zgeru ",
    "cblas_zher  ", "cblas_zhpr  ", "cblas_zher2 " , "cblas_zhpr2 " };

    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5;
    doublereal d__1;

    /* Local variables */
    static integer nalf, idim[9];
    static logical same;
    static integer ninc, nbet, ntra;
    static logical rewi;
    extern /* Subroutine */ int zchk1_(), zchk2_(), zchk3_(), zchk4_(), 
	    zchk5_(), zchk6_();
    static doublecomplex a[4225]	/* was [65][65] */;
    static doublereal g[65];
    static integer i__, j;
    extern doublereal ddiff_();
    static integer n;
    static logical fatal;
    static doublecomplex x[65], y[65], z__[130];
    static logical trace;
    static integer nidim;
    static char snaps[32], trans[1];
    extern /* Subroutine */ int zmvch_();
    static integer isnum;
    static logical ltest[17];
    static doublecomplex aa[4225];
    static integer kb[7];
    static doublecomplex as[4225];
    static logical sfatal;
    static doublecomplex xs[130], ys[130];
    static logical corder;
    static doublecomplex xx[130], yt[65], yy[130];
    static char snamet[12];
    static doublereal thresh;
    static logical rorder;
    static integer layout;
    static logical ltestt, tsterr;
    extern /* Subroutine */ int cz2chke_();
    static doublecomplex alf[7];
    static integer inc[7], nkb;
    static doublecomplex bet[7];
    static doublereal eps, err;
    extern logical lze_();
    char tmpchar;

/*  Test program for the DOUBLE PRECISION COMPLEX Level 2 Blas. */

/*  The program must be driven by a short data file. The first 17 records */
/*  of the file are read using list-directed input, the last 17 records */
/*  are read using the format ( A12, L2 ). An annotated example of a data */
/*  file can be obtained by deleting the first 3 characters from the */
/*  following 34 lines: */
/*  'CBLAT2.SNAP'     NAME OF SNAPSHOT OUTPUT FILE */
/*  -1                UNIT NUMBER OF SNAPSHOT FILE (NOT USED IF .LT. 0) */
/*  F        LOGICAL FLAG, T TO REWIND SNAPSHOT FILE AFTER EACH RECORD. */
/*  F        LOGICAL FLAG, T TO STOP ON FAILURES. */
/*  T        LOGICAL FLAG, T TO TEST ERROR EXITS. */
/*  2        0 TO TEST COLUMN-MAJOR, 1 TO TEST ROW-MAJOR, 2 TO TEST BOTH */
/*  16.0     THRESHOLD VALUE OF TEST RATIO */
/*  6                 NUMBER OF VALUES OF N */
/*  0 1 2 3 5 9       VALUES OF N */
/*  4                 NUMBER OF VALUES OF K */
/*  0 1 2 4           VALUES OF K */
/*  4                 NUMBER OF VALUES OF INCX AND INCY */
/*  1 2 -1 -2         VALUES OF INCX AND INCY */
/*  3                 NUMBER OF VALUES OF ALPHA */
/*  (0.0,0.0) (1.0,0.0) (0.7,-0.9)       VALUES OF ALPHA */
/*  3                 NUMBER OF VALUES OF BETA */
/*  (0.0,0.0) (1.0,0.0) (1.3,-1.1)       VALUES OF BETA */
/*  cblas_zgemv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zgbmv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zhemv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zhbmv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zhpmv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_ztrmv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_ztbmv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_ztpmv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_ztrsv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_ztbsv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_ztpsv  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zgerc  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zgeru  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zher   T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zhpr   T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zher2  T PUT F FOR NO TEST. SAME COLUMNS. */
/*  cblas_zhpr2  T PUT F FOR NO TEST. SAME COLUMNS. */

/*     See: */

/*        Dongarra J. J., Du Croz J. J., Hammarling S.  and Hanson R. J.. */
/*        An  extended  set of Fortran  Basic Linear Algebra Subprograms. */

/*        Technical  Memoranda  Nos. 41 (revision 3) and 81,  Mathematics */
/*        and  Computer Science  Division,  Argonne  National Laboratory, */
/*        9700 South Cass Avenue, Argonne, Illinois 60439, US. */

/*        Or */

/*        NAG  Technical Reports TR3/87 and TR4/87,  Numerical Algorithms */
/*        Group  Ltd.,  NAG  Central  Office,  256  Banbury  Road, Oxford */
/*        OX2 7DE, UK,  and  Numerical Algorithms Group Inc.,  1101  31st */
/*        Street,  Suite 100,  Downers Grove,  Illinois 60515-1263,  USA. */


/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Parameters .. */
/*     .. Local Scalars .. */
/*     .. Local Arrays .. */
/*     .. External Functions .. */
/*     .. External Subroutines .. */
/*     .. Intrinsic Functions .. */
/*     .. Scalars in Common .. */
/*     .. Common blocks .. */
/*     .. Data statements .. */
/*     .. Executable Statements .. */

    infoc_1.noutc = 6;

/*     Read name and unit number for summary output file and open file. */

    char line[80];
    
    fgets(line,80,stdin);
    sscanf(line,"'%s'",snaps);
    fgets(line,80,stdin);
    sscanf(line,"%d",&ntra);
    trace = ntra >= 0;
    if (trace) {
/*	o__1.oerr = 0;
	o__1.ounit = ntra;
	o__1.ofnmlen = 32;
	o__1.ofnm = snaps;
	o__1.orl = 0;
	o__1.osta = 0;
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);*/
    }
/*     Read the flag that directs rewinding of the snapshot file. */
   fgets(line,80,stdin);
   sscanf(line,"%d",&rewi);
   rewi = rewi && trace;
/*     Read the flag that directs stopping on any failure. */
   fgets(line,80,stdin);
   sscanf(line,"%c",&tmpchar);
/*     Read the flag that indicates whether error exits are to be tested. */
   sfatal=FALSE_;
   if (tmpchar=='T')sfatal=TRUE_;
   fgets(line,80,stdin);
   sscanf(line,"%c",&tmpchar);
/*     Read the flag that indicates whether error exits are to be tested. */
   tsterr=FALSE_;
   if (tmpchar=='T')tsterr=TRUE_;
/*     Read the flag that indicates whether row-major data layout to be tested. */
   fgets(line,80,stdin);
   sscanf(line,"%d",&layout);
/*     Read the threshold value of the test ratio */
   fgets(line,80,stdin);
   sscanf(line,"%lf",&thresh);

/*     Read and check the parameter values for the tests. */

/*     Values of N */
   fgets(line,80,stdin);
   sscanf(line,"%d",&nidim);

    if (nidim < 1 || nidim > 9) {
        fprintf(stderr,"NUMBER OF VALUES OF N IS LESS THAN 1 OR GREATER THAN 9");
        goto L230;
    }
   fgets(line,80,stdin);
   sscanf(line,"%d %d %d %d %d %d %d %d %d",&idim[0],&idim[1],&idim[2],
    &idim[3],&idim[4],&idim[5],&idim[6],&idim[7],&idim[8]);
    i__1 = nidim;
    for (i__ = 1; i__ <= i__1; ++i__) {
        if (idim[i__ - 1] < 0 || idim[i__ - 1] > 65) {
        fprintf(stderr,"VALUE OF N IS LESS THAN 0 OR GREATER THAN 65\n");
            goto L230;
        }
/* L10: */
    }
/*     Values of K */
   fgets(line,80,stdin);
   sscanf(line,"%d",&nkb);

    if (nkb < 1 || nkb > 7) {
        fprintf(stderr,"NUMBER OF VALUES OF K IS LESS THAN 1 OR GREATER THAN 7");
        goto L230;
    }
   fgets(line,80,stdin);
   sscanf(line,"%d %d %d %d %d %d %d",&kb[0],&kb[1],&kb[2],&kb[3],&kb[4],&kb[5],&kb[6]);
    i__1 = nkb;
    for (i__ = 1; i__ <= i__1; ++i__) {
        if (kb[i__ - 1] < 0 ) {
        fprintf(stderr,"VALUE OF K IS LESS THAN 0\n");
            goto L230;
        }
/* L20: */
    }
/*     Values of INCX and INCY */
   fgets(line,80,stdin);
   sscanf(line,"%d",&ninc);

    if (ninc < 1 || ninc > 7) {
        fprintf(stderr,"NUMBER OF VALUES OF INCX AND INCY IS LESS THAN 1 OR GREATER THAN 7");
        goto L230;
    }

   fgets(line,80,stdin);
   sscanf(line,"%d %d %d %d %d %d %d",&inc[0],&inc[1],&inc[2],&inc[3],&inc[4],&inc[5],&inc[6]);
    i__1 = ninc;
    for (i__ = 1; i__ <= i__1; ++i__) {
        if (inc[i__ - 1] == 0 || (i__2 = inc[i__ - 1], abs(i__2)) > 2) {
            fprintf (stderr,"ABSOLUTE VALUE OF INCX OR INCY IS 0 OR GREATER THAN 2\n");
            goto L230;
        }
/* L30: */
    }
/*     Values of ALPHA */
   fgets(line,80,stdin);
   sscanf(line,"%d",&nalf);
    if (nalf < 1 || nalf > 7) {
        fprintf(stderr,"VALUE OF ALPHA IS LESS THAN 0 OR GREATER THAN 7\n");
        goto L230;
    }
   fgets(line,80,stdin);
   sscanf(line,"(%lf,%lf) (%lf,%lf) (%lf,%lf) (%lf,%lf) (%lf,%lf) (%lf,%lf) (%lf,%lf)",&alf[0].r,&alf[0].i,&alf[1].r,&alf[1].i,&alf[2].r,&alf[2].i,&alf[3].r,&alf[3].i,
   &alf[4].r,&alf[4].i,&alf[5].r,&alf[5].i,&alf[6].r,&alf[6].i);

/*     Values of BETA */
   fgets(line,80,stdin);
   sscanf(line,"%d",&nbet);
    if (nbet < 1 || nbet > 7) {
        fprintf(stderr,"VALUE OF BETA IS LESS THAN 0 OR GREATER THAN 7\n");
        goto L230;
    }
   fgets(line,80,stdin);
   sscanf(line,"(%lf,%lf) (%lf,%lf) (%lf,%lf) (%lf,%lf) (%lf,%lf) (%lf,%lf) (%lf,%lf)",&bet[0].r,&bet[0].i,&bet[1].r,&bet[1].i,&bet[2].r,&bet[2].i,&bet[3].r,&bet[3].i,
   &bet[4].r,&bet[4].i,&bet[5].r,&bet[5].i,&bet[6].r,&bet[6].i);

/*     Report values of parameters. */
    printf("TESTS OF THE DOUBLE PRECISION COMPLEX LEVEL 2 BLAS\nTHE FOLLOWING PARAMETER VALUES WILL BE USED:\n");
    printf(" FOR N");
    for (i__ =1; i__ <=nidim;++i__) printf(" %d",idim[i__-1]);
    printf("\n");

    printf(" FOR K");
    for (i__ =1; i__ <=nkb;++i__) printf(" %d",kb[i__-1]);
    printf("\n");

    printf(" FOR INCX AND INCY");
    for (i__ =1; i__ <=ninc;++i__) printf(" %d",inc[i__-1]);
    printf("\n");

    printf(" FOR ALPHA");
    for (i__ =1; i__ <=nalf;++i__) printf(" (%f,%f)",alf[i__-1].r,alf[i__-1].i);
    printf("\n");    
    printf(" FOR BETA");
    for (i__ =1; i__ <=nbet;++i__) printf(" (%f,%f)",bet[i__-1].r,bet[i__-1].i);
    printf("\n");    

    if (! tsterr) {
      printf(" ERROR-EXITS WILL NOT BE TESTED\n"); 
    }
    printf("ROUTINES PASS COMPUTATIONAL TESTS IF TEST RATIO IS LESS THAN %f\n",thresh);
    
    rorder = FALSE_;
    corder = FALSE_;
    if (layout == 2) {
	rorder = TRUE_;
	corder = TRUE_;
        printf("COLUMN-MAJOR AND ROW-MAJOR DATA LAYOUTS ARE TESTED\n");
    } else if (layout == 1) {
	rorder = TRUE_;
        printf("ROW-MAJOR DATA LAYOUT IS TESTED\n");
    } else if (layout == 0) {
	corder = TRUE_;
        printf("COLUMN-MAJOR DATA LAYOUT IS TESTED\n");
    }

/*     Read names of subroutines and flags which indicate */
/*     whether they are to be tested. */

    for (i__ = 1; i__ <= 17; ++i__) {
	ltest[i__ - 1] = FALSE_;
/* L40: */
    }
L50:
    if (! fgets(line,80,stdin)) {
        goto L80;
    }
    i__1 = sscanf(line,"%12c %c",snamet,&tmpchar);
   ltestt=FALSE_;
   if (tmpchar=='T')ltestt=TRUE_;
    if (i__1 < 2) {
        goto L80;
    }
    for (i__ = 1; i__ <= 17; ++i__) {
	if (s_cmp(snamet, snames[i__ - 1], (ftnlen)12, (ftnlen)12) == 
		0) {
	    goto L70;
	}
/* L60: */
    }
    printf("SUBPROGRAM NAME %s NOT RECOGNIZED\n****** TESTS ABANDONED ******\n",snamet);
    exit(1);
L70:
    ltest[i__ - 1] = ltestt;
    goto L50;

L80:
/*    cl__1.cerr = 0;
    cl__1.cunit = 5;
    cl__1.csta = 0;
    f_clos(&cl__1);*/

/*     Compute EPS (the machine precision). */

    eps = 1.;
L90:
    d__1 = eps + 1.;
    if (ddiff_(&d__1, &c_b125) == 0.) {
	goto L100;
    }
    eps *= .5;
    goto L90;
L100:
    eps += eps;
    printf("RELATIVE MACHINE PRECISION IS TAKEN TO BE %9.1g\n",eps);

/*     Check the reliability of ZMVCH using exact data. */

    n = 32;
    i__1 = n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = i__ + j * 65 - 66;
/* Computing MAX */
	    i__5 = i__ - j + 1;
	    i__4 = f2cmax(i__5,0);
	    a[i__3].r = (doublereal) i__4, a[i__3].i = 0.;
/* L110: */
	}
	i__2 = j - 1;
	x[i__2].r = (doublereal) j, x[i__2].i = 0.;
	i__2 = j - 1;
	y[i__2].r = 0., y[i__2].i = 0.;
/* L120: */
    }
    i__1 = n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = j - 1;
	i__3 = j * ((j + 1) * j) / 2 - (j + 1) * j * (j - 1) / 3;
	yy[i__2].r = (doublereal) i__3, yy[i__2].i = 0.;
/* L130: */
    }
/*     YY holds the exact result. On exit from CMVCH YT holds */
/*     the result computed by CMVCH. */
    *(unsigned char *)trans = 'N';
    zmvch_(trans, &n, &n, &c_b2, a, &c__65, x, &c__1, &c_b1, y, &c__1, yt, g, 
	    yy, &eps, &err, &fatal, &c__6, &c_true, (ftnlen)1);
    same = lze_(yy, yt, &n);
    if (! same || err != (float)0.) {
      printf("ERROR IN ZMVCH - IN-LINE DOT PRODUCTS ARE BEING EVALUATED WRONGLY\n");
      printf("ZMVCH WAS CALLED WITH TRANS = %s ", trans);
      printf("AND RETURNED SAME = %c AND ERR = %12.3f.\n",(same==FALSE_? 'F':'T'),err);
      printf("THIS MAY BE DUE TO FAULTS IN THE ARITHMETIC OR THE COMPILER.\n");
      printf("****** TESTS ABANDONED ******\n");
      exit(1);
    }
    *(unsigned char *)trans = 'T';
    zmvch_(trans, &n, &n, &c_b2, a, &c__65, x, &c_n1, &c_b1, y, &c_n1, yt, g, 
	    yy, &eps, &err, &fatal, &c__6, &c_true, (ftnlen)1);
    same = lze_(yy, yt, &n);
    if (! same || err != 0.) {
      printf("ERROR IN ZMVCH - IN-LINE DOT PRODUCTS ARE BEING EVALUATED WRONGLY\n");
      printf("ZMVCH WAS CALLED WITH TRANS = %s ", trans);
      printf("AND RETURNED SAME = %c AND ERR = %12.3f.\n",(same==FALSE_? 'F':'T'),err);
      printf("THIS MAY BE DUE TO FAULTS IN THE ARITHMETIC OR THE COMPILER.\n");
      printf("****** TESTS ABANDONED ******\n");
      exit(1);
    }

/*     Test each subroutine in turn. */

    for (isnum = 1; isnum <= 17; ++isnum) {
	if (! ltest[isnum - 1]) {
/*           Subprogram is not to be tested. */
           printf("%12s WAS NOT TESTED\n",snames[isnum-1]);
	} else {
	    s_copy(srnamc_1.srnamt, snames[isnum - 1], (ftnlen)12, (
		    ftnlen)12);
/*           Test error exits. */
	    if (tsterr) {
		cz2chke_(snames[isnum - 1], (ftnlen)12);
	    }
/*           Test computations. */
	    infoc_1.infot = 0;
	    infoc_1.ok = TRUE_;
	    fatal = FALSE_;
	    switch ((int)isnum) {
		case 1:  goto L140;
		case 2:  goto L140;
		case 3:  goto L150;
		case 4:  goto L150;
		case 5:  goto L150;
		case 6:  goto L160;
		case 7:  goto L160;
		case 8:  goto L160;
		case 9:  goto L160;
		case 10:  goto L160;
		case 11:  goto L160;
		case 12:  goto L170;
		case 13:  goto L170;
		case 14:  goto L180;
		case 15:  goto L180;
		case 16:  goto L190;
		case 17:  goto L190;
	    }
/*           Test ZGEMV, 01, and ZGBMV, 02. */
L140:
	    if (corder) {
		zchk1_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nkb, kb, &nalf,
			 alf, &nbet, bet, &ninc, inc, &c__65, &c__2, a, aa, 
			as, x, xx, xs, y, yy, ys, yt, g, &c__0, (ftnlen)12);
	    }
	    if (rorder) {
		zchk1_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nkb, kb, &nalf,
			 alf, &nbet, bet, &ninc, inc, &c__65, &c__2, a, aa, 
			as, x, xx, xs, y, yy, ys, yt, g, &c__1, (ftnlen)12);
	    }
	    goto L200;
/*           Test ZHEMV, 03, ZHBMV, 04, and ZHPMV, 05. */
L150:
	    if (corder) {
		zchk2_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nkb, kb, &nalf,
			 alf, &nbet, bet, &ninc, inc, &c__65, &c__2, a, aa, 
			as, x, xx, xs, y, yy, ys, yt, g, &c__0, (ftnlen)12);
	    }
	    if (rorder) {
		zchk2_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nkb, kb, &nalf,
			 alf, &nbet, bet, &ninc, inc, &c__65, &c__2, a, aa, 
			as, x, xx, xs, y, yy, ys, yt, g, &c__1, (ftnlen)12);
	    }
	    goto L200;
/*           Test ZTRMV, 06, ZTBMV, 07, ZTPMV, 08, */
/*           ZTRSV, 09, ZTBSV, 10, and ZTPSV, 11. */
L160:
	    if (corder) {
		zchk3_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nkb, kb, &ninc,
			 inc, &c__65, &c__2, a, aa, as, y, yy, ys, yt, g, z__,
			 &c__0, (ftnlen)12);
	    }
	    if (rorder) {
		zchk3_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nkb, kb, &ninc,
			 inc, &c__65, &c__2, a, aa, as, y, yy, ys, yt, g, z__,
			 &c__1, (ftnlen)12);
	    }
	    goto L200;
/*           Test ZGERC, 12, ZGERU, 13. */
L170:
	    if (corder) {
		zchk4_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nalf, alf, &
			ninc, inc, &c__65, &c__2, a, aa, as, x, xx, xs, y, yy,
			 ys, yt, g, z__, &c__0, (ftnlen)12);
	    }
	    if (rorder) {
		zchk4_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nalf, alf, &
			ninc, inc, &c__65, &c__2, a, aa, as, x, xx, xs, y, yy,
			 ys, yt, g, z__, &c__1, (ftnlen)12);
	    }
	    goto L200;
/*           Test ZHER, 14, and ZHPR, 15. */
L180:
	    if (corder) {
		zchk5_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nalf, alf, &
			ninc, inc, &c__65, &c__2, a, aa, as, x, xx, xs, y, yy,
			 ys, yt, g, z__, &c__0, (ftnlen)12);
	    }
	    if (rorder) {
		zchk5_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nalf, alf, &
			ninc, inc, &c__65, &c__2, a, aa, as, x, xx, xs, y, yy,
			 ys, yt, g, z__, &c__1, (ftnlen)12);
	    }
	    goto L200;
/*           Test ZHER2, 16, and ZHPR2, 17. */
L190:
	    if (corder) {
		zchk6_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nalf, alf, &
			ninc, inc, &c__65, &c__2, a, aa, as, x, xx, xs, y, yy,
			 ys, yt, g, z__, &c__0, (ftnlen)12);
	    }
	    if (rorder) {
		zchk6_(snames[isnum - 1], &eps, &thresh, &c__6, &ntra,
			 &trace, &rewi, &fatal, &nidim, idim, &nalf, alf, &
			ninc, inc, &c__65, &c__2, a, aa, as, x, xx, xs, y, yy,
			 ys, yt, g, z__, &c__1, (ftnlen)12);
	    }

L200:
	    if (fatal && sfatal) {
		goto L220;
	    }
	}
/* L210: */
    }
    printf("\nEND OF TESTS\n");
    goto L240;

L220:
    printf("\n****** FATAL ERROR - TESTS ABANDONED ******\n");
    goto L240;

L230:
    printf("AMEND DATA FILE OR INCREASE ARRAY SIZES IN PROGRAM\n");
    printf("****** TESTS ABANDONED ******\n");

L240:
    if (trace) {
/*	cl__1.cerr = 0;
	cl__1.cunit = ntra;
	cl__1.csta = 0;
	f_clos(&cl__1);*/
    }
/*    cl__1.cerr = 0;
    cl__1.cunit = 6;
    cl__1.csta = 0;
    f_clos(&cl__1);*/
    exit(0);


/*     End of ZBLAT2. */

} /* MAIN__ */

/* Subroutine */ int zchk1_(sname, eps, thresh, nout, ntra, trace, rewi, 
	fatal, nidim, idim, nkb, kb, nalf, alf, nbet, bet, ninc, inc, nmax, 
	incmax, a, aa, as, x, xx, xs, y, yy, ys, yt, g, iorder, sname_len)
char *sname;
doublereal *eps, *thresh;
integer *nout, *ntra;
logical *trace, *rewi, *fatal;
integer *nidim, *idim, *nkb, *kb, *nalf;
doublecomplex *alf;
integer *nbet;
doublecomplex *bet;
integer *ninc, *inc, *nmax, *incmax;
doublecomplex *a, *aa, *as, *x, *xx, *xs, *y, *yy, *ys, *yt;
doublereal *g;
integer *iorder;
ftnlen sname_len;
{
    /* Initialized data */

    static char ich[3+1] = "NTC";

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5, i__6, i__7, i__8, 
	    i__9;

    /* Local variables */
    static doublecomplex beta;
    static integer ldas;
    static logical same;
    static integer incx, incy;
    static logical full, tran, null;
    static integer i__, m, n;
    static doublecomplex alpha;
    static logical isame[13];
    extern /* Subroutine */ int zmake_();
    static integer nargs;
    static logical reset;
    static integer incxs, incys;
    static char trans[1];
    extern /* Subroutine */ int zmvch_();
    static integer ia, ib, ic;
    static logical banded;
    static integer nc, nd, im, in, kl, ml, nk, nl, ku, ix, iy, ms, lx, ly, ns;
    extern /* Subroutine */ int czgbmv_();
    static char ctrans[14];
    extern /* Subroutine */ int czgemv_();
    static doublereal errmax;
    static doublecomplex transl;
    extern logical lzeres_();
    static char transs[1];
    static integer laa, lda;
    static doublecomplex als, bls;
    static doublereal err;
    static integer iku, kls;
    extern logical lze_();
    static integer kus;


/*  Tests CGEMV and CGBMV. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Parameters .. */
/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. Local Arrays .. */
/*     .. External Functions .. */
/*     .. External Subroutines .. */
/*     .. Intrinsic Functions .. */
/*     .. Scalars in Common .. */
/*     .. Common blocks .. */
/*     .. Data statements .. */
    /* Parameter adjustments */
    --idim;
    --kb;
    --alf;
    --bet;
    --inc;
    --g;
    --yt;
    --y;
    --x;
    --as;
    --aa;
    a_dim1 = *nmax;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ys;
    --yy;
    --xs;
    --xx;

    /* Function Body */
/*     .. Executable Statements .. */
    full = *(unsigned char *)&sname[8] == 'e';
    banded = *(unsigned char *)&sname[8] == 'b';
/*     Define the number of arguments. */
    if (full) {
	nargs = 11;
    } else if (banded) {
	nargs = 13;
    }

    nc = 0;
    reset = TRUE_;
    errmax = 0.;

    i__1 = *nidim;
    for (in = 1; in <= i__1; ++in) {
	n = idim[in];
	nd = n / 2 + 1;

	for (im = 1; im <= 2; ++im) {
	    if (im == 1) {
/* Computing MAX */
		i__2 = n - nd;
		m = f2cmax(i__2,0);
	    }
	    if (im == 2) {
/* Computing MIN */
		i__2 = n + nd;
		m = f2cmin(i__2,*nmax);
	    }

	    if (banded) {
		nk = *nkb;
	    } else {
		nk = 1;
	    }
	    i__2 = nk;
	    for (iku = 1; iku <= i__2; ++iku) {
		if (banded) {
		    ku = kb[iku];
/* Computing MAX */
		    i__3 = ku - 1;
		    kl = f2cmax(i__3,0);
		} else {
		    ku = n - 1;
		    kl = m - 1;
		}
/*              Set LDA to 1 more than minimum value if room. */
		if (banded) {
		    lda = kl + ku + 1;
		} else {
		    lda = m;
		}
		if (lda < *nmax) {
		    ++lda;
		}
/*              Skip tests if not enough room. */
		if (lda > *nmax) {
		    goto L100;
		}
		laa = lda * n;
		null = n <= 0 || m <= 0;

/*              Generate the matrix A. */

		transl.r = 0., transl.i = 0.;
		zmake_(sname + 7, " ", " ", &m, &n, &a[a_offset], nmax, &aa[1]
			, &lda, &kl, &ku, &reset, &transl, (ftnlen)2, (ftnlen)
			1, (ftnlen)1);

		for (ic = 1; ic <= 3; ++ic) {
		    *(unsigned char *)trans = *(unsigned char *)&ich[ic - 1];
		    if (*(unsigned char *)trans == 'N') {
			s_copy(ctrans, "  CblasNoTrans", (ftnlen)14, (ftnlen)
				14);
		    } else if (*(unsigned char *)trans == 'T') {
			s_copy(ctrans, "    CblasTrans", (ftnlen)14, (ftnlen)
				14);
		    } else {
			s_copy(ctrans, "CblasConjTrans", (ftnlen)14, (ftnlen)
				14);
		    }
		    tran = *(unsigned char *)trans == 'T' || *(unsigned char *
			    )trans == 'C';

		    if (tran) {
			ml = n;
			nl = m;
		    } else {
			ml = m;
			nl = n;
		    }

		    i__3 = *ninc;
		    for (ix = 1; ix <= i__3; ++ix) {
			incx = inc[ix];
			lx = abs(incx) * nl;

/*                    Generate the vector X. */

			transl.r = .5, transl.i = 0.;
			i__4 = abs(incx);
			i__5 = nl - 1;
			zmake_("ge", " ", " ", &c__1, &nl, &x[1], &c__1, &xx[
				1], &i__4, &c__0, &i__5, &reset, &transl, (
				ftnlen)2, (ftnlen)1, (ftnlen)1);
			if (nl > 1) {
			    i__4 = nl / 2;
			    x[i__4].r = 0., x[i__4].i = 0.;
			    i__4 = abs(incx) * (nl / 2 - 1) + 1;
			    xx[i__4].r = 0., xx[i__4].i = 0.;
			}

			i__4 = *ninc;
			for (iy = 1; iy <= i__4; ++iy) {
			    incy = inc[iy];
			    ly = abs(incy) * ml;

			    i__5 = *nalf;
			    for (ia = 1; ia <= i__5; ++ia) {
				i__6 = ia;
				alpha.r = alf[i__6].r, alpha.i = alf[i__6].i;

				i__6 = *nbet;
				for (ib = 1; ib <= i__6; ++ib) {
				    i__7 = ib;
				    beta.r = bet[i__7].r, beta.i = bet[i__7]
					    .i;

/*                             Generate the vector Y. */

				    transl.r = 0., transl.i = 0.;
				    i__7 = abs(incy);
				    i__8 = ml - 1;
				    zmake_("ge", " ", " ", &c__1, &ml, &y[1], 
					    &c__1, &yy[1], &i__7, &c__0, &
					    i__8, &reset, &transl, (ftnlen)2, 
					    (ftnlen)1, (ftnlen)1);

				    ++nc;

/*                             Save every datum before calling the */
/*                             subroutine. */

				    *(unsigned char *)transs = *(unsigned 
					    char *)trans;
				    ms = m;
				    ns = n;
				    kls = kl;
				    kus = ku;
				    als.r = alpha.r, als.i = alpha.i;
				    i__7 = laa;
				    for (i__ = 1; i__ <= i__7; ++i__) {
					i__8 = i__;
					i__9 = i__;
					as[i__8].r = aa[i__9].r, as[i__8].i = 
						aa[i__9].i;
/* L10: */
				    }
				    ldas = lda;
				    i__7 = lx;
				    for (i__ = 1; i__ <= i__7; ++i__) {
					i__8 = i__;
					i__9 = i__;
					xs[i__8].r = xx[i__9].r, xs[i__8].i = 
						xx[i__9].i;
/* L20: */
				    }
				    incxs = incx;
				    bls.r = beta.r, bls.i = beta.i;
				    i__7 = ly;
				    for (i__ = 1; i__ <= i__7; ++i__) {
					i__8 = i__;
					i__9 = i__;
					ys[i__8].r = yy[i__9].r, ys[i__8].i = 
						yy[i__9].i;
/* L30: */
				    }
				    incys = incy;

/*                             Call the subroutine. */

				    if (full) {
					if (*trace) {
/*
					    sprintf(ntra,"%6d: %12s (%14s %3d %3d (%4.1f,%4.1f) A\n          %3d, X, %2d, (%4.1f,%4.1f), Y, %2d).\n",
					    nc,sname,ctrans,m,n,alpha.r,alpha.i,lda,incx,beta.r,beta.i,incy);
*/
					}
					if (*rewi) {
/*					    al__1.aerr = 0;
					    al__1.aunit = *ntra;
					    f_rew(&al__1);*/
					}
					czgemv_(iorder, trans, &m, &n, &alpha,
						 &aa[1], &lda, &xx[1], &incx, 
						&beta, &yy[1], &incy, (ftnlen)
						1);
				    } else if (banded) {
					if (*trace) {
/*
					    sprintf(ntra,"%6d: %12s (%14s %3d %3d %3d %3d (%4.1f,%4.1f) A\n          %3d, X, %2d, (%4.1f,%4.1f), Y, %2d).\n",
					    nc,sname,ctrans,m,n,kl,ku,alpha.r,alpha.i,lda,incx,beta.r,beta.i,incy);
*/
					}
					if (*rewi) {
/*					    al__1.aerr = 0;
					    al__1.aunit = *ntra;
					    f_rew(&al__1);*/
					}
					czgbmv_(iorder, trans, &m, &n, &kl, &
						ku, &alpha, &aa[1], &lda, &xx[
						1], &incx, &beta, &yy[1], &
						incy, (ftnlen)1);
				    }

/*                            Check if error-exit was taken incorrectly. */

				    if (! infoc_1.ok) {
				    	printf("******* FATAL ERROR - ERROR-EXIT TAKEN ON VALID CALL *******\n");
					*fatal = TRUE_;
					goto L130;
				    }

/*                             See what data changed inside subroutines. */

/*        IF(TRANS .NE. 'C' .OR. (INCX .GT. 0 .AND. INCY .GT. 0)) THEN */
				    isame[0] = *(unsigned char *)trans == *(
					    unsigned char *)transs;
				    isame[1] = ms == m;
				    isame[2] = ns == n;
				    if (full) {
					isame[3] = als.r == alpha.r && als.i 
						== alpha.i;
					isame[4] = lze_(&as[1], &aa[1], &laa);
					isame[5] = ldas == lda;
					isame[6] = lze_(&xs[1], &xx[1], &lx);
					isame[7] = incxs == incx;
					isame[8] = bls.r == beta.r && bls.i ==
						 beta.i;
					if (null) {
					    isame[9] = lze_(&ys[1], &yy[1], &
						    ly);
					} else {
					    i__7 = abs(incy);
					    isame[9] = lzeres_("ge", " ", &
						    c__1, &ml, &ys[1], &yy[1],
						     &i__7, (ftnlen)2, (
						    ftnlen)1);
					}
					isame[10] = incys == incy;
				    } else if (banded) {
					isame[3] = kls == kl;
					isame[4] = kus == ku;
					isame[5] = als.r == alpha.r && als.i 
						== alpha.i;
					isame[6] = lze_(&as[1], &aa[1], &laa);
					isame[7] = ldas == lda;
					isame[8] = lze_(&xs[1], &xx[1], &lx);
					isame[9] = incxs == incx;
					isame[10] = bls.r == beta.r && bls.i 
						== beta.i;
					if (null) {
					    isame[11] = lze_(&ys[1], &yy[1], &
						    ly);
					} else {
					    i__7 = abs(incy);
					    isame[11] = lzeres_("ge", " ", &
						    c__1, &ml, &ys[1], &yy[1],
						     &i__7, (ftnlen)2, (
						    ftnlen)1);
					}
					isame[12] = incys == incy;
				    }

/*                             If data was incorrectly changed, report */
/*                             and return. */

				    same = TRUE_;
				    i__7 = nargs;
				    for (i__ = 1; i__ <= i__7; ++i__) {
					same = same && isame[i__ - 1];
					if (! isame[i__ - 1]) {
					    printf(" ******* FATAL ERROR - PARAMETER NUMBER %2d WAS CHANGED INCORRECTLY *******\n",i__);
					}
/* L40: */
				    }
				    if (! same) {
					*fatal = TRUE_;
					goto L130;
				    }

				    if (! null) {

/*                                Check the result. */

					zmvch_(trans, &m, &n, &alpha, &a[
						a_offset], nmax, &x[1], &incx,
						 &beta, &y[1], &incy, &yt[1], 
						&g[1], &yy[1], eps, &err, 
						fatal, nout, &c_true, (ftnlen)
						1);
					errmax = f2cmax(errmax,err);
/*                                If got really bad answer, report and */
/*                                return. */
					if (*fatal) {
					    goto L130;
					}
				    } else {
/*                                Avoid repeating tests with M.le.0 or */
/*                                N.le.0. */
					goto L110;
				    }
/*                          END IF */

/* L50: */
				}

/* L60: */
			    }

/* L70: */
			}

/* L80: */
		    }

/* L90: */
		}

L100:
		;
	    }

L110:
	    ;
	}

/* L120: */
    }

/*     Report result. */

    if (errmax < *thresh) {
        printf("%12s PASSED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
    } else {
        printf("%12s COMPLETED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
        printf("******* BUT WITH MAXIMUM TEST RATIO %8.2f - SUSPECT *******\n",errmax);
    }
    goto L140;

L130:
    printf("******* %12s FAILED ON CALL NUMBER:\n",sname);
    if (full) {
	printf("%6d: %12s (%14s %3d %3d (%4.1f,%4.1f) A\n          %3d, X, %2d, (%4.1f,%4.1f), Y, %2d).\n",
		nc,sname,ctrans,m,n,alpha.r,alpha.i,lda,incx,beta.r,beta.i,incy);
    } else if (banded) {
	printf("%6d: %12s (%14s %3d %3d %3d %3d (%4.1f,%4.1f) A\n          %3d, X, %2d, (%4.1f,%4.1f), Y, %2d).\n",
		nc,sname,ctrans,m,n,kl,ku,alpha.r,alpha.i,lda,incx,beta.r,beta.i,incy);
    }

L140:
    return 0;


/*     End of ZCHK1. */

} /* zchk1_ */

/* Subroutine */ int zchk2_(sname, eps, thresh, nout, ntra, trace, rewi, 
	fatal, nidim, idim, nkb, kb, nalf, alf, nbet, bet, ninc, inc, nmax, 
	incmax, a, aa, as, x, xx, xs, y, yy, ys, yt, g, iorder, sname_len)
char *sname;
doublereal *eps, *thresh;
integer *nout, *ntra;
logical *trace, *rewi, *fatal;
integer *nidim, *idim, *nkb, *kb, *nalf;
doublecomplex *alf;
integer *nbet;
doublecomplex *bet;
integer *ninc, *inc, *nmax, *incmax;
doublecomplex *a, *aa, *as, *x, *xx, *xs, *y, *yy, *ys, *yt;
doublereal *g;
integer *iorder;
ftnlen sname_len;
{
    /* Initialized data */

    static char ich[2+1] = "UL";

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5, i__6, i__7, i__8, 
	    i__9;

    /* Local variables */
    static doublecomplex beta;
    static integer ldas;
    static logical same;
    static integer incx, incy;
    static logical full, null;
    static char uplo[1];
    static integer i__, k, n;
    static doublecomplex alpha;
    static logical isame[13];
    extern /* Subroutine */ int zmake_();
    static integer nargs;
    static logical reset;
    static char cuplo[14];
    static integer incxs, incys;
    extern /* Subroutine */ int zmvch_();
    static char uplos[1];
    static integer ia, ib, ic;
    static logical banded;
    static integer nc, ik, in;
    static logical packed;
    static integer nk, ks, ix, iy, ns, lx, ly;
    extern /* Subroutine */ int czhbmv_(), czhemv_();
    static doublereal errmax;
    static doublecomplex transl;
    extern logical lzeres_();
    extern /* Subroutine */ int czhpmv_();
    static integer laa, lda;
    static doublecomplex als, bls;
    static doublereal err;
    extern logical lze_();

/*  Tests CHEMV, CHBMV and CHPMV. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Parameters .. */
/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. Local Arrays .. */
/*     .. External Functions .. */
/*     .. External Subroutines .. */
/*     .. Intrinsic Functions .. */
/*     .. Scalars in Common .. */
/*     .. Common blocks .. */
/*     .. Data statements .. */
    /* Parameter adjustments */
    --idim;
    --kb;
    --alf;
    --bet;
    --inc;
    --g;
    --yt;
    --y;
    --x;
    --as;
    --aa;
    a_dim1 = *nmax;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ys;
    --yy;
    --xs;
    --xx;

    /* Function Body */
/*     .. Executable Statements .. */
    full = *(unsigned char *)&sname[8] == 'e';
    banded = *(unsigned char *)&sname[8] == 'b';
    packed = *(unsigned char *)&sname[8] == 'p';
/*     Define the number of arguments. */
    if (full) {
	nargs = 10;
    } else if (banded) {
	nargs = 11;
    } else if (packed) {
	nargs = 9;
    }

    nc = 0;
    reset = TRUE_;
    errmax = 0.;

    i__1 = *nidim;
    for (in = 1; in <= i__1; ++in) {
	n = idim[in];

	if (banded) {
	    nk = *nkb;
	} else {
	    nk = 1;
	}
	i__2 = nk;
	for (ik = 1; ik <= i__2; ++ik) {
	    if (banded) {
		k = kb[ik];
	    } else {
		k = n - 1;
	    }
/*           Set LDA to 1 more than minimum value if room. */
	    if (banded) {
		lda = k + 1;
	    } else {
		lda = n;
	    }
	    if (lda < *nmax) {
		++lda;
	    }
/*           Skip tests if not enough room. */
	    if (lda > *nmax) {
		goto L100;
	    }
	    if (packed) {
		laa = n * (n + 1) / 2;
	    } else {
		laa = lda * n;
	    }
	    null = n <= 0;

	    for (ic = 1; ic <= 2; ++ic) {
		*(unsigned char *)uplo = *(unsigned char *)&ich[ic - 1];
		if (*(unsigned char *)uplo == 'U') {
		    s_copy(cuplo, "    CblasUpper", (ftnlen)14, (ftnlen)14);
		} else {
		    s_copy(cuplo, "    CblasLower", (ftnlen)14, (ftnlen)14);
		}

/*              Generate the matrix A. */

		transl.r = 0., transl.i = 0.;
		zmake_(sname + 7, uplo, " ", &n, &n, &a[a_offset], nmax, &aa[
			1], &lda, &k, &k, &reset, &transl, (ftnlen)2, (ftnlen)
			1, (ftnlen)1);

		i__3 = *ninc;
		for (ix = 1; ix <= i__3; ++ix) {
		    incx = inc[ix];
		    lx = abs(incx) * n;

/*                 Generate the vector X. */

		    transl.r = .5, transl.i = 0.;
		    i__4 = abs(incx);
		    i__5 = n - 1;
		    zmake_("ge", " ", " ", &c__1, &n, &x[1], &c__1, &xx[1], &
			    i__4, &c__0, &i__5, &reset, &transl, (ftnlen)2, (
			    ftnlen)1, (ftnlen)1);
		    if (n > 1) {
			i__4 = n / 2;
			x[i__4].r = 0., x[i__4].i = 0.;
			i__4 = abs(incx) * (n / 2 - 1) + 1;
			xx[i__4].r = 0., xx[i__4].i = 0.;
		    }

		    i__4 = *ninc;
		    for (iy = 1; iy <= i__4; ++iy) {
			incy = inc[iy];
			ly = abs(incy) * n;

			i__5 = *nalf;
			for (ia = 1; ia <= i__5; ++ia) {
			    i__6 = ia;
			    alpha.r = alf[i__6].r, alpha.i = alf[i__6].i;

			    i__6 = *nbet;
			    for (ib = 1; ib <= i__6; ++ib) {
				i__7 = ib;
				beta.r = bet[i__7].r, beta.i = bet[i__7].i;

/*                          Generate the vector Y. */

				transl.r = 0., transl.i = 0.;
				i__7 = abs(incy);
				i__8 = n - 1;
				zmake_("ge", " ", " ", &c__1, &n, &y[1], &
					c__1, &yy[1], &i__7, &c__0, &i__8, &
					reset, &transl, (ftnlen)2, (ftnlen)1, 
					(ftnlen)1);

				++nc;

/*                          Save every datum before calling the */
/*                          subroutine. */

				*(unsigned char *)uplos = *(unsigned char *)
					uplo;
				ns = n;
				ks = k;
				als.r = alpha.r, als.i = alpha.i;
				i__7 = laa;
				for (i__ = 1; i__ <= i__7; ++i__) {
				    i__8 = i__;
				    i__9 = i__;
				    as[i__8].r = aa[i__9].r, as[i__8].i = aa[
					    i__9].i;
/* L10: */
				}
				ldas = lda;
				i__7 = lx;
				for (i__ = 1; i__ <= i__7; ++i__) {
				    i__8 = i__;
				    i__9 = i__;
				    xs[i__8].r = xx[i__9].r, xs[i__8].i = xx[
					    i__9].i;
/* L20: */
				}
				incxs = incx;
				bls.r = beta.r, bls.i = beta.i;
				i__7 = ly;
				for (i__ = 1; i__ <= i__7; ++i__) {
				    i__8 = i__;
				    i__9 = i__;
				    ys[i__8].r = yy[i__9].r, ys[i__8].i = yy[
					    i__9].i;
/* L30: */
				}
				incys = incy;

/*                          Call the subroutine. */

				if (full) {
				    if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%14s, %3d, (%4.1f,%4.1f) A, %3d, X, %2d (%4.1f,%4.1f), Y, %2d ).\n",
					nc,sname,cuplo,n,alpha.r,alpha.i,lda,incx,beta.r,beta.i,incy);
*/
				    }
				    if (*rewi) {
/*					al__1.aerr = 0;
					al__1.aunit = *ntra;
					f_rew(&al__1);*/
				    }
				    czhemv_(iorder, uplo, &n, &alpha, &aa[1], 
					    &lda, &xx[1], &incx, &beta, &yy[1]
					    , &incy, (ftnlen)1);
				} else if (banded) {
				    if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%14s, %3d %3d, (%4.1f,%4.1f) A, %3d, X, %2d (%4.1f,%4.1f), Y, %2d ).\n",
					nc,sname,cuplo,n,k, alpha.r,alpha.i,lda,incx,beta.r,beta.i,incy);
*/
				    }
				    if (*rewi) {
/*					al__1.aerr = 0;
					al__1.aunit = *ntra;
					f_rew(&al__1);*/
				    }
				    czhbmv_(iorder, uplo, &n, &k, &alpha, &aa[
					    1], &lda, &xx[1], &incx, &beta, &
					    yy[1], &incy, (ftnlen)1);
				} else if (packed) {
				    if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%14s, %3d, (%4.1f,%4.1f) AP, X, %2d (%4.1f,%4.1f), Y, %2d ).\n",
					nc,sname,cuplo,n, alpha.r,alpha.i,incx,beta.r,beta.i,incy);
*/
				    }
				    if (*rewi) {
/*					al__1.aerr = 0;
					al__1.aunit = *ntra;
					f_rew(&al__1);*/
				    }
				    czhpmv_(iorder, uplo, &n, &alpha, &aa[1], 
					    &xx[1], &incx, &beta, &yy[1], &
					    incy, (ftnlen)1);
				}

/*                          Check if error-exit was taken incorrectly. */

				if (! infoc_1.ok) {
				    printf("******* FATAL ERROR - ERROR-EXIT TAKEN ON VALID CALL *******\n");
				    *fatal = TRUE_;
				    goto L120;
				}

/*                          See what data changed inside subroutines. */

				isame[0] = *(unsigned char *)uplo == *(
					unsigned char *)uplos;
				isame[1] = ns == n;
				if (full) {
				    isame[2] = als.r == alpha.r && als.i == 
					    alpha.i;
				    isame[3] = lze_(&as[1], &aa[1], &laa);
				    isame[4] = ldas == lda;
				    isame[5] = lze_(&xs[1], &xx[1], &lx);
				    isame[6] = incxs == incx;
				    isame[7] = bls.r == beta.r && bls.i == 
					    beta.i;
				    if (null) {
					isame[8] = lze_(&ys[1], &yy[1], &ly);
				    } else {
					i__7 = abs(incy);
					isame[8] = lzeres_("ge", " ", &c__1, &
						n, &ys[1], &yy[1], &i__7, (
						ftnlen)2, (ftnlen)1);
				    }
				    isame[9] = incys == incy;
				} else if (banded) {
				    isame[2] = ks == k;
				    isame[3] = als.r == alpha.r && als.i == 
					    alpha.i;
				    isame[4] = lze_(&as[1], &aa[1], &laa);
				    isame[5] = ldas == lda;
				    isame[6] = lze_(&xs[1], &xx[1], &lx);
				    isame[7] = incxs == incx;
				    isame[8] = bls.r == beta.r && bls.i == 
					    beta.i;
				    if (null) {
					isame[9] = lze_(&ys[1], &yy[1], &ly);
				    } else {
					i__7 = abs(incy);
					isame[9] = lzeres_("ge", " ", &c__1, &
						n, &ys[1], &yy[1], &i__7, (
						ftnlen)2, (ftnlen)1);
				    }
				    isame[10] = incys == incy;
				} else if (packed) {
				    isame[2] = als.r == alpha.r && als.i == 
					    alpha.i;
				    isame[3] = lze_(&as[1], &aa[1], &laa);
				    isame[4] = lze_(&xs[1], &xx[1], &lx);
				    isame[5] = incxs == incx;
				    isame[6] = bls.r == beta.r && bls.i == 
					    beta.i;
				    if (null) {
					isame[7] = lze_(&ys[1], &yy[1], &ly);
				    } else {
					i__7 = abs(incy);
					isame[7] = lzeres_("ge", " ", &c__1, &
						n, &ys[1], &yy[1], &i__7, (
						ftnlen)2, (ftnlen)1);
				    }
				    isame[8] = incys == incy;
				}

/*                          If data was incorrectly changed, report and */
/*                          return. */

				same = TRUE_;
				i__7 = nargs;
				for (i__ = 1; i__ <= i__7; ++i__) {
				    same = same && isame[i__ - 1];
				    if (! isame[i__ - 1]) {
					printf(" ******* FATAL ERROR - PARAMETER NUMBER %2d WAS CHANGED INCORRECTLY *******\n",i__);
				    }
/* L40: */
				}
				if (! same) {
				    *fatal = TRUE_;
				    goto L120;
				}

				if (! null) {

/*                             Check the result. */

				    zmvch_("N", &n, &n, &alpha, &a[a_offset], 
					    nmax, &x[1], &incx, &beta, &y[1], 
					    &incy, &yt[1], &g[1], &yy[1], eps,
					     &err, fatal, nout, &c_true, (
					    ftnlen)1);
				    errmax = f2cmax(errmax,err);
/*                             If got really bad answer, report and */
/*                             return. */
				    if (*fatal) {
					goto L120;
				    }
				} else {
/*                             Avoid repeating tests with N.le.0 */
				    goto L110;
				}

/* L50: */
			    }

/* L60: */
			}

/* L70: */
		    }

/* L80: */
		}

/* L90: */
	    }

L100:
	    ;
	}

L110:
	;
    }

/*     Report result. */

    if (errmax < *thresh) {
        printf("%12s PASSED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
    } else {
        printf("%12s COMPLETED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
        printf("******* BUT WITH MAXIMUM TEST RATIO %8.2f - SUSPECT *******\n",errmax);
    }
    goto L130;

L120:
    printf("******* %12s FAILED ON CALL NUMBER:\n",sname);
    if (full) {
	printf("%6d: %12s (%14s, %3d, (%4.1f,%4.1f) A, %3d, X, %2d (%4.1f,%4.1f), Y, %2d ).\n",
		nc,sname,cuplo,n, alpha.r,alpha.i,lda,incx,beta.r,beta.i,incy);
    } else if (banded) {
	printf("%6d: %12s (%14s, %3d, %3d, (%4.1f,%4.1f) A, %3d, X, %2d (%4.1f,%4.1f), Y, %2d ).\n",
		nc,sname,cuplo,n, k, alpha.r,alpha.i,lda,incx,beta.r,beta.i,incy);
    } else if (packed) {
	printf("%6d: %12s (%14s, %3d, (%4.1f,%4.1f) AP, X, %2d (%4.1f,%4.1f), Y, %2d ).\n",
		nc,sname,cuplo,n, alpha.r,alpha.i,incx,beta.r,beta.i,incy);
    }

L130:
    return 0;


/*     End of CZHK2. */

} /* zchk2_ */

/* Subroutine */ int zchk3_(sname, eps, thresh, nout, ntra, trace, rewi, 
	fatal, nidim, idim, nkb, kb, ninc, inc, nmax, incmax, a, aa, as, x, 
	xx, xs, xt, g, z__, iorder, sname_len)
char *sname;
doublereal *eps, *thresh;
integer *nout, *ntra;
logical *trace, *rewi, *fatal;
integer *nidim, *idim, *nkb, *kb, *ninc, *inc, *nmax, *incmax;
doublecomplex *a, *aa, *as, *x, *xx, *xs, *xt;
doublereal *g;
doublecomplex *z__;
integer *iorder;
ftnlen sname_len;
{
    /* Initialized data */

    static char ichu[2+1] = "UL";
    static char icht[3+1] = "NTC";
    static char ichd[2+1] = "UN";

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5, i__6;

    /* Local variables */
    static char diag[1];
    static integer ldas;
    static logical same;
    static integer incx;
    static logical full, null;
    static char uplo[1], cdiag[14];
    static integer i__, k, n;
    static char diags[1];
    static logical isame[13];
    extern /* Subroutine */ int zmake_();
    static integer nargs;
    static logical reset;
    static char cuplo[14];
    static integer incxs;
    static char trans[1];
    extern /* Subroutine */ int zmvch_();
    static char uplos[1];
    static logical banded;
    static integer nc, ik, in;
    static logical packed;
    static integer nk, ks, ix, ns, lx;
    static char ctrans[14];
    static doublereal errmax;
    static doublecomplex transl;
    extern logical lzeres_();
    extern /* Subroutine */ int cztbmv_();
    static char transs[1];
    extern /* Subroutine */ int cztbsv_(), cztpmv_(), cztrmv_(), cztpsv_(), 
	    cztrsv_();
    static integer laa, icd, lda, ict, icu;
    static doublereal err;
    extern logical lze_();




/*  Tests ZTRMV, ZTBMV, ZTPMV, ZTRSV, ZTBSV and ZTPSV. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Parameters .. */
/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. Local Arrays .. */
/*     .. External Functions .. */
/*     .. External Subroutines .. */
/*     .. Intrinsic Functions .. */
/*     .. Scalars in Common .. */
/*     .. Common blocks .. */
/*     .. Data statements .. */
    /* Parameter adjustments */
    --idim;
    --kb;
    --inc;
    --z__;
    --g;
    --xt;
    --x;
    --as;
    --aa;
    a_dim1 = *nmax;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --xs;
    --xx;

    /* Function Body */
/*     .. Executable Statements .. */
    full = *(unsigned char *)&sname[8] == 'r';
    banded = *(unsigned char *)&sname[8] == 'b';
    packed = *(unsigned char *)&sname[8] == 'p';
/*     Define the number of arguments. */
    if (full) {
	nargs = 8;
    } else if (banded) {
	nargs = 9;
    } else if (packed) {
	nargs = 7;
    }

    nc = 0;
    reset = TRUE_;
    errmax = 0.;
/*     Set up zero vector for ZMVCH. */
    i__1 = *nmax;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	z__[i__2].r = 0., z__[i__2].i = 0.;
/* L10: */
    }

    i__1 = *nidim;
    for (in = 1; in <= i__1; ++in) {
	n = idim[in];

	if (banded) {
	    nk = *nkb;
	} else {
	    nk = 1;
	}
	i__2 = nk;
	for (ik = 1; ik <= i__2; ++ik) {
	    if (banded) {
		k = kb[ik];
	    } else {
		k = n - 1;
	    }
/*           Set LDA to 1 more than minimum value if room. */
	    if (banded) {
		lda = k + 1;
	    } else {
		lda = n;
	    }
	    if (lda < *nmax) {
		++lda;
	    }
/*           Skip tests if not enough room. */
	    if (lda > *nmax) {
		goto L100;
	    }
	    if (packed) {
		laa = n * (n + 1) / 2;
	    } else {
		laa = lda * n;
	    }
	    null = n <= 0;

	    for (icu = 1; icu <= 2; ++icu) {
		*(unsigned char *)uplo = *(unsigned char *)&ichu[icu - 1];
		if (*(unsigned char *)uplo == 'U') {
		    s_copy(cuplo, "    CblasUpper", (ftnlen)14, (ftnlen)14);
		} else {
		    s_copy(cuplo, "    CblasLower", (ftnlen)14, (ftnlen)14);
		}

		for (ict = 1; ict <= 3; ++ict) {
		    *(unsigned char *)trans = *(unsigned char *)&icht[ict - 1]
			    ;
		    if (*(unsigned char *)trans == 'N') {
			s_copy(ctrans, "  CblasNoTrans", (ftnlen)14, (ftnlen)
				14);
		    } else if (*(unsigned char *)trans == 'T') {
			s_copy(ctrans, "    CblasTrans", (ftnlen)14, (ftnlen)
				14);
		    } else {
			s_copy(ctrans, "CblasConjTrans", (ftnlen)14, (ftnlen)
				14);
		    }

		    for (icd = 1; icd <= 2; ++icd) {
			*(unsigned char *)diag = *(unsigned char *)&ichd[icd 
				- 1];
			if (*(unsigned char *)diag == 'N') {
			    s_copy(cdiag, "  CblasNonUnit", (ftnlen)14, (
				    ftnlen)14);
			} else {
			    s_copy(cdiag, "     CblasUnit", (ftnlen)14, (
				    ftnlen)14);
			}

/*                    Generate the matrix A. */

			transl.r = 0., transl.i = 0.;
			zmake_(sname + 7, uplo, diag, &n, &n, &a[a_offset], 
				nmax, &aa[1], &lda, &k, &k, &reset, &transl, (
				ftnlen)2, (ftnlen)1, (ftnlen)1);

			i__3 = *ninc;
			for (ix = 1; ix <= i__3; ++ix) {
			    incx = inc[ix];
			    lx = abs(incx) * n;

/*                       Generate the vector X. */

			    transl.r = .5, transl.i = 0.;
			    i__4 = abs(incx);
			    i__5 = n - 1;
			    zmake_("ge", " ", " ", &c__1, &n, &x[1], &c__1, &
				    xx[1], &i__4, &c__0, &i__5, &reset, &
				    transl, (ftnlen)2, (ftnlen)1, (ftnlen)1);
			    if (n > 1) {
				i__4 = n / 2;
				x[i__4].r = 0., x[i__4].i = 0.;
				i__4 = abs(incx) * (n / 2 - 1) + 1;
				xx[i__4].r = 0., xx[i__4].i = 0.;
			    }

			    ++nc;

/*                       Save every datum before calling the subroutine. */

			    *(unsigned char *)uplos = *(unsigned char *)uplo;
			    *(unsigned char *)transs = *(unsigned char *)
				    trans;
			    *(unsigned char *)diags = *(unsigned char *)diag;
			    ns = n;
			    ks = k;
			    i__4 = laa;
			    for (i__ = 1; i__ <= i__4; ++i__) {
				i__5 = i__;
				i__6 = i__;
				as[i__5].r = aa[i__6].r, as[i__5].i = aa[i__6]
					.i;
/* L20: */
			    }
			    ldas = lda;
			    i__4 = lx;
			    for (i__ = 1; i__ <= i__4; ++i__) {
				i__5 = i__;
				i__6 = i__;
				xs[i__5].r = xx[i__6].r, xs[i__5].i = xx[i__6]
					.i;
/* L30: */
			    }
			    incxs = incx;

/*                       Call the subroutine. */

			    if (s_cmp(sname + 9, "mv", (ftnlen)2, (ftnlen)2) 
				    == 0) {
				if (full) {
				    if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%14s, %14s, %14s, %3d,  A, %3d, X, %2d).\n",
						nc, sname, cuplo, ctrans, cdiag, n, lda, incx);
*/
				    }
				    if (*rewi) {
/*					al__1.aerr = 0;
					al__1.aunit = *ntra;
					f_rew(&al__1);*/
				    }
				    cztrmv_(iorder, uplo, trans, diag, &n, &
					    aa[1], &lda, &xx[1], &incx, (
					    ftnlen)1, (ftnlen)1, (ftnlen)1);
				} else if (banded) {
				    if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%14s, %14s, %14s, %3d, %3d,  A, %3d, X, %2d).\n",
						nc, sname, cuplo, ctrans, cdiag, n, k, lda, incx);
*/
				    }
				    if (*rewi) {
/*					al__1.aerr = 0;
					al__1.aunit = *ntra;
					f_rew(&al__1);*/
				    }
				    cztbmv_(iorder, uplo, trans, diag, &n, &k,
					     &aa[1], &lda, &xx[1], &incx, (
					    ftnlen)1, (ftnlen)1, (ftnlen)1);
				} else if (packed) {
				    if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%14s, %14s, %14s, %3d,  AP X, %2d).\n",
						nc, sname, cuplo, ctrans, cdiag, n, incx);
*/
				    }
				    if (*rewi) {
/*					al__1.aerr = 0;
					al__1.aunit = *ntra;
					f_rew(&al__1);*/
				    }
				    cztpmv_(iorder, uplo, trans, diag, &n, &
					    aa[1], &xx[1], &incx, (ftnlen)1, (
					    ftnlen)1, (ftnlen)1);
				}
			    } else if (s_cmp(sname + 9, "sv", (ftnlen)2, (
				    ftnlen)2) == 0) {
				if (full) {
				    if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%14s, %14s, %14s, %3d,  A, %3d, X, %2d).\n",
						nc, sname, cuplo, ctrans, cdiag, n, lda, incx);
*/
				    }
				    if (*rewi) {
/*					al__1.aerr = 0;
					al__1.aunit = *ntra;
					f_rew(&al__1);*/
				    }
				    cztrsv_(iorder, uplo, trans, diag, &n, &
					    aa[1], &lda, &xx[1], &incx, (
					    ftnlen)1, (ftnlen)1, (ftnlen)1);
				} else if (banded) {
				    if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%14s, %14s, %14s, %3d, %3d,  A, %3d, X, %2d).\n",
						nc, sname, cuplo, ctrans, cdiag, n, k, lda, incx);
*/
				    }
				    if (*rewi) {
/*					al__1.aerr = 0;
					al__1.aunit = *ntra;
					f_rew(&al__1);*/
				    }
				    cztbsv_(iorder, uplo, trans, diag, &n, &k,
					     &aa[1], &lda, &xx[1], &incx, (
					    ftnlen)1, (ftnlen)1, (ftnlen)1);
				} else if (packed) {
				    if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%14s, %14s, %14s, %3d,  AP X, %2d).\n",
						nc, sname, cuplo, ctrans, cdiag, n, incx);
*/
				    }
				    if (*rewi) {
/*					al__1.aerr = 0;
					al__1.aunit = *ntra;
					f_rew(&al__1);*/
				    }
				    cztpsv_(iorder, uplo, trans, diag, &n, &
					    aa[1], &xx[1], &incx, (ftnlen)1, (
					    ftnlen)1, (ftnlen)1);
				}
			    }

/*                       Check if error-exit was taken incorrectly. */

			    if (! infoc_1.ok) {
				printf("******* FATAL ERROR - ERROR-EXIT TAKEN ON VALID CALL *******\n");
				*fatal = TRUE_;
				goto L120;
			    }

/*                       See what data changed inside subroutines. */

			    isame[0] = *(unsigned char *)uplo == *(unsigned 
				    char *)uplos;
			    isame[1] = *(unsigned char *)trans == *(unsigned 
				    char *)transs;
			    isame[2] = *(unsigned char *)diag == *(unsigned 
				    char *)diags;
			    isame[3] = ns == n;
			    if (full) {
				isame[4] = lze_(&as[1], &aa[1], &laa);
				isame[5] = ldas == lda;
				if (null) {
				    isame[6] = lze_(&xs[1], &xx[1], &lx);
				} else {
				    i__4 = abs(incx);
				    isame[6] = lzeres_("ge", " ", &c__1, &n, &
					    xs[1], &xx[1], &i__4, (ftnlen)2, (
					    ftnlen)1);
				}
				isame[7] = incxs == incx;
			    } else if (banded) {
				isame[4] = ks == k;
				isame[5] = lze_(&as[1], &aa[1], &laa);
				isame[6] = ldas == lda;
				if (null) {
				    isame[7] = lze_(&xs[1], &xx[1], &lx);
				} else {
				    i__4 = abs(incx);
				    isame[7] = lzeres_("ge", " ", &c__1, &n, &
					    xs[1], &xx[1], &i__4, (ftnlen)2, (
					    ftnlen)1);
				}
				isame[8] = incxs == incx;
			    } else if (packed) {
				isame[4] = lze_(&as[1], &aa[1], &laa);
				if (null) {
				    isame[5] = lze_(&xs[1], &xx[1], &lx);
				} else {
				    i__4 = abs(incx);
				    isame[5] = lzeres_("ge", " ", &c__1, &n, &
					    xs[1], &xx[1], &i__4, (ftnlen)2, (
					    ftnlen)1);
				}
				isame[6] = incxs == incx;
			    }

/*                       If data was incorrectly changed, report and */
/*                       return. */

			    same = TRUE_;
			    i__4 = nargs;
			    for (i__ = 1; i__ <= i__4; ++i__) {
				same = same && isame[i__ - 1];
				if (! isame[i__ - 1]) {
				printf(" ******* FATAL ERROR - PARAMETER NUMBER %2d WAS CHANGED INCORRECTLY *******\n",i__);
				}
/* L40: */
			    }
			    if (! same) {
				*fatal = TRUE_;
				goto L120;
			    }

			    if (! null) {
				if (s_cmp(sname + 9, "mv", (ftnlen)2, (ftnlen)
					2) == 0) {

/*                             Check the result. */

				    zmvch_(trans, &n, &n, &c_b2, &a[a_offset],
					     nmax, &x[1], &incx, &c_b1, &z__[
					    1], &incx, &xt[1], &g[1], &xx[1], 
					    eps, &err, fatal, nout, &c_true, (
					    ftnlen)1);
				} else if (s_cmp(sname + 9, "sv", (ftnlen)2, (
					ftnlen)2) == 0) {

/*                             Compute approximation to original vector. */

				    i__4 = n;
				    for (i__ = 1; i__ <= i__4; ++i__) {
					i__5 = i__;
					i__6 = (i__ - 1) * abs(incx) + 1;
					z__[i__5].r = xx[i__6].r, z__[i__5].i 
						= xx[i__6].i;
					i__5 = (i__ - 1) * abs(incx) + 1;
					i__6 = i__;
					xx[i__5].r = x[i__6].r, xx[i__5].i = 
						x[i__6].i;
/* L50: */
				    }
				    zmvch_(trans, &n, &n, &c_b2, &a[a_offset],
					     nmax, &z__[1], &incx, &c_b1, &x[
					    1], &incx, &xt[1], &g[1], &xx[1], 
					    eps, &err, fatal, nout, &c_false, 
					    (ftnlen)1);
				}
				errmax = f2cmax(errmax,err);
/*                          If got really bad answer, report and return. */
				if (*fatal) {
				    goto L120;
				}
			    } else {
/*                          Avoid repeating tests with N.le.0. */
				goto L110;
			    }

/* L60: */
			}

/* L70: */
		    }

/* L80: */
		}

/* L90: */
	    }

L100:
	    ;
	}

L110:
	;
    }

/*     Report result. */

    if (errmax < *thresh) {
        printf("%12s PASSED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
    } else {
        printf("%12s COMPLETED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
        printf("******* BUT WITH MAXIMUM TEST RATIO %8.2f - SUSPECT *******\n",errmax);
    }
    goto L130;

L120:
    printf("******* %12s FAILED ON CALL NUMBER:\n",sname);
    if (full) {
	printf("%6d: %12s (%14s, %14s, %14s, %3d,  A, %3d, X, %2d).\n",
		nc, sname, cuplo, ctrans, cdiag, n, lda, incx);
    } else if (banded) {
	printf("%6d: %12s (%14s, %14s, %14s, %3d, %3d,  A, %3d, X, %2d).\n",
		nc, sname, cuplo, ctrans, cdiag, n, k, lda, incx);
    } else if (packed) {

	printf("%6d: %12s (%14s, %14s, %14s, %3d,  AP X, %2d).\n",
		nc, sname, cuplo, ctrans, cdiag, n, incx);
    }

L130:
    return 0;


/*     End of ZCHK3. */

} /* zchk3_ */

/* Subroutine */ int zchk4_(sname, eps, thresh, nout, ntra, trace, rewi, 
	fatal, nidim, idim, nalf, alf, ninc, inc, nmax, incmax, a, aa, as, x, 
	xx, xs, y, yy, ys, yt, g, z__, iorder, sname_len)
char *sname;
doublereal *eps, *thresh;
integer *nout, *ntra;
logical *trace, *rewi, *fatal;
integer *nidim, *idim, *nalf;
doublecomplex *alf;
integer *ninc, *inc, *nmax, *incmax;
doublecomplex *a, *aa, *as, *x, *xx, *xs, *y, *yy, *ys, *yt;
doublereal *g;
doublecomplex *z__;
integer *iorder;
ftnlen sname_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5, i__6, i__7;
    doublecomplex z__1;

    /* Local variables */
    static integer ldas;
    static logical same, isconj;
    static integer incx, incy;
    static logical null;
    static integer i__, j, m, n;
    static doublecomplex alpha, w[1];
    static logical isame[13];
    extern /* Subroutine */ int zmake_();
    static integer nargs;
    static logical reset;
    static integer incxs, incys;
    extern /* Subroutine */ int zmvch_();
    static integer ia, nc, nd, im, in, ms, ix, iy, ns, lx, ly;
    extern /* Subroutine */ int czgerc_();
    static doublereal errmax;
    extern /* Subroutine */ int czgeru_();
    static doublecomplex transl;
    extern logical lzeres_();
    static integer laa, lda;
    static doublecomplex als;
    static doublereal err;
    extern logical lze_();




/*  Tests ZGERC and ZGERU. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Parameters .. */
/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. Local Arrays .. */
/*     .. External Functions .. */
/*     .. External Subroutines .. */
/*     .. Intrinsic Functions .. */
/*     .. Scalars in Common .. */
/*     .. Common blocks .. */
/*     .. Executable Statements .. */
    /* Parameter adjustments */
    --idim;
    --alf;
    --inc;
    --z__;
    --g;
    --yt;
    --y;
    --x;
    --as;
    --aa;
    a_dim1 = *nmax;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ys;
    --yy;
    --xs;
    --xx;

    /* Function Body */
    isconj = *(unsigned char *)&sname[10] == 'c';
/*     Define the number of arguments. */
    nargs = 9;

    nc = 0;
    reset = TRUE_;
    errmax = 0.;

    i__1 = *nidim;
    for (in = 1; in <= i__1; ++in) {
	n = idim[in];
	nd = n / 2 + 1;

	for (im = 1; im <= 2; ++im) {
	    if (im == 1) {
/* Computing MAX */
		i__2 = n - nd;
		m = f2cmax(i__2,0);
	    }
	    if (im == 2) {
/* Computing MIN */
		i__2 = n + nd;
		m = f2cmin(i__2,*nmax);
	    }

/*           Set LDA to 1 more than minimum value if room. */
	    lda = m;
	    if (lda < *nmax) {
		++lda;
	    }
/*           Skip tests if not enough room. */
	    if (lda > *nmax) {
		goto L110;
	    }
	    laa = lda * n;
	    null = n <= 0 || m <= 0;

	    i__2 = *ninc;
	    for (ix = 1; ix <= i__2; ++ix) {
		incx = inc[ix];
		lx = abs(incx) * m;

/*              Generate the vector X. */

		transl.r = .5, transl.i = 0.;
		i__3 = abs(incx);
		i__4 = m - 1;
		zmake_("ge", " ", " ", &c__1, &m, &x[1], &c__1, &xx[1], &i__3,
			 &c__0, &i__4, &reset, &transl, (ftnlen)2, (ftnlen)1, 
			(ftnlen)1);
		if (m > 1) {
		    i__3 = m / 2;
		    x[i__3].r = 0., x[i__3].i = 0.;
		    i__3 = abs(incx) * (m / 2 - 1) + 1;
		    xx[i__3].r = 0., xx[i__3].i = 0.;
		}

		i__3 = *ninc;
		for (iy = 1; iy <= i__3; ++iy) {
		    incy = inc[iy];
		    ly = abs(incy) * n;

/*                 Generate the vector Y. */

		    transl.r = 0., transl.i = 0.;
		    i__4 = abs(incy);
		    i__5 = n - 1;
		    zmake_("ge", " ", " ", &c__1, &n, &y[1], &c__1, &yy[1], &
			    i__4, &c__0, &i__5, &reset, &transl, (ftnlen)2, (
			    ftnlen)1, (ftnlen)1);
		    if (n > 1) {
			i__4 = n / 2;
			y[i__4].r = 0., y[i__4].i = 0.;
			i__4 = abs(incy) * (n / 2 - 1) + 1;
			yy[i__4].r = 0., yy[i__4].i = 0.;
		    }

		    i__4 = *nalf;
		    for (ia = 1; ia <= i__4; ++ia) {
			i__5 = ia;
			alpha.r = alf[i__5].r, alpha.i = alf[i__5].i;

/*                    Generate the matrix A. */

			transl.r = 0., transl.i = 0.;
			i__5 = m - 1;
			i__6 = n - 1;
			zmake_(sname + 7, " ", " ", &m, &n, &a[a_offset], 
				nmax, &aa[1], &lda, &i__5, &i__6, &reset, &
				transl, (ftnlen)2, (ftnlen)1, (ftnlen)1);

			++nc;

/*                    Save every datum before calling the subroutine. */

			ms = m;
			ns = n;
			als.r = alpha.r, als.i = alpha.i;
			i__5 = laa;
			for (i__ = 1; i__ <= i__5; ++i__) {
			    i__6 = i__;
			    i__7 = i__;
			    as[i__6].r = aa[i__7].r, as[i__6].i = aa[i__7].i;
/* L10: */
			}
			ldas = lda;
			i__5 = lx;
			for (i__ = 1; i__ <= i__5; ++i__) {
			    i__6 = i__;
			    i__7 = i__;
			    xs[i__6].r = xx[i__7].r, xs[i__6].i = xx[i__7].i;
/* L20: */
			}
			incxs = incx;
			i__5 = ly;
			for (i__ = 1; i__ <= i__5; ++i__) {
			    i__6 = i__;
			    i__7 = i__;
			    ys[i__6].r = yy[i__7].r, ys[i__6].i = yy[i__7].i;
/* L30: */
			}
			incys = incy;

/*                    Call the subroutine. */

			if (*trace) {
/*
					sprintf(ntra,"%6d: %12s (%3d, %3d, (%4.1f,%4.1f), X, %3d,  Y, %3d, A, %3d).\n",
						nc, sname, m, n, alpha.r, alpha.i, incx, incy, lda);
*/
			}
			if (isconj) {
			    if (*rewi) {
/*				al__1.aerr = 0;
				al__1.aunit = *ntra;
				f_rew(&al__1);*/
			    }
			    czgerc_(iorder, &m, &n, &alpha, &xx[1], &incx, &
				    yy[1], &incy, &aa[1], &lda);
			} else {
			    if (*rewi) {
/*				al__1.aerr = 0;
				al__1.aunit = *ntra;
				f_rew(&al__1);*/
			    }
			    czgeru_(iorder, &m, &n, &alpha, &xx[1], &incx, &
				    yy[1], &incy, &aa[1], &lda);
			}

/*                    Check if error-exit was taken incorrectly. */

			if (! infoc_1.ok) {
			    printf("******* FATAL ERROR - ERROR-EXIT TAKEN ON VALID CALL *******\n");
			    *fatal = TRUE_;
			    goto L140;
			}

/*                    See what data changed inside subroutine. */

			isame[0] = ms == m;
			isame[1] = ns == n;
			isame[2] = als.r == alpha.r && als.i == alpha.i;
			isame[3] = lze_(&xs[1], &xx[1], &lx);
			isame[4] = incxs == incx;
			isame[5] = lze_(&ys[1], &yy[1], &ly);
			isame[6] = incys == incy;
			if (null) {
			    isame[7] = lze_(&as[1], &aa[1], &laa);
			} else {
			    isame[7] = lzeres_("ge", " ", &m, &n, &as[1], &aa[
				    1], &lda, (ftnlen)2, (ftnlen)1);
			}
			isame[8] = ldas == lda;

/*                   If data was incorrectly changed, report and return. */

			same = TRUE_;
			i__5 = nargs;
			for (i__ = 1; i__ <= i__5; ++i__) {
			    same = same && isame[i__ - 1];
			    if (! isame[i__ - 1]) {
				printf(" ******* FATAL ERROR - PARAMETER NUMBER %2d WAS CHANGED INCORRECTLY *******\n",i__);
			    }
/* L40: */
			}
			if (! same) {
			    *fatal = TRUE_;
			    goto L140;
			}

			if (! null) {

/*                       Check the result column by column. */

			    if (incx > 0) {
				i__5 = m;
				for (i__ = 1; i__ <= i__5; ++i__) {
				    i__6 = i__;
				    i__7 = i__;
				    z__[i__6].r = x[i__7].r, z__[i__6].i = x[
					    i__7].i;
/* L50: */
				}
			    } else {
				i__5 = m;
				for (i__ = 1; i__ <= i__5; ++i__) {
				    i__6 = i__;
				    i__7 = m - i__ + 1;
				    z__[i__6].r = x[i__7].r, z__[i__6].i = x[
					    i__7].i;
/* L60: */
				}
			    }
			    i__5 = n;
			    for (j = 1; j <= i__5; ++j) {
				if (incy > 0) {
				    i__6 = j;
				    w[0].r = y[i__6].r, w[0].i = y[i__6].i;
				} else {
				    i__6 = n - j + 1;
				    w[0].r = y[i__6].r, w[0].i = y[i__6].i;
				}
				if (isconj) {
				    d_cnjg(&z__1, w);
				    w[0].r = z__1.r; w[0].i = z__1.i;
				}
				zmvch_("N", &m, &c__1, &alpha, &z__[1], nmax, 
					w, &c__1, &c_b2, &a[j * a_dim1 + 1], &
					c__1, &yt[1], &g[1], &aa[(j - 1) * 
					lda + 1], eps, &err, fatal, nout, &
					c_true, (ftnlen)1);
				errmax = f2cmax(errmax,err);
/*                          If got really bad answer, report and return. */
				if (*fatal) {
				    goto L130;
				}
/* L70: */
			    }
			} else {
/*                       Avoid repeating tests with M.le.0 or N.le.0. */
			    goto L110;
			}

/* L80: */
		    }

/* L90: */
		}

/* L100: */
	    }

L110:
	    ;
	}

/* L120: */
    }

/*     Report result. */

    if (errmax < *thresh) {
        printf("%12s PASSED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
    } else {
        printf("%12s COMPLETED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
        printf("******* BUT WITH MAXIMUM TEST RATIO %8.2f - SUSPECT *******\n",errmax);
    }
    goto L150;

L130:
    printf("      THESE ARE THE RESULTS FOR COLUMN %3d\n",j);

L140:
    printf("******* %12s FAILED ON CALL NUMBER:\n",sname);
    printf("%6d: %12s (%3d, %3d, (%4.1f,%4.1f), X, %3d,  Y, %3d, A, %3d).\n",
	nc, sname, m, n, alpha.r, alpha.i, incx, incy, lda);

L150:
    return 0;


/*     End of ZCHK4. */

} /* zchk4_ */

/* Subroutine */ int zchk5_(sname, eps, thresh, nout, ntra, trace, rewi, 
	fatal, nidim, idim, nalf, alf, ninc, inc, nmax, incmax, a, aa, as, x, 
	xx, xs, y, yy, ys, yt, g, z__, iorder, sname_len)
char *sname;
doublereal *eps, *thresh;
integer *nout, *ntra;
logical *trace, *rewi, *fatal;
integer *nidim, *idim, *nalf;
doublecomplex *alf;
integer *ninc, *inc, *nmax, *incmax;
doublecomplex *a, *aa, *as, *x, *xx, *xs, *y, *yy, *ys, *yt;
doublereal *g;
doublecomplex *z__;
integer *iorder;
ftnlen sname_len;
{
    /* Initialized data */

    static char ich[2+1] = "UL";

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5, i__6;
    doublecomplex z__1;

    /* Local variables */
    static integer ldas;
    static logical same;
    static doublereal rals;
    static integer incx;
    static logical full, null;
    static char uplo[1];
    static integer i__, j, n;
    static doublecomplex alpha, w[1];
    static logical isame[13];
    extern /* Subroutine */ int zmake_();
    static integer nargs;
    extern /* Subroutine */ int czher_();
    static logical reset;
    static char cuplo[14];
    static integer incxs;
    extern /* Subroutine */ int czhpr_(), zmvch_();
    static logical upper;
    static char uplos[1];
    static integer ia, ja, ic, nc, jj, lj, in;
    static logical packed;
    static integer ix, ns, lx;
    static doublereal ralpha, errmax;
    static doublecomplex transl;
    extern logical lzeres_();
    static integer laa, lda;
    static doublereal err;
    extern logical lze_();

/*  Tests ZHER and ZHPR. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Parameters .. */
/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. Local Arrays .. */
/*     .. External Functions .. */
/*     .. External Subroutines .. */
/*     .. Intrinsic Functions .. */
/*     .. Scalars in Common .. */
/*     .. Common blocks .. */
/*     .. Data statements .. */
    /* Parameter adjustments */
    --idim;
    --alf;
    --inc;
    --z__;
    --g;
    --yt;
    --y;
    --x;
    --as;
    --aa;
    a_dim1 = *nmax;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ys;
    --yy;
    --xs;
    --xx;

    /* Function Body */
/*     .. Executable Statements .. */
    full = *(unsigned char *)&sname[8] == 'e';
    packed = *(unsigned char *)&sname[8] == 'p';
/*     Define the number of arguments. */
    if (full) {
	nargs = 7;
    } else if (packed) {
	nargs = 6;
    }

    nc = 0;
    reset = TRUE_;
    errmax = 0.;

    i__1 = *nidim;
    for (in = 1; in <= i__1; ++in) {
	n = idim[in];
/*        Set LDA to 1 more than minimum value if room. */
	lda = n;
	if (lda < *nmax) {
	    ++lda;
	}
/*        Skip tests if not enough room. */
	if (lda > *nmax) {
	    goto L100;
	}
	if (packed) {
	    laa = n * (n + 1) / 2;
	} else {
	    laa = lda * n;
	}

	for (ic = 1; ic <= 2; ++ic) {
	    *(unsigned char *)uplo = *(unsigned char *)&ich[ic - 1];
	    if (*(unsigned char *)uplo == 'U') {
		s_copy(cuplo, "    CblasUpper", (ftnlen)14, (ftnlen)14);
	    } else {
		s_copy(cuplo, "    CblasLower", (ftnlen)14, (ftnlen)14);
	    }
	    upper = *(unsigned char *)uplo == 'U';

	    i__2 = *ninc;
	    for (ix = 1; ix <= i__2; ++ix) {
		incx = inc[ix];
		lx = abs(incx) * n;

/*              Generate the vector X. */

		transl.r = .5, transl.i = 0.;
		i__3 = abs(incx);
		i__4 = n - 1;
		zmake_("ge", " ", " ", &c__1, &n, &x[1], &c__1, &xx[1], &i__3,
			 &c__0, &i__4, &reset, &transl, (ftnlen)2, (ftnlen)1, 
			(ftnlen)1);
		if (n > 1) {
		    i__3 = n / 2;
		    x[i__3].r = 0., x[i__3].i = 0.;
		    i__3 = abs(incx) * (n / 2 - 1) + 1;
		    xx[i__3].r = 0., xx[i__3].i = 0.;
		}

		i__3 = *nalf;
		for (ia = 1; ia <= i__3; ++ia) {
		    i__4 = ia;
		    ralpha = alf[i__4].r;
		    z__1.r = ralpha, z__1.i = 0.;
		    alpha.r = z__1.r, alpha.i = z__1.i;
		    null = n <= 0 || ralpha == 0.;

/*                 Generate the matrix A. */

		    transl.r = 0., transl.i = 0.;
		    i__4 = n - 1;
		    i__5 = n - 1;
		    zmake_(sname + 7, uplo, " ", &n, &n, &a[a_offset], nmax, &
			    aa[1], &lda, &i__4, &i__5, &reset, &transl, (
			    ftnlen)2, (ftnlen)1, (ftnlen)1);

		    ++nc;

/*                 Save every datum before calling the subroutine. */

		    *(unsigned char *)uplos = *(unsigned char *)uplo;
		    ns = n;
		    rals = ralpha;
		    i__4 = laa;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			i__5 = i__;
			i__6 = i__;
			as[i__5].r = aa[i__6].r, as[i__5].i = aa[i__6].i;
/* L10: */
		    }
		    ldas = lda;
		    i__4 = lx;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			i__5 = i__;
			i__6 = i__;
			xs[i__5].r = xx[i__6].r, xs[i__5].i = xx[i__6].i;
/* L20: */
		    }
		    incxs = incx;

/*                 Call the subroutine. */

		    if (full) {
			if (*trace) {
/*
			   sprintf(ntra,"%6d: %12s (%14s, %3d, %4.1f, X, %2d,  A, %3d).\n",
					nc, sname, cuplo, n, ralpha, incx, lda);
*/
			}
			if (*rewi) {
/*			    al__1.aerr = 0;
			    al__1.aunit = *ntra;
			    f_rew(&al__1);*/
			}
			czher_(iorder, uplo, &n, &ralpha, &xx[1], &incx, &aa[
				1], &lda, (ftnlen)1);
		    } else if (packed) {
			if (*trace) {
/*
			   sprintf(ntra,"%6d: %12s (%14s, %3d, %4.1f, X, %2d,  AP).\n",
					nc, sname, cuplo, n, ralpha, incx);
*/
			}
			if (*rewi) {
/*			    al__1.aerr = 0;
			    al__1.aunit = *ntra;
			    f_rew(&al__1);*/
			}
			czhpr_(iorder, uplo, &n, &ralpha, &xx[1], &incx, &aa[
				1], (ftnlen)1);
		    }

/*                 Check if error-exit was taken incorrectly. */

		    if (! infoc_1.ok) {
			printf("******* FATAL ERROR - ERROR-EXIT TAKEN ON VALID CALL *******\n");
			*fatal = TRUE_;
			goto L120;
		    }

/*                 See what data changed inside subroutines. */

		    isame[0] = *(unsigned char *)uplo == *(unsigned char *)
			    uplos;
		    isame[1] = ns == n;
		    isame[2] = rals == ralpha;
		    isame[3] = lze_(&xs[1], &xx[1], &lx);
		    isame[4] = incxs == incx;
		    if (null) {
			isame[5] = lze_(&as[1], &aa[1], &laa);
		    } else {
			isame[5] = lzeres_(sname + 7, uplo, &n, &n, &as[1], &
				aa[1], &lda, (ftnlen)2, (ftnlen)1);
		    }
		    if (! packed) {
			isame[6] = ldas == lda;
		    }

/*                 If data was incorrectly changed, report and return. */

		    same = TRUE_;
		    i__4 = nargs;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			same = same && isame[i__ - 1];
			if (! isame[i__ - 1]) {
			    printf(" ******* FATAL ERROR - PARAMETER NUMBER %2d WAS CHANGED INCORRECTLY *******\n",i__);
			}
/* L30: */
		    }
		    if (! same) {
			*fatal = TRUE_;
			goto L120;
		    }

		    if (! null) {

/*                    Check the result column by column. */

			if (incx > 0) {
			    i__4 = n;
			    for (i__ = 1; i__ <= i__4; ++i__) {
				i__5 = i__;
				i__6 = i__;
				z__[i__5].r = x[i__6].r, z__[i__5].i = x[i__6]
					.i;
/* L40: */
			    }
			} else {
			    i__4 = n;
			    for (i__ = 1; i__ <= i__4; ++i__) {
				i__5 = i__;
				i__6 = n - i__ + 1;
				z__[i__5].r = x[i__6].r, z__[i__5].i = x[i__6]
					.i;
/* L50: */
			    }
			}
			ja = 1;
			i__4 = n;
			for (j = 1; j <= i__4; ++j) {
			    d_cnjg(&z__1, &z__[j]);
			    w[0].r = z__1.r, w[0].i = z__1.i;
			    if (upper) {
				jj = 1;
				lj = j;
			    } else {
				jj = j;
				lj = n - j + 1;
			    }
			    zmvch_("N", &lj, &c__1, &alpha, &z__[jj], &lj, w, 
				    &c__1, &c_b2, &a[jj + j * a_dim1], &c__1, 
				    &yt[1], &g[1], &aa[ja], eps, &err, fatal, 
				    nout, &c_true, (ftnlen)1);
			    if (full) {
				if (upper) {
				    ja += lda;
				} else {
				    ja = ja + lda + 1;
				}
			    } else {
				ja += lj;
			    }
			    errmax = f2cmax(errmax,err);
/*                       If got really bad answer, report and return. */
			    if (*fatal) {
				goto L110;
			    }
/* L60: */
			}
		    } else {
/*                    Avoid repeating tests if N.le.0. */
			if (n <= 0) {
			    goto L100;
			}
		    }

/* L70: */
		}

/* L80: */
	    }

/* L90: */
	}

L100:
	;
    }

/*     Report result. */

    if (errmax < *thresh) {
        printf("%12s PASSED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
    } else {
        printf("%12s COMPLETED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
        printf("******* BUT WITH MAXIMUM TEST RATIO %8.2f - SUSPECT *******\n",errmax);
    }
    goto L130;

L110:
    printf("      THESE ARE THE RESULTS FOR COLUMN %3d\n",j);

L120:
    printf("******* %12s FAILED ON CALL NUMBER:\n",sname);
    if (full) {
	printf("%6d: %12s (%14s, %3d, %4.1f, X, %2d,  A, %3d).\n",
		nc, sname, cuplo, n, ralpha, incx, lda);
    } else if (packed) {
	printf("%6d: %12s (%14s, %3d, %4.1f, X, %2d,  AP).\n",
		nc, sname, cuplo, n, ralpha, incx);
    }

L130:
    return 0;


/*     End of CZHK5. */

} /* zchk5_ */

/* Subroutine */ int zchk6_(sname, eps, thresh, nout, ntra, trace, rewi, 
	fatal, nidim, idim, nalf, alf, ninc, inc, nmax, incmax, a, aa, as, x, 
	xx, xs, y, yy, ys, yt, g, z__, iorder, sname_len)
char *sname;
doublereal *eps, *thresh;
integer *nout, *ntra;
logical *trace, *rewi, *fatal;
integer *nidim, *idim, *nalf;
doublecomplex *alf;
integer *ninc, *inc, *nmax, *incmax;
doublecomplex *a, *aa, *as, *x, *xx, *xs, *y, *yy, *ys, *yt;
doublereal *g;
doublecomplex *z__;
integer *iorder;
ftnlen sname_len;
{
    /* Initialized data */

    static char ich[2+1] = "UL";

    /* System generated locals */
    integer a_dim1, a_offset, z_dim1, z_offset, i__1, i__2, i__3, i__4, i__5, 
	    i__6, i__7;
    doublecomplex z__1, z__2, z__3;

    /* Local variables */
    static integer ldas;
    static logical same;
    static integer incx, incy;
    static logical full, null;
    static char uplo[1];
    static integer i__, j, n;
    static doublecomplex alpha, w[2];
    static logical isame[13];
    extern /* Subroutine */ int zmake_();
    static integer nargs;
    static logical reset;
    static char cuplo[14];
    static integer incxs, incys;
    extern /* Subroutine */ int zmvch_();
    static logical upper;
    static char uplos[1];
    extern /* Subroutine */ int czher2_(), czhpr2_();
    static integer ia, ja, ic, nc, jj, lj, in;
    static logical packed;
    static integer ix, iy, ns, lx, ly;
    static doublereal errmax;
    static doublecomplex transl;
    extern logical lzeres_();
    static integer laa, lda;
    static doublecomplex als;
    static doublereal err;
    extern logical lze_();

/*  Tests ZHER2 and ZHPR2. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Parameters .. */
/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. Local Arrays .. */
/*     .. External Functions .. */
/*     .. External Subroutines .. */
/*     .. Intrinsic Functions .. */
/*     .. Scalars in Common .. */
/*     .. Common blocks .. */
/*     .. Data statements .. */
    /* Parameter adjustments */
    --idim;
    --alf;
    --inc;
    z_dim1 = *nmax;
    z_offset = 1 + z_dim1 * 1;
    z__ -= z_offset;
    --g;
    --yt;
    --y;
    --x;
    --as;
    --aa;
    a_dim1 = *nmax;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ys;
    --yy;
    --xs;
    --xx;

    /* Function Body */
/*     .. Executable Statements .. */
    full = *(unsigned char *)&sname[8] == 'e';
    packed = *(unsigned char *)&sname[8] == 'p';
/*     Define the number of arguments. */
    if (full) {
	nargs = 9;
    } else if (packed) {
	nargs = 8;
    }

    nc = 0;
    reset = TRUE_;
    errmax = 0.;

    i__1 = *nidim;
    for (in = 1; in <= i__1; ++in) {
	n = idim[in];
/*        Set LDA to 1 more than minimum value if room. */
	lda = n;
	if (lda < *nmax) {
	    ++lda;
	}
/*        Skip tests if not enough room. */
	if (lda > *nmax) {
	    goto L140;
	}
	if (packed) {
	    laa = n * (n + 1) / 2;
	} else {
	    laa = lda * n;
	}

	for (ic = 1; ic <= 2; ++ic) {
	    *(unsigned char *)uplo = *(unsigned char *)&ich[ic - 1];
	    if (*(unsigned char *)uplo == 'U') {
		s_copy(cuplo, "    CblasUpper", (ftnlen)14, (ftnlen)14);
	    } else {
		s_copy(cuplo, "    CblasLower", (ftnlen)14, (ftnlen)14);
	    }
	    upper = *(unsigned char *)uplo == 'U';

	    i__2 = *ninc;
	    for (ix = 1; ix <= i__2; ++ix) {
		incx = inc[ix];
		lx = abs(incx) * n;

/*              Generate the vector X. */

		transl.r = .5, transl.i = 0.;
		i__3 = abs(incx);
		i__4 = n - 1;
		zmake_("ge", " ", " ", &c__1, &n, &x[1], &c__1, &xx[1], &i__3,
			 &c__0, &i__4, &reset, &transl, (ftnlen)2, (ftnlen)1, 
			(ftnlen)1);
		if (n > 1) {
		    i__3 = n / 2;
		    x[i__3].r = 0., x[i__3].i = 0.;
		    i__3 = abs(incx) * (n / 2 - 1) + 1;
		    xx[i__3].r = 0., xx[i__3].i = 0.;
		}

		i__3 = *ninc;
		for (iy = 1; iy <= i__3; ++iy) {
		    incy = inc[iy];
		    ly = abs(incy) * n;

/*                 Generate the vector Y. */

		    transl.r = 0., transl.i = 0.;
		    i__4 = abs(incy);
		    i__5 = n - 1;
		    zmake_("ge", " ", " ", &c__1, &n, &y[1], &c__1, &yy[1], &
			    i__4, &c__0, &i__5, &reset, &transl, (ftnlen)2, (
			    ftnlen)1, (ftnlen)1);
		    if (n > 1) {
			i__4 = n / 2;
			y[i__4].r = 0., y[i__4].i = 0.;
			i__4 = abs(incy) * (n / 2 - 1) + 1;
			yy[i__4].r = 0., yy[i__4].i = 0.;
		    }

		    i__4 = *nalf;
		    for (ia = 1; ia <= i__4; ++ia) {
			i__5 = ia;
			alpha.r = alf[i__5].r, alpha.i = alf[i__5].i;
			null = n <= 0 || (alpha.r == 0. && alpha.i == 0.);

/*                    Generate the matrix A. */

			transl.r = 0., transl.i = 0.;
			i__5 = n - 1;
			i__6 = n - 1;
			zmake_(sname + 7, uplo, " ", &n, &n, &a[a_offset], 
				nmax, &aa[1], &lda, &i__5, &i__6, &reset, &
				transl, (ftnlen)2, (ftnlen)1, (ftnlen)1);

			++nc;

/*                    Save every datum before calling the subroutine. */

			*(unsigned char *)uplos = *(unsigned char *)uplo;
			ns = n;
			als.r = alpha.r, als.i = alpha.i;
			i__5 = laa;
			for (i__ = 1; i__ <= i__5; ++i__) {
			    i__6 = i__;
			    i__7 = i__;
			    as[i__6].r = aa[i__7].r, as[i__6].i = aa[i__7].i;
/* L10: */
			}
			ldas = lda;
			i__5 = lx;
			for (i__ = 1; i__ <= i__5; ++i__) {
			    i__6 = i__;
			    i__7 = i__;
			    xs[i__6].r = xx[i__7].r, xs[i__6].i = xx[i__7].i;
/* L20: */
			}
			incxs = incx;
			i__5 = ly;
			for (i__ = 1; i__ <= i__5; ++i__) {
			    i__6 = i__;
			    i__7 = i__;
			    ys[i__6].r = yy[i__7].r, ys[i__6].i = yy[i__7].i;
/* L30: */
			}
			incys = incy;

/*                    Call the subroutine. */

			if (full) {
			    if (*trace) {
/*
				sprintf(ntra,"%6d: %12s (%14s, %3d, (%4.1f,%4.1f), X, %2d, Y, %2d,  A, %3d).\n",
					nc, sname, cuplo, n, alpha.r,alpha.i, incx, incy, lda);
*/
			    }
			    if (*rewi) {
/*				al__1.aerr = 0;
				al__1.aunit = *ntra;
				f_rew(&al__1);*/
			    }
			    czher2_(iorder, uplo, &n, &alpha, &xx[1], &incx, &
				    yy[1], &incy, &aa[1], &lda, (ftnlen)1);
			} else if (packed) {
			    if (*trace) {
/*
				sprintf(ntra,"%6d: %12s (%14s, %3d, (%4.1f,%4.1f), X, %2d, Y, %2d,  AP).\n",
					nc, sname, cuplo, n, alpha.r,alpha.i, incx, incy;
*/
			    }
			    if (*rewi) {
/*				al__1.aerr = 0;
				al__1.aunit = *ntra;
				f_rew(&al__1);*/
			    }
			    czhpr2_(iorder, uplo, &n, &alpha, &xx[1], &incx, &
				    yy[1], &incy, &aa[1], (ftnlen)1);
			}

/*                    Check if error-exit was taken incorrectly. */

			if (! infoc_1.ok) {
			    printf("******* FATAL ERROR - ERROR-EXIT TAKEN ON VALID CALL *******\n");
			    *fatal = TRUE_;
			    goto L160;
			}

/*                    See what data changed inside subroutines. */

			isame[0] = *(unsigned char *)uplo == *(unsigned char *
				)uplos;
			isame[1] = ns == n;
			isame[2] = als.r == alpha.r && als.i == alpha.i;
			isame[3] = lze_(&xs[1], &xx[1], &lx);
			isame[4] = incxs == incx;
			isame[5] = lze_(&ys[1], &yy[1], &ly);
			isame[6] = incys == incy;
			if (null) {
			    isame[7] = lze_(&as[1], &aa[1], &laa);
			} else {
			    isame[7] = lzeres_(sname + 7, uplo, &n, &n, &as[1]
				    , &aa[1], &lda, (ftnlen)2, (ftnlen)1);
			}
			if (! packed) {
			    isame[8] = ldas == lda;
			}

/*                   If data was incorrectly changed, report and return. */

			same = TRUE_;
			i__5 = nargs;
			for (i__ = 1; i__ <= i__5; ++i__) {
			    same = same && isame[i__ - 1];
			    if (! isame[i__ - 1]) {
			        printf(" ******* FATAL ERROR - PARAMETER NUMBER %2d WAS CHANGED INCORRECTLY *******\n",i__);
			    }
/* L40: */
			}
			if (! same) {
			    *fatal = TRUE_;
			    goto L160;
			}

			if (! null) {

/*                       Check the result column by column. */

			    if (incx > 0) {
				i__5 = n;
				for (i__ = 1; i__ <= i__5; ++i__) {
				    i__6 = i__ + z_dim1;
				    i__7 = i__;
				    z__[i__6].r = x[i__7].r, z__[i__6].i = x[
					    i__7].i;
/* L50: */
				}
			    } else {
				i__5 = n;
				for (i__ = 1; i__ <= i__5; ++i__) {
				    i__6 = i__ + z_dim1;
				    i__7 = n - i__ + 1;
				    z__[i__6].r = x[i__7].r, z__[i__6].i = x[
					    i__7].i;
/* L60: */
				}
			    }
			    if (incy > 0) {
				i__5 = n;
				for (i__ = 1; i__ <= i__5; ++i__) {
				    i__6 = i__ + (z_dim1 << 1);
				    i__7 = i__;
				    z__[i__6].r = y[i__7].r, z__[i__6].i = y[
					    i__7].i;
/* L70: */
				}
			    } else {
				i__5 = n;
				for (i__ = 1; i__ <= i__5; ++i__) {
				    i__6 = i__ + (z_dim1 << 1);
				    i__7 = n - i__ + 1;
				    z__[i__6].r = y[i__7].r, z__[i__6].i = y[
					    i__7].i;
/* L80: */
				}
			    }
			    ja = 1;
			    i__5 = n;
			    for (j = 1; j <= i__5; ++j) {
				d_cnjg(&z__2, &z__[j + (z_dim1 << 1)]);
				z__1.r = alpha.r * z__2.r - alpha.i * z__2.i, 
					z__1.i = alpha.r * z__2.i + alpha.i * 
					z__2.r;
				w[0].r = z__1.r, w[0].i = z__1.i;
				d_cnjg(&z__2, &alpha);
				d_cnjg(&z__3, &z__[j + z_dim1]);
				z__1.r = z__2.r * z__3.r - z__2.i * z__3.i, 
					z__1.i = z__2.r * z__3.i + z__2.i * 
					z__3.r;
				w[1].r = z__1.r, w[1].i = z__1.i;
				if (upper) {
				    jj = 1;
				    lj = j;
				} else {
				    jj = j;
				    lj = n - j + 1;
				}
				zmvch_("N", &lj, &c__2, &c_b2, &z__[jj + 
					z_dim1], nmax, w, &c__1, &c_b2, &a[jj 
					+ j * a_dim1], &c__1, &yt[1], &g[1], &
					aa[ja], eps, &err, fatal, nout, &
					c_true, (ftnlen)1);
				if (full) {
				    if (upper) {
					ja += lda;
				    } else {
					ja = ja + lda + 1;
				    }
				} else {
				    ja += lj;
				}
				errmax = f2cmax(errmax,err);
/*                          If got really bad answer, report and return. */
				if (*fatal) {
				    goto L150;
				}
/* L90: */
			    }
			} else {
/*                       Avoid repeating tests with N.le.0. */
			    if (n <= 0) {
				goto L140;
			    }
			}

/* L100: */
		    }

/* L110: */
		}

/* L120: */
	    }

/* L130: */
	}

L140:
	;
    }

/*     Report result. */

    if (errmax < *thresh) {
        printf("%12s PASSED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
    } else {
        printf("%12s COMPLETED THE COMPUTATIONAL TESTS (%6d CALLS)\n",sname,nc);
        printf("******* BUT WITH MAXIMUM TEST RATIO %8.2f - SUSPECT *******\n",errmax);
    }
    goto L170;

L150:
    printf("      THESE ARE THE RESULTS FOR COLUMN %3d\n",j);

L160:
    printf("******* %12s FAILED ON CALL NUMBER:\n",sname);
    if (full) {
	printf("%6d: %12s (%14s, %3d, (%4.1f,%4.1f), X, %2d, Y, %2d,  A, %3d).\n",
		nc, sname, cuplo, n, alpha.r,alpha.i, incx, incy,lda);
    } else if (packed) {
	printf("%6d: %12s (%14s, %3d, (%4.1f,%4.1f), X, %2d, Y, %2d,  AP).\n",
		nc, sname, cuplo, n, alpha.r,alpha.i, incx, incy);
    }

L170:
    return 0;


/*     End of ZCHK6. */

} /* zchk6_ */

/* Subroutine */ int zmvch_(trans, m, n, alpha, a, nmax, x, incx, beta, y, 
	incy, yt, g, yy, eps, err, fatal, nout, mv, trans_len)
char *trans;
integer *m, *n;
doublecomplex *alpha, *a;
integer *nmax;
doublecomplex *x;
integer *incx;
doublecomplex *beta, *y;
integer *incy;
doublecomplex *yt;
doublereal *g;
doublecomplex *yy;
doublereal *eps, *err;
logical *fatal;
integer *nout;
logical *mv;
ftnlen trans_len;
{

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5, i__6;
    doublereal d__1, d__2, d__3, d__4, d__5, d__6;
    doublecomplex z__1, z__2, z__3;

    /* Local variables */
    static doublereal erri;
    static logical tran;
    static integer i__, j;
    static logical ctran;
    static integer incxl, incyl, ml, nl, iy, jx, kx, ky;

/*  Checks the results of the computational tests. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Parameters .. */
/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. Intrinsic Functions .. */
/*     .. Statement Functions .. */
/*     .. Statement Function definitions .. */
/*     .. Executable Statements .. */
    /* Parameter adjustments */
    a_dim1 = *nmax;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --x;
    --y;
    --yt;
    --g;
    --yy;

    /* Function Body */
    tran = *(unsigned char *)trans == 'T';
    ctran = *(unsigned char *)trans == 'C';
    if (tran || ctran) {
	ml = *n;
	nl = *m;
    } else {
	ml = *m;
	nl = *n;
    }
    if (*incx < 0) {
	kx = nl;
	incxl = -1;
    } else {
	kx = 1;
	incxl = 1;
    }
    if (*incy < 0) {
	ky = ml;
	incyl = -1;
    } else {
	ky = 1;
	incyl = 1;
    }

/*     Compute expected result in YT using data in A, X and Y. */
/*     Compute gauges in G. */

    iy = ky;
    i__1 = ml;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = iy;
	yt[i__2].r = 0., yt[i__2].i = 0.;
	g[iy] = 0.;
	jx = kx;
	if (tran) {
	    i__2 = nl;
	    for (j = 1; j <= i__2; ++j) {
		i__3 = iy;
		i__4 = iy;
		i__5 = j + i__ * a_dim1;
		i__6 = jx;
		z__2.r = a[i__5].r * x[i__6].r - a[i__5].i * x[i__6].i, 
			z__2.i = a[i__5].r * x[i__6].i + a[i__5].i * x[i__6]
			.r;
		z__1.r = yt[i__4].r + z__2.r, z__1.i = yt[i__4].i + z__2.i;
		yt[i__3].r = z__1.r, yt[i__3].i = z__1.i;
		i__3 = j + i__ * a_dim1;
		i__4 = jx;
		g[iy] += ((d__1 = a[i__3].r, abs(d__1)) + (d__2 = d_imag(&a[j 
			+ i__ * a_dim1]), abs(d__2))) * ((d__3 = x[i__4].r, 
			abs(d__3)) + (d__4 = d_imag(&x[jx]), abs(d__4)));
		jx += incxl;
/* L10: */
	    }
	} else if (ctran) {
	    i__2 = nl;
	    for (j = 1; j <= i__2; ++j) {
		i__3 = iy;
		i__4 = iy;
		d_cnjg(&z__3, &a[j + i__ * a_dim1]);
		i__5 = jx;
		z__2.r = z__3.r * x[i__5].r - z__3.i * x[i__5].i, z__2.i = 
			z__3.r * x[i__5].i + z__3.i * x[i__5].r;
		z__1.r = yt[i__4].r + z__2.r, z__1.i = yt[i__4].i + z__2.i;
		yt[i__3].r = z__1.r, yt[i__3].i = z__1.i;
		i__3 = j + i__ * a_dim1;
		i__4 = jx;
		g[iy] += ((d__1 = a[i__3].r, abs(d__1)) + (d__2 = d_imag(&a[j 
			+ i__ * a_dim1]), abs(d__2))) * ((d__3 = x[i__4].r, 
			abs(d__3)) + (d__4 = d_imag(&x[jx]), abs(d__4)));
		jx += incxl;
/* L20: */
	    }
	} else {
	    i__2 = nl;
	    for (j = 1; j <= i__2; ++j) {
		i__3 = iy;
		i__4 = iy;
		i__5 = i__ + j * a_dim1;
		i__6 = jx;
		z__2.r = a[i__5].r * x[i__6].r - a[i__5].i * x[i__6].i, 
			z__2.i = a[i__5].r * x[i__6].i + a[i__5].i * x[i__6]
			.r;
		z__1.r = yt[i__4].r + z__2.r, z__1.i = yt[i__4].i + z__2.i;
		yt[i__3].r = z__1.r, yt[i__3].i = z__1.i;
		i__3 = i__ + j * a_dim1;
		i__4 = jx;
		g[iy] += ((d__1 = a[i__3].r, abs(d__1)) + (d__2 = d_imag(&a[
			i__ + j * a_dim1]), abs(d__2))) * ((d__3 = x[i__4].r, 
			abs(d__3)) + (d__4 = d_imag(&x[jx]), abs(d__4)));
		jx += incxl;
/* L30: */
	    }
	}
	i__2 = iy;
	i__3 = iy;
	z__2.r = alpha->r * yt[i__3].r - alpha->i * yt[i__3].i, z__2.i = 
		alpha->r * yt[i__3].i + alpha->i * yt[i__3].r;
	i__4 = iy;
	z__3.r = beta->r * y[i__4].r - beta->i * y[i__4].i, z__3.i = beta->r *
		 y[i__4].i + beta->i * y[i__4].r;
	z__1.r = z__2.r + z__3.r, z__1.i = z__2.i + z__3.i;
	yt[i__2].r = z__1.r, yt[i__2].i = z__1.i;
	i__2 = iy;
	g[iy] = ((d__1 = alpha->r, abs(d__1)) + (d__2 = d_imag(alpha), abs(
		d__2))) * g[iy] + ((d__3 = beta->r, abs(d__3)) + (d__4 = 
		d_imag(beta), abs(d__4))) * ((d__5 = y[i__2].r, abs(d__5)) + (
		d__6 = d_imag(&y[iy]), abs(d__6)));
	iy += incyl;
/* L40: */
    }

/*     Compute the error ratio for this result. */

    *err = 0.;
    i__1 = ml;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	i__3 = (i__ - 1) * abs(*incy) + 1;
	z__1.r = yt[i__2].r - yy[i__3].r, z__1.i = yt[i__2].i - yy[i__3].i;
	erri = z_abs(&z__1) / *eps;
	if (g[i__] != 0.) {
	    erri /= g[i__];
	}
	*err = f2cmax(*err,erri);
	if (*err * sqrt(*eps) >= 1.) {
	    goto L60;
	}
/* L50: */
    }
/*     If the loop completes, all results are at least half accurate. */
    goto L80;

/*     Report fatal error. */

L60:
    *fatal = TRUE_;
    printf(" ******* FATAL ERROR - COMPUTED RESULT IS LESS THAN HALF ACCURATE *******\n                       EXPECTED RESULT                    COMPUTED RESULT\n");
    i__1 = ml;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (*mv) {
	    printf("%7d    (%15.6g,%15.6g)       (%15.6g,%15.6g)\n",i__,yt[i__].r,yt[i__].i, yy[(i__ - 1) * abs(*incy) + 1].r, yy[(i__ - 1) * abs(*incy) + 1].i);
	} else {
	    printf("%7d    (%15.6g,%15.6g)       (%15.6g,%15.6g),\n",i__, yy[(i__ - 1) * abs(*incy) + 1].r, yy[(i__ - 1) * abs(*incy) + 1].i, yt[i__].r,yt[i__].i); 
	}
/* L70: */
    }

L80:
    return 0;


/*     End of ZMVCH. */

} /* zmvch_ */

logical lze_(ri, rj, lr)
doublecomplex *ri, *rj;
integer *lr;
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    logical ret_val;

    /* Local variables */
    static integer i__;


/*  Tests if two arrays are identical. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. Executable Statements .. */
    /* Parameter adjustments */
    --rj;
    --ri;

    /* Function Body */
    i__1 = *lr;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	i__3 = i__;
	if (ri[i__2].r != rj[i__3].r || ri[i__2].i != rj[i__3].i) {
	    goto L20;
	}
/* L10: */
    }
    ret_val = TRUE_;
    goto L30;
L20:
    ret_val = FALSE_;
L30:
    return ret_val;

/*     End of LZE. */

} /* lze_ */

logical lzeres_(type__, uplo, m, n, aa, as, lda, type_len, uplo_len)
char *type__, *uplo;
integer *m, *n;
doublecomplex *aa, *as;
integer *lda;
ftnlen type_len;
ftnlen uplo_len;
{
    /* System generated locals */
    integer aa_dim1, aa_offset, as_dim1, as_offset, i__1, i__2, i__3, i__4;
    logical ret_val;

    /* Local variables */
    static integer ibeg, iend, i__, j;
    static logical upper;


/*  Tests if selected elements in two arrays are equal. */

/*  TYPE is 'ge', 'he' or 'hp'. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. Executable Statements .. */
    /* Parameter adjustments */
    as_dim1 = *lda;
    as_offset = 1 + as_dim1 * 1;
    as -= as_offset;
    aa_dim1 = *lda;
    aa_offset = 1 + aa_dim1 * 1;
    aa -= aa_offset;

    /* Function Body */
    upper = *(unsigned char *)uplo == 'U';
    if (s_cmp(type__, "ge", (ftnlen)2, (ftnlen)2) == 0) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *lda;
	    for (i__ = *m + 1; i__ <= i__2; ++i__) {
		i__3 = i__ + j * aa_dim1;
		i__4 = i__ + j * as_dim1;
		if (aa[i__3].r != as[i__4].r || aa[i__3].i != as[i__4].i) {
		    goto L70;
		}
/* L10: */
	    }
/* L20: */
	}
    } else if (s_cmp(type__, "he", (ftnlen)2, (ftnlen)2) == 0) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (upper) {
		ibeg = 1;
		iend = j;
	    } else {
		ibeg = j;
		iend = *n;
	    }
	    i__2 = ibeg - 1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = i__ + j * aa_dim1;
		i__4 = i__ + j * as_dim1;
		if (aa[i__3].r != as[i__4].r || aa[i__3].i != as[i__4].i) {
		    goto L70;
		}
/* L30: */
	    }
	    i__2 = *lda;
	    for (i__ = iend + 1; i__ <= i__2; ++i__) {
		i__3 = i__ + j * aa_dim1;
		i__4 = i__ + j * as_dim1;
		if (aa[i__3].r != as[i__4].r || aa[i__3].i != as[i__4].i) {
		    goto L70;
		}
/* L40: */
	    }
/* L50: */
	}
    }

/* L60: */
    ret_val = TRUE_;
    goto L80;
L70:
    ret_val = FALSE_;
L80:
    return ret_val;

/*     End of LZERES. */

} /* lzeres_ */

/* Double Complex */ VOID zbeg_( ret_val, reset)
doublecomplex * ret_val;
logical *reset;
{
    /* System generated locals */
    doublereal d__1, d__2;
    doublecomplex z__1;

    /* Local variables */
    static integer i__, j, ic, mi, mj;


/*  Generates complex numbers as pairs of random numbers uniformly */
/*  distributed between -0.5 and 0.5. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Scalar Arguments .. */
/*     .. Local Scalars .. */
/*     .. Save statement .. */
/*     .. Intrinsic Functions .. */
/*     .. Executable Statements .. */
    if (*reset) {
/*        Initialize local variables. */
	mi = 891;
	mj = 457;
	i__ = 7;
	j = 7;
	ic = 0;
	*reset = FALSE_;
    }

/*     The sequence of values of I or J is bounded between 1 and 999. */
/*     If initial I or J = 1,2,3,6,7 or 9, the period will be 50. */
/*     If initial I or J = 4 or 8, the period will be 25. */
/*     If initial I or J = 5, the period will be 10. */
/*     IC is used to break up the period by skipping 1 value of I or J */
/*     in 6. */

    ++ic;
L10:
    i__ *= mi;
    j *= mj;
    i__ -= i__ / 1000 * 1000;
    j -= j / 1000 * 1000;
    if (ic >= 5) {
	ic = 0;
	goto L10;
    }
    d__1 = (doublereal) ((i__ - 500) / (float)1001.);
    d__2 = (doublereal) ((j - 500) / (float)1001.);
    z__1.r = d__1, z__1.i = d__2;
     ret_val->r = z__1.r,  ret_val->i = z__1.i;
    return ;

/*     End of ZBEG. */

} /* zbeg_ */

doublereal ddiff_(x, y)
doublereal *x, *y;
{
    /* System generated locals */
    doublereal ret_val;


/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */

/*     .. Scalar Arguments .. */
/*     .. Executable Statements .. */
    ret_val = *x - *y;
    return ret_val;

/*     End of DDIFF. */

} /* ddiff_ */

/* Subroutine */ int zmake_(type__, uplo, diag, m, n, a, nmax, aa, lda, kl, 
	ku, reset, transl, type_len, uplo_len, diag_len)
char *type__, *uplo, *diag;
integer *m, *n;
doublecomplex *a;
integer *nmax;
doublecomplex *aa;
integer *lda, *kl, *ku;
logical *reset;
doublecomplex *transl;
ftnlen type_len;
ftnlen uplo_len;
ftnlen diag_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;
    doublereal d__1;
    doublecomplex z__1, z__2;

    /* Local variables */
    static integer ibeg, iend, ioff;
    extern /* Double Complex */ VOID zbeg_();
    static logical unit;
    static integer i__, j;
    static logical lower;
    static integer i1, i2, i3;
    static logical upper;
    static integer jj, kk;
    static logical gen, tri, sym;


/*  Generates values for an M by N matrix A within the bandwidth */
/*  defined by KL and KU. */
/*  Stores the values in the array AA in the data structure required */
/*  by the routine, with unwanted elements set to rogue value. */

/*  TYPE is 'ge', 'gb', 'he', 'hb', 'hp', 'tr', 'tb' OR 'tp'. */

/*  Auxiliary routine for test program for Level 2 Blas. */

/*  -- Written on 10-August-1987. */
/*     Richard Hanson, Sandia National Labs. */
/*     Jeremy Du Croz, NAG Central Office. */

/*     .. Parameters .. */
/*     .. Scalar Arguments .. */
/*     .. Array Arguments .. */
/*     .. Local Scalars .. */
/*     .. External Functions .. */
/*     .. Intrinsic Functions .. */
/*     .. Executable Statements .. */
    /* Parameter adjustments */
    a_dim1 = *nmax;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --aa;

    /* Function Body */
    gen = *(unsigned char *)type__ == 'g';
    sym = *(unsigned char *)type__ == 'h';
    tri = *(unsigned char *)type__ == 't';
    upper = (sym || tri) && *(unsigned char *)uplo == 'U';
    lower = (sym || tri) && *(unsigned char *)uplo == 'L';
    unit = tri && *(unsigned char *)diag == 'U';

/*     Generate data in array A. */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    if (gen || (upper && i__ <= j) || (lower && i__ >= j)) {
		if ((i__ <= j && j - i__ <= *ku )|| (i__ >= j && i__ - j <= *kl)) 
			{
		    i__3 = i__ + j * a_dim1;
		    zbeg_(&z__2, reset);
		    z__1.r = z__2.r + transl->r, z__1.i = z__2.i + transl->i;
		    a[i__3].r = z__1.r, a[i__3].i = z__1.i;
		} else {
		    i__3 = i__ + j * a_dim1;
		    a[i__3].r = 0., a[i__3].i = 0.;
		}
		if (i__ != j) {
		    if (sym) {
			i__3 = j + i__ * a_dim1;
			d_cnjg(&z__1, &a[i__ + j * a_dim1]);
			a[i__3].r = z__1.r, a[i__3].i = z__1.i;
		    } else if (tri) {
			i__3 = j + i__ * a_dim1;
			a[i__3].r = 0., a[i__3].i = 0.;
		    }
		}
	    }
/* L10: */
	}
	if (sym) {
	    i__2 = j + j * a_dim1;
	    i__3 = j + j * a_dim1;
	    d__1 = a[i__3].r;
	    z__1.r = d__1, z__1.i = 0.;
	    a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	}
	if (tri) {
	    i__2 = j + j * a_dim1;
	    i__3 = j + j * a_dim1;
	    z__1.r = a[i__3].r + 1., z__1.i = a[i__3].i + 0.;
	    a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	}
	if (unit) {
	    i__2 = j + j * a_dim1;
	    a[i__2].r = 1., a[i__2].i = 0.;
	}
/* L20: */
    }

/*     Store elements in array AS in data structure required by routine. */

    if (s_cmp(type__, "ge", (ftnlen)2, (ftnlen)2) == 0) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = i__ + (j - 1) * *lda;
		i__4 = i__ + j * a_dim1;
		aa[i__3].r = a[i__4].r, aa[i__3].i = a[i__4].i;
/* L30: */
	    }
	    i__2 = *lda;
	    for (i__ = *m + 1; i__ <= i__2; ++i__) {
		i__3 = i__ + (j - 1) * *lda;
		aa[i__3].r = -1e10, aa[i__3].i = 1e10;
/* L40: */
	    }
/* L50: */
	}
    } else if (s_cmp(type__, "gb", (ftnlen)2, (ftnlen)2) == 0) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *ku + 1 - j;
	    for (i1 = 1; i1 <= i__2; ++i1) {
		i__3 = i1 + (j - 1) * *lda;
		aa[i__3].r = -1e10, aa[i__3].i = 1e10;
/* L60: */
	    }
/* Computing MIN */
	    i__3 = *kl + *ku + 1, i__4 = *ku + 1 + *m - j;
	    i__2 = f2cmin(i__3,i__4);
	    for (i2 = i1; i2 <= i__2; ++i2) {
		i__3 = i2 + (j - 1) * *lda;
		i__4 = i2 + j - *ku - 1 + j * a_dim1;
		aa[i__3].r = a[i__4].r, aa[i__3].i = a[i__4].i;
/* L70: */
	    }
	    i__2 = *lda;
	    for (i3 = i2; i3 <= i__2; ++i3) {
		i__3 = i3 + (j - 1) * *lda;
		aa[i__3].r = -1e10, aa[i__3].i = 1e10;
/* L80: */
	    }
/* L90: */
	}
    } else if (s_cmp(type__, "he", (ftnlen)2, (ftnlen)2) == 0 || s_cmp(type__,
	     "tr", (ftnlen)2, (ftnlen)2) == 0) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (upper) {
		ibeg = 1;
		if (unit) {
		    iend = j - 1;
		} else {
		    iend = j;
		}
	    } else {
		if (unit) {
		    ibeg = j + 1;
		} else {
		    ibeg = j;
		}
		iend = *n;
	    }
	    i__2 = ibeg - 1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = i__ + (j - 1) * *lda;
		aa[i__3].r = -1e10, aa[i__3].i = 1e10;
/* L100: */
	    }
	    i__2 = iend;
	    for (i__ = ibeg; i__ <= i__2; ++i__) {
		i__3 = i__ + (j - 1) * *lda;
		i__4 = i__ + j * a_dim1;
		aa[i__3].r = a[i__4].r, aa[i__3].i = a[i__4].i;
/* L110: */
	    }
	    i__2 = *lda;
	    for (i__ = iend + 1; i__ <= i__2; ++i__) {
		i__3 = i__ + (j - 1) * *lda;
		aa[i__3].r = -1e10, aa[i__3].i = 1e10;
/* L120: */
	    }
	    if (sym) {
		jj = j + (j - 1) * *lda;
		i__2 = jj;
		i__3 = jj;
		d__1 = aa[i__3].r;
		z__1.r = d__1, z__1.i = -1e10;
		aa[i__2].r = z__1.r, aa[i__2].i = z__1.i;
	    }
/* L130: */
	}
    } else if (s_cmp(type__, "hb", (ftnlen)2, (ftnlen)2) == 0 || s_cmp(type__,
	     "tb", (ftnlen)2, (ftnlen)2) == 0) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (upper) {
		kk = *kl + 1;
/* Computing MAX */
		i__2 = 1, i__3 = *kl + 2 - j;
		ibeg = f2cmax(i__2,i__3);
		if (unit) {
		    iend = *kl;
		} else {
		    iend = *kl + 1;
		}
	    } else {
		kk = 1;
		if (unit) {
		    ibeg = 2;
		} else {
		    ibeg = 1;
		}
/* Computing MIN */
		i__2 = *kl + 1, i__3 = *m + 1 - j;
		iend = f2cmin(i__2,i__3);
	    }
	    i__2 = ibeg - 1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = i__ + (j - 1) * *lda;
		aa[i__3].r = -1e10, aa[i__3].i = 1e10;
/* L140: */
	    }
	    i__2 = iend;
	    for (i__ = ibeg; i__ <= i__2; ++i__) {
		i__3 = i__ + (j - 1) * *lda;
		i__4 = i__ + j - kk + j * a_dim1;
		aa[i__3].r = a[i__4].r, aa[i__3].i = a[i__4].i;
/* L150: */
	    }
	    i__2 = *lda;
	    for (i__ = iend + 1; i__ <= i__2; ++i__) {
		i__3 = i__ + (j - 1) * *lda;
		aa[i__3].r = -1e10, aa[i__3].i = 1e10;
/* L160: */
	    }
	    if (sym) {
		jj = kk + (j - 1) * *lda;
		i__2 = jj;
		i__3 = jj;
		d__1 = aa[i__3].r;
		z__1.r = d__1, z__1.i = -1e10;
		aa[i__2].r = z__1.r, aa[i__2].i = z__1.i;
	    }
/* L170: */
	}
    } else if (s_cmp(type__, "hp", (ftnlen)2, (ftnlen)2) == 0 || s_cmp(type__,
	     "tp", (ftnlen)2, (ftnlen)2) == 0) {
	ioff = 0;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (upper) {
		ibeg = 1;
		iend = j;
	    } else {
		ibeg = j;
		iend = *n;
	    }
	    i__2 = iend;
	    for (i__ = ibeg; i__ <= i__2; ++i__) {
		++ioff;
		i__3 = ioff;
		i__4 = i__ + j * a_dim1;
		aa[i__3].r = a[i__4].r, aa[i__3].i = a[i__4].i;
		if (i__ == j) {
		    if (unit) {
			i__3 = ioff;
			aa[i__3].r = -1e10, aa[i__3].i = 1e10;
		    }
		    if (sym) {
			i__3 = ioff;
			i__4 = ioff;
			d__1 = aa[i__4].r;
			z__1.r = d__1, z__1.i = -1e10;
			aa[i__3].r = z__1.r, aa[i__3].i = z__1.i;
		    }
		}
/* L180: */
	    }
/* L190: */
	}
    }
    return 0;

/*     End of ZMAKE. */

} /* zmake_ */

