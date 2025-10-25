#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

////////////////////////////////////////////////////////---FUNÇÕES DAS CHAVES---////////////////////////////////////////////////////////
// Funções mdc, totiente, sao_coprimos, eh_primo 
long long mdc(long long a, long long b) {
    if (b == 0) return a;
    else return mdc(b, a % b);
}

long long totiente(long long p, long long q) {
    return (p - 1) * (q - 1);
}

int sao_coprimos(long long a, long long b) {
    return mdc(a, b) == 1;
}

int eh_primo(long long n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;

    long long limite = (long long)sqrt(n);
    for (long long i = 3; i <= limite; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// --- DUAS FUNÇÕES DE INVERSO MODULAR ---

// 1. Algoritmo de Euclides Estendido 
long long inverso_modular_euclides(long long e, long long totiente)
{
    // Usa o algoritmo mais geral (Euclides Estendido).
    if(totiente == 1) return 0;

    long long totiente0 = totiente;
    long long x = 1, y = 0;

    while (e > 1)
    {
        long long q = e / totiente;

        long long n = totiente;
        totiente = e % totiente;
        e = n;

        n = y;
        y = x - q * y;
        x = n;
    }

    if(x < 0)
    {
        x += totiente0;
    }

    return x;
}

// 2. Teorema de Fermat 
long long inverso_modular_fermat(long long e, long long modulo_primo){
    // Usa a exponenciação por quadrados para calcular e^(m-2) mod m.

    long long inverso = 1;
    long long base = e % modulo_primo;
    long long expoente = modulo_primo - 2;

    while(expoente > 0)
    {
        if(expoente % 2 == 1)
        {
            inverso = (inverso * base) % modulo_primo;
        }
        base = (base * base) % modulo_primo;
        expoente = expoente / 2;
    }

    return inverso;
}


// --- NOVA FUNÇÃO QUE ESCOLHE O ALGORITMO ---

long long calcular_inverso_modular(long long e, long long phi_n) {

    if (eh_primo(phi_n)) {
        // Se phi_n for primo, usamos o método obrigatório de Fermat

        return inverso_modular_fermat(e, phi_n);
    } else {
        // Se phi_n não for primo, usamos o método correto e geral (Euclides Estendido)

        return inverso_modular_euclides(e, phi_n);
    }
}


void gerar_chaves_rsa(long long p, long long q, long long e, long long phi_n) {
    long long n, d;
    int metodo_usado = 0; // Variável para rastrear o algoritmo usado

    // 1. Calcular n
    n = p * q;

    // 2. Totiente ja foi enviado na cópia da função

    // 3. Calcular o Expoente Privado 'd'
    d = calcular_inverso_modular(e, phi_n);

    // Exibir o resultado final
    printf("\n--- Chaves RSA Geradas ---\n");
    printf("Chave Pública: (n = %lld, e = %lld)\n", n, e);
    printf("Chave Privada: (n = %lld, d = %lld)\n", n, d);

    // Verificação de segurança (d * e mod phi_n deve ser 1)
    if ((d * e) % phi_n != 1) {
        printf("\nERRO CRÍTICO: O cálculo de 'd' falhou na verificação (d * e mod phi_n != 1). A chave privada está incorreta.\n");
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////-----------FUNÇÕES DA ENCRIPTA-----------////////////////////////////////////////////////////
long long mod_exp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

// Converte caractere A-Z ou espaço em número (2–28)
int char_para_codigo(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (c - 'A') + 2;
    else if (c == ' ')
        return 28;
    else
        return -1; // caractere inválido
}

// *** FUNÇÃO ADICIONADA PARA CORRIGIR A DESCRIPTOGRAFIA ***
// Converte código (2-28) de volta para caractere
char codigo_para_char(int codigo)
{
    if (codigo >= 2 && codigo <= 27)
    {
        // Mapeia 2-27 para A-Z
        return (char)(codigo - 2 + 'A');
    }
    else if (codigo == 28)
    {
        // Mapeia 28 para espaço
        return ' ';
    }
    else
    {
        // Retorna '?' para qualquer código inválido (ex: 0, 1, >28)
        return '?';
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    //parte que ta no docs do trabalho

    // Variáveis de arquivo e buffer removidas, pois não são usadas na main
    // FILE *arquivoOrigem;
    // FILE *arquivoDestino;
    // char buffer[1024];//leitura dos dados

    //achei meio confuso essa parte, nao consegui fazer esse lance de abrir os files e a função q fecha eles direito, acho q ta errado

    printf ("Escolha uma das opções abaixo:\n\n");
    printf ("1 - Gerar chave pública\n");
    printf ("2 - Encriptar mensagem\n");
    printf ("3 - Desencriptar mensagem\n\n");

    int tipo;
    printf ("Digite a opção escolhida: ");
    scanf ("%d", &tipo);

    while (tipo < 1|| tipo > 3){
        printf ("\nNúmero inválido. Tente novamente.\n\n");
        printf ("Digite a opção escolhida: ");
        scanf ("%d", &tipo);//outro printf e outro scanf para que digite um valor válido
    }

    if (tipo == 1){

        printf ("\nGerar chave pública\n");
        long long p, q, e;
        long long phi_n;

        // ... (Entrada e validação de p e q) ...
        while (1) {
            printf("\nDigite um número primo p: ");
            if (scanf("%lld", &p) != 1) { return 1; }
            printf("Digite um número primo q (diferente de p): ");
            if (scanf("%lld", &q) != 1) { return 1; }

            if (!eh_primo(p)) {
                printf("Erro: p = %lld não é primo. Tente novamente.\n", p);
            } else if (!eh_primo(q)) {
                printf("Erro: q = %lld não é primo. Tente novamente.\n", q);
            } else if (p == q) {
                printf("Erro: p e q devem ser diferentes. Tente novamente.\n");
            } else {
                break;
            }
        }

        // Cálculo ÚNICO do Totiente (para a validação de 'e')
        phi_n = totiente(p, q);

        // ... (Entrada e validação de e) ...
        while (1) {
            printf("\nDigite o expoente público e (1 < e < %lld e coprimo com %lld): ", phi_n, phi_n);
            if (scanf("%lld", &e) != 1) { return 1; }

            if (e <= 1 || e >= phi_n) {
                printf("Erro: 'e' deve ser maior que 1 e menor que Totiente(n).\n");
            } else if (!sao_coprimos(e, phi_n)) {
                printf("Erro: 'e' = %lld não é coprimo com Totiente(n) = %lld (MDC é %lld). Tente novamente.\n", e, phi_n, mdc(e, phi_n));
            } else {
                break;
            }
        }

        // Geração das Chaves
        gerar_chaves_rsa(p, q, e, phi_n);//chama a função da chave pública, não lembro qual o nome que escolheram
    }

    else if (tipo == 2){
        printf("\nEncriptar mensagem\n\n");
        long long n, e;
        char mensagem[256];

        // Entrada da chave pública
        printf("Digite a chave publica (n): ");
        scanf("%lld", &n);
        printf("Digite a chave publica (e): ");
        scanf("%lld", &e);
        getchar(); // limpa o buffer do teclado

        // Entrada da mensagem
        printf("Digite a mensagem (A-Z e espacos): ");
        fgets(mensagem, sizeof(mensagem), stdin);

        // Remove o \n do final, se houver
        mensagem[strcspn(mensagem, "\n")] = '\0';

        // Abre arquivo para salvar a mensagem criptografada
        FILE *arquivo = fopen("mensagem_criptografada.txt", "w");
        if (arquivo == NULL)
        {
            perror("Erro ao criar o arquivo");
            return 1;
        }

        // Criptografa e salva no arquivo
        for (int i = 0; i < strlen(mensagem); i++)
        {
            char c = toupper(mensagem[i]);
            int codigo = char_para_codigo(c);

            if (codigo != -1)
            {
                long long cript = mod_exp(codigo, e, n);
                fprintf(arquivo, "%lld ", cript);
            }
        }

        fclose(arquivo);
        printf("Mensagem criptografada salva em 'mensagem_criptografada.txt'\n");//chama a função de encriptar a mensagem;
    }

    else
    {  // opção 3 - Desencriptar
        printf("\nDesencriptar mensagem\n\n");

        long long p, q, e, n, phi, d;

        // Pergunta se o usuário quer fornecer (p,q,e) para recalcular d ou fornecer (n,d) diretamente
        printf("Você tem (1) p, q e e  ou (2) n e d ? Digite 1 ou 2: ");
        int modo  =  0;
        if  (scanf("%d",  & modo)  !=  1)
        {
            printf("Entrada inválida.\n");
            return  1;
        }
        getchar();  // limpa newline

        if  (modo  ==  1)  // caso digite 1
        {
            // lê p, q, e e valida
            printf("Digite p: ");
            if  (scanf("%lld",  & p)  !=  1)
            {
                printf("Entrada inválida.\n");
                return  1;
            }
            printf("Digite q: ");
            if  (scanf("%lld",  & q)  !=  1)
            {
                printf("Entrada inválida.\n");
                return  1;
            }
            printf("Digite e: ");
            if  (scanf("%lld",  & e)  !=  1)
            {
                printf("Entrada inválida.\n");
                return  1;
            }
            getchar();  // limpa newline

            if  ( ! eh_primo(p)  ||   ! eh_primo(q))
            {
                printf("Erro: p e q devem ser primos.\n");
                return  1;
            }
            if  (p  ==  q)
            {
                printf("Erro: p e q devem ser diferentes.\n");
                return  1;
            }

            n  =  p  * q;
            phi  =  totiente(p, q);

            if  ( ! sao_coprimos(e, phi))
            {
                printf("Erro: e não é coprimo com phi(n). MDC = %lld\n", mdc(e, phi));
                return  1;
            }

            // calcula d usando inverso modular
            d  =  calcular_inverso_modular(e, phi);
            if  (d  <=  0)
            {
                printf("Erro: falha ao calcular d (inverso modular inválido).\n");
                return  1;
            }

            // Verifica
            if  ((d  * e)  %  phi  !=  1)
            {
                printf("Erro: verificação falhou: (d * e) mod phi != 1\n");
                return  1;
            }
        }
        else   if  (modo  ==  2)  // a opção 2
        {
            // lê n e d diretamente (se já possui a chave privada)
            printf("Digite n: ");
            if  (scanf("%lld",  & n)  !=  1)
            {
                printf("Entrada inválida.\n");
                return  1;
            }
            printf("Digite d: ");
            if  (scanf("%lld",  & d)  !=  1)
            {
                printf("Entrada inválida.\n");
                return  1;
            }
            getchar();  // limpa newline
        }
        else
        {
            printf("Opção inválida.\n");
            return  1;
        }

        // Abre o arquivo com a mensagem criptografada
        FILE  * entrada  =  fopen("mensagem_criptografada.txt", "r");
        if  (entrada  ==  NULL)
        {
            perror("Erro ao abrir 'mensagem_criptografada.txt'");
            return  1;
        }

        // Cria o arquivo de saída para a mensagem descriptografada
        FILE  * saida  =  fopen("mensagem.txt", "w");
        if  (saida  ==  NULL)
        {
            perror("Erro ao criar 'mensagem.txt'");
            fclose(entrada);
            return  1;
        }

        printf("Descriptografando mensagem...\n");

        // Lê cada número criptografado e descriptografa
        long long c;
        while  (fscanf(entrada, "%lld",  & c)  ==  1)
        {
            // Descriptografa: m = c^d mod n
            long long m  =  mod_exp(c, d, n);

            // converte número em caractere
            char letra  =  codigo_para_char((int)m);

            // Escreve no arquivo de saída
            fprintf(saida, "%c", letra);
        }

        fclose(entrada);
        fclose(saida);

        printf("Mensagem descriptografada salva em 'mensagem.txt' \n");
    }
    return  0;
}