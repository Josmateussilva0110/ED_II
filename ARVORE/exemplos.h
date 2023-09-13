typedef struct arvore Arvore;
Arvore *criar_no(int valor);
Arvore *inserir(Arvore *no, int valor);
void exibir(Arvore *no);
Arvore *tree_min(Arvore *no);
Arvore *tree_max(Arvore *no);
Arvore *tree_search(Arvore *x, int k);
Arvore *tree_sucessor(Arvore *x);
