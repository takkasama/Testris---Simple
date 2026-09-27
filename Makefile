
.PHONY: all clean resources

all: Debug resources Debug/Tetris-Simple.bin

clean:
	rm -rf ${OBJS} Debug/Tetris-Simple.bin Debug/resources

Debug:
	mkdir -p Debug

resources:
	cp -r resources Debug/
