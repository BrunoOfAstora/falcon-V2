<h1 align="center">F.A.L.C.O.N - V.2</h1>
<h2 align="center"> File Analysis & Lib </h2>

**Falcon** é uma ferramenta de linha de comando (CLI) escrita em **C**, focada em **segurança**, **integridade e manipulação de arquivos**.

O principal objetivo é fornecer um conjunto de utilitários para :

- Calcular e verificar hashes (ex: **SHA-256**, **SHA-384**, **MD5**)
- Realizar operações seguras de remoção de arquivos (**shred**, futuramente)
- Detectar duplicatas
- Trabalhar com banco de dados de checksums

>**Aviso:** Este projeto está em fase inicial de desenvolvimento. Algumas funcionalidades ainda estão incompletas ou instáveis.

## Instalação:
Você pode Instalar o Falcon facilmente com os seguintes comandos no terminal:

```bash
    git clone https://github.com/BrunoOfAstora/falcon-V2.git

    cd falcon-V2

    ./installer.sh
```

Você pode desinstalar o falcon completamente usando:

```bash
    ./installer un
```

Caso queira fazerr alterações e compilar por conta prórpia:

### Requisitos: **Linux** + **GCC**

```bash
git clone https://github.com/BrunoOfAstora/falcon-V2.git
cd falcon
make
```

O binário `falcon` será gerado na pasta raiz do projeto.


##  Como Usar

Após compilar o Falcon, você poderá executar os seguintes comandos diretamente no terminal:

| Comando                          | Descrição                                        |
|----------------------------------|--------------------------------------------------|
| `falcon save .`                  | Salva o hash de todos os arquivos no diretório atual |
| `falcon --md5 <arquivo>`           | Calcula o hash **MD5** de um arquivo             |
| `falcon --sha256 <arquivo>`        | Calcula o hash **SHA-256**                      |
| `falcon --sha384 <arquivo>`        | Calcula o hash **SHA-384**                       |    
| `falcon --sha512 <arquivo>`        | Calcula o hash **SHA-512**                       |
| `falcon --rmdup`                   | Remove arquivos duplicados no diretório atual   |
| `falcon --verify <arquivo>`                  | Verifica integridade com base nos hashes salvos (Parcial) |
| `falcon --help` ou `falcon -h`   | Exibe o menu de ajuda                           |

# Como Funciona ?:

## falcon -s ou --save < arquivo >: 
Ao ser chamado, recebe um argumento, calcula o hash SHA256 do arquivo e salva na pasta "flcn-hash" junto ao nome original do arquivo dentro do diretório home, assim sempre que for verificado com a função "verify" ou com alguma outra função, o programa busca sempre pelo mesmo diretório, o que torna essa busca mais organizada.

## falcon -m  or --md5, -2 ou --sha256, -3 ou sha384, -5 ou --sha512 < arquivo >:
Ao ser chamado, calcula o HASH do arquivo especificado pelo usuário e printa na tela.

## falcon -r ou --rmdup:
Ao ser chamado, itera sobre o diretório e utiliza um hashmap que guarda o HASH SHA256 de cada arquivo e a cada iteração, verifica se o hash se repete, se o hash se repetir, isso significa que o arquivo é o mesmo, assim removendo automaticamente o(s) arquivo(s) duplicado(s). (A escolha do SHA256 como padrão se deu devido a uma falha contida no HASH MD5, na qual pode haver colisão de hashes, o que poderia levar a remoção indesejada de arquivos que não estão duplicados. Esse problema é **impossivel** com o SHA256).

## falcon -v ou --verify < arquivo >:
Essa função verifica a base de dados criada pela função "save" verificando se o nome e o hash do arquivo especificado são os mesmos, se sim printa OK para ambos, se o nome for diferente, e o hash for o mesmo, o programa ainda printa OK para o hash mas printa um aviso informando que o nome foi modificado. Se o hash não bater, isso singifica que o arquivo foi **modificado** ou está **corrompido** e o programa printa um aviso na tela informando isso.

## falcon -h ou --help:
Printa o menu de ajuda na tela.

## ✅ Funcionalidades Concluídas

- ✅ Cálculo de hash **MD5**
- ✅ Cálculo de hash **SHA-256**
- ✅ Cálculo de hash **SHA-384**
- ✅ Cálculo de hash **SHA-512**
- ✅ Salvamento de hashes e nomes de arquivos em um Banco de Dados para posterior verificação
- ✅ Remoção de duplicatas em qualquer diretório
- ✅ Verificação de integridade (comparação de hashes salvos)
- ✅ Interface de ajuda via `--help` e `-h`
- ✅ Verificação de integridade de arquivos

##  Funcionalidades Planejadas (To-Do)

- [ ] Comparação direta via linha de comando
- [ ] Opção de **shred**
- [ ] Outros...
