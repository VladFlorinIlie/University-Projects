.PHONY: build clean run

build: tema2

run:
	java -Xmx1G tema2POO/Main ${ARGS}

tema2:
	javac -d ./ src/*.java src/*/*.java

clean:
	rm -rf tema2POO
