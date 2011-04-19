/* misc/auxiliary.h.  Generated from auxiliary.h.in by configure.  */
/*****************************************************************************\
 * Computer Algebra System SINGULAR    
\*****************************************************************************/
/** @file auxiliary.h
 * 
 * All the auxiliary stuff.
 *
 * ABSTRACT: we shall put here everything that does not have its own place.
 *
 * @author Oleksandr Motsak
 *
 * @internal @version \$Id$
 *
 **/
/*****************************************************************************/

#ifndef MISC_AUXILIARY_H
#define MISC_AUXILIARY_H

// ----------------- which parts/extensions of Singular to build
#ifndef HAVE_RINGS
#define HAVE_RINGS
#endif

#ifndef HAVE_PLURAL
#define HAVE_PLURAL
#endif

// no factory yet...
// #ifndef HAVE_FACTORY
// #define HAVE_FACTORY
// #endif

// ----------------  end of parts/extensions
// -----------------  configure stuff

// TODO: the following should go to some config.h... no?

/* Define version as a string */
#ifndef S_VERSION1
#define S_VERSION1 "spielwiese"
#endif

/* Absolute pathname of root directory of Singular source */
#ifndef S_ROOT_DIR
#define S_ROOT_DIR ""
#endif

// ----------------- end of configure stuff

// ---------------- Singular standard types etc.
// BOOLEAN

#ifndef SIZEOF_LONG

#include <misc/mylimits.h>

#ifndef LONG_BIT
#if ULONG_MAX == 0xffffffffUL
#define LONG_BIT 32
#elif ULONG_MAX == 0xffffffffffffffffULL
#define LONG_BIT 64
#else
#error "Unexpected max for unsigned long"
#endif
#endif

#define SIZEOF_LONG 8
// another option for SIZEOF_LONG: use omConfig included in <omalloc/omalloc.h>...

#endif





#if (SIZEOF_LONG == 8)
typedef int BOOLEAN;
/* testet on x86_64, gcc 3.4.6: 2 % */
/* testet on IA64, gcc 3.4.6: 1 % */
#else
/* testet on athlon, gcc 2.95.4: 1 % */
typedef short BOOLEAN;
#endif

#ifndef FALSE
#define FALSE       0
#endif

#ifndef TRUE
#define TRUE        1
#endif

#ifndef NULL
#define NULL        (0)
#endif

#ifndef NULLp
#define NULLp        ((void*)NULL)
#endif

// #ifdef _TRY
#ifndef ABS
#define ABS(x) ((x)<0?(-(x)):(x))
#endif
// #endif

static const int MAX_INT_LEN= 11;
typedef void* ADDRESS;

#define loop for(;;)

#if defined(__cplusplus)
static inline int si_max(const int a, const int b)  { return (a>b) ? a : b; }
static inline int si_min(const int a, const int b)  { return (a<b) ? a : b; }
static inline long si_max(const long a, const long b)  { return (a>b) ? a : b; }
static inline unsigned long si_max(const unsigned long a, const unsigned long b)  { return (a>b) ? a : b; }
static inline long si_min(const long a, const long b)  { return (a<b) ? a : b; }
static inline unsigned long si_min(const unsigned long a, const unsigned long b)  { return (a<b) ? a : b; }
#else
#define si_max(A,B) ((A) > (B) ? (A) : (B))
#define si_min(A,B) ((A) < (B) ? (A) : (B))
#endif


// ---------------- end of Singular standard types etc.
// ---------------- defines which depend on the settings above

#ifndef HAVE_MULT_MOD
#define HAVE_MULT_MOD 1
#endif

#ifndef HAVE_DIV_MOD
/* #undef HAVE_DIV_MOD */
#endif

#ifndef HAVE_GENERIC_ADD
/* #undef HAVE_GENERIC_ADD */
#endif

/*******************************************************************
 * DEBUG OPTIONS
 * -- only significant for for compiling without -DNDEBUG
 * -- you better know what your are doing, if you touch this
 ******************************************************************/
#ifndef NDEBUG

/* undefine to enable inline */
#define NO_INLINE

/* undefine to disable assume -- should normally be defined for NDEBUG */
#define HAVE_ASSUME

