var stack;
var frame;
var binding;
var arglist;
var zero;
var one;
var minusone;
var imaginaryunit;
var expanding;
var evaldepth;
var inbuf;
var trace1;
var trace2;

var symtab = {
abs:		{printname:ABS,		func:eval_abs},
adj:		{printname:ADJ,		func:eval_adj},
and:		{printname:AND,		func:eval_and},
arccos:		{printname:ARCCOS,	func:eval_arccos},
arccosh:	{printname:ARCCOSH,	func:eval_arccosh},
arcsin:		{printname:ARCSIN,	func:eval_arcsin},
arcsinh:	{printname:ARCSINH,	func:eval_arcsinh},
arctan:		{printname:ARCTAN,	func:eval_arctan},
arctanh:	{printname:ARCTANH,	func:eval_arctanh},
arg:		{printname:ARG,		func:eval_arg},
binding:	{printname:BINDING,	func:eval_binding},
check:		{printname:CHECK,	func:eval_check},
circexp:	{printname:CIRCEXP,	func:eval_circexp},
clear:		{printname:CLEAR,	func:eval_clear},
clock:		{printname:CLOCK,	func:eval_clock},
conj:		{printname:CONJ,	func:eval_conj},
contract:	{printname:CONTRACT,	func:eval_contract},
cos:		{printname:COS,		func:eval_cos},
cosh:		{printname:COSH,	func:eval_cosh},
defint:		{printname:DEFINT,	func:eval_defint},
denominator:	{printname:DENOMINATOR,	func:eval_denominator},
derivative:	{printname:DERIVATIVE,	func:eval_derivative},
det:		{printname:DET,		func:eval_det},
"do":		{printname:DO,		func:eval_do},
dot:		{printname:DOT,		func:eval_dot},
"eval":		{printname:EVAL,	func:eval_eval},
exp:		{printname:EXP,		func:eval_exp},
expcos:		{printname:EXPCOS,	func:eval_expcos},
expcosh:	{printname:EXPCOSH,	func:eval_expcosh},
expsin:		{printname:EXPSIN,	func:eval_expsin},
expsinh:	{printname:EXPSINH,	func:eval_expsinh},
exptan:		{printname:EXPTAN,	func:eval_exptan},
exptanh:	{printname:EXPTANH,	func:eval_exptanh},
factorial:	{printname:FACTORIAL,	func:eval_factorial},
"float":	{printname:FLOAT,	func:eval_float},
floor:		{printname:FLOOR,	func:eval_floor},
"for":		{printname:FOR,		func:eval_for},
imag:		{printname:IMAG,	func:eval_imag},
inner:		{printname:INNER,	func:eval_inner},
integral:	{printname:INTEGRAL,	func:eval_integral},
inv:		{printname:INV,		func:eval_inv},
log:		{printname:LOG,		func:eval_log},
mag:		{printname:MAG,		func:eval_mag},
nil:		{printname:NIL,		func:eval_nil},
not:		{printname:NOT,		func:eval_not},
number:		{printname:NUMBER,	func:eval_number},
numerator:	{printname:NUMERATOR,	func:eval_numerator},
or:		{printname:OR,		func:eval_or},
outer:		{printname:OUTER,	func:eval_outer},
polar:		{printname:POLAR,	func:eval_polar},
prefixform:	{printname:PREFIXFORM,	func:eval_prefixform},
print:		{printname:PRINT,	func:eval_print},
product:	{printname:PRODUCT,	func:eval_product},
quote:		{printname:QUOTE,	func:eval_quote},
rank:		{printname:RANK,	func:eval_rank},
rationalize:	{printname:RATIONALIZE,	func:eval_rationalize},
real:		{printname:REAL,	func:eval_real},
rect:		{printname:RECT,	func:eval_rect},
sgn:		{printname:SGN,		func:eval_sgn},
sin:		{printname:SIN,		func:eval_sin},
sinh:		{printname:SINH,	func:eval_sinh},
sqrt:		{printname:SQRT,	func:eval_sqrt},
stop:		{printname:STOP,	func:eval_stop},
sum:		{printname:SUM,		func:eval_sum},
tan:		{printname:TAN,		func:eval_tan},
tanh:		{printname:TANH,	func:eval_tanh},
test:		{printname:TEST,	func:eval_test},
testeq:		{printname:TESTEQ,	func:eval_testeq},
testge:		{printname:TESTGE,	func:eval_testge},
testgt:		{printname:TESTGT,	func:eval_testgt},
testle:		{printname:TESTLE,	func:eval_testle},
testlt:		{printname:TESTLT,	func:eval_testlt},
transpose:	{printname:TRANSPOSE,	func:eval_transpose},
unit:		{printname:UNIT,	func:eval_unit},
zero:		{printname:ZERO,	func:eval_zero},

"+":		{printname:ADD,		func:eval_add},
"*":		{printname:MULTIPLY,	func:eval_multiply},
"^":		{printname:POWER,	func:eval_power},
"[":		{printname:INDEX,	func:eval_index},
"=":		{printname:SETQ,	func:eval_setq},

"(e)":		{printname:EXP1,	func:eval_symbol},
"(a)":		{printname:METAA,	func:eval_symbol},
"(b)":		{printname:METAB,	func:eval_symbol},
"(x)":		{printname:METAX,	func:eval_symbol},
"(X)":		{printname:SPECX,	func:eval_symbol},

last:		{printname:LAST,	func:eval_symbol},
pi:		{printname:PI,		func:eval_symbol},
trace:		{printname:TRACE,	func:eval_symbol},

d:		{printname:SYMBOL_D,	func:eval_symbol},
i:		{printname:SYMBOL_I,	func:eval_symbol},
j:		{printname:SYMBOL_J,	func:eval_symbol},
s:		{printname:SYMBOL_S,	func:eval_symbol},
t:		{printname:SYMBOL_T,	func:eval_symbol},
x:		{printname:SYMBOL_X,	func:eval_symbol},
y:		{printname:SYMBOL_Y,	func:eval_symbol},
z:		{printname:SYMBOL_Z,	func:eval_symbol},

};
