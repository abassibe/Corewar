#ifndef COREWAR_H
# define COREWAR_H

int		read_n_oct(t_vm *vm, int where, int n);
void	dump_process(t_process *process);
#ifndef COREWAR_H
# define COREWAR_H

int		read_n_oct(t_vm *vm, int where, int n);
void	dump_process(t_process *process);
int		decode_param(t_vm *vm, t_process *process, int param_type, int param_num);
void do_sti(t_vm *vm, t_process *process, int *params);
void    decode2_sti(t_vm *vm, t_process *process);
void    decode_sti(t_vm *vm, t_process *process);
void	do_and(t_vm *vm, int *params, t_process *process, int totaloffset);
void    decode_and(t_vm *vm, t_process *process);
void    decode_zjmp(t_vm *vm, t_process *process);
void	copy_regs(t_process *process, t_process *destination);
void    decode_lfork(t_vm *vm, t_process *process);
void    decode_fork(t_vm *vm, t_process *process);
void	do_lld(t_vm *vm, int *params, t_process *process);
void  decode_lld(t_vm *vm, t_process *process);
void	do_add(t_vm *vm, int *params, t_process *process);
void  decode_add(t_vm *vm, t_process *process);
void	do_sub(t_vm *vm, int *params, t_process *process);
void  decode_sub(t_vm *vm, t_process *process);
void	do_ldi(t_vm *vm, int *params, t_process *process, int totaloffset);
void    decode_ldi(t_vm *vm, t_process *process);
void	do_or(t_vm *vm, int *params, t_process *process, int totaloffset);
void    decode_or(t_vm *vm, t_process *process);
void	do_st(t_vm *vm, int *params, t_process *process);
void    decode_st(t_vm *vm, t_process *process);
void	do_aff(t_vm *vm, int *params, t_process *process);
void    decode_aff(t_vm *vm, t_process *process);
void	do_xor(t_vm *vm, int *params, t_process *process);
void    decode_xor(t_vm *vm, t_process *process);
void	do_lldi(t_vm *vm, int *params, t_process *process, int totaloffset);
void    decode_lldi(t_vm *vm, t_process *process);
void	live_for_player(t_vm *vm, int player_num, int order, int proc);
void	decode_live(t_vm *vm, t_process *process);
void	do_ld(t_vm *vm, int *params, t_process *process);
void  decode_ld(t_vm *vm, t_process *process);
#endif