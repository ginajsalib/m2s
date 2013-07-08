/*
 *  Multi2Sim
 *  Copyright (C) 2013  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <assert.h>

#include <lib/mhandle/mhandle.h>
#include <lib/util/debug.h>
#include <lib/util/string.h>

#include "symbol.h"


struct str_map_t llvm2si_symbol_type_map =
{
	3, {
		{ "vreg", llvm2si_symbol_vector_register },
		{ "sreg", llvm2si_symbol_scalar_register }
	}
};


static struct llvm2si_symbol_t *llvm2si_symbol_create(char *name,
		enum llvm2si_symbol_type_t type, int reg, int count)
{
	struct llvm2si_symbol_t *symbol;

	/* Check valid name */
	if (!name || !*name)
		fatal("%s: empty symbol name", __FUNCTION__);

	/* Initialize */
	symbol = xcalloc(1, sizeof(struct llvm2si_symbol_t));
	symbol->name = xstrdup(name);
	symbol->type = type;
	symbol->reg = reg;
	symbol->count = count;

	/* Return */
	return symbol;
}


struct llvm2si_symbol_t *llvm2si_symbol_create_vreg(char *name, int vreg)
{
	return llvm2si_symbol_create(name, llvm2si_symbol_vector_register,
			vreg, 1);
}


struct llvm2si_symbol_t *llvm2si_symbol_create_sreg(char *name, int sreg)
{
	return llvm2si_symbol_create(name, llvm2si_symbol_scalar_register,
			sreg, 1);
}


struct llvm2si_symbol_t *llvm2si_symbol_create_vreg_series(char *name,
		int vreg_lo, int vreg_hi)
{
	assert(vreg_hi > vreg_lo);
	return llvm2si_symbol_create(name, llvm2si_symbol_vector_register,
			vreg_lo, vreg_hi - vreg_lo + 1);
}


struct llvm2si_symbol_t *llvm2si_symbol_create_sreg_series(char *name,
		int sreg_lo, int sreg_hi)
{
	assert(sreg_hi > sreg_lo);
	return llvm2si_symbol_create(name, llvm2si_symbol_scalar_register,
			sreg_lo, sreg_hi - sreg_lo + 1);
}


void llvm2si_symbol_free(struct llvm2si_symbol_t *symbol)
{
	free(symbol->name);
	free(symbol);
}


void llvm2si_symbol_dump(struct llvm2si_symbol_t *symbol, FILE *f)
{
	/* Name, type, register */
	fprintf(f, "name='%s', type=%s, reg=%d", symbol->name,
			str_map_value(&llvm2si_symbol_type_map, symbol->type),
			symbol->reg);

	/* UAV index */
	if (symbol->address)
		fprintf(f, ", uav%d", symbol->uav_index + 10);
	
	/* End */
	fprintf(f, "\n");
}


void llvm2si_symbol_set_uav_index(struct llvm2si_symbol_t *symbol,
		int uav_index)
{
	symbol->address = 1;
	symbol->uav_index = uav_index;
}

