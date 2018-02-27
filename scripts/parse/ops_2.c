#include "corewar.h"

void    decode_and(t_vm *vm, t_process *process)
{
	int prs[4];

	if (process->cycles_to_go == 0)
	{
		process->offset = 0;
		if (acquire_params(vm, process, 6, prs))
		{
			do_and(vm, prs, process, process->offset);
		}
		process->PC_index += process->offset + 2;

		process->cycles_to_go = -1;
		set_cycles_to_go(vm, process);
	}
	else
		process->cycles_to_go--;
}
#include "corewar.h"

void    decode_zjmp(t_vm *vm, t_process *process)
{
	short adresse;
	int	params[1];



	//uniquement un param direct, 2 bytes.
	//ft_printf("read +1 :%02x\n",ARENA[PCID+1]);
	//ft_printf("read +2 :%02x\n",ARENA[PCID+2]);
	//printf("ZJMP ADRESS :%d\n", (short)adresse);
	if (process->cycles_to_go == 0)
	{

	adresse = read_n_oct(vm, PCID + 1, 2);
	//ft_printf("ZJMP adress :%d\n",(short)adresse);
	params[0] = (short)adresse;

		//ft_printf("JUMP CALLED\n");
		if (process->carry == 1)	
		{

			check_debug(vm, process->process_id, 9, params);

			//ft_printf("ZJMP SUCCES\n");
			PCID = (PCID + (short)adresse) % MEM_SIZE;
			if (PCID < 0)
			{
				PCID = MEM_SIZE + PCID;
			}

			process->cycles_to_go = -1;
			set_cycles_to_go(vm, process);
		}
		else
		{


			check_debug(vm, process->process_id, 10, params);
			//ft_printf("ZJMP FAILED\n");
			PCID = (PCID + 3) % MEM_SIZE;
			process->cycles_to_go = -1;
			set_cycles_to_go(vm, process);
		}
	}
	else
		process->cycles_to_go--;
}
#include "corewar.h"

void    decode_lfork(t_vm *vm, t_process *process)
{
	short adresse;
	t_process new_process;
	int	params[1];

	//uniquement un param direct, 2 bytes.
	//ft_printf("envoye :%08x\n",adresse);
	//ft_printf("read +1 :%02x\n",ARENA[PCID+1]);
	//ft_printf("read +2 :%02x\n",ARENA[PCID+2]);
	//printf("ZJMP ADRESS :%d\n", (short)adresse);
	if (process->cycles_to_go == 0)
	{
		adresse = read_n_oct(vm, PCID + 1, 2);
		params[0] = adresse;

		check_debug(vm, process->process_id, 16, params);

		new_process = (t_process){
			.num_player = process->num_player,
		   	.PC_index = (process->PC_index + (adresse)) %MEM_SIZE, 
			.carry = process->carry,
	        .lives = process->lives, 
			.next = NULL, 
			.cycles_to_go = -1,
			.offset = 0,
			.process_id = vm->nbprocess + 1,
			.order = 0
		};
		copy_regs(process, &new_process);

		set_cycles_to_go(vm,&new_process);
		add_process(vm,new_process);

		PCID = (PCID + 3) % MEM_SIZE;
		process->cycles_to_go = -1;
		set_cycles_to_go(vm,process);
	}
	else
		process->cycles_to_go--;


}
#include "corewar.h"

void    decode_fork(t_vm *vm, t_process *process)
{
	short adresse;
	int		params[1];
	t_process new_process;

	//uniquement un param direct, 2 bytes.
	//ft_printf("envoye :%08x\n",adresse);
	//ft_printf("read +1 :%02x\n",ARENA[PCID+1]);
	//ft_printf("read +2 :%02x\n",ARENA[PCID+2]);
	//printf("ZJMP ADRESS :%d\n", (short)adresse);
	if (process->cycles_to_go == 0)
	{

		adresse = read_n_oct(vm, PCID + 1, 2);
		params[0] = adresse;

		check_debug(vm, process->process_id, 13, params);

		new_process = (t_process){
			.num_player = process->num_player,
		   	.PC_index = (process->PC_index + (adresse % IDX_MOD)) % MEM_SIZE, 
			.carry = process->carry,
	        .lives = process->lives, 
			.next = NULL, 
			.cycles_to_go = -1,
			.offset = 0,
			.process_id = vm->nbprocess + 1,
			.order = 0
		};
		copy_regs(process, &new_process);

		set_cycles_to_go(vm,&new_process);
		add_process(vm,new_process);

		PCID = (PCID + 3) % MEM_SIZE;
		process->cycles_to_go = -1;
		set_cycles_to_go(vm,process);
		//dump_process(&new_process);
		//ft_printf("old:");
		//dump_process(process);
	}
	else
		process->cycles_to_go--;
}
