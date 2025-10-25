# 🔐 Criptografia RSA em C

Projeto desenvolvido para implementar o algoritmo de **Criptografia RSA** de forma didática, usando apenas **linguagem C** e **bibliotecas padrão**.  
O programa permite **gerar chaves públicas e privadas**, **criptografar mensagens** e **descriptografar mensagens** salvas em arquivos de texto.

---

## 📘 Sobre o Projeto

O RSA é um dos algoritmos mais utilizados em segurança digital.  
Neste projeto, a implementação é feita **passo a passo**, desde o cálculo do **MDC**, **Totiente**, e **Inverso Modular**, até a **criptografia** e **descriptografia** completas de mensagens.

O código completo se encontra no arquivo `RSAMDFINAL.C`, e foi escrito em C puro, sem dependências externas, com foco no aprendizado da lógica interna do RSA.

---

## ⚙️ Funcionalidades

- 🔑 **Geração de chaves RSA** (p, q, e, d, n)  
- ✉️ **Criptografia** de mensagens (gera `mensagem_criptografada.txt`)  
- 🔓 **Descriptografia** (gera `mensagem.txt`)  
- 📄 Uso direto pelo terminal  
- 🧮 Implementação manual do inverso modular, totiente e MDC

---

## 🧩 Estrutura do Projeto

```
RSA/
├── RSAMDFINAL.C         # Código principal com todas as funções
└── README.md            # Este arquivo
```

---

## 💻 Como Compilar

Use o compilador **gcc**:

```bash
gcc RSAMDFINAL.C -o rsa
```

---

## ▶️ Como Executar

Após compilar, execute o programa no terminal:

```bash
./rsa
```

O programa exibirá um menu interativo:

```
Escolha uma das opções abaixo:

1 - Gerar chave pública
2 - Encriptar mensagem
3 - Desencriptar mensagem
```

---

## 🧠 Exemplos de Uso

### 🧩 1. Gerar Chaves
```
Escolha: 1
Digite um número primo p: 61
Digite um número primo q (diferente de p): 53
Digite o expoente público e: 17
```

**Saída:**
```
--- Chaves RSA Geradas ---
Chave Pública: (n = 3233, e = 17)
Chave Privada: (n = 3233, d = 2753)
```

---

### ✉️ 2. Criptografar Mensagem
```
Escolha: 2
Digite a chave publica (n): 3233
Digite a chave publica (e): 17
Digite a mensagem (A-Z e espaços): OI
```

**Resultado:**  
Arquivo `mensagem_criptografada.txt` será criado com os números criptografados.

---

### 🔓 3. Descriptografar Mensagem
```
Escolha: 3
Você tem (1) p, q e e  ou (2) n e d ? Digite 1 ou 2: 2
Digite n: 3233
Digite d: 2753
```

**Resultado:**  
Arquivo `mensagem.txt` criado com o texto original descriptografado.

---

## 📄 Arquivos Gerados

| Arquivo | Descrição |
|---------|-----------|
| `mensagem_criptografada.txt` | Contém a mensagem criptografada (números) |
| `mensagem.txt` | Contém a mensagem descriptografada (texto original) |

---

## 🛠️ Funções Importantes

O código contém funções bem organizadas e comentadas para cada etapa do RSA:

| Função | Descrição |
|--------|-----------|
| `mdc(a, b)` | Calcula o máximo divisor comum |
| `totiente(p, q)` | Calcula o totiente de Euler |
| `eh_primo(n)` | Verifica se um número é primo |
| `sao_coprimos(a, b)` | Verifica se dois números são coprimos |
| `inverso_modular_euclides()` | Calcula o inverso modular pelo Algoritmo de Euclides Estendido |
| `inverso_modular_fermat()` | Calcula o inverso modular usando o Teorema de Fermat |
| `calcular_inverso_modular()` | Escolhe automaticamente o método correto (Fermat ou Euclides) |
| `mod_exp()` | Faz a exponenciação modular eficiente (base^expoente mod n) |
| `char_para_codigo()` | Converte caracteres A–Z e espaço em números para criptografia |
| `codigo_para_char()` | Converte os números de volta em letras |
| `gerar_chaves_rsa()` | Calcula e exibe as chaves pública e privada RSA |

---

## 🧾 Requisitos

- Compilador **C** (gcc, clang, etc.)  
- Sistema **Windows, Linux** ou **macOS**  
- Nenhuma biblioteca externa necessária

---

## 🧑‍💻 Autoria

**Ana Carolina, Calebe de Oliveira, Danielle Vitória, Larissa Lopes, Maria Luisa, Mayara Lins, Sophia Byernes**  
Projeto desenvolvido como estudo prático do algoritmo RSA e da implementação de criptografia em linguagem C.

---

## 📚 Licença

Código aberto para fins **educacionais e acadêmicos**.  
Sinta-se livre para modificar e melhorar!
