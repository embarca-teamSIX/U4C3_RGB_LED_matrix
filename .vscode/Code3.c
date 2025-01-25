#include <stdio.h>  // Inclui biblioteca padrão para entrada e saída

int main() {
    int num1, num2, soma;

    // Solicita ao usuário para inserir dois números
    printf("Digite o primeiro numero: ");
    scanf("%d", &num1);
    printf("Digite o segundo numero: ");
    scanf("%d", &num2);

    // Calcula a soma dos dois números
    soma = num1 + num2;

    // Exibe o resultado
    printf("A soma de %d e %d é: %d\n", num1, num2, soma);

    return 0;  // Indica que o programa terminou com sucesso
}
