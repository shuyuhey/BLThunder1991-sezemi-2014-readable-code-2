#include<stdio.h>

int main (int argc, char* argv[]){
  FILE *recipe_fp;

  /* エラー処理 */
  if (argc < 2){
    fprintf (stderr, "Usage:recipe [file_name]\n");
    return -1;
  }
  char *recipe_file_path = argv[1];
  if ((recipe_fp = fopen(recipe_file_path , "r")) == NULL){
    fprintf (stderr, "ファイルが開けません\n");
    return -1;
  }

  /* 全てのレシピを出力 */
  char recipe_line[256];
  while (fscanf (recipe_fp, "%s", recipe_line) != EOF){
    printf ("%s\n", recipe_line);
  }

  return 0;
}
