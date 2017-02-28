/*
 * mem.h - header file for memory and process management routines
 *
 * Copyright (C) 2001 Lineo, Inc. and
 *               2002-2016 The EmuTOS development team
 *
 * Authors:
 *  LVL Laurent Vogel
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#ifndef MEM_H
#define MEM_H

#include "memdefs.h"


/*
 *  externals
 */

extern  FTAB    sft[];
extern  MPB     pmd;    /* the mem pool for the main user ST ram */
#if CONF_WITH_ALT_RAM
extern  MPB     pmdalt;  /* the memory pool for the alternative ram (TT-RAM or other) */
extern  int     has_alt_ram; /* 1 if alternative RAM has been declared to BDOS */
#endif


/*
 * in osmem.c
 */

/*  xmgetblk - get a block of memory from the o/s pool. */
void *xmgetblk(WORD memtype);

/*  MGET - wrapper around xmgetblk */
#define MGET(x)         ((x *)xmgetblk(MEMTYPE_ ## x))
#define MEMTYPE_MDBLOCK 0   /* the 4 types of valid request, all needing 64 bytes */
#define MEMTYPE_DMD     1
#define MEMTYPE_DND     2
#define MEMTYPE_OFD     3

/*  xmfreblk - free up memory allocated through mgetblk */
void xmfreblk(void *m);

MD *xmgetmd(void);          /* xmgetmd - get an MD */
void xmfremd(MD *md);       /* xmfremd - free an MD */

/* init os memory */
void osmem_init(void);

/*
 * in umem.c
 */

/* allocate memory */
void *xmalloc(long amount);
/* mfree */
long xmfree(void *addr);
/* mshrink */
long xsetblk(int n, void *blk, long len);
/* mxalloc */
void *xmxalloc(long amount, int mode);
/* srealloc */
void *srealloc(long amount);

/* supported values for Mxalloc mode: */
#define MX_STRAM 0
#define MX_TTRAM 1
#define MX_PREFSTRAM 2
#define MX_PREFTTRAM 3
#define MX_MODEMASK  0x03   /* mask for supported mode bits */

#if CONF_WITH_ALT_RAM
/* declare additional memory */
long xmaddalt(UBYTE *start, long size);
long total_alt_ram(void);
#endif /* CONF_WITH_ALT_RAM */

/* init user memory */
void umem_init(void);

/* set memory ownership */
void set_owner(void *addr, PD *p);


/*
 * in iumem.c
 */

/* find first fit for requested memory in ospool */
MD *ffit(long amount, MPB *mp);
/* Free up a memory descriptor */
void freeit(MD *m, MPB *mp);
/* shrink a memory descriptor */
WORD shrinkit(MD *m, MPB *mp, LONG newlen);


#endif /* MEM_H */
