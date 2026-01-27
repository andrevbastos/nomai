# Nomai
Ferramenta TUI para gerenciar projetos de desenvolvimento de software. Ela facilita a navegação entre projetos, o lançamento de ambientes de desenvolvimento e a integração com Git, tudo através de uma interface intuitiva e eficiente.

## 📋 Funcionalidades Planejadas

### Core
- **Navegação Assíncrona:** Estilo Yazi/Ranger (Tree & Flat view).
- **Vim Motions:** Navegação completa via teclado.
- **Smart Preview:** Visualização rápida de arquivos de texto e código.
- **File Queue:** Operações de I/O (copiar, mover, deletar) em background.
- **Registry Centralizado:** Armazenamento de configurações e caminhos em `~/.config/nomai` (ou similar).
- **TUI Dashboard:** Interface limpa (FTXUI) para listar, filtrar e gerenciar os projetos cadastrados.
- **Leave Messages:** Persistência de notas rápidas sobre o estado do trabalho ao encerrar a sessão.

### Launcher
- **Wizard de Projetos:** Adição manual de projetos via TUI com configuração passo-a-passo.
- **Multi-App Launch:** Disparo simultâneo da IDE escolhida e apps auxiliares (DBeaver, Insomnia, etc.).
- **CLI Smart Jump:** Suporte a argumentos (`nomai <nome>`) para lançamento direto sem passar pela TUI.
- **Fuzzy Matching:** Detecção inteligente de nomes de projetos (estilo `zoxide`).

### Integração Git
- **Advanced Config:** Gestão visual de `git update-index --skip-worktree`.
- **Interactive Staging:** Seleção e stage de arquivos via interface.
- **Live Status:** Monitoramento de branch, dirty state e ahead/behind.
- **Git Branch Config:** Definição manual de branches `master` e `dev` por projeto para monitoramento rápido.
- **Quality Gate:** Bloqueio de commits em projetos gerenciados caso testes falhem.

### Quality Gate (Local CI)
- **Commit Guard:** Bloqueio de commits caso os testes locais falhem.
- **Test Runner Config:** Definição de comandos de teste via `.nomai/rules.yaml`.
