#include "corewar.h"

void	do_lld(t_vm *vm, int *params, t_process *process)
{


	check_debug(vm, process->process_id, 14, params);

	//dump_process(process);
	if (params[2] > 0 && params[2] < REG_NUMBER + 1)
	{
		write_reg(process,params[1], params[2]);
	}
	process->carry = !params[1];
	//dump_process(process);
}
#include "corewar.h"

void  decode_lld(t_vm *vm, t_process *process)
{
	int prs[4];

	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		process->longread = 1;
		if (acquire_params(vm, process, 13, prs))
		{
			do_lld(vm, prs, process);
		}
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;
}
#include "corewar.h"

void	do_add(t_vm *vm, int *params, t_process *process)
{
	int result;

	result = params[1] + params[2];
	//dump_process(process);
	if (params[3] > 0 && params[3] < REG_NUMBER + 1)
	{
		write_reg(process, result, params[3]);
	}
	process->carry = !result;
	//dump_process(process);
}
#include "corewar.h"

void  decode_add(t_vm *vm, t_process *process)
{
	int prs[4];

	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		if (acquire_params(vm, process, 4, prs))
		{
			do_add(vm, prs, process);
		}
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;
}
