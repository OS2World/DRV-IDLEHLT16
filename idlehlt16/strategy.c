/************************************************************************\
**                                                                      **
**               OS/2 Physical Device Driver Example Code               **
**                       for Open Watcom C/C++                          **
**                                                                      **
**  COPYRIGHT:                                                          **
**                                                                      **
**    (C) Copyright Advanced Gravis Computer Technology Ltd 1994.       **
**        All Rights Reserved.                                          **
**                                                                      **
**    Also includes code from Open Watcom perforce tree which was       **
**    originally adapted from the Fall 1991 issue of                    **
**    IBM Personal Systems Developer magazine.                          **
**                                                                      **
**    Adapted for Open Watcom C/C++                                     **
**    Original Author: Rick Fishman                                     **
**                     Code Blazers, Inc.                               **
**                     4113 Apricot                                     **
**                     Irvine, CA 92720                                 **
**                                                                      **
**                                                                      **
**  DISCLAIMER OF WARRANTIES:                                           **
**                                                                      **
**    The following [enclosed] code is provided to you "AS IS",         **
**    without warranty of any kind.  You have a royalty-free right to   **
**    use, modify, reproduce and distribute the following code (and/or  **
**    any modified version) provided that you agree that Advanced       **
**    Gravis has no warranty obligations and shall not be liable for    **
**    any damages arising out of your use of this code, even if they    **
**    have been advised of the possibility of such damages.  This       **
**    Copyright statement and Disclaimer of Warranties may not be       **
**    removed.                                                          **
**                                                                      **
\************************************************************************/

/* strategy.c
 *
 * Device driver strategy entry point and dispatch table
 *
 * History:
 *
 * Sep 30, 94  David Bollo    Initial version
 * Jul 02, 07  Mike Greene    Modified for Open Watcom
 * Sep 13, 11  Andy Willis    HLT version
 * Sep 21, 14  Tobias Karnat  HLT16 version
 */

#include <devhdr.h>
#include <devreqp.h>

// Strategy entry point
//
// The strategy entry point must be declared according to the STRATEGY
// calling convention, which fetches arguments from the correct registers.
#pragma aux STRATEGY far parm [es bx];
#pragma aux (STRATEGY) Strategy;

// Declare strategy entry points that are located in other source files
//
// StratInit  - Initialization entry point [init.c]
// StratIOCtl - IOCtl interface [ioctl.c]
extern uint16_t StratInit(REQP_INIT FAR *rp);
extern uint16_t StratIOCtl(REQP_HEADER FAR* rp);

ULONG  DevHlp;    // DevHelp Interface Address

static void StratNoOp(REQP_HEADER FAR *rp)
{
    rp->status = RPDONE;
}

void Strategy(REQP_ANY FAR *rp)
{
    // Strategy routine for device set in header.c
    if(rp->header.command < RP_END) {
        switch(rp->header.command) {
            case RP_INIT:
                StratInit((REQP_INIT FAR *)rp);
                break;

            case RP_IOCTL:
                StratIOCtl((REQP_HEADER FAR *)rp);
                break;

            case RP_OPEN:
            case RP_CLOSE:
                StratNoOp((REQP_HEADER FAR *)rp);
                break;

            default:
                rp->header.status = RPERR_COMMAND | RPDONE;
        }
    } else {
        rp->header.status = RPERR_COMMAND | RPDONE;
    }
}
