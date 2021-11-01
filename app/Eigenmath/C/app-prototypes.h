// Run 'make' in 'eigenmath/tools' directory to update this file
void eval_exit(void);
void echo_input(char *s);
int check_display(void);
void prep_display(void);
void clear_display(void);
struct display * get_display_ptr(void);
void set_display_ptr(struct display *p);
void display(void);
void draw_display(double ymin, double ymax);
void draw_display_nib(struct display *p, double y, double ymin, double ymax);
void draw_text(double x, double y, uint8_t *buf, int len);
void draw_formula(double x, double y, double *p);
void draw_char(double x, double y, int font_num, int char_num);
void draw_stroke(double x1, double y1, double x2, double y2, double stroke_width);
void draw_point(double x, double y);
void draw_selection_rect(double x, double y, double width, double height);
void emit_args(struct atom *p);
void emit_base(struct atom *p);
void emit_box(void);
void emit_denominators(struct atom *p);
void emit_double(struct atom *p);
void emit_exponent(struct atom *p);
void emit_expr(struct atom *p);
void emit_expr_nib(struct atom *p);
void emit_factor(struct atom *p);
void emit_formula(double x, double y, struct atom *p);
void emit_formula_delims(double x, double y, double h, double d, double w, double stroke_width, int font_num);
void emit_formula_ldelim(double x, double y, double h, double d, double w, double stroke_width);
void emit_formula_rdelim(double x, double y, double h, double d, double w, double stroke_width);
void emit_formula_fraction(double x, double y, double h, double d, double w, double stroke_width, int font_num, struct atom *p);
void emit_formula_table(double x, double y, struct atom *p);
void emit_formula_char(double x, double y, int font_num, int char_num);
void emit_formula_stroke(double x1, double y1, double x2, double y2, double stroke_width);
void emit_frac(struct atom *p);
void emit_function(struct atom *p);
void emit_graph(void);
void emit_indices(struct atom *p);
void emit_infix_operator(int c);
void emit_italic_char(int char_num);
void emit_italic_string(char *s);
void emit_labels(void);
void emit_list(struct atom *p);
void emit_matrix(struct atom *p, int d, int k);
void emit_medium_space(void);
void emit_numerators(struct atom *p);
void emit_numeric_exponent(struct atom *p);
void emit_power(struct atom *p);
void emit_push(double d);
void emit_rational(struct atom *p);
void emit_reciprocal(struct atom *p);
void emit_roman_char(int char_num);
void emit_roman_string(char *s);
void emit_string(struct atom *p);
void emit_subexpr(struct atom *p);
void emit_symbol(struct atom *p);
int emit_symbol_fragment(char *s, int k);
void emit_tensor(struct atom *p);
void emit_term(struct atom *p);
void emit_term_nib(struct atom *p);
void emit_text(char *buf, int len, int color);
void emit_thick_space(void);
void emit_thin_space(void);
void emit_update_fraction(void);
void emit_update_list(int t);
void emit_update_list_nib(int t);
void emit_update_subexpr(void);
void emit_update_subscript(void);
void emit_update_superscript(void);
void emit_update_table(int n, int m);
void emit_vector(struct atom *p);
void emit_xaxis(void);
void emit_yaxis(void);
void eval_draw(void);
void eval_draw_nib(void);
void setup_trange(void);
void setup_xrange(void);
void setup_yrange(void);
void setup_final(void);
void draw_pass1(void);
void draw_pass2(void);
void sample(double t);
int inrange(double x, double y);
void eval_nonstop(void);
void eval_nonstop_nib(void);
void init_fonts(void);
double get_ascent(int font_num);
double get_cap_height(int font_num);
double get_char_depth(int font_num, int char_num);
CFStringRef get_char_name(int char_num);
double get_char_width(int font_num, int char_num);
double get_descent(int font_num);
CTFontRef get_font_ref(int font_num);
double get_leading(int font_num);
double get_xheight(int font_num);
double get_operator_height(int font_num);
void printbuf(char *s, int color);
void run_thread(char *s);
void * run_thread_nib(void *s);
void shipout(struct display *p);
