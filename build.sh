# -v                                                                        \
mkdir -p build/clay                                                       \
&& clang                                                                  \
-Wall                                                                     \
-Werror                                                                   \
-Os                                                                       \
-DCLAY_WASM                                                               \
-mbulk-memory                                                             \
--target=wasm32                                                           \
-nostdlib                                                                 \
-fno-builtin                                                              \
-Wl,--strip-all                                                           \
-Wl,--export-dynamic                                                      \
-Wl,--no-entry                                                            \
-Wl,--export=__heap_base                                                  \
-Wl,--export=ACTIVE_RENDERER_INDEX                                        \
-Wl,--initial-memory=6553600                                              \
-o build/clay/index.wasm                                                  \
main.c                                                                    \
&& cp server.py build/server.py && cp -r fonts/ build/clay/fonts          \
&& cp index.html build/index.html && cp -r images/ build/clay/images