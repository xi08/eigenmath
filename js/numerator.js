function
numerator()
{
	var p1;

	p1 = pop();

	if (isrational(p1)) {
		push_integer(p1.a);
		return;
	}

	while (cross_expr(p1)) {
		push(p1);
		cancel_factor();
		p1 = pop();
	}

	push(p1);
}
