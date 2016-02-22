#ifndef WBDEF_H
#define WBDEF_H

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

enum {
    Auth_Id = 0,
    Auth_Name,
    Auth_Passwd,
    Auth_Authrity,
    Auth_Creater,
    Auth_CreateTime,
    Auth_Comment,
};

enum {
    Lib_Id = 0,
    Lib_Name,
    Lib_Creater,
    Lib_CreateTime,
    Lib_Comment,
};

enum {
    Authority_Id = 0,
    Authority_Level,
};

enum {
    Method_Id = 0,
    Method_Name,
    Method_Type,
};

enum {
    Stage_Id = 0,
    Stage_Index,
    Stage_Vessel,
    Stage_Timeramp,
    Stage_Presspsi,
    Stage_Tempture,
    Stage_Hold,
    Stage_MethodId,
};


enum{
    Type_Standard = 0,
    Type_Temprature,
    Type_Stressure,
};

enum {
    Login_Request,
    Login_Success,
};

enum{
    Language_English,
    Language_Chinese,
};

enum {
    FILE_NAME,
    FILE_ID,
    FILE_SIZE,
    FILE_DATE,
    FILE_MAX,
};

enum {
    DIR_NAME,
    DIR_CODE,
    DIR_MAX,
};

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

#define MAX_LEN 1024

#define DB_TYPE "QSQLITE"
#define DB_MANAGER "Manager"
#define TABLE_USERINFO "User"
#define TABLE_AUTHORITY "Authority"
#define TABLE_LIBRARY "Library"
#define TABLE_METHOD "Method"
#define TABLE_STAGE "Stage"

#define WARNING "Warning"
#define NOTICE "Notice"

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif // WBDEF_H
