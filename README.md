# 開発言語

C

# プログラムの説明
現状満たしている仕様: 仕様8まで

## ファイルフォーマット recipe-data.txt

```sh
% cat recipe-data.txt
オムライス http://cookpad.com/recipe/2653946
親子丼 http://cookpad.com/recipe/2657882
杏仁豆腐 http://cookpad.com/recipe/2654398
```

## プログラムのコンパイルと実行
gccを使用してビルドする

```sh
% gcc -std=c99 recipe.c -o recipe
```

プログラムの使用方法
```sh
% ./recipe ユーザ名 ファイル名 [レシピID（オプション）]
```

プログラムの実行
```sh
% ./recipe BLThunder recipe-data.txt
ユーザ名: BLThunder
0: オムライス http://cookpad.com/recipe/2653946
1: 親子丼 http://cookpad.com/recipe/2657882
2: 杏仁豆腐 http://cookpad.com/recipe/2654398
```
