#define CHECKSUM_OPEN_FAILURE       1
#define CHECKSUM_MAP_FAILURE        2
#define CHECKSUM_MAPVIEW_FAILURE    3

ULONG CheckSum(FILE *, PUCHAR, BOOLEAN, PULONG);
