# CHaser Client Library - C Language

## 本プログラムについて

[U-16プログラミングコンテスト](http://www.procon-asahikawa.org/)の競技部門で利用できるC言語ライブラリです。

## U-16プログラミングコンテストとは
2011年に北海道旭川市での開催をはじまりとし、全国にて行われているプログラミングコンテストです。

競技部門はCHaserと呼ばれる対戦競技を行います。
CHaserは2人で対戦する競技であり、競技サーバと2つのクライアントプログラムを用います。
競技サーバ上で行われる対戦は、碁盤の目状のマップが用意されており、アイテムやブロックが配置されています。

各クライアントプログラムはブロックを避けながら、アイテムを回収し、任意のタイミングでマップ上にブロックを配置する動作を行います。

勝敗は「対戦相手の上にブロックを配置する」「アイテムの回収数」「相手の周囲4方向をブロックで囲む」などにより決定します。

本プログラミングコンテストの参加者はクライアントプログラムの行動を制御するプログラムを開発します。


## C言語ライブラリの利用方法

本ライブラリはgcc(C言語コンパイラ)を用いてコンパイルすることと想定しています。

### コンパイル方法

```
gcc tst.c
```

コンパイルの結果`a.out`というファイルが出力され、これが実行ファイルです。

### プログラムの実行
コンパイルして出来た`a.out`は以下の方法で実行します。

```
./a.out <競技サーバのIPアドレス> <ポート番号>
```

競技サーバのIPアドレスが192.168.1.xxx、ポートが2209の場合の実行方法は以下のとおりです。

```
./a.out 192.168.1.xxx 2009
```

## ライブラリの構成
本ライブラリは以下のファイルで構成されており、新たにクライアントプログラムを作る際には以下のファイルを同一のフォルダに格納の上ご利用ください。

|ファイル名|説明|
|---|---|
|proConnect.h|競技用のライブラリヘッダファイル|
|proConnect.c|競技用のライブラリファイル|

`tst.c`はライブラリの利用方法を記載したサンプルプログラムです。