/* undef PDEBUG to disable checks of polys

 define PDEBUG to
  0 for enabling pTest
  1 plus tests in Level 1 poly routines (operations on monomials)
  2 plus tests in Level 2 poly routines (operations on single exponents)
 -- see also polys.h for more info

 NOTE: you can set the value of PDEBUG on a per-file basis, before
       including mod2.h, provided ! PDEBUG is defined in mod2.h E.g.:

       #define PDEBUG 2
       #include "auxiliary.h"
       ...

       makes sure that all poly operations in your file are done with 
       PDEBUG == 2
 To break after an error occured, set a debugger breakpoint on
 dErrorBreak. 
*/
#ifndef PDEBUG
#define PDEBUG 0
#endif

/* define MDEBUG to enable memory checks */
#define MDEBUG 0

#ifdef MDEBUG
/* If ! defined(OM_NDEBUG) and (defined(OM_TRACK) or defined(OM_CHECK)
   then omDebug routines are used for memory allocation/free:

   The omDebug routines are controlled by the values of OM_TRACK, OM_CHECK
   and OM_KEEP.  There meaning is roughly as follows:
   OM_TRACK: strored with address                              : extra space
     0     : no additional info is stored                      : 0
     1     : file:line of location where address was allocated : 1 word
     2     : plus backtrace of stack where adress was allocated: 6 words
     3     : plus size/bin info and front-, and back padding   : 9 words
     4     : plus file:line of location where adress was freed : 10 words
     5     : plus backtrace of stack where adress was allocated: 15 words
   OM_CHECK: checks done
     0     : no checks
     1     : constant-time checks: i.e. addr checks only
     2     : plus linear-time checks and constant related bin check
     3     : plus quadratic-time checks and linear-time related bin checks and
             constant time all memory checks
     4     : and so on
     ==> for OM_CHECK >= 3 it gets rather slow
   OM_KEEP:  determines whether addresses are really freed  (
     0     : addresses are really freed
     1     : addresses are only marked as free and not really freed.

   OM_CHECK, OM_TRACK, and OM_KEEP can be set on a per-file basis 
   (as can OM_NDEBUG),  e.g.:
     #define OM_CHECK 3
     #define OM_TRACK 5
     #define OM_KEEP  1
     #include "mod2.h"
     #include "omalloc.h"
   ensures that all memory allocs/free in this file are done with 
   OM_CHECK==3 and OM_TRACK==5, and that all addresses allocated/freed 
   in this file are only marked as free and never really freed.
 
   To set OM_CHECK, OM_TRACK and OM_KEEP under dynamic scope, set 
   om_Opts.MinCheck, om_Opts.MinTrack to the respectiv values and 
   om_Opts.Keep to the number of addresses which are kept before they are 
   actually freed. E.g.:
     int check=om_Opts.MinCheck, track=om_Opts.MinTrack, keep= m_OPts.Keep;
     om_Opts.MinCheck = 3; om_Opts.MinTrack = 5; omOpts.Keep = LONG_MAX;
     ExternalRoutine();
     om_Opts.MinCheck = check; omOpts.MinTrack = track; omOpts.Keep = keep;
   ensures that all calls omDebug routines  occuring during the computation of
   ExternalRoutine() are done with OM_CHECK==3 and OM_TRACK==5, and 
   calls to omFree only mark addresses as free and not really free them.

   Furthermore, the value of OM_SING_KEEP (resp. om_Opts.Keep) specifies 
   how many addresses are kept before they are actually freed, independently 
   of the value of OM_KEEP.

   Some tips on possible values of OM_TRACK, OM_CHECK, OM_KEEP:
   + To find out about an address that has been freed twice, first locate the
     file(s) where the error occured, and then at the beginning of these files:
       #define OM_CHECK 3
       #define OM_TRACK 5
       #define OM_KEEP  1
       #include "mod2.h"
       #include "omalloc.h"
     Under dynamic scope, do (e.g., from within the debugger):
       om_Opts.MinCheck = 3; om_Opts.MinTrack = 5; omOpts.Keep = LONG_MAX;
   + to find out where "memory corruption" occured, increase value of 
     OM_CHECK - the higher this value is, the more consistency checks are 
     done (However a value > 3 checks the entire memory each time an omalloc 
     routine is used!)
   
   Some more tips on the usage of omalloc:
   + omAlloc*, omRealloc*, omFree*, omCheck* omDebug* omTest* rotuines 
     assume that sizes are > 0 and pointers are != NULL
   + omalloc*, omrealloc*, omfree* omcheck*, omdebug* omtest* routines allow
     NULL pointers and sizes == 0
   + You can safely use any free/realloc routine in combination with any alloc 
     routine (including the debug versions): E.g., an address allocated with
     omAllocBin can be freed with omfree, or an adress allocated with 
     om(Debug)Alloc can be freed with omfree, or omFree, or omFreeSize, etc.
     However, keep in mind that the efficiency decreases from 
     Bin over Size to General routines (i.e., omFreeBin is more efficient than
     omFreeSize which is more efficient than omFree, likewise with the alloc
     routines).
   + if OM_CHECK is undefined or 0, then all omCheck routines do nothing
   + if OM_CHECK and OM_TRACK are both undefined (or 0), or if OM_NDEBUG is 
     defined, then the "real" alloc/realloc/free macros are used, and all 
     omTest, omDebug and omCheck routines are undefined
   + to break after an omError occured within a debugger, 
     set a breakpoint on dErrorBreak
   + to do checks from within the debugger, or to do checks with explicit 
     check level, use omTest routines.
*/

