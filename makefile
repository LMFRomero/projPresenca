CP = g++
HEADER = -I ./header

all: computer keyboard screen db aula bixo
	$(CP) *.o main.cpp -o prog $(HEADER)

run: clean
	./prog

clean:
	rm -rf *.o

computer:
	$(CP) -c Computer.cpp $(HEADER)

keyboard:
	$(CP) -c Keyboard.cpp $(HEADER)

screen:
	$(CP) -c Screen.cpp  $(HEADER)

db:
	$(CP) -c Database.cpp $(HEADER)

bixo:
	$(CP) -c Bixo.cpp $(HEADER)

aula:
	$(CP) -c Aula.cpp $(HEADER)
