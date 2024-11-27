 
for i in {0..6}; do
    convert "portrait$i.png" -strip -interlace Plane -colors 256 -quality 85 "portrait$i-optimized.png"
done
