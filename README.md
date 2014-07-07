# 開発言語

C

# プログラムの説明
現状満たしている仕様: 仕様6まで

## ファイルフォーマット recipe-data.txt

```sh
% cat recipe-data.txt
オムライス
親子丼
杏仁豆腐
```

## プログラムのコンパイルと実行
gccを使用してビルドする

```sh
% gcc recipe.c -o recipe
```

プログラムの使用方法
```sh
% ./recipe ファイル名 [レシピID（オプション）]
```

プログラムの実行
```sh
% ./recipe recipe-data.txt
0: オムライス
1: 親子丼
2: 杏仁豆腐
```
