# AviUtl プラグイン - ズーム変更

* version 1.0.0 by 蛇色 - 2022/03/15 初版

拡張編集ウィンドウのタイムラインのズーム値を変更します。

![ズーム変更](https://user-images.githubusercontent.com/96464759/158314982-969f31c0-65c1-4e97-bb91-430bc00dbe02.png)

## 導入方法

以下のファイルを AviUtl の Plugins フォルダに入れてください。
* SetZoom.auf
* SetZoom.ini

## 使用方法

1. トラックバーを動かしてよく使用するズーム値を予め決定しておきます。
2. ボタンを押してズーム値を適用します。

## 設定方法

SetZoom.ini をテキストエディタで編集してから AviUtl を起動します。

```ini
[Settings]
Zoom1=0
Zoom2=5
Zoom3=10
Zoom4=15
Zoom5=20
Zoom6=26
; 各トラックバーの初期値を指定します。(0～26)
```

## 動作確認

* (必須) AviUtl 1.10 & 拡張編集 0.92 http://spring-fragrance.mints.ne.jp/aviutl/
* (共存確認) patch.aul r14 https://www.nicovideo.jp/watch/sm40087155

## 参考サイト

* Auls https://auls.client.jp/
	* yulib、aulslib を使用しています。
