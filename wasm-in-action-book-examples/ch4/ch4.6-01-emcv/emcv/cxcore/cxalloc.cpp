////////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                 License For Embedded Computer Vision Library
//
// Copyright (c) 2008-2013, EMCV Project,
// Copyright (c) 2000-2007, Intel Corporation,
// All rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, 
//      this list of conditions and the following disclaimer in the documentation 
//      and/or other materials provided with the distribution.
//    * Neither the name of the copyright holders nor the names of their contributors 
//      may be used to endorse or promote products derived from this software 
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
// OF SUCH DAMAGE.
//
// Contributors:
//    * Shiqi Yu (Shenzhen Institute of Advanced Technology, Chinese Academy of Sciences)


#include "_cxcore.h"

#ifdef _TMS320C6X

// default <memalign>
void*
cvAlloc( size_t size)
{
	void * ptr;
	CV_FUNCNAME( "cvAlloc" );
	__BEGIN__;

	ptr = memalign( (CV_MALLOC_ALIGN/8), size);
	if( !ptr )
        CV_ERROR( CV_StsNoMem, "Out of memory" );

	__END__;
	return ptr;
}
// default <free>
void
cvFree_( void* ptr)
{
	if(ptr)
	    free(ptr);
}

#else	// _TMS320C6X

#include <stdlib.h>

// default <malloc>
void*
cvAlloc( size_t size)
{
    char *ptr, *ptr0;
	CV_FUNCNAME( "cvAlloc" );
	__BEGIN__;
    
    ptr0 = (char*)malloc(
        (size_t)(size + CV_MALLOC_ALIGN*((size >= 4096) + 1) + sizeof(char*)));

    if( !ptr0 )
        return 0;

    // align the pointer
    ptr = (char*)cvAlignPtr(ptr0 + sizeof(char*) + 1, CV_MALLOC_ALIGN);
    *(char**)(ptr - sizeof(char*)) = ptr0;

	__END__;
    return ptr;
}
// default <free>
void
cvFree_( void* ptr)
{
    // Pointer must be aligned by CV_MALLOC_ALIGN
	if(ptr)
	{
	    if( ((size_t)ptr & (CV_MALLOC_ALIGN-1)) != 0 )
    	    abort();
	    free( *((char**)ptr - 1) );
	}
	
}

#endif	// _TMS320C6X

/* End of file. */

