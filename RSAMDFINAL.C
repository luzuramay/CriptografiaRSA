#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

long long mdc(long long a, long long b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return mdc(b, a % b);
    }
}

long long totiente(long long p, long long q)
{
    return (p - 1) * (q - 1);
}

int sao_coprimos(long long a, long long b)
{
    return mdc(a, b) == 1;
}

int eh_primo(long long n)
{
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;

    long long limite = (long long)sqrt(n);
    
    for (long long i = 3; i <= limite; i += 2)
    {
        if (n % i == 0) return 0;
    }
    
    return 1;
}

long long inverso_modular_euclides(long long e, long long totiente)
{
    if (totiente == 1) return 0;

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

    if (x < 0)
    {
        x += totiente0;
    }

    return x;
}

long long inverso_modular_fermat(long long e, long long modulo_primo)
{
    long long inverso = 1;
    long long base = e % modulo_primo;
    long long expoente = modulo_primo - 2;

    while (expoente > 0)
    {
        if (expoente % 2 == 1)
        {
            inverso = (inverso * base) % modulo_primo;
        }
        base = (base * base) % modulo_primo;
        expoente = expoente / 2;
    }

    return inverso;
}

long long calcular_inverso_modular(long long e, long long phi_n)
{
    if (eh_primo(phi_n))
    {
        return inverso_modular_fermat(e, phi_n);
    }
    else
    {
        return inverso_modular_euclides(e, phi_n);
    }
}

void gerar_chaves_rsa(long long p, long long q, long long e, long long phi_n)
{
    long long n, d;

    n = p * q;

    d = calcular_inverso_modular(e, phi_n);

    printf("\n--- Chaves RSA Geradas ---\n");
    printf("Chave Publica: (n = %lld, e = %lld)\n", n, e);
    printf("Chave Privada: (n = %lld, d = %lld)\n", n, d);

    if ((d * e) % phi_n != 1)
    {
        printf("\nERRO CRITICO: O calculo de 'd' falhou na verificacao (d * e mod phi_n != 1).\n");
        printf("A chave privada esta incorreta.\n");
    }
}

long long mod_exp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;

    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }

        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

int char_para_codigo(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return (c - 'A') + 2;
    }
    else if (c == ' ')
    {
        return 28;
    }
    else
    {
        return -1;
    }
}

char codigo_para_char(int codigo)
{
    if (codigo >= 2 && codigo <= 27)
    {
        return (char)(codigo - 2 + 'A');
    }
    else if (codigo == 28)
    {
        return ' ';
    }
    else
    {
        return '?';
    }
}

