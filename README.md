# libmxdrv
MXDRV function call C bridge library for X68k

elf2x68k環境向けのMXDRVのファンクションコールラッパーCライブラリです。

MXDRVのファンクションコールに準じた以下の関数が利用可能です。
```
#include <mxdrv.h>

uint32_t mxdrv_load_mml(uint8_t* mml_data, size_t mml_len, uint8_t* data_title, int16_t use_pdx);
uint32_t mxdrv_load_pcm(uint8_t* pcm_data, size_t pcm_len, uint8_t* pcm_name);
uint32_t mxdrv_m_play();
uint32_t mxdrv_m_end();
uint32_t mxdrv_m_stop();
uint32_t mxdrv_m_cont();
uint8_t* mxdrv_mml_name();
uint8_t* mxdrv_pcm_name();
uint32_t mxdrv_m_fadeout(uint16_t speed);
uint16_t mxdrv_m_stat();
uint16_t mxdrv_m_stat2();
```

また、MXDRVの常駐確認を行う関数も利用可能です。
```
int16_t mxdrv_isavailable();
```


使う時は、サブモジュールとして組み込むのが簡単です。例えばプロジェクト直下にて以下を実行します。

```
git submodule add https://github.com/tantanGH/libmxdrv.git libs/libmxdrv
```

以下のようなツリーとなります。

```
my_app/
├── .git/
├── .gitmodules
├── libs/
│   └── libmxdrv/
│       ├── include/mxdrv.h
│       └── lib/libmxdrv.a
└── src/
    ├── main.c
    └── Makefile
```

ヘッダー検索パスとライブラリ検索パスをMakefile内で
```
-I../libs/libj/include
-L../libs/libj/lib
```
のように指定し、`-ldos -liocs -lmxdrv` でリンクできます。
内部的にDOSコールとIOCSコールを使っているため、`-ldos -liocs`もリンクしてください。