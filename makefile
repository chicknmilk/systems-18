all: pipe.c
	gcc -o pipe pipe.c

run: pipe
	./pipe

p:
	git add .
	git commit -m "push to comp"
	git push