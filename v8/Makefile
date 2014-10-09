LIBS = 
for lib in /home/thiago/src/v8/out/x64.release/obj.target/tools/gyp/libv8_{base.x64,snapshot}.a,/home/thiago/src/v8/out/x64.release/obj.target/third_party/icu/libicu{i18n,uc,data}.a; do ${LIBS} += ${lib}; done;

all:
	g++ -Wall hello_world.cpp -o hello_world $(LIBS) -lpthread
