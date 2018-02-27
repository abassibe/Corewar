#include "corewar.h"

int		read_n_oct(t_vm *vm, int where, int n)
{
	int ret;
	int i;

	ret = 0;
	i = 0;

	while (i < n)
	{
		ret = ret | ((unsigned char*)vm->arena)[(where + i) % MEM_SIZE];
		i++;
		if (i != n)
			ret = ret << 8;
	}
	return (ret);
}
#include "corewar.h"

void	dump_process(t_process *process)
{
	int i;

	ft_printf("\n\n PROCESS DUMP : #%d\n",process->process_id);
	ft_printf(" PC : %d\n",process->PC_index);
	ft_printf(" player : %d\n",process->num_player);
	ft_printf(" carry : %d\n",process->carry);
	ft_printf(" lives : %d\n",process->lives);
	
	ft_printf("\n REGS :\n");
	i = 1;
	while (i < REG_NUMBER + 1)
	{
	ft_printf(" Reg[%d] = \t%d\n", i , read_reg(process,i));
	i++;
	}

	ft_printf("\n");
}
#include "corewar.h"

void	copy_regs(t_process *process, t_process *destination)
{
		int i;

		i = 1;
		while (i < 17)
		{
			write_reg(destination, read_reg(process, i), i);
			i++;
		}
}
