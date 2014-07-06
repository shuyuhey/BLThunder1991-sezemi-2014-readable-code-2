# 開発言語

C

# README.md
現状満たしている仕様: 仕様5まで

## ファイルフォーマット recipe-data.txt

    % cat recipe-data.txt
    オムライス
    親子丼
    杏仁豆腐


## プログラムのコンパイルと実行
gccを使用してビルドする

    % gcc recipe.c -o recipe

プログラムの使用方法

    % ./recipe [ファイル名]

プログラムの実行

    % ./recipe recipe-data.txt
    オムライス
    親子丼
    杏仁豆腐
