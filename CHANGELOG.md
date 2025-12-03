# Changelog - Tabela de Setores do Hospital

## [1.0.0] - 2025-12-03

### Adicionado
- ✨ Funcao `exibir_tabela_setores()` em `modules/fila.c`
- ✨ Tabela interativa de setores em ASCII puro
- ✨ Exibicao dos 10 setores do hospital quando paciente eh adicionado
- ✨ Validacao segura de entrada do usuario (tipo e intervalo)
- ✨ Compatibilidade com qualquer terminal (sem caracteres especiais)
- ✨ Integracao com estrutura do grafo do hospital
- ✨ Prototipo adicionado em `modules/fila.h`
- ✨ Documentacao completa em `TABELA_SETORES_HOSPITAL.md`

### Modificado
- 🔧 Atualizacao de `main.c` para chamar tabela de setores
- 🔧 Remocao de caracteres especiais para melhor compatibilidade
- 🔧 Melhorias nas mensagens de validacao

### Tecnologia
- Linguagem: C
- Compilador: GCC
- Compilacao: `gcc -Wall modules/fila.c main.c -o atendimento_pacientes`

### Setores Disponiveis
0. Recepcao
1. Administracao
2. Enfermaria
3. UTI
4. Centro Cirurgico
5. Farmacia
6. Almoxarifado
7. Laboratorio
8. Raio-X
9. Saida de Emergencia

### Fluxo de Uso
1. Usuario seleciona "1. Adicionar paciente a fila"
2. Sistema exibe tabela com 10 setores
3. Usuario seleciona setor de destino (0-9)
4. Sistema valida entrada e confirma encaminhamento
5. Paciente eh adicionado a fila apropriada

### Validacoes
- ✓ Entrada numerica (rejeita letras e simbolos)
- ✓ Intervalo valido (0-9)
- ✓ Limpeza de buffer de entrada
- ✓ Mensagens de erro claras

### Status
✅ Implementado
✅ Testado
✅ Compilacao OK
✅ Sem warnings
