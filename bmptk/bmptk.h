//***************************************************************************
//
// file : bmptk/bmptk.h
//
// Copyright (c) 2012 ... 2015 Wouter van Ooijen (wouter@voti.nl)
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// This is the one header file a user should include to use bmptk.
//
//***************************************************************************

#ifndef _BMPTK_H_
#define _BMPTK_H_ 

#ifdef __cplusplus
   #include <cstdlib>
#else   
   #include <stdlib.h>
#endif

// ==========================================================================
// 
// BMPTK_HERE debug macro
//
// ==========================================================================

//! file-name : line-number macro
//
//! The macro BMPTK_HERE tranlsates to a newline, the file-name, ":",
//! and the line-number of the place where the BMPTK_HERE macro
//! appears. This can be usefull for debug logging.
#define BMPTK_STRINGYFY( X ) #X
#define BMPTK_HERE2( F, L ) ( "\n" F ":" BMPTK_STRINGYFY( L ) " " )
#define BMPTK_HERE BMPTK_HERE2( __FILE__, __LINE__ )

          
// ==========================================================================
// 
// include the target-specific header file(s)
//
// These macros are supplied by the makefile:
// BMPTK_INCLUDE_CHIP  : the chip (register) definition files
// BMPTK_INCLUDE_BMPTK : the bmptk functional implementation (as yet empty)
//
// ==========================================================================

#define BMPTK_QUOTE( X ) BMPTK_STRINGYFY( X )

#ifdef BMPTK_INCLUDE_CHIP
   #include BMPTK_QUOTE( BMPTK_INCLUDE_CHIP )
#endif
#ifdef BMPTK_INCLUDE_BMPTK
   #include BMPTK_QUOTE( BMPTK_INCLUDE_BMPTK )
#endif    

#ifdef __cplusplus
extern "C" {
#endif

/// the size (in bytes) reserved for the heap
//
/// On a bare-metal system this function returns the number of bytes reserved
/// for the heap. 
/// On a hosted system, where the heap space is allocated on demand,
/// it might not return a meaningful number.
size_t bmptk_heap_size();   

/// the size (in bytes) of the free space on the heap
//
/// On a bare-metal system this function returns the number of bytes of the 
/// heap that are currently free (not allocated).
///
/// On a hosted system, where the heap space is allocated on demand,
/// it might not return a meaningful number.
size_t bmptk_heap_free();   

/// the size (in bytes) in use (allocated) on the heap
//
/// On a bare-metal system this function returns the number of bytes of the 
/// heap that are currently in use (allocated).
///
/// On a hosted system it might not return a meaningful number.
size_t bmptk_heap_used();   

/// the size (in bytes) reserved for the stack
//
/// On a bare-metal system this function returns the number of bytes reserved
/// for the stack. 
///
/// On a hosted system, where the stack space is allocated on demand,
/// it might not return a meaningful number.
size_t bmptk_stack_size();

/// the size (in bytes) of the stack space that has never been used
//
/// On a bare-metal system this function returns the number of bytes of
/// the stack that have never been used. This is detected by 
/// initializing the stack space words with a marker value, and
/// checking for the first word that no longer contains the marker value.
///
/// On a hosted system, where the stack space is allocated on demand,
/// it might not return a meaningful number. 
size_t bmptk_stack_free();

/// the size (in bytes) of the stack space that has been used at some time
//
/// On a bare-metal system this function returns the maximum number of bytes of
/// the stack that have been used. This is detected by 
/// initializing the stack space words with a marker value, and
/// checking for the first word that no longer contains the marker value.
///
/// On a hosted system, where the stack space is allocated on demand,
/// it might not return a meaningful number. 
size_t bmptk_stack_used();

#ifdef __cplusplus
}
#endif
  
      
#endif // #ifndef _BMPTK_H_
