#include<stdio.h>
#include<string.h>

int main (int argc, char* argv[]){
  FILE *recipe_fp;

  /* Usageの表示 */
  if (argc < 2){

    fprintf (stderr, "Usage:recipe [file_name]\n");
    return -1;
  }

  /* ファイルを開く */
  char *recipe_file_path = argv[1];
  if ((recipe_fp = fopen(recipe_file_path , "r")) == NULL){

    fprintf (stderr, "ファイルが開けません\n");
    return -1;
  }

  /* 全てのレシピを出力 */
  char recipe_line[256];
  int recipe_id = 1;
  while (fscanf (recipe_fp, "%s", recipe_line) != EOF){

    if( strlen(recipe_line) == 0) continue;
    printf ("%d: %s\n", recipe_id, recipe_line);
    recipe_id++;
  }

  return 0;
}
