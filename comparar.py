def comparar_arquivos(arquivo1, arquivo2):
    with open(arquivo1, "r", encoding="utf-8") as f1, \
         open(arquivo2, "r", encoding="utf-8") as f2:

        linha = 1

        while True:
            l1 = f1.readline()
            l2 = f2.readline()

            if l1 != l2:
                print(f"Arquivos diferentes na linha {linha}")
                return False

            if not l1 and not l2:
                break

            linha += 1

    print("Arquivos iguais")
    return True

comparar_arquivos("biblia-em-txt.txt", "restaurado.txt")