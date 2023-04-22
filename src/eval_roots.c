void
eval_roots(struct atom *p1)
{
	push(cadr(p1));
	evalf();

	p1 = cddr(p1);

	if (iscons(p1)) {
		push(car(p1));
		evalf();
	} else
		push_symbol(X_LOWER);

	roots();
}

void
roots(void)
{
	int h, i, j, k, n;
	struct atom *A, *P, *X;

	X = pop();
	P = pop();

	h = tos;

	coeffs(P, X); // put coeffs on stack

	k = tos;

	n = k - h; // number of coeffs on stack

	// check coeffs

	for (i = 0; i < n; i++)
		if (!isrational(stack[h + i]))
			stopf("roots: coeffs");

	// find roots

	while (n > 1) {

		if (findroot(h, n) == 0)
			break; // no root found

		// A is the root

		A = stack[tos - 1];

		// divide p(x) by X - A

		reduce(h, n, A);

		n--;
	}

	n = tos - k; // number of roots on stack

	if (n == 0) {
		tos = h; // pop all
		push_symbol(NIL); // no roots
		return;
	}

	sort(n); // sort roots

	// eliminate repeated roots

	for (i = 0; i < n - 1; i++)
		if (equal(stack[k + i], stack[k + i + 1])) {
			for (j = i + 1; j < n - 1; j++)
				stack[k + j] = stack[k + j + 1];
			i--;
			n--;
		}

	if (n == 1) {
		A = stack[k];
		tos = h; // pop all
		push(A); // one root
		return;
	}

	A = alloc_vector(n);

	for (i = 0; i < n; i++)
		A->u.tensor->elem[i] = stack[k + i];

	tos = h; // pop all

	push(A);
}

int
findroot(int h, int n)
{
	int i, j, m, p, q, r;
	struct atom *A, *C, *PA;

	// check constant term

	if (iszero(stack[h])) {
		push_integer(0); // root is zero
		return 1;
	}

	// eliminate denominators

	for (i = 0; i < n; i++) {
		C = stack[h + i];
		if (isinteger(C))
			continue;
		push(C);
		denominator();
		C = pop();
		for (j = 0; j < n; j++) {
			push(stack[h + j]);
			push(C);
			multiply();
			stack[h + j] = pop();
		}
	}

	p = tos;

	push(stack[h]);
	m = pop_integer();
	divisors(m); // divisors of constant term

	q = tos;

	push(stack[h + n - 1]);
	m = pop_integer();
	divisors(m); // divisors of leading coeff

	r = tos;

	for (i = p; i < q; i++) {
		for (j = q; j < r; j++) {

			// try positive A

			push(stack[i]);
			push(stack[j]);
			divide();
			A = pop();

			horner(h, n, A);

			PA = pop(); // polynomial evaluated at A

			if (iszero(PA)) {
				tos = p; // pop all
				push(A);
				return 1; // root on stack
			}

			// try negative A

			push(A);
			negate();
			A = pop();

			horner(h, n, A);

			PA = pop(); // polynomial evaluated at A

			if (iszero(PA)) {
				tos = p; // pop all
				push(A);
				return 1; // root on stack
			}
		}
	}

	tos = p; // pop all

	return 0; // no root
}

// evaluate p(x) at x = A using horner's rule

void
horner(int h, int n, struct atom *A)
{
	int i;

	push(stack[h + n - 1]);

	for (i = n - 2; i >= 0; i--) {
		push(A);
		multiply();
		push(stack[h + i]);
		add();
	}
}

// push all divisors of n

void
divisors(int n)
{
	int h, i, k;

	h = tos;

	factor_int(n);

	k = tos;

	// contruct divisors by recursive descent

	push_integer(1);

	divisors_nib(h, k);

	// move

	n = tos - k;

	for (i = 0; i < n; i++)
		stack[h + i] = stack[k + i];

	tos = h + n; // pop all
}

//	Generate all divisors for a factored number
//
//	Input:		Factor pairs on stack (base, expo)
//
//			h	first pair
//
//			k	just past last pair
//
//	Output:		Divisors on stack
//
//	For example, the number 12 (= 2^2 3^1) has 6 divisors:
//
//	1, 2, 3, 4, 6, 12

void
divisors_nib(int h, int k)
{
	int i, n;
	struct atom *ACCUM, *BASE, *EXPO;

	if (h == k)
		return;

	ACCUM = pop();

	BASE = stack[h + 0];
	EXPO = stack[h + 1];

	push(EXPO);
	n = pop_integer();

	for (i = 0; i <= n; i++) {
		push(ACCUM);
		push(BASE);
		push_integer(i);
		power();
		multiply();
		divisors_nib(h + 2, k);
	}
}

// divide by X - A

void
reduce(int h, int n, struct atom *A)
{
	int i;

	for (i = n - 1; i > 0; i--) {
		push(A);
		push(stack[h + i]);
		multiply();
		push(stack[h + i - 1]);
		add();
		stack[h + i - 1] = pop();
	}

	if (!iszero(stack[h]))
		stopf("roots: residual error"); // not a root

	// move

	for (i = 0; i < n - 1; i++)
		stack[h + i] = stack[h + i + 1];
}

// push coefficients of polynomial P(X) on stack

void
coeffs(struct atom *P, struct atom *X)
{
	struct atom *C;

	for (;;) {

		push(P);
		push(X);
		push_integer(0);
		subst();
		evalf();
		C = pop();

		push(C);

		push(P);
		push(C);
		subtract();
		P = pop();

		if (iszero(P))
			break;

		push(P);
		push(X);
		divide();
		P = pop();
	}
}
