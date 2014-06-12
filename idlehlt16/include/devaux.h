extern ULONG  DevHlp;

/*
 * Look at \WATCOM\H\OS2\DEVHLP.INC for the list of
 * definitions for device driver helper functions
 */

USHORT DevSetTimer            // Register a timer handler
  (
  NPVOID      Handler         // Handler function entry-point
  );                          // Returns: 0 = success, other = error code

#pragma aux DevSetTimer =     \
  "mov dl,1Dh"                \
  "call dword ptr DevHlp"     \
  "setc dl"                   \
  "xor dh,dh"                 \
  "neg dx"                    \
  "and ax,dx"                 \
  modify [dx]                 \
  parm [ax]                   \
  value [ax];

USHORT DevPhysToVirt          // Convert a physical address to a 16:16 address
  (
  ULONG     PhysAddr,         // Physical address to convert
  USHORT    Length,           // Length of virtual segment
  PVOID     VirtAddr          // Storage for virtual address
  );                          // Returns: 0 = success, other = error code

#pragma aux DevPhysToVirt =   \
  "xchg ax,bx"                \
  "mov dx,0115h"              \
  "call dword ptr DevHlp"     \
  "setc dl"                   \
  "xor dh,dh"                 \
  "neg dx"                    \
  "mov fs:[si][0],di"         \
  "mov fs:[si][2],es"         \
  "and ax,dx"                 \
  modify [dx es di]           \
  parm [bx ax] [cx] [fs si]   \
  value [ax];


//extern WORD32 Dev_Entry;
//extern WORD32 Dev_StdEntry;
//extern WORD32 Dev_DbgEntry;

//void DevInit                  // Initialize the Dev* library (call at Init)
//  (
//  WORD32 DeviceHelp           // Far pointer to OS/2 Dev_Help entry point
//  );                          // Returns: Nothing

//inline void DevInit(WORD32 DeviceHelp) {
//    Dev_Entry = Dev_StdEntry = DeviceHelp;
//    return;
//}

//WORD16 DosPutMessage(HFILE, WORD16 Length, CONST CHAR FAR* Message);
//#pragma aux (API16) DosPutMessage;
