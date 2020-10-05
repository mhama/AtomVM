#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/*
 * M5 Stack functions to be exposed to AtomVM
 */
EXTERNC void M5Stack_Init();
EXTERNC void M5Stack_ShowMessageAndWait(char *msg);

#undef EXTERNC

