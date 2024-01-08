#ifndef _athw_defmacro_h
#define _athw_defmacro_h


#ifdef __cplusplus
extern "C" {}
#endif

/**
 * 
 */

#define X_ERRMSG()                  strerror(errno)


//<! \def RETURN_IF_FAIL if given expression is fail, function is terminate and return
#define X_RET_IF_FAIL(expr)         \
    do { if (!(expr)) {printf("'%s' FAILED. \r\n"), #expr}; return;}} while(0)

//<! X_RET_VAL_IF_FAIL if given expression is fail, function is terminate and return
#ifdef __GNUC__
#define X_RET_VAL_IF_FAIL(expr, val)               \
    do { 		\
		int _expr_val=(int)expr;	\
		if (!(_expr_val)) { \
			printf("'%s' FAILED.", ##_expr_val); \
			return(val); \
		}	\
	} while(0)
#else
#define X_RET_VAL_IF_FAIL(expr, val)               
#endif

///**<! X_RET_VALIDATE_ERRCODE set errno and return error code*/
//#define X_RET_VALIDATE_ERRCODE( expr , errorcode )								\
//	{																			\
//		int _expr_val=!!(expr);													\
//		if( !(_expr_val) )	{													\
//			errno = errorcode;													\
//			return (errorcode);													\
//		}																		\
//	}








#ifdef __cplusplus
}
#endif

#endif
