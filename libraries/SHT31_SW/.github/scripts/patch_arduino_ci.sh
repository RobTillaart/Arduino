#!/bin/bash

# Temporay patch for arduino_ci
# 
# util/atomic.h hasn't been mocked so far, once this chenges, throw this awy.
# For now copy a mock version of atomic.h into the appropriate directory.


GEMDIR="`gem environment gemdir 2>/dev/null`"
CIDIR="gems/`ls -1 ${GEMDIR}/gems | grep 'arduino_ci.*'`"
UTILDIR="${GEMDIR}/${CIDIR}/cpp/arduino/util"

if [[ ! -e  "${UTILDIR}" ]]; then
    mkdir "${UTILDIR}"
fi

ATOMIC_H="${UTILDIR}/atomic.h"

if [[ -e "${ATOMIC_H}" ]]; then
    exit 0
fi

echo '/* Copyright (c) 2007 Dean Camera' >>${ATOMIC_H}
echo '   All rights reserved.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '   Redistribution and use in source and binary forms, with or without' >>${ATOMIC_H}
echo '   modification, are permitted provided that the following conditions are met:' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '   * Redistributions of source code must retain the above copyright' >>${ATOMIC_H}
echo '     notice, this list of conditions and the following disclaimer.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '   * Redistributions in binary form must reproduce the above copyright' >>${ATOMIC_H}
echo '     notice, this list of conditions and the following disclaimer in' >>${ATOMIC_H}
echo '     the documentation and/or other materials provided with the' >>${ATOMIC_H}
echo '     distribution.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '   * Neither the name of the copyright holders nor the names of' >>${ATOMIC_H}
echo '     contributors may be used to endorse or promote products derived' >>${ATOMIC_H}
echo '     from this software without specific prior written permission.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"' >>${ATOMIC_H}
echo '  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE' >>${ATOMIC_H}
echo '  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE' >>${ATOMIC_H}
echo '  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE' >>${ATOMIC_H}
echo '  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR' >>${ATOMIC_H}
echo '  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF' >>${ATOMIC_H}
echo '  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS' >>${ATOMIC_H}
echo '  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN' >>${ATOMIC_H}
echo '  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)' >>${ATOMIC_H}
echo '  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE' >>${ATOMIC_H}
echo '  POSSIBILITY OF SUCH DAMAGE.' >>${ATOMIC_H}
echo '*/' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '/* $Id$ */' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '#ifndef _UTIL_ATOMIC_H_' >>${ATOMIC_H}
echo '#define _UTIL_ATOMIC_H_ 1' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '#include <avr/io.h>' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '#if !defined(__DOXYGEN__)' >>${ATOMIC_H}
echo '/* Internal helper functions. */' >>${ATOMIC_H}
echo 'static __inline__ uint8_t __iSeiRetVal(void)' >>${ATOMIC_H}
echo '{' >>${ATOMIC_H}
echo '    return 1;' >>${ATOMIC_H}
echo '}' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo 'static __inline__ uint8_t __iCliRetVal(void)' >>${ATOMIC_H}
echo '{' >>${ATOMIC_H}
echo '    return 1;' >>${ATOMIC_H}
echo '}' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo 'static __inline__ void __iSeiParam(const uint8_t *__s)' >>${ATOMIC_H}
echo '{' >>${ATOMIC_H}
echo '    __asm__ volatile ("" ::: "memory");' >>${ATOMIC_H}
echo '    (void)__s;' >>${ATOMIC_H}
echo '}' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo 'static __inline__ void __iCliParam(const uint8_t *__s)' >>${ATOMIC_H}
echo '{' >>${ATOMIC_H}
echo '    __asm__ volatile ("" ::: "memory");' >>${ATOMIC_H}
echo '    (void)__s;' >>${ATOMIC_H}
echo '}' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo 'static __inline__ void __iRestore(const  uint8_t *__s)' >>${ATOMIC_H}
echo '{' >>${ATOMIC_H}
echo '    SREG = *__s;' >>${ATOMIC_H}
echo '    __asm__ volatile ("" ::: "memory");' >>${ATOMIC_H}
echo '}' >>${ATOMIC_H}
echo '#endif	/* !__DOXYGEN__ */' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '/** \file */' >>${ATOMIC_H}
echo '/** \defgroup util_atomic <util/atomic.h> Atomically and Non-Atomically Executed Code Blocks' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    \code' >>${ATOMIC_H}
echo '    #include <util/atomic.h>' >>${ATOMIC_H}
echo '    \endcode' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    \note The macros in this header file require the ISO/IEC 9899:1999' >>${ATOMIC_H}
echo '    ("ISO C99") feature of for loop variables that are declared inside' >>${ATOMIC_H}
echo '    the for loop itself.  For that reason, this header file can only' >>${ATOMIC_H}
echo '    be used if the standard level of the compiler (option --std=) is' >>${ATOMIC_H}
echo '    set to either \c c99 or \c gnu99.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    The macros in this header file deal with code blocks that are' >>${ATOMIC_H}
echo '    guaranteed to be excuted Atomically or Non-Atmomically.  The term' >>${ATOMIC_H}
echo '    "Atomic" in this context refers to the unability of the respective' >>${ATOMIC_H}
echo '    code to be interrupted.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    These macros operate via automatic manipulation of the Global' >>${ATOMIC_H}
echo '    Interrupt Status (I) bit of the SREG register. Exit paths from' >>${ATOMIC_H}
echo '    both block types are all managed automatically without the need' >>${ATOMIC_H}
echo '    for special considerations, i. e. the interrupt status will be' >>${ATOMIC_H}
echo '    restored to the same value it has been when entering the' >>${ATOMIC_H}
echo '    respective block.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    A typical example that requires atomic access is a 16 (or more)' >>${ATOMIC_H}
echo '    bit variable that is shared between the main execution path and an' >>${ATOMIC_H}
echo '    ISR.  While declaring such a variable as volatile ensures that the' >>${ATOMIC_H}
echo '    compiler will not optimize accesses to it away, it does not' >>${ATOMIC_H}
echo '    guarantee atomic access to it.  Assuming the following example:' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    \code' >>${ATOMIC_H}
echo '#include <inttypes.h>' >>${ATOMIC_H}
echo '#include <avr/interrupt.h>' >>${ATOMIC_H}
echo '#include <avr/io.h>' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo 'volatile uint16_t ctr;' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo 'ISR(TIMER1_OVF_vect)' >>${ATOMIC_H}
echo '{' >>${ATOMIC_H}
echo '  ctr--;' >>${ATOMIC_H}
echo '}' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '...' >>${ATOMIC_H}
echo 'int' >>${ATOMIC_H}
echo 'main(void)' >>${ATOMIC_H}
echo '{' >>${ATOMIC_H}
echo '   ...' >>${ATOMIC_H}
echo '   ctr = 0x200;' >>${ATOMIC_H}
echo '   start_timer();' >>${ATOMIC_H}
echo '   while (ctr != 0)' >>${ATOMIC_H}
echo '     // wait' >>${ATOMIC_H}
echo '       ;' >>${ATOMIC_H}
echo '   ...' >>${ATOMIC_H}
echo '}' >>${ATOMIC_H}
echo '    \endcode' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    There is a chance where the main context will exit its wait loop' >>${ATOMIC_H}
echo '    when the variable \c ctr just reached the value 0xFF.  This happens' >>${ATOMIC_H}
echo '    because the compiler cannot natively access a 16-bit variable' >>${ATOMIC_H}
echo '    atomically in an 8-bit CPU.  So the variable is for example at' >>${ATOMIC_H}
echo '    0x100, the compiler then tests the low byte for 0, which succeeds.' >>${ATOMIC_H}
echo '    It then proceeds to test the high byte, but that moment the ISR' >>${ATOMIC_H}
echo '    triggers, and the main context is interrupted.  The ISR will' >>${ATOMIC_H}
echo '    decrement the variable from 0x100 to 0xFF, and the main context' >>${ATOMIC_H}
echo '    proceeds.  It now tests the high byte of the variable which is' >>${ATOMIC_H}
echo '    (now) also 0, so it concludes the variable has reached 0, and' >>${ATOMIC_H}
echo '    terminates the loop.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    Using the macros from this header file, the above code can be' >>${ATOMIC_H}
echo '    rewritten like:' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    \code' >>${ATOMIC_H}
echo '#include <inttypes.h>' >>${ATOMIC_H}
echo '#include <avr/interrupt.h>' >>${ATOMIC_H}
echo '#include <avr/io.h>' >>${ATOMIC_H}
echo '#include <util/atomic.h>' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo 'volatile uint16_t ctr;' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo 'ISR(TIMER1_OVF_vect)' >>${ATOMIC_H}
echo '{' >>${ATOMIC_H}
echo '  ctr--;' >>${ATOMIC_H}
echo '}' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '...' >>${ATOMIC_H}
echo 'int' >>${ATOMIC_H}
echo 'main(void)' >>${ATOMIC_H}
echo '{' >>${ATOMIC_H}
echo '   ...' >>${ATOMIC_H}
echo '   ctr = 0x200;' >>${ATOMIC_H}
echo '   start_timer();' >>${ATOMIC_H}
echo '   sei();' >>${ATOMIC_H}
echo '   uint16_t ctr_copy;' >>${ATOMIC_H}
echo '   do' >>${ATOMIC_H}
echo '   {' >>${ATOMIC_H}
echo '     ATOMIC_BLOCK(ATOMIC_FORCEON)' >>${ATOMIC_H}
echo '     {' >>${ATOMIC_H}
echo '       ctr_copy = ctr;' >>${ATOMIC_H}
echo '     }' >>${ATOMIC_H}
echo '   }' >>${ATOMIC_H}
echo '   while (ctr_copy != 0);' >>${ATOMIC_H}
echo '   ...' >>${ATOMIC_H}
echo '}' >>${ATOMIC_H}
echo '    \endcode' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    This will install the appropriate interrupt protection before' >>${ATOMIC_H}
echo '    accessing variable \c ctr, so it is guaranteed to be consistently' >>${ATOMIC_H}
echo '    tested.  If the global interrupt state were uncertain before' >>${ATOMIC_H}
echo '    entering the ATOMIC_BLOCK, it should be executed with the' >>${ATOMIC_H}
echo '    parameter ATOMIC_RESTORESTATE rather than ATOMIC_FORCEON.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    See \ref optim_code_reorder for things to be taken into account' >>${ATOMIC_H}
echo '    with respect to compiler optimizations.' >>${ATOMIC_H}
echo '*/' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '/** \def ATOMIC_BLOCK(type)' >>${ATOMIC_H}
echo '    \ingroup util_atomic' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    Creates a block of code that is guaranteed to be executed' >>${ATOMIC_H}
echo '    atomically. Upon entering the block the Global Interrupt Status' >>${ATOMIC_H}
echo '    flag in SREG is disabled, and re-enabled upon exiting the block' >>${ATOMIC_H}
echo '    from any exit path.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    Two possible macro parameters are permitted, ATOMIC_RESTORESTATE' >>${ATOMIC_H}
echo '    and ATOMIC_FORCEON.' >>${ATOMIC_H}
echo '*/' >>${ATOMIC_H}
echo '#if defined(__DOXYGEN__)' >>${ATOMIC_H}
echo '#define ATOMIC_BLOCK(type)' >>${ATOMIC_H}
echo '#else' >>${ATOMIC_H}
echo '#define ATOMIC_BLOCK(type) for ( type, __ToDo = __iCliRetVal(); \' >>${ATOMIC_H}
echo '	                       __ToDo ; __ToDo = 0 )' >>${ATOMIC_H}
echo '#endif	/* __DOXYGEN__ */' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '/** \def NONATOMIC_BLOCK(type)' >>${ATOMIC_H}
echo '    \ingroup util_atomic' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    Creates a block of code that is executed non-atomically. Upon' >>${ATOMIC_H}
echo '    entering the block the Global Interrupt Status flag in SREG is' >>${ATOMIC_H}
echo '    enabled, and disabled upon exiting the block from any exit' >>${ATOMIC_H}
echo '    path. This is useful when nested inside ATOMIC_BLOCK sections,' >>${ATOMIC_H}
echo '    allowing for non-atomic execution of small blocks of code while' >>${ATOMIC_H}
echo '    maintaining the atomic access of the other sections of the parent' >>${ATOMIC_H}
echo '    ATOMIC_BLOCK.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    Two possible macro parameters are permitted,' >>${ATOMIC_H}
echo '    NONATOMIC_RESTORESTATE and NONATOMIC_FORCEOFF.' >>${ATOMIC_H}
echo '*/' >>${ATOMIC_H}
echo '#if defined(__DOXYGEN__)' >>${ATOMIC_H}
echo '#define NONATOMIC_BLOCK(type)' >>${ATOMIC_H}
echo '#else' >>${ATOMIC_H}
echo '#define NONATOMIC_BLOCK(type) for ( type, __ToDo = __iSeiRetVal(); \' >>${ATOMIC_H}
echo '	                          __ToDo ;  __ToDo = 0 )' >>${ATOMIC_H}
echo '#endif	/* __DOXYGEN__ */' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '/** \def ATOMIC_RESTORESTATE' >>${ATOMIC_H}
echo '    \ingroup util_atomic' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    This is a possible parameter for ATOMIC_BLOCK. When used, it will' >>${ATOMIC_H}
echo '    cause the ATOMIC_BLOCK to restore the previous state of the SREG' >>${ATOMIC_H}
echo '    register, saved before the Global Interrupt Status flag bit was' >>${ATOMIC_H}
echo '    disabled. The net effect of this is to make the ATOMIC_BLOCK s' >>${ATOMIC_H}
echo '    contents guaranteed atomic, without changing the state of the' >>${ATOMIC_H}
echo '    Global Interrupt Status flag when execution of the block' >>${ATOMIC_H}
echo '    completes.' >>${ATOMIC_H}
echo '*/' >>${ATOMIC_H}
echo '#if defined(__DOXYGEN__)' >>${ATOMIC_H}
echo '#define ATOMIC_RESTORESTATE' >>${ATOMIC_H}
echo '#else' >>${ATOMIC_H}
echo '#define ATOMIC_RESTORESTATE uint8_t sreg_save \' >>${ATOMIC_H}
echo '	__attribute__((__cleanup__(__iRestore))) = SREG' >>${ATOMIC_H}
echo '#endif	/* __DOXYGEN__ */' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '/** \def ATOMIC_FORCEON' >>${ATOMIC_H}
echo '    \ingroup util_atomic' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    This is a possible parameter for ATOMIC_BLOCK. When used, it will' >>${ATOMIC_H}
echo '    cause the ATOMIC_BLOCK to force the state of the SREG register on' >>${ATOMIC_H}
echo '    exit, enabling the Global Interrupt Status flag bit. This saves on' >>${ATOMIC_H}
echo '    flash space as the previous value of the SREG register does not' >>${ATOMIC_H}
echo '    need to be saved at the start of the block.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    Care should be taken that ATOMIC_FORCEON is only used when it is' >>${ATOMIC_H}
echo '    known that interrupts are enabled before the block s execution or' >>${ATOMIC_H}
echo '    when the side effects of enabling global interrupts at the block s' >>${ATOMIC_H}
echo '    completion are known and understood.' >>${ATOMIC_H}
echo '*/' >>${ATOMIC_H}
echo '#if defined(__DOXYGEN__)' >>${ATOMIC_H}
echo '#define ATOMIC_FORCEON' >>${ATOMIC_H}
echo '#else' >>${ATOMIC_H}
echo '#define ATOMIC_FORCEON uint8_t sreg_save \' >>${ATOMIC_H}
echo '	__attribute__((__cleanup__(__iSeiParam))) = 0' >>${ATOMIC_H}
echo '#endif	/* __DOXYGEN__ */' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '/** \def NONATOMIC_RESTORESTATE' >>${ATOMIC_H}
echo '    \ingroup util_atomic' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    This is a possible parameter for NONATOMIC_BLOCK. When used, it' >>${ATOMIC_H}
echo '    will cause the NONATOMIC_BLOCK to restore the previous state of' >>${ATOMIC_H}
echo '    the SREG register, saved before the Global Interrupt Status flag' >>${ATOMIC_H}
echo '    bit was enabled. The net effect of this is to make the' >>${ATOMIC_H}
echo '    NONATOMIC_BLOCK s contents guaranteed non-atomic, without changing' >>${ATOMIC_H}
echo '    the state of the Global Interrupt Status flag when execution of' >>${ATOMIC_H}
echo '    the block completes.' >>${ATOMIC_H}
echo '*/' >>${ATOMIC_H}
echo '#if defined(__DOXYGEN__)' >>${ATOMIC_H}
echo '#define NONATOMIC_RESTORESTATE' >>${ATOMIC_H}
echo '#else' >>${ATOMIC_H}
echo '#define NONATOMIC_RESTORESTATE uint8_t sreg_save \' >>${ATOMIC_H}
echo '	__attribute__((__cleanup__(__iRestore))) = SREG' >>${ATOMIC_H}
echo '#endif	/* __DOXYGEN__ */' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '/** \def NONATOMIC_FORCEOFF' >>${ATOMIC_H}
echo '    \ingroup util_atomic' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    This is a possible parameter for NONATOMIC_BLOCK. When used, it' >>${ATOMIC_H}
echo '    will cause the NONATOMIC_BLOCK to force the state of the SREG' >>${ATOMIC_H}
echo '    register on exit, disabling the Global Interrupt Status flag' >>${ATOMIC_H}
echo '    bit. This saves on flash space as the previous value of the SREG' >>${ATOMIC_H}
echo '    register does not need to be saved at the start of the block.' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '    Care should be taken that NONATOMIC_FORCEOFF is only used when it' >>${ATOMIC_H}
echo '    is known that interrupts are disabled before the block s execution' >>${ATOMIC_H}
echo '    or when the side effects of disabling global interrupts at the' >>${ATOMIC_H}
echo '    block s completion are known and understood.' >>${ATOMIC_H}
echo '*/' >>${ATOMIC_H}
echo '#if defined(__DOXYGEN__)' >>${ATOMIC_H}
echo '#define NONATOMIC_FORCEOFF' >>${ATOMIC_H}
echo '#else' >>${ATOMIC_H}
echo '#define NONATOMIC_FORCEOFF uint8_t sreg_save \' >>${ATOMIC_H}
echo '	__attribute__((__cleanup__(__iCliParam))) = 0' >>${ATOMIC_H}
echo '#endif	/* __DOXYGEN__ */' >>${ATOMIC_H}
echo '' >>${ATOMIC_H}
echo '#endif' >>${ATOMIC_H}
