#include <linux/kernel.h>
#include <linux/syscalls.h>

struct proc_info {
	pid_t pid;
	char name[16];
};

struct procinfos {
	long studentID;
	struct proc_info proc;
	struct proc_info parent_proc;
	struct proc_info oldest_child_proc;
};

SYSCALL_DEFINE2(get_proc_info, pid_t, pid, struct procinfos *, info)
{
	info->studentID = 1812475;
	
	//Kiem tra pid co hop le hay khong.
	if (pid == -1) {
		pid = current->pid;
	}
	struct task_struct *proces;
	for_each_process (proces) {
		if (proces->pid == pid) {
			struct task_struct *cProces;
			cProces = list_first_entry_or_null(&proces->children, struct task_struct, sibling); // Tao ra oldes_child_proc
			
			//Truy xuat thong tin cua proc			
			info->proc.pid = proces->pid;
			strcpy(info->proc.name, proces->comm);
			
			//Truy xuat thong tin cua parent_proc
			if (proces->real_parent == NULL) {
				info->parent_proc.pid = 0;
				strcpy(info->parent_proc.name, "\0");//info->parent_proc.name = "\0";
			} 
			else {
				info->parent_proc.pid = proces->real_parent->pid;
				strcpy(info->parent_proc.name, proces->real_parent->comm);//info->patent_proc.name = proces->real_parent->comm;
			}
			
			//Truy xuat thong tin cua oldest_child_proc
			if (cProces == NULL) {
				info->oldest_child_proc.pid = 0;
				strcpy(info->oldest_child_proc.name, "\0");//info->oldest_child_proc.name = "\0";
			} 
			else {
				info->oldest_child_proc.pid = cProces->pid;
				strcpy(info->oldest_child_proc.name, cProces->comm);//info->oldest_child_proc.name = cProces->comm;
			}
		}
	}
}
