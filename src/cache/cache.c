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



/*
 * These are compatibility routines for older SGI architectures.  They
 * are now defined in OpenSHMEM to do nothing.
 */

#include "utils.h"
#include "trace.h"

/*
 * Compatibility no-op cache routines
 */

#ifdef HAVE_FEATURE_PSHMEM
# include "pshmem.h"
#endif /* HAVE_FEATURE_PSHMEM */


#ifdef HAVE_FEATURE_PSHMEM
# pragma weak shmem_clear_cache_inv = pshmem_clear_cache_inv
# define shmem_clear_cache_inv pshmem_clear_cache_inv
# pragma weak shmem_set_cache_inv = pshmem_set_cache_inv
# define shmem_set_cache_inv pshmem_set_cache_inv
# pragma weak shmem_set_cache_line_inv = pshmem_set_cache_line_inv
# define shmem_set_cache_line_inv pshmem_set_cache_line_inv
# pragma weak shmem_clear_cache_line_inv = pshmem_clear_cache_line_inv
# define shmem_clear_cache_line_inv pshmem_clear_cache_line_inv
# pragma weak shmem_udcflush = pshmem_udcflush
# define shmem_udcflush pshmem_udcflush
# pragma weak shmem_udcflush_line = pshmem_udcflush_line
# define shmem_udcflush_line pshmem_udcflush_line
#endif /* HAVE_FEATURE_PSHMEM */

static
inline
void
cache_helper (const char *name)
{
  INIT_CHECK ();
  __shmem_trace (SHMEM_LOG_CACHE,
		 "operation \"%s\" is a no-op",
		 name
		 );
  return;
}

/**
 * \brief shmem_set_cache_inv has no effect.
 *
 * \b Synopsis:
 *
 * - C/C++:
 * \code
 *   void shmem_set_cache_inv (void);
 * \endcode
 *
 * - Fortran:
 * \code
 *   CALL SHMEM_SET_CACHE_INV()
 * \endcode
 *
 * \b Effect:
 *
 * None.  Included for legacy use only.
 *
 * \return None.
 *
 */

void
shmem_set_cache_inv (void)
{
  cache_helper ("shmem_set_cache_inv");
}

/**
 * \brief shmem_clear_cache_inv has no effect.
 *
 * \b Synopsis:
 *
 * - C/C++:
 * \code
 *   void shmem_clear_cache_inv (void);
 * \endcode
 *
 * - Fortran:
 * \code
 *   CALL SHMEM_CLEAR_CACHE_INV()
 * \endcode
 *
 * \b Effect:
 *
 * None.  Included for legacy use only.
 *
 * \return None.
 *
 */

void
shmem_clear_cache_inv (void)
{
  cache_helper ("shmem_clear_cache_inv");
}

/**
 * \brief shmem_set_cache_line_inv has no effect.
 *
 * \b Synopsis:
 *
 * - C/C++:
 * \code
 *   void shmem_set_cache_line_inv (void *target);
 * \endcode
 *
 * - Fortran:
 * \code
 *   CALL SHMEM_SET_CACHE_LINE_INV(target)
 * \endcode
 *
 * \param target is the address of the cache line.
 *
 * \b Effect:
 *
 * None.  Included for legacy use only.
 *
 * \return None.
 *
 */

void
shmem_set_cache_line_inv (void *target)
{
  cache_helper ("shmem_set_cache_line_inv");
}

/**
 * \brief shmem_clear_cache_line_inv has no effect.
 *
 * \b Synopsis:
 *
 * - C/C++:
 * \code
 *   void shmem_clear_cache_line_inv (void *target);
 * \endcode
 *
 * - Fortran:
 * \code
 *   CALL SHMEM_CLEAR_CACHE_LINE_INV(target)
 * \endcode
 *
 * \param target is the address of the cache line.
 *
 * \b Effect:
 *
 * None.  Included for legacy use only.
 *
 * \return None.
 *
 */

void
shmem_clear_cache_line_inv (void *target)
{
  cache_helper ("shmem_clear_cache_line_inv");
}

/**
 * \brief shmem_udcflush has no effect.
 *
 * \b Synopsis:
 *
 * - C/C++:
 * \code
 *   void shmem_udcflush (void);
 * \endcode
 *
 * - Fortran:
 * \code
 *   CALL SHMEM_UDCFLUSH()
 * \endcode
 *
 * \b Effect:
 *
 * None.  Included for legacy use only.
 *
 * \return None.
 *
 */

void
shmem_udcflush (void)
{
  cache_helper ("shmem_udcflush");
}

/**
 * \brief shmem_udcflush_line has no effect.
 *
 * \b Synopsis:
 *
 * - C/C++:
 * \code
 *   void shmem_udcflush_line (void *target);
 * \endcode
 *
 * - Fortran:
 * \code
 *   CALL SHMEM_UDCFLUSH_LINE(target)
 * \endcode
 *
 * \param target is the address of the cache line.
 *
 * \b Effect:
 *
 * None.  Included for legacy use only.
 *
 * \return None.
 *
 */

void
shmem_udcflush_line (void *target)
{
  cache_helper ("shmem_udcflush_line");
}
