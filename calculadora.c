// Inclusão das bibliotecas
#include <stdio.h> // Necessária para as funções wprintf() e fgets().
#include <stdlib.h> // Necessária para as funções strtof() e atoi().
#include <math.h> // Necessária para a função pow().
#include <string.h> // Necessária para a função strchr().
#include <locale.h> // Necessária para a função setlocale().

// A função principal é do tipo "void" pois não retorna nenhum valor.
void main() {
    
    // Declaração das variáveis.
    char primeiro_numero[100], segundo_numero[100], opcao_menu[100], opcao_sair[100], *ponteiro_final;
    int operacao, valido, continuar;
    float a, b;

    // A função setlocale() altera a região para suportar os caracteres especiais do Português. "LC_CTYPE" significa que ela deve alterar apenas os caracteres, mantendo o sistema internacional para números decimais (com o ponto).
    setlocale(LC_CTYPE, "Portuguese");

    // Mensagem de boas vindas ao usuário.
    wprintf(L"\nBem-vindo à calculadora escrita em C!\n");

    inicio:
    // Solicita o primeiro número ao usuário.
    do { 
        wprintf(L"\nDigite o primeiro número: "); // Exibe na tela a solicitação do primeiro número.
        fgets(primeiro_numero, 100, stdin); // A função fgets() lê o input do usuário (stdin) e armazena como string na variável "primeiro_numero".
        a = strtof(primeiro_numero, &ponteiro_final); // A função strtof() converte a string "primeiro_numero" para float, caso possível, e armazena na variável "a". O ponteiro final representa o primeiro caractere que não pôde ser lido, ou seja, se nenhum valor do tipo float for inserido, a string "primeiro_numero" e o ponteiro "ponteiro_final" terão o mesmo valor.

        if (primeiro_numero == ponteiro_final) { // Se "primeiro_numero" for igual a "ponteiro_final", ou seja, se nenhum valor válido (float) foi lido,
            wprintf(L"\nValor inválido. Por favor, digite um número inteiro ou decimal.\n"); // então é exibida uma mensagem de erro,
            valido = 0; // e a variável "valido" continua igual a zero, mantendo o loop.
        } else if (strchr(primeiro_numero, ',') != NULL) { // A função strchr() busca por uma vírgula na string primeiro_numero. Se for verdadeiro (ou seja, != de NULL),
            wprintf(L"\nPor favor, separe a casa decimal com o ponto.\n"); // então é exibida uma mensagem de erro,
            valido = 0; // e a variável "valido" continua igual a zero, mantendo o loop.
        } else {
            valido = 1; // Do contrário, tudo deu certo e se atribui o valor 1 à variável "valido", saindo do loop.
        }
    } while (!valido); // O loop continua enquanto não for válido (!valido), isto é, enquanto for igual a zero.
        
    // Solicita ao usuário qual a operação desejada. A lógica da validação é basicamente a mesma utilizada na solicitação do primeiro número, com pequenas alterações.
    do {
        wprintf(L"\nQue operação deseja realizar?\n\n1 - Soma\n2 - Subtração\n3 - Multiplicação\n4 - Divisão\n5 - Porcentagem\n6 - Potenciação\n\nOpção: ");
        fgets(opcao_menu, 100, stdin);
        operacao = atoi(opcao_menu); // Neste caso, não precisamos da função strtof(), pois queremos apenas um número inteiro. A função atoi() converte qualquer valor possível para inteiro (int). Se não puder converter nada, o valor retornado é zero.

        if (strlen(opcao_menu) != 2 || operacao < 1 || operacao > 6) { // A função strlen() retorna o tamanho (length) da variável, sendo o valor 2 no caso de um único caractere. Se for diferente de 2 (ou seja, se o usuário digitar mais de um caractere), ou se a variável "operacao" não estiver entre os números 1 e 6.
            wprintf(L"\nOpção inválida. Por favor, digite um número do menu.\n");
            valido = 0;    
        } else {
            valido = 1;
        }
    } while (!valido);

    meio:
    // Solicita o segundo número ao usuário. Aqui é feita a mesma validação utilizada na solicitação do primeiro número, apenas alterando as variáveis "primeiro_numero" e "a" para "segundo_numero" e "b".
    do {
        wprintf(L"\nDigite o segundo número: ");
        fgets(segundo_numero, 100, stdin);
        b = strtof(segundo_numero, &ponteiro_final);

        if (segundo_numero == ponteiro_final) {
            wprintf(L"\nValor inválido. Por favor, digite um número inteiro ou decimal.\n");
            valido = 0;
        } else if (strchr(segundo_numero, ',') != NULL) {
            wprintf(L"\nPor favor, separe a casa decimal com o ponto.\n");
            valido = 0;
        } else {
            valido = 1;
        }
    } while (!valido);

    // Mostra o resultado ao usuário
    switch(operacao) { // O switch vai lidar com o valor digitado pelo usuário para a operação desejada, armazenado na variável "operacao".
        case 1: // Se digitar 1,
            wprintf(L"\n%f mais %f é igual a: %f\n", a, b, a + b); // imprime a soma de "a" e "b",
            break; // e sai do loop.
        case 2: // Se digitar 2,
            wprintf(L"\n%f menos %f é igual a: %f\n", a, b, a - b); // imprime a subtração de "a" e "b",
            break; // e sai do loop.
        case 3: // Se digitar 3,
            wprintf(L"\n%f vezes %f é igual a: %f\n", a, b, a * b); // imprime a multiplicação de "a" por "b",
            break; // e sai do loop.
        case 4: // Se digitar 4 (divisão),
            if (b == 0) { // se o segundo número for igual a zero,
                wprintf(L"\nNão é possível dividir por zero. Por favor, escolha um divisor válido.\n"); // imprime a mensagem de erro,
                goto meio; // e volta para a solicitação do segundo número.
            } else { // Do contrário,
                wprintf(L"\n%f dividido por %f é igual a: %f\n", a, b, a / b); // imprime a divisão de "a" por "b",
                break; // e sai do loop.
            }
        case 5: // Se digitar 5,
            wprintf(L"\nA porcentagem de %f em %f é igual a: %f%%\n", a, b, a / b * 100); // imprime a porcentagem de "a" em "b",
            break; // e sai do loop.
        case 6: // Se digitar 6,
            wprintf(L"\n%f elevado à potência %f é igual a: %f\n", a, b, pow(a,b)); // imprime a potenciação de "a" em "b",
            break; // e sai do loop.
    }

    // Pergunta ao usuário se deseja realizar outra operação. Aqui a lógica da validação é a mesma utilizada na solicitação do menu de operações.
    do {
        wprintf(L"\nDeseja realizar outra operação?\n\n1 - Sim\n2 - Não\n\nOpção: ");
        fgets(opcao_sair, 100, stdin);
        continuar = atoi(opcao_sair);

        if (strlen(opcao_sair) != 2 || continuar < 1 || continuar > 2) {
            wprintf(L"\nOpcao inválida. Por favor, digite um número do menu.\n");
            valido = 0;    
        } else if (continuar == 1) { // Se o usuário digitar 1,
            goto inicio; // voltar para o início do programa.
        } else if (continuar == 2) { // Se o usuário digitar 2,
            valido = 1; // sair do loop.
        }
    } while (!valido);
}