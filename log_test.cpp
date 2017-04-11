#ifdef _WIN32
#include <windows.h>

#else

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "printlog.h"

#endif

#ifdef _WIN32
DWORD WINAPI thread_func(LPVOID param) {
#else
void *thread_func(void *args) {
#endif
	for (int i = 0; i < 100; i++) {
		_printlog(__FILE__, __LINE__, PRIORITY_UNKNOWN, "test tid %d",i);
	}
	return 0;
}

int main() {
	initlogs("", 1000, "./", 1, 1024);
	_printlog(__FILE__, __LINE__, PRIORITY_UNKNOWN, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_NOTSET, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_TRACE, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_DEBUG, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_INFO, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_NOTICE, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_WARN, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_ERROR, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_CRIT, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_ALERT, "test");
	_printlog(__FILE__, __LINE__, PRIORITY_FATAL, "test");

	// 多线程测试
#ifdef _WIN32
	HANDLE tids[4];
#else
	pthread_t tids[4];
#endif
	for (int i = 0; i < 4; i++) {
#ifdef _WIN32
		tids[i] = CreateThread(NULL, 0, thread_func, NULL, 0, NULL);
#else
		pthread_create(&tids[i], NULL, thread_func, NULL);
#endif
	}

	for (int i = 0; i < 4; i++) {
#ifdef _WIN32
		while(WaitForSingleObject(handle, INFINITE) != WAIT_OBJECT_0);
#else
		pthread_join(tids[i], NULL);
#endif
	}
}
