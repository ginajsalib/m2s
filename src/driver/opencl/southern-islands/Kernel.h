/*
 *  Multi2Sim
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
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

#ifndef DRIVER_OPENCL_SI_KERNEL_H
#define DRIVER_OPENCL_SI_KERNEL_H

#include <memory>
#include <string>

#include <src/arch/southern-islands/asm/Arg.h>

#include "Program.h"

namespace SI
{

class NDRange;

class Kernel
{
	// Kernel identifier
	int id;

	// Kernel name
	std::string name;

	// Program it belongs to
	const Program *program;

	// List of kernel arguments
	std::vector<std::unique_ptr<SI::Arg>> args;

	// Memory requirements 
	int mem_size_local;
	int mem_size_private;

	// Kernel function metadata
	int func_uniqueid;  // Id of kernel function

	void Expect(std::vector<std::string> &token_list, std::string head_token);

	void ExpectInt(std::vector<std::string> &token_list);

	void ExpectCount(std::vector<std::string> &token_list);

	void LoadMetaDataV3();

	void LoadMetaData();

public:
	Kernel(int id, std::string name);

	///
	void SetupNDRangeConstantBuffers(NDRange *ndrange);

	/// 
	void SetupNDRangeArgs(NDRange *ndrange);

	///
	void DebugNDRangeState(NDRange *ndrange);

	/// FIXME
	void FlushNDRangeBuffers(NDRange *ndrange /*SIGpu *gpu, X86Emu *x86_emu*/);
	void CreateNDRangeTables(NDRange *ndrange /* MMU *gpu_mmu */);
	void CreateNDRangeConstantBuffers(NDRange *ndrange /*MMU *gpu_mmu*/);
	void NDRangeSetupMMU(NDRange *ndrange);
	
};

}  // namespace SI

#endif
