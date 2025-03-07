## wasmでWebSocketにアクセスするサンプル
### ビルド方法
1. emsdkを有効にする。
2. 本プロジェクト直下で `emcmake cmake -B build-web -G Ninja`を実行。
3. 続けて `cmake --build build-web`を実行。
4. Webサーバー起動。 `python -m http.server -d build-web -port 3000`
