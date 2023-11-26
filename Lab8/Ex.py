def calculate_operations(a, b):
    suma = a + b
    roznica = a - b
    iloczyn = a * b
    iloraz = a / b
    return suma, roznica, iloczyn, iloraz

def main():
    a = 5
    b = 3

    print("Prosty program")
    print(f"Wartość zmiennej 'a': {a}")
    print(f"Wartość zmiennej 'b': {b}")

    suma, roznica, iloczyn, iloraz = calculate_operations(a, b)

    print(f"Suma: {suma}")
    print(f"Różnica: {roznica}")
    print(f"Iloczyn: {iloczyn}")
    print(f"Iloraz: {iloraz}")

if __name__ == "__main__":
    main()
