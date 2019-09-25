// Condense an expression by factoring common terms.

#include "defs.h"

void
eval_condense(void)
{
	push(cadr(p1));
	eval();
	condense_expr();
}

void
condense_expr(void)
{
	int t;
	t = expanding;
	expanding = 0;
	save();
	condense_expr_nib();
	restore();
	expanding = t;
}

void
condense_expr_nib(void)
{
	p1 = pop();

	if (car(p1) != symbol(ADD)) {
		push(p1);
		return;
	}

	// get gcd of all terms

	p3 = cdr(p1);
	push(car(p3));
	p3 = cdr(p3);
	while (iscons(p3)) {
		push(car(p3));
		gcd();
		p3 = cdr(p3);
	}

	// divide each term by gcd

	reciprocate();
	p2 = pop();
	push(zero);
	p3 = cdr(p1);
	while (iscons(p3)) {
		push(p2);
		push(car(p3));
		multiply();
		add();
		p3 = cdr(p3);
	}

	// We multiplied above w/o expanding so sum factors cancelled.

	// Now we expand which which normalizes the result and, in some cases,
	// simplifies it too (see test case H).

	expand_expr();

	// multiply result by gcd

	push(p2);
	divide();
}
