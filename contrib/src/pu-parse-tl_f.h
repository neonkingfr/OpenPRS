/*
 *   This file was a long time ago automatically generated by version 1.7 of cextract.
 *   Manual editing has been done already...

 */
#ifdef __cplusplus
extern "C" {
#endif

/* Prototypes */
PBoolean PU_bind_short(short *shortPtr, Term *term);
PBoolean PU_bind_integer(int *intPtr, Term *term);
PBoolean PU_bind_long_long(long long int *intPtr, Term *term);
PBoolean PU_bind_string(char **strPtr, Term *paramTerm);
PBoolean PU_bind_atom(Symbol *atomPtr, Term *paramTerm);
PBoolean PU_bind_u_pointer(void **ptr, Term *paramTerm);
PBoolean PU_bind_u_memory(U_Memory **u_mem, Term *paramTerm);
PBoolean PU_bind_expr(Expression **tcPtr, Term *paramTerm);
PBoolean PU_bind_l_list(L_List *lispList, Term *paramTerm);
PBoolean PU_bind_float(float *floatPtr, Term *paramTerm);
PBoolean PU_bind_double(double *doublePtr, Term *paramTerm);

PBoolean PUGetOprsParameters ( TermList paramList, int NbParametres, ... );
PBoolean PUGetLispListElem ( L_List lispList, int NbTerm, ... );
int PUGetLispListCar ( L_List *lispListPtr, Term_Type type, void *ptr );
PBoolean PUGetOprsTermCompArgs ( Expression *tc, int NbParametres, ... );
PBoolean PUGetOprsTermCompSpecArg ( Expression *tc, int rank, Term_Type type, void *ptr );
PBoolean PUGetOprsParametersSpecArg ( TermList paramList, int rank, Term_Type type, void *ptr );
PBoolean PUGetOprsVarArgParameters(TermList paramList, PBoolean find_them_all, int nb, ...);
PBoolean PUGetOprsVarArgG3Parameters(Expression *expr, PBoolean find_them_all, int nb, ...);


/* These are tricky macros...   */
#define set_parameter_or_default_value(parameter,default_value,oprs_type) (parameter = (default_value),oprs_type),#parameter,&(parameter)

#define set_val_addr_func(in,field,mandatory,encode_func) #field, mandatory, &(in->field), encode_func

  

#ifdef __cplusplus
}
#endif
