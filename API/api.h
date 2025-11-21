#ifndef API_H
#define API_H

/* Funções retornam int: 0 = sucesso, -1 = erro (quando aplicável) */
int api_init(void);
int api_finalize(void);

/* operações que retornam status */
int api_reset_cpa(void);
int api_refresh_cpa(void);

/* VMP / repixel / blocos - retornam status */
int api_vmp_in(void);
int api_vmp_out(void);
int api_repixel(void);
int api_mblocos(void);

/* Carregar e armazenar:
   api_load retorna o valor lido (em r0) - use convenção int
   api_store pode receber um caminho se desejar; no asm atual r0 é ignorado,
   mas manter assinatura que recebe um const char* é mais explícito. */
int api_load(int mem_sel, int address);
int api_store(const char *file_path);

#endif /* API_H */
