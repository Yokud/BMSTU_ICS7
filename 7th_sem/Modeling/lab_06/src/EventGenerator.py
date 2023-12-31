
class Generator:
    def __init__(self, generator, count):
        self._generator = generator
        self.receivers = []
        self.num_requests = count
        self.next = 0 

    def next_time(self):
        return self._generator.generate()
    
    def generate_request(self):
        # if self.num_requests <= 0: 
        #     return None
        self.num_requests -= 1
        receiver_min = self.receivers[0];
        min = self.receivers[0].current_queue_size;
        for receiver in self.receivers:
            if receiver.current_queue_size < min: 
                min = receiver.current_queue_size
                receiver_min = receiver
        receiver_min.receive_request()
        return receiver_min