/**
 * @file
 *
 * @ingroup mpc55xx_esci
 *
 * @brief Header file for the Enhanced Serial Communication Interface (eSCI).
 */

/*
 * Copyright (c) 2008
 * Embedded Brains GmbH
 * Obere Lagerstr. 30
 * D-82178 Puchheim
 * Germany
 * rtems@embedded-brains.de
 *
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rtems.com/license/LICENSE.
 */

/**
 * @defgroup mpc55xx_esci Enhanced Serial Communication Interface (eSCI).
 *
 * @ingroup mpc55xx
 */

#ifndef LIBCPU_POWERPC_MPC55XX_ESCI_H
#define LIBCPU_POWERPC_MPC55XX_ESCI_H

#include <rtems/termiostypes.h>

#define MPC55XX_ESCI_NUMBER 2

struct ESCI_tag;

typedef struct {
	volatile struct ESCI_tag *regs;
	const char *device_name;
	int use_termios;
	int use_interrupts;
	int console;
	struct rtems_termios_tty *tty;
	unsigned irq_number;
} mpc55xx_esci_driver_entry;

extern mpc55xx_esci_driver_entry mpc55xx_esci_driver_table [ /* MPC55XX_ESCI_NUMBER */ ];

#endif /* LIBCPU_POWERPC_MPC55XX_ESCI_H */
