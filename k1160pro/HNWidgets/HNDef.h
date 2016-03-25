#ifndef HNDEF_H
#define HNDEF_H

#define pline() qDebug() << __FILE__ << __LINE__ << __func__
#define perr(var, cond) if(var == cond) pline() << hex << cond

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef bool BOOL;
typedef int		s32;
typedef unsigned int   u32;
typedef unsigned char	u8;
typedef unsigned short  u16;
typedef short           s16;
typedef char            s8;
typedef long int		s64;
typedef unsigned long int u64;
typedef unsigned char uint8_t;

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR   1
#endif

#ifndef SEEK_END
#define SEEK_END   2
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef NULL
#define NULL   0
#endif

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

#define MAX_LEN 1024

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif // HNDEF_H
