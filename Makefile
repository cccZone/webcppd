PRO=$(shell basename `realpath .`)

all:
	cd src && make && cd ..

clean:
	cd src && make clean && cd ..
	
run:
	./$(PRO) --daemon

stop:
	kill `pidof $(PRO)`
