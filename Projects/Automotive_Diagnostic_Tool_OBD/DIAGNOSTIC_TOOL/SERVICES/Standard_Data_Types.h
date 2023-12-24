
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef  unsigned char				uint8;
typedef  unsigned short				uint16;
typedef  unsigned long				uint32;
typedef  unsigned long long			uint64;

typedef  char						sint8;
typedef  short						sint16;
typedef  long						sint32;
typedef  long long					sint64;

typedef  float						float32;
typedef  double						float64;
typedef  long double				float80;

typedef  unsigned char*				Puint8;
typedef  unsigned short*			Puint16;
typedef  unsigned long*				Puint32;
typedef  unsigned long long*		Puint64;

typedef  char*						Psint8;
typedef  short*						Psint16;
typedef  long*						Psint32;
typedef  long long*					Psint64;



typedef  float*						Pfloat32;
typedef  double*					Pfloat64;
typedef  long double*				Pfloat80;

#define NULL						((void *)0)
typedef void 					(*CALL_BACK_FN_TYPE)(void);


#endif /* STD_TYPES_H_ */





