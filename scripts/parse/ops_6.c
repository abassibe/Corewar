#include "corewar.h"

void	do_aff(t_vm *vm, int *params, t_process *process)
{
	//printf("\n\npw1 : %d\n",params[1]);
	//
	//

	if (vm->aff)
		ft_printf("%c", params[1] % 256);
}
#include "corewar.h"

void    decode_aff(t_vm *vm, t_process *process)
{

	int prs[4];

	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		if (acquire_params(vm, process, 16, prs))
		{
			do_aff(vm, prs, process);
		}
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;

}
#include "corewar.h"

void    decode_xor(t_vm *vm, t_process *process)
{
	int prs[4];

	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		if (acquire_params(vm, process, 8, prs))
		{
			do_xor(vm, prs, process);
		}
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;
}
#include "corewar.h"

void	do_lldi(t_vm *vm, int *params, t_process *process, int totaloffset)
{
	
	/*
	printf("PARAMS RECU :\n");
	printf("[1] : %d\n",params[1]);
	printf("[2] : %d\n",params[2]);
	printf("[3] : %d\n",params[3]);
	*/
	
	int adress;
	int read;


	check_debug(vm, process->process_id, 15, params);

	//dump_process(process);
	adress = (params[1] + params[2]);
	read = read_n_oct(vm,process->PC_index + adress, 4);

	//printf("adresse lue : %d\n", process->PC_index + adress);
	//printf("read @ adresse : %d\n", read);
	if (params[3] > 0 && params[3] < REG_NUMBER + 1)
	{
		write_reg(process, read, params[3]);
	}
	process->carry = !read;
	//dump_process(process);
}
