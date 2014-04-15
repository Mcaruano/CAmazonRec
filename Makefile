
all: ListListdr ListHashdr Recommendation Debug
	
ListListdr:
	gcc ListListdr.c ListList.h ListList.c -o ListListdr
	
ListHashdr:
	gcc ListHashdr.c ListHash.h ListList.h ListHash.c ListList.c -o ListHashdr

Recommendation:
	gcc Recommendation.c ListHash.h ListList.h ListHash.c ListList.c -o Recommendation

Debug:
	gcc -g Recommendation.c ListHash.h ListList.h ListHash.c ListList.c -o debug

clean:
	rm Recommendation debug
