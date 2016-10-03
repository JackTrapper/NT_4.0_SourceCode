#ifndef          _INC_NDDESEC
#define          _INC_NDDESEC

#include <winnt.h>

#define NDDE_SHAREDB_ADD        (0x00000001)
#define NDDE_SHAREDB_DELETE     (0x00000002)
#define NDDE_SHAREDB_LIST       (0x00000004)
#define NDDE_SHAREDB_FSERVICE   (0x00000008)

#define NDDE_SHAREDB_ADMIN      (NDDE_SHAREDB_ADD |         \
                                 NDDE_SHAREDB_DELETE |      \
                                 NDDE_SHAREDB_LIST |        \
                                 NDDE_SHAREDB_FSERVICE |    \
                                 READ_CONTROL |             \
                                 WRITE_DAC |                \
                                 WRITE_OWNER)

#define NDDE_SHAREDB_OPER       (NDDE_SHAREDB_ADD |         \
                                 NDDE_SHAREDB_LIST)

#define NDDE_SHAREDB_POWER      (NDDE_SHAREDB_ADD |         \
                                 NDDE_SHAREDB_FSERVICE |    \
                                 NDDE_SHAREDB_LIST)

#define NDDE_SHAREDB_USER       (NDDE_SHAREDB_ADD |         \
                                 NDDE_SHAREDB_LIST)

#define NDDE_SHAREDB_EVERYONE   (NDDE_SHAREDB_LIST)

#define NDDE_SHARE_READ             (0x00000001)
#define NDDE_SHARE_WRITE            (0x00000002)
#define NDDE_SHARE_INITIATE_STATIC  (0x00000004)
#define NDDE_SHARE_INITIATE_LINK    (0x00000008)
#define NDDE_SHARE_REQUEST          (0x00000010)
#define NDDE_SHARE_ADVISE           (0x00000020)
#define NDDE_SHARE_POKE             (0x00000040)
#define NDDE_SHARE_EXECUTE          (0x00000080)
#define NDDE_SHARE_ADD_ITEMS        (0x00000100)
#define NDDE_SHARE_LIST_ITEMS       (0x00000200)

#define NDDE_SHARE_GENERIC_READ     (NDDE_SHARE_READ |               \
                                    NDDE_SHARE_INITIATE_STATIC |     \
                                    NDDE_SHARE_REQUEST |             \
                                    NDDE_SHARE_ADVISE |              \
                                    NDDE_SHARE_LIST_ITEMS)

#define NDDE_SHARE_GENERIC_WRITE    (NDDE_SHARE_INITIATE_STATIC |    \
                                     NDDE_SHARE_INITIATE_LINK |      \
                                     NDDE_SHARE_POKE |               \
                                     DELETE)

#define NDDE_SHARE_GENERIC_EXECUTE (NDDE_SHARE_INITIATE_STATIC |     \
                                    NDDE_SHARE_INITIATE_LINK |       \
                                    NDDE_SHARE_EXECUTE)

#define NDDE_SHARE_GENERIC_ALL     (NDDE_SHARE_READ |                \
                                    NDDE_SHARE_WRITE |               \
                                    NDDE_SHARE_INITIATE_STATIC |     \
                                    NDDE_SHARE_INITIATE_LINK |       \
                                    NDDE_SHARE_REQUEST |             \
                                    NDDE_SHARE_ADVISE |              \
                                    NDDE_SHARE_POKE |                \
                                    NDDE_SHARE_EXECUTE |             \
                                    NDDE_SHARE_ADD_ITEMS |           \
                                    NDDE_SHARE_LIST_ITEMS |          \
                                    DELETE |                         \
                                    READ_CONTROL |                   \
                                    WRITE_DAC |                      \
                                    WRITE_OWNER)


#define NDDE_ITEM_REQUEST          (0x00000001)
#define NDDE_ITEM_ADVISE           (0x00000002)
#define NDDE_ITEM_POKE             (0x00000004)

#define NDDE_ITEM_GENERIC_READ     (NDDE_ITEM_REQUEST | NDDE_ITEM_ADVISE)
#define NDDE_ITEM_GENERIC_WRITE    (NDDE_ITEM_POKE)
#define NDDE_ITEM_GENERIC_EXECUTE  (0)
#define NDDE_ITEM_GENERIC_ALL      (NDDE_ITEM_REQUEST |               \
                                   NDDE_ITEM_ADVISE |                 \
                                   NDDE_ITEM_POKE |                   \
                                   DELETE |                           \
                                   READ_CONTROL |                     \
                                   WRITE_DAC |                        \
                                   WRITE_OWNER)

#define NDDE_GUI_NONE              (0)

#define NDDE_GUI_READ              (NDDE_SHARE_GENERIC_READ)

#define NDDE_GUI_READ_LINK         (NDDE_SHARE_GENERIC_READ |         \
                                    NDDE_SHARE_INITIATE_LINK)

#define NDDE_GUI_CHANGE            (NDDE_SHARE_GENERIC_READ |         \
                                    NDDE_SHARE_GENERIC_WRITE |        \
                                    NDDE_SHARE_GENERIC_EXECUTE)

#define NDDE_GUI_FULL_CONTROL      (NDDE_SHARE_GENERIC_ALL)

#endif
