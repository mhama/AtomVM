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
EXTERNC void M5Stack_ShowMessage(char *msg);
EXTERNC int M5Stack_ButtonRead(int button);

#undef EXTERNC

