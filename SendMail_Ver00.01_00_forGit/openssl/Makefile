#============================================================

# 各項目を設定してください

# file name and dir of openSSL
path = ./openssl*.tar.gz

# 生成ファイル名
TARGET = openssl

#============================================================

SRC      = $(wildcard $(path))
fileName = $(patsubst %.tar.gz,%, $(SRC))

# openssl のコンパイル
$(TARGET):
	@echo "\n============================================================\n"
	@echo "     SRC: $(SRC)"
	@echo "fileName: $(fileName)"
	@echo "\n============================================================\n"
	tar xzvf $(SRC)
	mv $(fileName) ./$(TARGET)
	(cd ./$(TARGET); ./config --openssldir=../ shared; make -j; make)


.PHONY: all
all:
	@(make clean)
	@(make)
#	make clean ; \	#別表記
#	make			#別表記


.PHONY: clean
clean:
	-rm -rf $(TARGET)
