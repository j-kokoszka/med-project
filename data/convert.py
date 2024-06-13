import csv

# Funkcja do odczytywania transakcji z pliku
def read_transactions(filename):
    with open(filename, 'r') as file:
        transactions = [line.strip() for line in file]
    return transactions



# Ścieżki do plików
# input_filename = 'transactions.txt'
input_filename = 'accidents.csv'
output_filename = 'mushroom-out.csv'

# Wywołanie funkcji
# process_transactions(input_filename, output_filename)

# Wypisywanie wyniku w formacie CSV na ekranie
transactions = read_transactions(input_filename)
unique_elements = sorted(set(item for transaction in transactions for item in transaction.split(',')))
unique_elements = sorted([int(element) for element in unique_elements if element])
str_unique_elements = ','.join(map(str, unique_elements))
# print(str_unique_elements)
for i, t in enumerate(transactions):
    tmp = []
    # for e in :
    #     tmp.append(chr(32+e))
    # print(str(i)+','+''.join(tmp))
    # print(i, t)
    t = [int(num) for num in t.split(',')]
    tmp = []
    for e in t:
        tmp.append(chr(32+e))
    # print(tmp)
    # for e in unique_elements:
        # if e in t:
            # tmp.append('t,')
        # else:
            # tmp.append(',')
    print(str(i+1)+','+''.join(tmp))