#ifndef COMPILER_H
#define COMPILER_H

#define RTE_CODE
#define RTE_CONST
#define RTE_APPL_DATA
#define RTE_APPL_CONST
#define RTE_APPL_CODE
#define RTE_VAR_NOINIT
#define RTE_VAR_POWER_ON_INIT
#define RTE_VAR_FAST
#define RTE_VAR
#define AUTOMATIC
#define TYPEDEF
#define STATIC static
#define _STATIC_ STATIC
#define NULL_PTR ((void *)0)
#define INLINE
#define _INLINE_ INLINE
#define LOCAL_INLINE
#define FUNC(rettype, memclass) rettype
#define FUNC_P2CONST(rettype, ptrclass, memclass) const rettype *
#define FUNC_P2VAR(rettype, ptrclass, memclass) rettype * memclass
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const
#define P2FUNC(rettype, ptrclass, fctname) rettype (* fctname)
#define CONST(consttype, memclass) const consttype
#define VAR(vartype, memclass) vartype

#endif