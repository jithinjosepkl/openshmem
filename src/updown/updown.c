/*
 *
 * Copyright (c) 2011 - 2015
 *   University of Houston System and Oak Ridge National Laboratory.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * o Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * o Neither the name of the University of Houston System, Oak Ridge
 *   National Laboratory nor the names of its contributors may be used to
 *   endorse or promote products derived from this software without specific
 *   prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */



#include <stdio.h>		/* NULL                           */
#include <sys/utsname.h>	/* uname()                        */
#include <sys/types.h>		/* size_t                         */

#include "globalvar.h"
#include "state.h"
#include "trace.h"
#include "atomic.h"

#include "barrier.h"
#include "barrier-all.h"
#include "broadcast.h"
#include "collect.h"
#include "fcollect.h"

#include "ping.h"
#include "utils.h"
#include "clock.h"
#include "exe.h"

#include "shmem.h"

#include "comms/comms.h"

#ifdef HAVE_FEATURE_PSHMEM
# include "pshmem.h"
#endif /* HAVE_FEATURE_PSHMEM */

#ifdef HAVE_FEATURE_EXPERIMENTAL
# include "pshmemx.h"
#endif /* HAVE_FEATURE_EXPERIMENTAL */

#include "version.h"

/* ----------------------------------------------------------------- */

/**
 * I shouldn't really initialize more than once
 */
static
inline
int
check_pe_status (void)
{
  int yn = 1;
  const pe_status_t s = GET_STATE (pe_status);

  switch (s)
    {
    case PE_UNINITIALIZED:	/* this is what it should be */
      yn = 1;
      break;
    case PE_UNKNOWN:
    case PE_RUNNING:
    case PE_SHUTDOWN:
    case PE_FAILED:
      __shmem_trace (SHMEM_LOG_INFO,
		     "OpenSHMEM has already been initialized (%s)",
		     __shmem_state_as_string (s)
		     );
      yn = 0;
      break;
    default:			/* shouldn't be here */
      yn = 0;
      break;
    }

  return yn;
}

static
inline
void
report_up (void)
{
  int maj, min;
  const int n = GET_STATE (numpes);
  const size_t h = GET_STATE (heapsize);

  if (__shmem_version (&maj, &min) == 0)
    {
      __shmem_trace (SHMEM_LOG_INIT,
		     "version %d.%d running on %d PE%s, using %zd bytes of symmetric heap",
		     maj, min,
		     n, (n == 1) ? "" : "s",
		     h
		     );
    }
}

#ifdef HAVE_FEATURE_PSHMEM
# pragma weak start_pes = pstart_pes
# define start_pes pstart_pes
#endif /* HAVE_FEATURE_PSHMEM */

/**
 * \brief This routine initializes the OpenSHMEM environment on the calling PE.
 *
 * \b Synopsis:
 *
 * - C/C++:
 * \code
 *   void start_pes (int npes);
 * \endcode
 *
 * - Fortran:
 * \code
 *   INTEGER npes
 *
 *   CALL START_PES (npes)
 * \endcode
 *
 * \param npes the number of PEs participating in the program.  This
 * is ignored and should be set to 0.
 *
 * \b Effect:
 *
 * Initializes the OpenSHMEM environment on the calling PE.
 *
 * \return None.
 *
 */

void
start_pes (int npes)
{
  if ( ! check_pe_status ())
    {
      return;
    }

  __shmem_comms_init ();

  /* just note start_pes() not passed 0, it's not a big deal */
  if (npes != 0)
    {
      __shmem_trace (SHMEM_LOG_INFO,
		     "start_pes() was passed %d, should be 0",
                     npes
		     );
    }

  report_up ();

  /*
   * and we're up and running
   */
}

#ifdef HAVE_FEATURE_EXPERIMENTAL

#ifdef HAVE_FEATURE_PSHMEM
# pragma weak shmemx_init = pshmemx_init
# define shmemx_init pshmemx_init
# pragma weak shmemx_finalize = pshmemx_finalize
# define shmemx_finalize pshmemx_finalize
#endif /* HAVE_FEATURE_PSHMEM */

void
shmemx_init (void)
{
  start_pes (0);
}

void
shmemx_finalize (void)
{
  __shmem_comms_exit (0);
}

#endif /* HAVE_FEATURE_EXPERIMENTAL */
