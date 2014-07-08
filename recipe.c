#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "recipe.h"

const int MAX_BUFFERLINE = 256;

char *strcpy_with_alloc(char *src_str) {
  char *dst_str = (char *)malloc(sizeof(char) * strlen(src_str));
  sprintf(dst_str, "%s", src_str);
  return dst_str;
}

Recipe *create_Recipe(int id, char *name ,char *url) {
  Recipe *instance = (Recipe *)malloc(sizeof(Recipe));

  instance->id   = id;
  instance->name = strcpy_with_alloc(name);
  instance->url  = strcpy_with_alloc(url);

  return instance;
}

void destroy_Recipe(Recipe *recipe){
  free(recipe->name);
  free(recipe);
}

void print_Recipe(Recipe *recipe){
  printf("%d: %s %s\n", recipe->id, recipe->name, recipe->url);
}


RecipeList *create_RecipeList() {
  RecipeList *instance = (RecipeList *)malloc (sizeof(RecipeList));

  instance->size = 0;

  return instance;
}

void destroy_RecipeList(RecipeList *list){
  for (int i = 0; i < list->size; i++) {
    destroy_Recipe(list->list[i]);
  }
  free(list->list);
  free(list);
}

void add_recipe_to_RecipeList(RecipeList *list, Recipe *recipe) {
  size_t new_size = list->size + 1;
  Recipe **new_list = (Recipe **)malloc(sizeof(Recipe *) * new_size);

  int i;
  for (i = 0; i < list->size; i++) {
    new_list[i] = list->list[i];
  }
  new_list[new_size - 1] = recipe;
  list->size++;

  free(list->list);
  list->list = new_list;
}

void open_RecipeList(RecipeList *list, char *path) {
  FILE *fp;
  /* ファイルを開く */
  if ((fp = fopen(path , "r")) == NULL){
    fprintf (stderr, "ファイルが開けません\n");
    exit(EXIT_FAILURE);
  }

  char line[MAX_BUFFERLINE];  /* 一行の文字数 */
  while (fscanf (fp, "%[^\n]\n", line) != EOF){ /* 改行以外を読込 */
    if (strlen(line) == 0) continue;

    char name[MAX_BUFFERLINE];
    char url[MAX_BUFFERLINE];
    sscanf(line, "%s %s", name, url);

    int id = list->size;
    Recipe *recipe = create_Recipe(id, name, url);
    add_recipe_to_RecipeList(list, recipe);
  }
}

void print_RecipeList(RecipeList *list) {
  for (int i = 0; i < list->size; i++) {
    print_Recipe(list->list[i]);
  }
}

void print_target_recipe_RecipeList(RecipeList *list, int id){
  for (int i = 0; i < list->size; i++) {
    Recipe *recipe = list->list[i];
    if(recipe->id == id) {
      print_Recipe(recipe);
    }
  }
}

void usage(int argc, char *argv[]) {
  /* 引数の処理 */
  if (argc < 2){
    fprintf ( stderr, "Usage:%s file_name [recipe_id]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}

int main (int argc, char* argv[]){
  usage(argc, argv);
  char *recipe_path = argv[1];
  int recipe_id = argc > 2 ? atoi(argv[2]) : -1;

  RecipeList *recipe_list = create_RecipeList();
  open_RecipeList(recipe_list, recipe_path);
  if(recipe_id == -1) {
    print_RecipeList(recipe_list);
  }else {
    print_target_recipe_RecipeList(recipe_list, recipe_id);
  }

  destroy_RecipeList(recipe_list);
  return EXIT_SUCCESS;
}
