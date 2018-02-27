#include "corewar.h"

void  decode_ld(t_vm *vm, t_process *process)
{
	int prs[4];

	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		if (acquire_params(vm, process, 2, prs))
		{
			do_ld(vm, prs, process);
		}
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;


}
