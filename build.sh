
release_flag=true

for arg in "$@"; do
    if [[ "$arg" == "--release" ]]; then
        release_flag=false
        break
    fi
done

mkdir -p build                                                            \
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
-o build/index.wasm                                                       \
main.c                                                                    \
&& cp -r fonts/ build/fonts                                               \
&& cp index.html build/index.html && cp -r images/ build/images           \

if $release_flag; then
    echo "Release mode activated."
    cp server.py build/server.py
fi