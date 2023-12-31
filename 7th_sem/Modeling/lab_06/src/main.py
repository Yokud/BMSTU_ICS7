from Modeller import Modeller
from prettytable import PrettyTable
from EventGenerator import Generator
from Distributions import UniformDistribution
from Processor import Processor

if __name__ == '__main__':
    table = PrettyTable()
    table.field_names = ['# итерации', 'прибыло', 'обработано', 'время работы']
    table2 = PrettyTable()



    clients_number = 300 #Количество клиентов

    operator_time = 3 #Время обслуживания кассира
    operator_delta = 2 #Погрешность обслуживания кассира

    computer_time = 1 #Время обслуживания терминала
    computer_delta = 1 #Погрешность обслуживания терминала

    clients_time = 1 #Время прихода клиента
    clients_delta = 1 #Погрешность времени прихода клиента

    generator = Generator(
            UniformDistribution(0, 2),
            clients_number,
        )

    operators = [
            Processor(
                UniformDistribution(operator_time - operator_delta, operator_delta + operator_time)
            ),
            Processor(
                UniformDistribution(operator_time - operator_delta, operator_delta + operator_time)
            ),
            Processor(
                UniformDistribution(operator_time - operator_delta, operator_delta + operator_time)
            ),
            Processor(
                UniformDistribution(operator_time - operator_delta, operator_delta + operator_time)
            ),
            # Processor(
            #     UniformDistribution(operator_time - operator_delta, operator_delta + operator_time)
            # ),
            # Processor(
            #     UniformDistribution(operator_time - operator_delta, operator_delta + operator_time)
            # ),
            # Processor(
            #     UniformDistribution(operator_time - operator_delta, operator_delta + operator_time)
            # ),
        ]

    computers = [
        Processor(UniformDistribution(computer_time - computer_delta, computer_delta + computer_time),),
        Processor(UniformDistribution(computer_time - computer_delta, computer_delta + computer_time),),
        Processor(UniformDistribution(computer_time - computer_delta, computer_delta + computer_time),),
    ]

    generator.receivers = operators.copy()
    operators[0].receivers = computers
    operators[1].receivers = computers
    operators[2].receivers = computers
    operators[3].receivers = computers
    # operators[4].receivers = computers
    # operators[5].receivers = computers
    # operators[6].receivers = computers

    model = Modeller(generator, operators, computers)
    result = model.event_mode()
    table.add_row([ 1, result['pribilo'],result['processed'], result['time']])

    table2.add_column('Элементы', [('оператор'+ str(i)) for i in range(len(operators))] + [('терминал' + str(i)) for i in range(len(computers))])
    table2.add_column('Максимальная очередь', result['max_queue'])
    table2.add_column('Обработано', result['proc_arr'])
    
    print("Количество заявок: ", clients_number)
    print(table)
    print(table2)

    


