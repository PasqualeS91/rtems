/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/apimutex.h>

void _API_Mutex_Unlock(
  API_Mutex_Control *the_mutex
)
{
  _Thread_Disable_dispatch();
    _CORE_mutex_Surrender(
      &the_mutex->Mutex,
      the_mutex->Object.id,
      NULL
   );
  _Thread_Enable_dispatch();
}
