#include "corewar.h"

void	do_or(t_vm *vm, int *params, t_process *process, int totaloffset)
{
	int result;

	//dump_process(process);
	result = params[1] | params[2];
	if (params[3] > 0 && params[3] < REG_NUMBER + 1)
	{
		check_debug(vm, process->process_id, 7, params);
		write_reg(process,result,params[3]);
	}
		process->carry = !result;
	//dump_process(process);
}
#include "corewar.h"

void    decode_or(t_vm *vm, t_process *process)
{
	int prs[4];

	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		if (acquire_params(vm, process, 7, prs))
		{
			do_or(vm, prs, process, process->offset);
		}
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;
}
#include "corewar.h"

void	do_st(t_vm *vm, int *params, t_process *process)
{
	int playerid;
	int i;

	playerid = process->num_player;

	i = 0;


	while (i < 4)
	{
		single_access(vm, PCID + (params[2] % IDX_MOD) + i, 
				get_bytes_n( i + 1, params[1]), playerid);
		i++;
	}
	check_debug(vm, process->process_id, 3, params);

}
#include "corewar.h"

void    decode_st(t_vm *vm, t_process *process)
{
	int prs[4];



	//ft_printf("\nPCID : %d\n", PCID);
	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		if (acquire_params(vm, process, 3, prs))
		{


			//ft_printf("\npw 1 : %d\n",prs[1]);
			//ft_printf("\npw 2 : %d\n",prs[2]);
			//ft_printf("\npw 3 : %d\n",prs[3]);
			//ft_printf("\npw 4 : %d\n",prs[4]);

			do_st(vm, prs, process);
		}
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;
}
