
release_flag=true

for arg in "$@"; do
    if [[ "$arg" == "--release" ]]; then
        release_flag=false
        break
    fi
done

build_dir="build"
if $release_flag; then
    build_dir="build/ookee"  # Change to build/ookee if release_flag is set
fi

mkdir -p $build_dir                                                       \
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
-o $build_dir/index.wasm                                                  \
main.c                                                                    \
&& cp -r fonts/ $build_dir/fonts                                          \
&& cp index.html build/index.html && cp -r images/ $build_dir/images      \

if $release_flag; then
    echo "Release mode activated."                                            
    cp server.py build/server.py
fi