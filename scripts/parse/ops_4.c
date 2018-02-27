#include "corewar.h"

void	do_sub(t_vm *vm, int *params, t_process *process)
{
	int result;

	result = params[1] - params[2];
	//dump_process(process);
	if (params[3] > 0 && params[3] < REG_NUMBER + 1)
	{
		write_reg(process, result, params[3]);
	}
	process->carry = !result;
	//dump_process(process);
}
#include "corewar.h"

void  decode_sub(t_vm *vm, t_process *process)
{
	int prs[4];

	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		if (acquire_params(vm, process, 5, prs))
		{
			do_sub(vm, prs, process);
		}
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;
}
#include "corewar.h"

void	do_ldi(t_vm *vm, int *params, t_process *process, int totaloffset)
{
	
	//printf("PARAMS RECU :\n");
	//printf("[1] : %d\n",params[1]);
	//printf("[2] : %d\n",params[2]);
	//printf("[3] : %d\n",params[3]);
	
	int adress;
	int read;

	////dump_process(process);
	adress = (params[1] + params[2]) % IDX_MOD;
	read = read_n_oct(vm,(process->PC_index + adress) % MEM_SIZE, 4);

	//printf("adresse lue : %d\n", process->PC_index + adress);
	//printf("read @ adresse : %d\n", read);
	if (params[3] > 0 && params[3] < REG_NUMBER + 1)
	{
		check_debug(vm, process->process_id, 11, params);
		write_reg(process, read, params[3]);
	}
	//dump_process(process);
}
#include "corewar.h"

void    decode_ldi(t_vm *vm, t_process *process)
{
	int prs[4];

	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		if (acquire_params(vm, process, 10, prs))
		{
			do_ldi(vm, prs, process, process->offset);
		}
		//ft_printf("offset : %d\n",process->offset);
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;
}
