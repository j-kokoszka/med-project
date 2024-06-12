import csv

# Funkcja do odczytywania transakcji z pliku
def read_transactions(filename):
    with open(filename, 'r') as file:
        transactions = [line.strip() for line in file]
    return transactions

# Funkcja do zapisywania macierzy do pliku CSV
def write_matrix_to_csv(matrix, headers, output_filename):
    with open(output_filename, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(headers)
        csvwriter.writerows(matrix)

# Główna funkcja przetwarzająca transakcje na macierz
def process_transactions(input_filename, output_filename):
    transactions = read_transactions(input_filename)

    # Wyodrębnianie unikalnych elementów i ich sortowanie
    unique_elements = sorted(set(item for transaction in transactions for item in transaction.split(',')))
    num_elements = len(unique_elements)

    # Tworzenie mapowania elementów do kolumn
    element_to_index = {element: index for index, element in enumerate(unique_elements)}

    # Tworzenie macierzy
    matrix = [['' for _ in range(num_elements)] for _ in range(len(transactions))]

    for i, transaction in enumerate(transactions):
        items = transaction.split(',')
        for item in items:
            index = element_to_index[item]
            matrix[i][index] = 't'

    # Generowanie nagłówków (A, B, C, ...)
    headers = [i+1 for i in range(num_elements)]

    # Zapisywanie macierzy do pliku CSV
    write_matrix_to_csv(matrix, headers, output_filename)

# Ścieżki do plików
# input_filename = 'transactions.txt'
input_filename = 'chess-test.csv'
output_filename = 'output.csv'

# Wywołanie funkcji
process_transactions(input_filename, output_filename)

# Wypisywanie wyniku w formacie CSV na ekranie
transactions = read_transactions(input_filename)
unique_elements = sorted(set(item for transaction in transactions for item in transaction.split(',')))
unique_elements = sorted([int(element) for element in unique_elements if element])
str_unique_elements = ','.join(map(str, unique_elements))
print(str_unique_elements)
for i, t in enumerate(transactions):
    tmp = []
    for e in unique_elements:
        tmp.append(chr(32+e))
    print(str(i)+','+''.join(tmp))
    # print(i, t)
    # t = [int(num) for num in t.split(',')]
    # tmp = []
    # for e in unique_elements:
    #     if e in t:
    #         tmp.append('t,')
    #     else:
    #         tmp.append(',')
    # print(''.join(tmp))