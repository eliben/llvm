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

Scalar types
------------

* The only scalar types allowed are integer, float, double and void.

  * The only integer sizes allowed are i1, i8, i16, i32 and i64.
  * The only integer sizes allowed for function arguments are i32 and i64.

Arrays and structs are only allowed in TODO.

.. _pointertypes:

Pointer types
-------------

Pointer types are allowed with the following restrictions:

* Pointers to valid PNaCl bitcode scalar types, as specified above.
* Pointers to functions (but not intrinsics).
* The address space for all points must be 0.

A pointer is *inherent* when it represents the return value of an ``alloca``
instruction, or is an address of a global value.

A pointer is *normalized* if it's either:

* *inherent*
* Is the return value of a ``bitcast`` instruction.
* Is the return value of a ``inttoptr`` instruction.

Global Variable and Function Addresses
--------------------------------------

Undefined Values
----------------

`LLVM LangRef: Undefined Values <LangRef.html#undefvalues>`_

Poison Values
-------------

`LLVM LangRef: Poison Values <LangRef.html#poisonvalues>`_

PNaCl bitcode does not support poison values; consequently, the ``nsw`` and
``nuw`` are not supported.

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

PNaCl bitcode does not support intrinsic global variables.

Instruction Reference
=====================

Terminator Instructions
-----------------------

`LLVM LangRef: Terminator Instructions <LangRef.html#terminators>`_

'``ret``' Instruction
^^^^^^^^^^^^^^^^^^^^^

'``br``' Instruction
^^^^^^^^^^^^^^^^^^^^

'``switch``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

'``indirectbr``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

'``invoke``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

'``resume``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

'``unreachable``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

Binary Operations
-----------------

`LLVM LangRef: Binary Operations <LangRef.html#binaryops>`_

'``add``' Instruction
^^^^^^^^^^^^^^^^^^^^^

Note: for this and other relevant LLVM IR instructions, PNaCl bitcode does not
support the ``nsw`` and ``nuw`` modes.

'``fadd``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

'``sub``' Instruction
^^^^^^^^^^^^^^^^^^^^^

'``fsub``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

'``mul``' Instruction
^^^^^^^^^^^^^^^^^^^^^

'``fmul``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

'``udiv``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Integer division is guaranteed to trap in PNaCl bitcode.

'``sdiv``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Integer division is guaranteed to trap in PNaCl bitcode.

'``fdiv``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

'``urem``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Integer division is guaranteed to trap in PNaCl bitcode.

'``srem``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Integer division is guaranteed to trap in PNaCl bitcode.

'``frem``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

Bitwise Binary Operations
-------------------------

'``shl``' Instruction
^^^^^^^^^^^^^^^^^^^^^

'``lshr``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

'``ashr``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

'``and``' Instruction
^^^^^^^^^^^^^^^^^^^^^

'``or``' Instruction
^^^^^^^^^^^^^^^^^^^^

'``xor``' Instruction
^^^^^^^^^^^^^^^^^^^^^

Vector Operations
-----------------

'``extractelement``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

'``insertelement``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

'``shufflevector``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

Aggregate Operations
--------------------

'``extractvalue``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

'``insertvalue``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

Memory Access and Addressing Operations
---------------------------------------

`LLVM LangRef: Memory Access and Addressing Operations <LangRef.html#memoryops>`_

'``alloca``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

The only allowed type for ``alloca`` instructions in PNaCl bitcode is i8.

'``load``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

The pointer argument of a ``load`` instruction must be a *normalized* pointer
(see :ref:`pointer types <pointertypes>`).

'``store``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^

The pointer argument of a ``store`` instruction must be a *normalized* pointer
(see :ref:`pointer types <pointertypes>`).

'``fence``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^

'``cmpxchg``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^

The pointer argument of a ``cmpxchg`` instruction must be a *normalized*
pointer (see :ref:`pointer types <pointertypes>`).

'``atomicrmw``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^

The pointer argument of a ``atomicrmw`` instruction must be a *normalized*
pointer (see :ref:`pointer types <pointertypes>`).

'``getelementptr``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

Conversion Operations
---------------------

'``trunc .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

'``zext .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

'``sext .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

'``fptrunc .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

'``fpext .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

'``fptoui .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

'``fptosi .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

'``uitofp .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

'``sitofp .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

'``ptrtoint .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The pointer argument of a ``ptrtoint`` instruction must be a *normalized*
pointer (see :ref:`pointer types <pointertypes>`) and the integer argument
must be an i32.

'``inttoptr .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The integer argument of a ``inttoptr`` instruction must be an i32.

'``bitcast .. to``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The pointer argument of a ``bitcast`` instruction must be a *inherent* pointer
(see :ref:`pointer types <pointertypes>`).

Other Operations
----------------

`LLVM LangRef: Other Operations <LangRef.html#otherops>`_

'``icmp``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

'``fcmp``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

'``phi``' Instruction
^^^^^^^^^^^^^^^^^^^^^

'``select``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

'``call``' Instruction
^^^^^^^^^^^^^^^^^^^^^^

'``va_arg``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

'``landingpad``' Instruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not supported by PNaCl bitcode.

Intrinsic Functions
===================

`LLVM LangRef: Intrinsic Functions <LangRef.html#intrinsics>`_

The only intrinsics supported by PNaCl bitcode are the following.

'``llvm.memcpy``' Intrinsic
---------------------------

'``llvm.memmove``' Intrinsic
----------------------------

'``llvm.memset.*``' Intrinsics
------------------------------

'``llvm.bswap.*``' Intrinsics
-----------------------------

The llvm.bswap intrinsic is only supported with the following argument types:
i16, i32, i64.

'``llvm.trap``' Intrinsic
-------------------------

'``llvm.nacl.read.tp``' Intrinsic
---------------------------------

TODO: describe

'``llvm.nacl.longjmp``' Intrinsic
---------------------------------

TODO: describe

'``llvm.nacl.setjmp``' Intrinsic
--------------------------------

TODO: describe