/* by default, store alloc info and file/line where addr was freed */
#ifndef OM_TRACK
#define OM_TRACK 4
#endif
/* only do constant-time memory checks */
#ifndef OM_CHECK
#define OM_CHECK 1
#endif
/* Do actually free memory: 
   (be careful: if this is set, memory is never really freed, 
    but only marked as free) */
#ifndef OM_KEEP
#define OM_KEEP 0
#endif
/* but only after you have freed 1000 more addresses 
   (this is actually independent of the value of OM_KEEP and used
   to initialize om_Opts.Keep) */
#ifndef OM_SING_KEEP
#define OM_SING_KEEP 1000
#endif

#endif /* MDEBUG */


/* undef KDEBUG for check of data during std computations 
 *
 * define KDEBUG to
 * 0 for basic tests
 * 1 for tests in kSpoly 
 * NOTE: You can locally enable tests in kspoly by setting the 
 *       define at the beginning of kspoly.cc
 */
#define KDEBUG 0

/* define LDEBUG checking numbers, undefine otherwise */
#define LDEBUG
/* define RDEBUG checking rings (together with TRACE=9) */
#define RDEBUG
/* define TEST for non time critical tests, undefine otherwise */
#define TEST

/* define YYDEBUG 1 for debugging bison texts, 0 otherwise */
#define YYDEBUG 1

#endif 
/* end of debugging option (ifndef NDEBUG) */



#ifdef _DEBUG
#      define FORCE_INLINE inline
#else
#ifdef NDEBUG
#if   defined(_MSC_VER)
#      define FORCE_INLINE __forceinline
#elif defined(__GNUC__) && __GNUC__ > 3
#      define FORCE_INLINE inline __attribute__ ((always_inline))
#else
#      define FORCE_INLINE inline
#endif
#else
#      define FORCE_INLINE inline
#endif
/* NDEBUG */
#endif
/* _DEBUG */


#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(who, msg) DO_PRAGMA(message ("TODO [for " #who "]: " #msg))



#if defined(__GNUC__) && defined(__GNUC_MINOR__)
#define _GNUC_PREREQ(maj, min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#define _GNUC_PREREQ(maj, min) 0
#endif

#if _GNUC_PREREQ(3,3) && defined(__ELF__)
#define FORCE_INTERNAL __attribute__ ((visibility ("internal")))
#else
#define FORCE_INTERNAL
#endif

#if _GNUC_PREREQ(3,3)
#define FORCE_DEPRECATED __attribute__ ((deprecated))
#else
#define FORCE_DEPRECATED
#endif

#ifdef __cplusplus
# define  BEGIN_CDECL extern "C" {
# define  END_CDECL   }
#else
# define  BEGIN_CDECL
# define  END_CDECL
#endif



#endif 
/* MISC_AUXILIARY_H */

