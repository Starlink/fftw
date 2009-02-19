/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Feb  9 19:53:05 EST 2009 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twiddle_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 3 -name t1bv_3 -include t1b.h -sign 1 */

/*
 * This function contains 8 FP additions, 8 FP multiplications,
 * (or, 5 additions, 5 multiplications, 3 fused multiply/add),
 * 12 stack variables, 2 constants, and 6 memory accesses
 */
#include "t1b.h"

static void t1bv_3(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DVK(KP866025403, +0.866025403784438646763723170752936183471402627);
     INT m;
     R *x;
     x = ii;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 4)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 4), MAKE_VOLATILE_STRIDE(rs)) {
	  V T1, T2, T4;
	  T1 = LD(&(x[0]), ms, &(x[0]));
	  T2 = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
	  T4 = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
	  {
	       V T3, T5, T8, T6, T7;
	       T3 = BYTW(&(W[0]), T2);
	       T5 = BYTW(&(W[TWVL * 2]), T4);
	       T8 = VMUL(LDK(KP866025403), VSUB(T3, T5));
	       T6 = VADD(T3, T5);
	       T7 = VFNMS(LDK(KP500000000), T6, T1);
	       ST(&(x[0]), VADD(T1, T6), ms, &(x[0]));
	       ST(&(x[WS(rs, 2)]), VFNMSI(T8, T7), ms, &(x[0]));
	       ST(&(x[WS(rs, 1)]), VFMAI(T8, T7), ms, &(x[WS(rs, 1)]));
	  }
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 3, "t1bv_3", twinstr, &GENUS, {5, 5, 3, 0}, 0, 0, 0 };

void X(codelet_t1bv_3) (planner *p) {
     X(kdft_dit_register) (p, t1bv_3, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twiddle_c -simd -compact -variables 4 -pipeline-latency 8 -n 3 -name t1bv_3 -include t1b.h -sign 1 */

/*
 * This function contains 8 FP additions, 6 FP multiplications,
 * (or, 7 additions, 5 multiplications, 1 fused multiply/add),
 * 12 stack variables, 2 constants, and 6 memory accesses
 */
#include "t1b.h"

static void t1bv_3(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DVK(KP866025403, +0.866025403784438646763723170752936183471402627);
     INT m;
     R *x;
     x = ii;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 4)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 4), MAKE_VOLATILE_STRIDE(rs)) {
	  V T6, T2, T4, T7, T1, T3, T5, T8;
	  T6 = LD(&(x[0]), ms, &(x[0]));
	  T1 = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
	  T2 = BYTW(&(W[0]), T1);
	  T3 = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
	  T4 = BYTW(&(W[TWVL * 2]), T3);
	  T7 = VADD(T2, T4);
	  ST(&(x[0]), VADD(T6, T7), ms, &(x[0]));
	  T5 = VBYI(VMUL(LDK(KP866025403), VSUB(T2, T4)));
	  T8 = VFNMS(LDK(KP500000000), T7, T6);
	  ST(&(x[WS(rs, 1)]), VADD(T5, T8), ms, &(x[WS(rs, 1)]));
	  ST(&(x[WS(rs, 2)]), VSUB(T8, T5), ms, &(x[0]));
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 3, "t1bv_3", twinstr, &GENUS, {7, 5, 1, 0}, 0, 0, 0 };

void X(codelet_t1bv_3) (planner *p) {
     X(kdft_dit_register) (p, t1bv_3, &desc);
}
#endif				/* HAVE_FMA */
