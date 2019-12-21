main:
	@echo "Building ..."
	mkdir -p build
	g++ main.cpp -o build/typing-game
	@echo "Done!"

generator:
	@echo "Building ..."
	mkdir -p build
	g++ word-generator.cpp -o build/word-generator
	@echo "Done!"

run:
	./build/typing-game text.txt
