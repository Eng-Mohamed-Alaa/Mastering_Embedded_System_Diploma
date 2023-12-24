
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef  unsigned char			uint8;
typedef  unsigned short			uint16;
typedef  unsigned long long		uint32;

typedef  char					sint8;
typedef  short					sint16;
typedef  long long				sint32;

typedef  float					float32;
typedef  double					float64;
typedef  long double			float80;

typedef  unsigned char*			Puint8;
typedef  unsigned short*		Puint16;
typedef  unsigned long long*	Puint32;

typedef  char*					Psint8;
typedef  short*					Psint16;
typedef  long long*				Psint32;

typedef  float*					Pfloat32;
typedef  double*				Pfloat64;
typedef  long double*			Pfloat80;

#define PTR_NULL				((void*)0)

#endif /* STD_TYPES_H_ */
