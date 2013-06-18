==============================
PNaCl Bitcode Reference Manual
==============================

.. contents::
   :local:
   :depth: 3

Introduction
============

This document is a reference manual for the PNaCl bitcode format. It describes
the bitcode on a *semantic* level; the physical encoding level will be described
elsewhere. For the purpose of this document, the textual form of LLVM IR is
used to describe instructions and other bitcode constructs.

Since the PNaCl bitcode is based to a large extent on LLVM IR, many sections
in this document point to a relevant section of the LLVM language reference
manual. Only the changes, restrictions and variations specific to PNaCl are
described - full semantic descriptions are not duplicated from the LLVM
reference manual.

*[TODO(eliben): this may gradually change in the future, as we move more
contents into this document; also, the physical encoding will also be described
here in the future, once we know what it's going to be]*

**Note:** constructs not mentioned in this document are **not supported**.

Identifiers
===========

`LLVM LangRef: Identifiers <LangRef.html#identifiers>`_

High Level Structure
====================

A PNaCl portable executable ("pexe" in short) is a single LLVM IR module.

Linkage Types
-------------

`LLVM LangRef: Linkage Types <LangRef.html#linkage>`_

The linkage types supported by PNaCl bitcode are ``internal`` and ``external``.
A single function in the pexe, named ``_start``, has the linkage type
``external``. All the other functions have the linkage type ``internal``.

Calling Conventions
-------------------

`LLVM LangRef: Calling Conventions <LangRef.html#callingconv>`_

The only calling convention supported by PNaCl bitcode is ``ccc`` - the C
calling convention.

Visibility Styles
-----------------

`LLVM LangRef: Visibility Styles <LangRef.html#visibilitystyles>`_

PNaCl bitcode does not support visibility styles.

Global Variables
----------------

`LLVM LangRef: Global Variables <LangRef.html#globalvars>`_

TODO: TLSModel (localdynamic, etc.) - no support?
TODO: describe our restrictions on global variables

Functions
---------

`LLVM LangRef: Functions <LangRef.html#functionstructure>`_

The restrictions on linkage types, calling conventions and visibility styles
apply to functions. In addition, the following are not supported for functions:

* Function attributes.
* Section specification.
* Garbage collector name.
* Parameter attributes for the return type.

Aliases
-------

`LLVM LangRef: Aliases <LangRef.html#langref_aliases>`_

PNaCl bitcode does not support aliases.

Named Metadata
--------------

`LLVM LangRef: Named Metadata <LangRef.html#namedmetadatastructure>`_

While PNaCl bitcode has provisions for debugging metadata, it is not considered
part of the stable ABI. It exists for tool support and should not appear in
distributed pexes.

Other kinds of LLVM metadata are not supported.

Parameter Attributes
--------------------

`LLVM LangRef: Parameter Attributes <LangRef.html#paramattrs>`_

TODO: what parameter attributes are supported.

Function Attributes
-------------------

`LLVM LangRef: Function Attributes <LangRef.html#fnattrs>`_

PNaCl bitcode does not support function attributes.

Module-Level Inline Assembly
----------------------------

`LLVM LangRef: Module-Level Inline Assembly <LangRef.html#moduleasm>`_

PNaCl bitcode does not support inline assembly.

Volatile Memory Accesses
------------------------

`LLVM LangRef: Volatile Memory Accesses <LangRef.html#volatile>`_

Memory Model for Concurrent Operations
--------------------------------------

`LLVM LangRef: Memory Model for Concurrent Operations <LangRef.html#memmodel>`_

TODO.

Atomic Memory Ordering Constraints
----------------------------------

`LLVM LangRef: Atomic Memory Ordering Constraints <LangRef.html#ordering>`_

TODO.

Fast-Math Flags
---------------

`LLVM LangRef: Fast-Math Flags <LangRef.html#fastmath>`_

Fast-math mode is not currently supported by the PNaCl bitcode.

Type System
===========

`LLVM LangRef: Type System <LangRef.html#typesystem>`_

The LLVM types allowed in PNaCl bitcode are restricted, as follows:

* The only scalar types allowed are integer, float, double and void.

  * The only integer sizes allowed are i1, i8, i16, i32 and i64.
  * The only integer sizes allowed for function arguments are i32 and i64.

Arrays and structs are only allowed in TODO.
Pointers are only allowed in TODO.

Global Variable and Function Addresses
--------------------------------------

Undefined Values
----------------

`LLVM LangRef: Undefined Values <LangRef.html#undefvalues>`_

Poison Values
-------------

`LLVM LangRef: Poison Values <LangRef.html#poisonvalues>`_

PNaCl bitcode does not support poison values.

Constant Expressions
--------------------

`LLVM LangRef: Constant Expressions <LangRef.html#constantexprs>`_

In the general sense, PNaCl bitcode does not support constant expressions.
There is a single, restricted, use case permitted in global initializers,
where the ``add`` and ``ptrtoint`` constant expressions are allowed.

Other Values
============

Metadata Nodes and Metadata Strings
-----------------------------------

`LLVM LangRef: Metadata Nodes and Metadata Strings <LangRef.html#metadata>`_

While PNaCl bitcode has provisions for debugging metadata, it is not considered
part of the stable ABI. It exists for tool support and should not appear in
distributed pexes.

Other kinds of LLVM metadata are not supported.

Intrinsic Global Variables
==========================

`LLVM LangRef: Intrinsic Global Variables <LangRef.html#intrinsicglobalvariables>`_

The '``llvm.used``' Global Variable
-----------------------------------

`LLVM LangRef: The llvm.used Global Variable <LangRef.html#gv_llvmused>`_

The '``llvm.compiler.used``' Global Variable
--------------------------------------------

`LLVM LangRef: The llvm.compiler.used Global Variable <LangRef.html#gv_llvmcompilerused>`_

The '``llvm.global_ctors``' Global Variable
-------------------------------------------

`LLVM LangRef: The llvm.global_ctors Global Variable <LangRef.html#gv_llvmglobalctors>`_

The '``llvm.global_dtors``' Global Variable
-------------------------------------------

`LLVM LangRef: The llvm.global_dtors Global Variable <LangRef.html#llvmglobaldtors>`_

Instruction Reference
=====================

Terminator Instructions
-----------------------

`LLVM LangRef: Terminator Instructions <LangRef.html#terminators>`_

'``ret``' Instruction
^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: ret Instruction <LangRef.html#i_ret>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``br``' Instruction
^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: br Instruction <LangRef.html#i_br>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``switch``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: switch Instruction <LangRef.html#i_switch>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Implementation:
"""""""""""""""

Example:
""""""""

'``indirectbr``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: indirectbr Instruction <LangRef.html#i_indirectbr>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Implementation:
"""""""""""""""

Example:
""""""""

'``invoke``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: invoke Instruction <LangRef.html#i_invoke>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``resume``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: resume Instruction <LangRef.html#i_resume>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``unreachable``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: unreachable Instruction <LangRef.html#i_unreachable>`_

Syntax:
"""""""

Overview:
"""""""""

Semantics:
""""""""""

Binary Operations
-----------------

`LLVM LangRef: Binary Operations <LangRef.html#binaryops>`_

'``add``' Instruction
^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: add Instruction <LangRef.html#i_add>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fadd``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: fadd Instruction <LangRef.html#i_fadd>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``sub``' Instruction
^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fsub``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: fsub Instruction <LangRef.html#i_fsub>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``mul``' Instruction
^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fmul``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: fmul Instruction <LangRef.html#i_fmul>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``udiv``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``sdiv``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fdiv``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: fdiv Instruction <LangRef.html#i_fdiv>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``urem``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``srem``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``frem``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: frem Instruction <LangRef.html#i_frem>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

Bitwise Binary Operations
-------------------------

`LLVM LangRef: Bitwise Binary Operations <LangRef.html#bitwiseops>`_

'``shl``' Instruction
^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``lshr``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``ashr``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``and``' Instruction
^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``or``' Instruction
^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``xor``' Instruction
^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

Vector Operations
-----------------

'``extractelement``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: extractelement Instruction <LangRef.html#i_extractelement>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``insertelement``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: insertelement Instruction <LangRef.html#i_insertelement>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``shufflevector``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: shufflevector Instruction <LangRef.html#i_shufflevector>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

Aggregate Operations
--------------------

'``extractvalue``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: extractvalue Instruction <LangRef.html#i_extractvalue>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``insertvalue``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: insertvalue Instruction <LangRef.html#i_insertvalue>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

Memory Access and Addressing Operations
---------------------------------------

`LLVM LangRef: Memory Access and Addressing Operations <LangRef.html#memoryops>`_

'``alloca``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: alloca Instruction <LangRef.html#i_alloca>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``load``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: load Instruction <LangRef.html#i_load>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

'``store``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: store Instruction <LangRef.html#i_store>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fence``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: fence Instruction <LangRef.html#i_fence>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``cmpxchg``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: cmpxchg Instruction <LangRef.html#i_cmpxchg>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``atomicrmw``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: atomicrmw Instruction <LangRef.html#i_atomicrmw>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``getelementptr``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: getelementptr Instruction <LangRef.html#i_getelementptr>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

Conversion Operations
---------------------

'``trunc .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``zext .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``sext .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fptrunc .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fpext .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fptoui .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fptosi .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``uitofp .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``sitofp .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``ptrtoint .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: ptrtoint .. to Instruction <LangRef.html#i_ptrtoint>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``inttoptr .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: inttoptr .. to Instruction <LangRef.html#i_inttoptr>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``bitcast .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: bitcast .. to Instruction <LangRef.html#i_bitcast>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

Other Operations
----------------

`LLVM LangRef: Other Operations <LangRef.html#otherops>`_

'``icmp``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: icmp Instruction <LangRef.html#i_icmp>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``fcmp``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: fcmp Instruction <LangRef.html#i_fcmp>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``phi``' Instruction
^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: phi Instruction <LangRef.html#i_phi>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``select``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: select Instruction <LangRef.html#i_select>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``call``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: call Instruction <LangRef.html#i_call>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``va_arg``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: va_arg Instruction <LangRef.html#i_va_arg>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

'``landingpad``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: landingpad Instruction <LangRef.html#i_landingpad>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Example:
""""""""

Intrinsic Functions
===================

`LLVM LangRef: Intrinsic Functions <LangRef.html#intrinsics>`_

Variable Argument Handling Intrinsics
-------------------------------------

`LLVM LangRef: Variable Argument Handling Intrinsics <LangRef.html#int_varargs>`_

'``llvm.va_start``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.va_start Intrinsic <LangRef.html#int_va_start>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.va_end``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.va_copy``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.va_copy Intrinsic <LangRef.html#int_va_copy>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Accurate Garbage Collection Intrinsics
--------------------------------------

'``llvm.gcroot``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.gcroot Intrinsic <LangRef.html#int_gcroot>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.gcread``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.gcread Intrinsic <LangRef.html#int_gcread>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.gcwrite``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.gcwrite Intrinsic <LangRef.html#int_gcwrite>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Code Generator Intrinsics
-------------------------

'``llvm.returnaddress``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.frameaddress``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.stacksave``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.stacksave Intrinsic <LangRef.html#int_stacksave>`_

Syntax:
"""""""

Overview:
"""""""""

Semantics:
""""""""""

'``llvm.stackrestore``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.stackrestore Intrinsic <LangRef.html#int_stackrestore>`_

Syntax:
"""""""

Overview:
"""""""""

Semantics:
""""""""""

'``llvm.prefetch``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.pcmarker``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.readcyclecounter``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Semantics:
""""""""""

Standard C Library Intrinsics
-----------------------------

'``llvm.memcpy``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.memcpy Intrinsic <LangRef.html#int_memcpy>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.memmove``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.memset.*``' Intrinsics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.sqrt.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.powi.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.sin.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.cos.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.pow.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.exp.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.exp2.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.log.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.log10.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.log2.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.fma.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.fabs.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.floor.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.ceil.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.trunc.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.rint.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.nearbyint.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Bit Manipulation Intrinsics
---------------------------

'``llvm.bswap.*``' Intrinsics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Semantics:
""""""""""

'``llvm.ctpop.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.ctlz.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.cttz.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Arithmetic with Overflow Intrinsics
-----------------------------------

'``llvm.sadd.with.overflow.*``' Intrinsics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

'``llvm.uadd.with.overflow.*``' Intrinsics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

'``llvm.ssub.with.overflow.*``' Intrinsics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

'``llvm.usub.with.overflow.*``' Intrinsics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

'``llvm.smul.with.overflow.*``' Intrinsics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

'``llvm.umul.with.overflow.*``' Intrinsics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

Specialised Arithmetic Intrinsics
---------------------------------

'``llvm.fmuladd.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

Half Precision Floating Point Intrinsics
----------------------------------------

'``llvm.convert.to.fp16``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.convert.to.fp16 Intrinsic <LangRef.html#int_convert_to_fp16>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

'``llvm.convert.from.fp16``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.convert.from.fp16 Intrinsic <LangRef.html#int_convert_from_fp16>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Examples:
"""""""""

Debugger Intrinsics
-------------------

Exception Handling Intrinsics
-----------------------------

Trampoline Intrinsics
---------------------

`LLVM LangRef: Trampoline Intrinsics <LangRef.html#int_trampoline>`_

'``llvm.init.trampoline``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.init.trampoline Intrinsic <LangRef.html#int_it>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.adjust.trampoline``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`LLVM LangRef: llvm.adjust.trampoline Intrinsic <LangRef.html#int_at>`_

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

Memory Use Markers
------------------

'``llvm.lifetime.start``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.lifetime.end``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.invariant.start``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.invariant.end``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

General Intrinsics
------------------

'``llvm.var.annotation``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.ptr.annotation.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.annotation.*``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.trap``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.debugtrap``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.stackprotector``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.objectsize``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.expect``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

'``llvm.donothing``' Intrinsic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Syntax:
"""""""

Overview:
"""""""""

Arguments:
""""""""""

Semantics:
""""""""""

