import random as rnd
from faker import Faker
import csv
from datetime import datetime
import calendar


PRODUCTS_COUNT = 10000
SHOPS_COUNT = 1000
SR_COUNT = 25000
 
def GenProductsTable(csvfilename):
    with open(csvfilename, 'w', newline='') as csvfile:
        fieldnames = ['ID', 'Name', 'ProductType']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames, delimiter=';')

        writer.writeheader()
        with open('src_data/product_data.csv', newline='') as csvfile:
            reader = csv.DictReader(csvfile, delimiter=';')

            i = 1
            for row in reader:
                if i > PRODUCTS_COUNT:
                    break

                writer.writerow({fieldnames[0] : i,
                                 fieldnames[1] : row['product_name'],
                                 fieldnames[2] : row['product_type']})
                
                i += 1


def GenShopsTable(csvfilename):
    def GenName(faker):
        word = faker.word()
        if word[-1] != 'ь' and word[-2:-1] != 'ся' and len(word) > 3:
            return word.capitalize()
        else:
            return GenName(faker)
    
    with open(csvfilename, 'w', newline='') as csvfile:
        fieldnames = ['ID', 'Name', 'Description']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames, delimiter=';')
        faker = Faker('ru_RU')
        writer.writeheader()
        for i in range(SHOPS_COUNT):
            writer.writerow({fieldnames[0] : i + 1,
                             fieldnames[1] : GenName(faker),
                             fieldnames[2] : faker.sentence()})
                
            i += 1


def GenSRTable(csvfilename):
    with open(csvfilename, 'w', newline='') as csvfile:
        fieldnames = ['ID', 'FIO', 'ShopID', 'DateOfPurchase']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames, delimiter=';')
        faker = Faker('ru_RU')
        writer.writeheader()
        for i in range(SR_COUNT):
            writer.writerow({fieldnames[0] : i + 1,
                             fieldnames[1] : faker.name(),
                             fieldnames[2] : rnd.randint(1, SHOPS_COUNT),
                             fieldnames[3] : faker.date_between_dates(date_start=datetime(2021,1,1), date_end=datetime(2022,6,30))})
                
            i += 1


def GenAvailabilityTable(csvfilename):
    with open(csvfilename, 'w', newline='') as csvfile:
        fieldnames = ['ID', 'ShopID', 'ProductID']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames, delimiter=';')
        writer.writeheader()

        j = 1
        for i in range(SHOPS_COUNT):
            for _ in range(rnd.randint(1, 199)):
                writer.writerow({fieldnames[0] : j,
                                 fieldnames[1] : i + 1,
                                 fieldnames[2] : rnd.randint(1, PRODUCTS_COUNT)})
                j += 1
                
            i += 1


def GenSaleReceiptPositionsTable(csvfilename):
    avail_table = []
    with open('Availability.csv', newline='') as avail_table_csv:
        reader = csv.DictReader(avail_table_csv, delimiter=';')
        for row in reader:
            avail_table.append((row['ID'], row['ShopID'], row['ProductID']))

    sr_table = []
    with open('SaleReceipts.csv', newline='') as sr_table_csv:
        reader = csv.DictReader(sr_table_csv, delimiter=';')
        for row in reader:
            sr_table.append((row['ID'], row['ShopID']))
    
    with open(csvfilename, 'w', newline='') as csvfile:
        fieldnames = ['ID', 'AvailabilityID', 'SaleReceiptID']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames, delimiter=';')
        writer.writeheader()
        j = 1
        for i in range(SR_COUNT):
            sr_avails = [x[0] for x in avail_table if x[1] == sr_table[i][1]]
            for _ in range(rnd.randint(1, 7)):
                writer.writerow({fieldnames[0] : j,
                                 fieldnames[1] : rnd.choice(sr_avails),
                                 fieldnames[2] : i + 1})
                j += 1


def GenCostStory(csvfilename):
    costs = [0] * PRODUCTS_COUNT

    with open('src_data/product_data.csv', newline='') as csvfile:
            reader = csv.DictReader(csvfile, delimiter=';')
            i = 0
            for row in reader:
                costs[i] = float(row['product_cost'])
                i += 1
    
    with open(csvfilename, 'w', newline='') as csvfile, open('Availability.csv', newline='') as avail_table:
        fieldnames = ['ID', 'Year', 'Month', 'Cost', 'AvailabilityID']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames, delimiter=';')
        writer.writeheader()

        reader = csv.DictReader(avail_table, delimiter=';')
        i = 0
        j = 1
        for row in reader:
            prod_id = int(row['ProductID'])
            
            mu = costs[prod_id - 1]
            disp = mu * 0.15
            for date in month_year_iter(1, 2021, 6, 2022):      
                writer.writerow({fieldnames[0] : j,
                                 fieldnames[1] : date[0],
                                 fieldnames[2] : date[1],
                                 fieldnames[3] : int(rnd.gauss(mu, disp)),
                                 fieldnames[4] : i + 1})
                j += 1
                    
            i += 1


def month_year_iter(start_month, start_year, end_month, end_year):
    ym_start = 12 * start_year + start_month - 1
    ym_end = 12 * end_year + end_month - 1
    for ym in range(ym_start, ym_end + 1):
        y, m = divmod(ym, 12)
        yield y, m+1


def main():
    GenProductsTable('Products.csv')
    print('Products generated')
    GenShopsTable('Shops.csv')
    print('Shops generated')
    GenSRTable('SaleReceipts.csv')
    print('SaleReceipts generated')
    GenAvailabilityTable('Availability.csv')
    print('Availability generated')
    GenSaleReceiptPositionsTable('SaleReceiptPositions.csv')
    print('SaleReceiptPositions generated')
    GenCostStory('CostStory.csv')
    print('CostStory generated')
    print('exiting...')


if __name__ == '__main__':
    main()
