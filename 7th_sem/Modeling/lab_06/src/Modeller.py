  
from Distributions import UniformDistribution
from EventGenerator import Generator
from Processor import Processor


class Modeller:
    def __init__(self, generator, operators, computers):
        self._generator = generator
        self._operators = operators
        self._computers = computers

    def event_mode(self):
        refusals = 0
        processed = 0
        generated_requests = self._generator.num_requests
        generator = self._generator

        generator.next = generator.next_time()
        self._operators[0].next = self._operators[0].next_time()

        blocks = [
            generator
        ] + self._computers + self._operators 

        num_requests = generator.num_requests
        count = 0;
        while count < num_requests:
            my_str = 'iter '
            for oper in self._operators: 
                my_str += str(oper.current_queue_size) + ' '
            my_str += "|||||" 
            for oper in self._computers: 
                my_str += str(oper.current_queue_size) + ' '
            my_str += "|||||" 
            for oper in self._computers: 
                my_str += str(oper.processed_requests) + ' '
            my_str += "|||||" 
            for oper in self._operators: 
                my_str += str(oper.processed_requests) + ' '
            # находим наименьшее время
            print(my_str)
            current_time = generator.next
            for block in blocks:
                if 0 < block.next < current_time:
                    current_time = block.next

            # для каждого из блоков
            for block in blocks:
                # если событие наступило для этого блока
                if current_time == block.next:
                    if not isinstance(block, Processor):
                        # для генератора 
                        # проверяем, может ли оператор обработать
                        next_generator = generator.generate_request()
                        if next_generator is not None:
                            next_generator.next = \
                                current_time + next_generator.next_time()
                            processed += 1
                        else:
                            refusals += 1
                        generator.next = current_time + generator.next_time()
                    else:
                        block.process_request()
                        if block.current_queue_size == 0:
                            block.next = 0
                        else:
                            block.next = current_time + block.next_time()
            count = 0 
            for oper in self._computers: 
                count += oper.processed_requests

        max_queue = []
        for oper in self._operators: 
            max_queue.append(oper.max_size)
        for oper in self._computers: 
            max_queue.append(oper.max_size)
        processed_arr = []
        for oper in self._operators: 
            processed_arr.append(oper.processed_requests)
        for oper in self._computers: 
            processed_arr.append(oper.processed_requests)
        return {"max_queue": max_queue,
                'time': current_time,
                "processed": count,
                "proc_arr": processed_arr,
                "pribilo": processed
                }