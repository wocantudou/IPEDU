/data/kaiyao3/SEE_EN_STUDY/arm-himix200-linux/build/arm-himix200-linux/bin/arm-himix200-linux-gcc -O2 -fPIC -c ./source/common/common.c ./source/decrypt/decrypt.c -I ./include
/data/kaiyao3/SEE_EN_STUDY/arm-himix200-linux/build/arm-himix200-linux/bin/arm-himix200-linux-ar -r libdecrypt.a common.o decrypt.o
rm -fr common.o decrypt.o

/data/kaiyao3/SEE_EN_STUDY/arm-himix200-linux/build/arm-himix200-linux/bin/arm-himix200-linux-gcc -O2 -fPIC -o encrypt_test ./source/encrypt_test/encrypt_test.c ./source/common/common.c ./source/decrypt/decrypt.c ./source/encrypt/encrypt.c -I ./include
mv encrypt_test ./bin/encrypt_test
mv libdecrypt.a ./lib/libdecrypt.a