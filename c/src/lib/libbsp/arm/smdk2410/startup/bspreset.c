/*
 *  Copyright (c) 2002 by Jay Monkman <jtm@smoothsmoothie.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#include <bsp.h>

void bsp_reset(void)
{
#if ON_SKYEYE == 1
  #define SKYEYE_MAGIC_ADDRESS (*(volatile unsigned int *)(0xb0000000))

  SKYEYE_MAGIC_ADDRESS = 0xff;
#else
  /* XXX TODO this code is copied from gp32.. move it to a shared place */
  rtems_interrupt_level level;
  rtems_interrupt_disable(level);
  /* disable mmu, invalide i-cache and call swi #4 */
  asm volatile(""
    "mrc    p15,0,r0,c1,c0,0  \n"
    "bic    r0,r0,#1          \n"
    "mcr    p15,0,r0,c1,c0,0  \n"
    "nop                      \n"
    "nop                      \n"
    "nop                      \n"
    "nop                      \n"
    "nop                      \n"
    "mov    r0,#0             \n"
    "MCR    p15,0,r0,c7,c5,0  \n"
    "nop                      \n"
    "nop                      \n"
    "nop                      \n"
    "nop                      \n"
    "nop                      \n"
    "swi    #4                "
    :
    :
    : "r0"
  );
  /* we should be back in bios now */
#endif
}
