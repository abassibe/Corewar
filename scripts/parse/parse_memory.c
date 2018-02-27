#include "corewar.h"

int		decode_param(t_vm *vm, t_process *process, int param_type, int param_num)
{
	int param_size;
	int ret;
	int offset;

	ret = 0;
	offset = process->offset;
	param_size = n_bytes_in_type(process->opcode, param_type);
	//printf("param %d is %d bytes long\n",param_num, param_size);
	//printf("read at adress %d\n", PCID + 1 + offset);
	param_type = code_to_t(param_type);
	if (param_type == T_REG)
	{
		ret = read_n_oct(vm, (PCID + 2 + offset) % MEM_SIZE, param_size);
//		ft_printf("REGISTER READ : (offset : %d PCID : %d) %d\n",offset, PCID, ret);
		//TODO : if register index not in boundaries error or whatever
		//note : maybe deal wth it in do_x ??

		//printf("param #%d rwinfos : %c\n", param_num, 
		//op_tab[ARENA[PCID] - 1].rwinfo[param_num - 1]);

		if (op_tab[process->opcode - 1].rwinfo[param_num - 1] == 'R')
		{
			ret = read_reg(process,ret);
		}
	}
	else if (param_type == T_DIR)
	{
		ret = read_n_oct(vm, (PCID + 2 + offset) % MEM_SIZE, param_size);
	}
	else if (param_type == T_IND)
	{
		ret = (short) read_n_oct(vm, (PCID + 2 + offset) % MEM_SIZE, param_size);
		//ft_printf("INDIRECT READ : %d\n",ret);
		if (process->opcode != 3)
		{
		//	ft_printf("here");
			ret = (short)ret;
			if (!process->longread)
				ret = ret % IDX_MOD;

			//printf("adress to read =%d\n", PCID + ret);
			ret = read_n_oct(vm, PCID + ret, (process->longread) ? 2 : 4);

			/*
			printf("reading : %02x\n",read_n_oct(vm, PCID + ret, 1));
			printf("reading : %02x\n",read_n_oct(vm, PCID + ret + 1, 1));
			printf("reading : %02x\n",read_n_oct(vm, PCID + ret + 2, 1));
			printf("reading : %02x\n",read_n_oct(vm, PCID + ret + 3, 1));
			printf("read =%d\n", ret);
			*/
		}
	}
	if (param_size == 2)
		ret = (short)ret;
	return (ret);
}	

char	acquire_params(t_vm *vm, t_process *process, int opcode, int params[])
{
	char fail;
	char current_type;
	int i;
	int paramdef;

	fail = 0;
	i = 1;
	paramdef = read_n_oct(vm, PCID + 1, 1);
	while ( i <= op_tab[opcode - 1].nb_args)
	{
		current_type = get_param_type(i, paramdef);	
		//printf("param type : %d\n",current_type);
//		ft_printf("param %d has type %d\n", i, code_to_t(current_type));
//		ft_printf("param %d compared to mask : %d\n", i, op_tab[opcode - 1].args[i - 1]);
//		ft_printf("name of op : %s\n", op_tab[opcode - 1].label);
		if (code_to_t(current_type) && 
	((code_to_t(current_type) & op_tab[opcode - 1].args[i - 1]) == 
	 code_to_t(current_type)) && !fail)
		{
			params[i] = decode_param(vm, process, current_type, i);	
		}
		else
		{
		//	printf("params type parsing failed\n");
			fail = 1;
		}
		process->offset += n_bytes_in_type(opcode, current_type);
//		ft_printf("P  %d of player %d, offset at : %d\n",process->process_id, process->num_player, process->offset);
		i++;
	}
//	ft_printf("Reussite read: %d\n",!fail);
	//ft_printf("offset: %d\n", process->offset);
	return ( !fail);
}
