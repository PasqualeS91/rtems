/*  bspstart.c
 *
 *  This set of routines starts the application.  It includes application,
 *  board, and monitor specific initialization and configuration.
 *  The generic CPU dependent initialization has been performed
 *  before any of these are invoked.
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may in
 *  the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#include <string.h>

#include <bsp.h>
#include <rtems/bspIo.h>
#include <rtems/libio.h>
#include <libcpu/cpuIdent.h>
#define DEBUG 1

/*
 * Where the heap starts; is used by bsp_pretasking_hook;
 */
unsigned int BSP_heap_start;

/*
 * Total RAM available and associated linker symbol
 */
unsigned int BSP_mem_size;
extern char  RamSize[];

/*
 * PCI Bus Frequency
 */
unsigned int BSP_bus_frequency;  /* XXX - Set this based upon the Score board */

/*
 * processor clock frequency
 */
unsigned int BSP_processor_frequency; /* XXX - Set this based upon the Score board */

/*
 * Time base divisior (how many tick for 1 second).
 */
unsigned int BSP_time_base_divisor = 4000;

extern unsigned long __rtems_end[];

/*
 *  Driver configuration parameters
 */
uint32_t   bsp_clicks_per_usec;

void BSP_panic(char *s)
{
  printk("%s PANIC %s\n",_RTEMS_version, s);
  __asm__ __volatile ("sc");
}

void _BSP_Fatal_error(unsigned int v)
{
  printk("%s PANIC ERROR %x\n",_RTEMS_version, v);
  __asm__ __volatile ("sc");
}

/*
 *  bsp_predriver_hook
 *
 *  Before drivers are setup initialize interupt vectors.
 */

void init_RTC();
void initialize_PMC();

void bsp_predriver_hook(void)
{

#if (HAS_PMC_PSC8)
  #if DEBUG
    printk("bsp_predriver_hook: initialize_PMC\n");
  #endif
  initialize_PMC();
#endif

  #if DEBUG
    printk("bsp_predriver_hook: End of routine\n");
  #endif

}

/*PAGE
 *
 *  initialize_PMC
 */

void initialize_PMC() {
  volatile uint32_t     *PMC_addr;
  uint32_t               data;

  /*
   * Clear status, enable SERR and memory space only.
   */
  PMC_addr = BSP_PCI_DEVICE_ADDRESS( 0x4 );
  *PMC_addr = 0x020080cc;
  #if DEBUG
    printk("initialize_PMC: 0x%x = 0x%x\n", PMC_addr, 0x020080cc);
  #endif

  /*
   * set PMC base address.
   */
  PMC_addr  = BSP_PCI_DEVICE_ADDRESS( 0x14 );
  *PMC_addr = (BSP_PCI_REGISTER_BASE >> 24) & 0x3f;
  #if DEBUG
    printk("initialize_PMC: 0x%x = 0x%x\n", PMC_addr, ((BSP_PCI_REGISTER_BASE >> 24) & 0x3f));
  #endif

   PMC_addr = (volatile uint32_t*)
      BSP_PMC_SERIAL_ADDRESS( 0x100000 );
  data = *PMC_addr;
  #if DEBUG
    printk("initialize_PMC: Read 0x%x (0x%x)\n", PMC_addr, data );
    printk("initialize_PMC: Read 0x%x (0x%x)\n", PMC_addr, data & 0xfc );
  #endif
  *PMC_addr = data & 0xfc;
}

/*PAGE
 *
 *  bsp_postdriver_hook
 *
 *  Standard post driver hook plus some BSP specific stuff.
 */

void bsp_postdriver_hook(void)
{
  extern void Init_EE_mask_init(void);
  extern void open_dev_console(void);

  #if DEBUG
    printk("bsp_postdriver_hook: initialize libio\n");
  #endif
  if (rtems_libio_supp_helper)
    (*rtems_libio_supp_helper)();
  ShowBATS();

  #if DEBUG
    printk("bsp_postdriver_hook: Init_EE_mask_init\n");
  #endif
  Init_EE_mask_init();
  ShowBATS();
  #if DEBUG
    printk("bsp_postdriver_hook: Finished procedure\n");
  #endif
}

void bsp_set_trap_vectors( void );

/*PAGE
 *
 *  bsp_start
 *
 *  This routine does the bulk of the system initialization.
 */

void bsp_start( void )
{
  unsigned int         msr_value = 0x0000;
  uint32_t             intrStackStart;
  uint32_t             intrStackSize;
  volatile uint32_t   *ptr;
  ppc_cpu_id_t         myCpu;
  ppc_cpu_revision_t   myCpuRevision;
 
  rtems_bsp_delay( 1000 );

  /*
   *  Zero out lots of memory
   */
  #if DEBUG
    printk("bsp_start: Zero out lots of memory\n");
  #endif

  memset(
    &end,
    0,
    (unsigned char *)&RAM_END - (unsigned char *) &end
  );

  BSP_processor_frequency = 266000000;
  BSP_bus_frequency       =  66000000;

  /*
   * Get CPU identification dynamically. Note that the get_ppc_cpu_type()
   * function store the result in global variables so that it can be used 
   * later...
   */
  myCpu         = get_ppc_cpu_type();
  myCpuRevision = get_ppc_cpu_revision();
  printk("Cpu: 0x%x  Revision: %d\n", myCpu, myCpuRevision);
  printk("Cpu %s\n", get_ppc_cpu_type_name(myCpu) );

  /*
   * Initialize the interrupt related settings.
   */
  intrStackStart = (uint32_t) __rtems_end;
  intrStackSize = rtems_configuration_get_interrupt_stack_size();

  BSP_heap_start = intrStackStart + intrStackSize;
  BSP_mem_size = (uintptr_t) RamSize;

  /*
   * Initialize default raw exception handlers.
   */
  ppc_exc_initialize(
    PPC_INTERRUPT_DISABLE_MASK_DEFAULT,
    intrStackStart,
    intrStackSize
  );
  #if DEBUG
    printk("bsp_predriver_hook: init_RTC\n");
  #endif

/*   init_RTC(); */
  init_PCI();
  initialize_universe();

  #if DEBUG
    printk("bsp_predriver_hook: initialize_PCI_bridge\n");
  #endif
  initialize_PCI_bridge ();

  msr_value = 0x2030;
  _CPU_MSR_SET( msr_value );


  _CPU_MSR_SET( msr_value );

  /*
   *  initialize the device driver parameters
   */
  #if DEBUG
    printk("bsp_start: set clicks poer usec\n");
  #endif
  bsp_clicks_per_usec = 66 / 4;  /* XXX get from linkcmds */

#if ( PPC_USE_DATA_CACHE )
  #if DEBUG
    printk("bsp_start: cache_enable\n");
  #endif
  instruction_cache_enable ();
  data_cache_enable ();
  #if DEBUG
    printk("bsp_start: END PPC_USE_DATA_CACHE\n");
  #endif
#endif

  /* Initalize interrupt support */
  if (bsp_interrupt_initialize() != RTEMS_SUCCESSFUL) {
    BSP_panic( "Cannot intitialize interrupt support\n");
  }

  #if DEBUG
    printk("bsp_start: end BSPSTART\n");
  ShowBATS();
  #endif
}
