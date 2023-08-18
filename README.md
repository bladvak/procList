# procList
Small project that prints iformation about processes under Linux by reading /proc/[PID]/status files. 
Prints name, pid and status by default. Other options as below:

sage: proclist [OPTIONS]
-v      virtual memory
-g     groups info
-p     parent pid
-u      umask
-h      prints this information
