#ifndef _athw_defmacro_h
#define _athw_defmacro_h


#ifdef __cplusplus
extern "C" {}
#endif

extern void error_handler(void *priv);

/**
 * 
 */

#define X_ERRMSG()                  strerror(errno)


//<! \def RETURN_IF_FAIL if given expression is fail, function is terminate and return
#define X_RET_IF_FAIL(expr)         \
    do { if (!(expr)) {printf("'%s' FAILED. \r\n"), #expr}; return;}} while(0)

//<! X_RET_VAL_IF_FAIL if given expression is fail, function is terminate and return

#define X_RET_VAL_IF_FAIL(expr, val)               \
	do { if(!(expr)) {printf("'%s' FAILED.", #expr); return(val);} } while (0)

#define X_ASSERT_PARAM(expr,val) ((expr) ? (void)0U : printf("assert param (%s:%d) ret: %d\r\n",__FILE__, __LINE__, val)); return (val)
#define X_ASSERT_ERRORH(expr,val) ((expr) ? (void)0U : printf("assert param (%s:%d) ret : %d\r\n",__FILE__, __LINE__, val)); error_handler(val)

#define X_RET_CHECK(fnc)	do {	\
	int result;						\
	\
	result = (fnc);					\
	if(result != 0) {				\
		printf(#fnc "function failed : line %d, 0x%x \r\n", \
		__LINE__, result);									\
	}														\
} while(0)


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
