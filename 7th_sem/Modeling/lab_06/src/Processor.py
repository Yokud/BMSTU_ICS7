from EventGenerator import Generator
from numpy import random as nr

class Processor(Generator):
    def __init__(self, generator, max_queue=-1):
        self._generator = generator
        self.current_queue_size = 0
        self.max_queue_size = max_queue
        self.max_size = 0
        self.processed_requests = 0
        self.received_requests  = 0
        self.next = 0
        self.receivers = []

# обрабатываем запрос, если они есть
    def process_request(self):
        if self.current_queue_size > 0:
            self.processed_requests += 1
            self.current_queue_size -= 1
 
        if len(self.receivers) != 0:
            receiver_min = self.receivers[0];
            min = self.receivers[0].current_queue_size;
            for receiver in self.receivers:
                if receiver.current_queue_size < min: 
                    min = receiver.current_queue_size
                    receiver_min = receiver
            receiver_min.receive_request()
            receiver_min.next  = self.next + receiver_min.next_time()
            #self.emit_request()
    
# добавляем реквест в очередь
    def receive_request(self):
        # print(self.max_queue_size, self.current_queue_size ) 
        # if self.max_queue_size != -1 and self.max_queue_size < self.current_queue_size:
        #     return False
        self.current_queue_size += 1
        self.received_requests += 1
        if self.max_size < self.current_queue_size:
            self.max_size = self.current_queue_size
        return True

    def next_time(self):
        return self._generator.generate()