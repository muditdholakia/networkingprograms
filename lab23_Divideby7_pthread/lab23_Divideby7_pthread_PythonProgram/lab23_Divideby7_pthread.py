from socket import * 
import thread
from threading import Thread, Lock
import time
mutex = Lock()
def sum_from_to(start):
    mutex.acquire()
    i = 0
    while i < 1000:
	start = start + 1
	if((start % 7)==0):
		print 'Answer is : ' , start
    mutex.release()
    return 
  
if __name__ == '__main__':
    try:
	a = 0
	b = 1
	threads = []
	while b <= 10:
		threads = thread.start_new_thread(sum_from_to,(a,))
		a = a + 1000
		b = b + 1
	for threads in threads:
		thread.join()
    except Exception, errtxt:
        print errtxt
    time.sleep(2)
