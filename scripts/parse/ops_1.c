#include "corewar.h"

void do_sti(t_vm *vm, t_process *process, int *params)
{
	short adr; 
	int playerid; 
	int i;
	unsigned char to_write;

	//dump_process(process);
	adr = ((short)params[2] + (short)params[3]);

	check_debug(vm, process->process_id, 12, params);
	playerid = process->num_player;
	i = 0;

	while (i < 4)
	{
		to_write = get_bytes_n(i + 1, params[1]);
		single_access(vm, PCID + adr + i, to_write, playerid);
		//ft_printf(" adresse modif: %d\n", (PCID + adr + i) % MEM_SIZE);
		//ft_printf(" wrote :: %#02x\n", to_write);
		i++;
	}
}
#include "corewar.h"

void    decode2_sti(t_vm *vm, t_process *process)
{
	int	params[4];

	//printf("player : %d, PC is %d\n", process->num_player, process->PC_index);

	process->offset = 0;
	if (acquire_params(vm, process, 11, params) )
	{
	//	printf("do sti\n");
		//if (vm->cycle < 2810)
		//{
		do_sti(vm, process, params);
		//}
	}
	// on ajoute 2 car il y a un octet de codage des params
	//printf("player %d, offset :%d\n", process->num_player, process->offset);
	process->PC_index += process->offset + 2;
	//printf("player : %d, PC set to %d\n", process->num_player, process->PC_index);
		process->cycles_to_go = -1;
	set_cycles_to_go(vm, process);
}
#include "corewar.h"

void    decode_sti(t_vm *vm, t_process *process)
{


	if (process->cycles_to_go == 0)
		decode2_sti(vm, process);
	else
	{
		process->cycles_to_go--;
	}
}
#include "corewar.h"

void	do_and(t_vm *vm, int *params, t_process *process, int totaloffset)
{
	int result;

	result = params[1] & params[2];
	if (params[3] > 0 && params[3] < REG_NUMBER + 1)
	{
		check_debug(vm, process->process_id, 6, params);
		write_reg(process,result,params[3]);
	}
		process->carry = !result;
}
