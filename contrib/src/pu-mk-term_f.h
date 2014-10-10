/*
 *   This file was automatically generated by version 1.7 of cextract.
 *   Manual editing not recommended.

 */

#ifdef __cplusplus
extern "C" {
#endif

Term * PUMakeTermInteger ( int val );
Term * PUMakeTermLongLong(long long int val);
Term* PUMakeTermFloat ( double val );
Term * PUMakeTermAtom ( const char *atom );
Term* PUMakeTermUPointer ( void *pointer );
Term* PUMakeTermUMemory ( void *p, int size );
Term * PUMakeTermTrue ( void );
Term * PUMakeTermNil ( void );
Term *PUMakeTermString (const char *string );
Term * PUMakeTermLispList ( int NbTerm, ... );
Term * PUMakeTermComp ( Pred_Func_Rec* funcName, int NbTerm, ... );
Term * PUMakeExternalTermComp ( char* fName, int NbTerm, ... );
TermList PUMakeTermList ( int NbTerm, ... );
Term * PUMakeTermCList ( int NbTerm, ... );

#ifdef __cplusplus
}
#endif
