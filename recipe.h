#ifndef RECIPE_H
#define RECIPE_H

typedef struct {
  int id;
  char *name;
  char *url;
} Recipe;

typedef struct {
  size_t size;
  Recipe **list;
} RecipeList;

typedef struct {
  char *name;
  RecipeList *list;
}User;


#endif
