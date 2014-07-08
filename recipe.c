#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "recipe.h"

const int MAX_BUFFERLINE = 256;

char *strcpy_with_alloc(char *src_str) {
  char *dst_str = (char *)malloc(sizeof(char) * (strlen(src_str) + 1));
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
  free(recipe->url);
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

  for (int i = 0; i < list->size; i++) {
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
  if ((fp = fopen(path , "r")) == NULL) {
    fprintf (stderr, "ファイルが開けません\n");
    fclose(fp);
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
  fclose(fp);
}

void print_RecipeList(RecipeList *list) {
  for (int i = 0; i < list->size; i++) {
    print_Recipe(list->list[i]);
  }
}

void print_target_recipe_RecipeList(RecipeList *list, int id){
  for (int i = 0; i < list->size; i++) {
    Recipe *recipe = list->list[i];
    if (recipe->id == id) {
      print_Recipe(recipe);
    }
  }
}

User *create_User(char *name, RecipeList *list) {
  User *instance = (User *)malloc(sizeof(User));

  instance->name = strcpy_with_alloc(name);
  instance->list = list;

  return instance;
}

void destroy_User(User *user) {
  free(user->name);
  free(user);
}

void print_name_User(User *user) {
  printf("ユーザ名: %s\n", user->name);
}

void print_recipe_list_User(User *user) {
  print_RecipeList(user->list);
}

void print_target_recipe_User(User *user, int id) {
  print_target_recipe_RecipeList(user->list, id);
}

void check_arguments(int argc, char *argv[]) {
  /* 引数の処理 */
  if (argc < 3) {
    fprintf ( stderr, "Usage:%s user_name file_name [recipe_id]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}

int main (int argc, char* argv[]){
  check_arguments(argc, argv);  /* 引数チェック */

  char *recipe_path = argv[2];
  int recipe_id = argc > 3 ? atoi(argv[3]) : -1;
  char *user_name = argv[1];


  RecipeList *recipe_list = create_RecipeList();
  open_RecipeList(recipe_list, recipe_path);

  User *user = create_User(user_name, recipe_list);

  print_name_User(user);
  if (recipe_id == -1) {
    print_recipe_list_User(user);
  } else {
    print_target_recipe_User(user, recipe_id);
  }

  destroy_RecipeList(recipe_list);
  destroy_User(user);
  return EXIT_SUCCESS;
}
