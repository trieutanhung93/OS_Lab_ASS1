
#include <get_proc_info.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(){
	pid_t mypid = getpid();
	printf("PID: %d\n", mypid);
	struct procinfos info;

	if(get_proc_info(mypid, &info) == 0){
		printf("studentID: %ld\n", info.studentID);	//xuat Student id:
		printf("proc.pid: %d\n", info.proc.pid);// xuat pid cua proc
		printf("proc.name: %s\n", info.proc.name);//xuat name cua proc
		printf("parent_proc.pid: %d\n", info.parent_proc.pid);//xuat pid cua parent_proc
		printf("parent_proc.name: %s\n", info.parent_proc.name);//xuat name cua parent_proc
		printf("oldest_child_proc.pid: %d\n", info.oldest_child_proc.pid);//xuat pid cua oldest_child_proc
		printf("oldest_child_proc.name: %s\n", info.oldest_child_proc.name);//xuat name cua oldest_child_proc
	} else {
		printf("Cannot get infomation from the process %d\n", mypid);
	}
}