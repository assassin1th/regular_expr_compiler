#ifndef ATTR_H_
#define ATTR_H_

#ifdef __GNUC__

#define _inline __attribute__ ((always_inline))
#define _fastcall __attribute__ ((fastcall))

#else

#define _inline
#define _fastcall

#endif

#endif // ATTR_H_
