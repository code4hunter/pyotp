
CC=g++

CFLAGS=-D_DEBUG -g -Wall -fPIC -lrt

INCEX= ../../sdk/inc

LIB= -L ../../sdk/linux/linux64 \
     -lksotpmarketdataapi \
     -lkslkc64r

ifeq ($(vtype),32r)
    CFLAGS= -O2  -m32 -fPIC
    LIB:=$(subst lnx64,lnx32,${LIB})
    LIB:=$(subst kslkc64r,kslkc32r,${LIB})
endif

ifeq ($(vtype),64r)
    CFLAGS= -O2 -fPIC
endif

all: testKSOTPMarketAPI

testKSOTPMarketAPI: testKSOTPMarketAPI.o
	${CC} ${CFLAGS} -o $@ $^  ${LIB} 
testKSOTPMarketAPI.o: testKSOTPMarketAPI.cpp
	${CC} ${CFLAGS} -o $@ -c $^ -I ${INCEX}
clean:
	rm *.o testKSOTPMarketAPI 
