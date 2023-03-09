
#ifndef platform_types_h_
#define platform_types_h_

/******** <CPU terms>********/

#define CPU_TYPE CPU_TYPE_16
#define CPU_BIT_ORDER LSB_FIRST
#define CPU_BYTE_ORDER LOW_BYTE_FIRST

/******** <non volatile integers>********/

typedef unsigned char boolean;

typedef signed char 					sint8_t;
typedef unsigned char 					uint8_t;
typedef signed short 					sint16_t;
typedef unsigned short 					uint16_t;
typedef signed long						sint32_t;
typedef unsigned long 					uint32_t;
typedef signed long long				sint64_t;
typedef unsigned long long				uint64_t;

/******** <volatile integers>********/

typedef unsigned char boolean;

typedef volatile signed char 			vsint8_t;
typedef volatile unsigned char 			vuint8_t;
typedef volatile signed short 			vsint16_t;
typedef volatile unsigned short 		vuint16_t;
typedef volatile signed long			vsint32_t;
typedef volatile unsigned long 			vuint32_t;
typedef volatile signed long long		vsint64_t;
typedef volatile unsigned long long		vuint64_t;

/******** <non volatile float variables>********/

typedef float							float32;
typedef double 							float64;

/******** <non volatile float variables>********/

typedef volatile float					vfloat32;
typedef volatile double 				vfloat64;

#endif
