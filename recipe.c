#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "recipe.h"

Recipe *create_Recipe(int id, char *name) {
  Recipe *instance = (Recipe *)malloc(sizeof(Recipe));

  instance->id = id;
  instance->name = (char *)malloc(sizeof(char) * strlen(name));
  sprintf(instance->name, "%s", name);

  return instance;
}

void destroy_Recipe(Recipe *recipe){
  free(recipe->name);
  free(recipe);
}

void print_Recipe(Recipe *recipe){
  printf("%d: %s\n", recipe->id, recipe->name);
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

  char line[256];  /* 一行の文字数 */
  while (fscanf (fp, "%s", line) != EOF){
    if (strlen(line) == 0) continue;

    int id = list->size;
    Recipe *recipe = create_Recipe(id, line);
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
  return EXIT_SUCCESS;
}