int main()
{
    printf("Escolha uma das opcoes abaixo:\n\n");
    printf("1 - Gerar chave publica\n");
    printf("2 - Encriptar mensagem\n");
    printf("3 - Desencriptar mensagem\n\n");

    int tipo;
    printf("Digite a opcao escolhida: ");
    scanf("%d", &tipo);

    while (tipo < 1 || tipo > 3)
    {
        printf("\nNumero invalido. Tente novamente.\n\n");
        printf("Digite a opcao escolhida: ");
        scanf("%d", &tipo);
    }

    if (tipo == 1)
    {
        printf("\nGerar chave publica\n");
        long long p, q, e;
        long long phi_n;

        while (1)
        {
            printf("\nDigite um numero primo p: ");
            if (scanf("%lld", &p) != 1) { return 1; }
            printf("Digite um numero primo q (diferente de p): ");
            if (scanf("%lld", &q) != 1) { return 1; }

            if (!eh_primo(p))
            {
                printf("Erro: p = %lld nao é primo. Tente novamente.\n", p);
            }
            else if (!eh_primo(q))
            {
                printf("Erro: q = %lld nao é primo. Tente novamente.\n", q);
            }
            else if (p == q)
            {
                printf("Erro: p e q devem ser diferentes. Tente novamente.\n");
            }
            else
            {
                break;
            }
        }

        phi_n = totiente(p, q);

        while (1)
        {
            printf("\nDigite o expoente publico e (1 < e < %lld e coprimo com %lld): ", phi_n, phi_n);
            if (scanf("%lld", &e) != 1) { return 1; }

            if (e <= 1 || e >= phi_n)
            {
                printf("Erro: 'e' deve ser maior que 1 e menor que Totiente(n).\n");
            }
            else if (!sao_coprimos(e, phi_n))
            {
                printf("Erro: 'e' = %lld nao é coprimo com Totiente(n) = %lld (MDC é %lld). Tente novamente.\n", e, phi_n, mdc(e, phi_n));
            }
            else
            {
                break;
            }
        }

        gerar_chaves_rsa(p, q, e, phi_n);
    }

    else if (tipo == 2)
    {
        printf("\nEncriptar mensagem\n\n");
        long long n, e;
        char mensagem[256];

        printf("Digite a chave publica (n): ");
        scanf("%lld", &n);
        printf("Digite a chave publica (e): ");
        scanf("%lld", &e);

        getchar();

        printf("Digite a mensagem (A-Z e espacos): ");
        fgets(mensagem, sizeof(mensagem), stdin);

        mensagem[strcspn(mensagem, "\n")] = '\0';

        FILE *arquivo = fopen("mensagem_criptografada.txt", "w");
        if (arquivo == NULL)
        {
            perror("Erro ao criar o arquivo");
            return 1;
        }

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
        printf("Mensagem criptografada salva em 'mensagem_criptografada.txt'\n");
    }

    else
    {
        printf("\nDesencriptar mensagem\n\n");

        long long p, q, e, n, phi, d;

        printf("Voce tem (1) p, q e e  ou (2) n e d ? Digite 1 ou 2: ");
        int modo = 0;
        if (scanf("%d", &modo) != 1)
        {
            printf("Entrada invalida.\n");
            return 1;
        }
        
        getchar();

        if (modo == 1)
        {
            printf("Digite p: ");
            if (scanf("%lld", &p) != 1) { printf("Entrada inválida.\n"); return 1; }
            printf("Digite q: ");
            if (scanf("%lld", &q) != 1) { printf("Entrada inválida.\n"); return 1; }
            printf("Digite e: ");
            if (scanf("%lld", &e) != 1) { printf("Entrada inválida.\n"); return 1; }
            getchar(); 

            if (!eh_primo(p) || !eh_primo(q))
            {
                printf("Erro: p e q devem ser primos.\n");
                return 1;
            }
            if (p == q)
            {
                printf("Erro: p e q devem ser diferentes.\n");
                return 1;
            }

            n = p * q;
            phi = totiente(p, q);

            if (!sao_coprimos(e, phi))
            {
                printf("Erro: e nao é coprimo com phi(n). MDC = %lld\n", mdc(e, phi));
                return 1;
            }

            d = calcular_inverso_modular(e, phi);
            if (d <= 0)
            {
                printf("Erro: falha ao calcular d (inverso modular invalido).\n");
                return 1;
            }

            if ((d * e) % phi != 1)
            {
                printf("Erro: verificaçao falhou: (d * e) mod phi != 1\n");
                return 1;
            }
        }
        else if (modo == 2)
        {
            printf("Digite n: ");
            if (scanf("%lld", &n) != 1) { printf("Entrada inválida.\n"); return 1; }
            printf("Digite d: ");
            if (scanf("%lld", &d) != 1) { printf("Entrada inválida.\n"); return 1; }
            getchar();
        }
        else
        {
            printf("Opcao invalida.\n");
            return 1;
        }

        FILE *entrada = fopen("mensagem_criptografada.txt", "r");
        if (entrada == NULL)
        {
            perror("Erro ao abrir 'mensagem_criptografada.txt'");
            return 1;
        }

        FILE *saida = fopen("mensagem.txt", "w");
        if (saida == NULL)
        {
            perror("Erro ao criar 'mensagem.txt'");
            fclose(entrada);
            return 1;
        }

        printf("Descriptografando mensagem...\n");

        long long c;
        while (fscanf(entrada, "%lld", &c) == 1)
        {
            long long m = mod_exp(c, d, n);

            char letra = codigo_para_char((int)m);

            fprintf(saida, "%c", letra);
        }

        fclose(entrada);
        fclose(saida);

        printf("Mensagem descriptografada salva em 'mensagem.txt' \n");
    }
    
    return 0;
}
