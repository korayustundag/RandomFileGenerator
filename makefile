build:
	g++ -std=c++11 rfg.cpp -o rfg

release:
	g++ -std=c++11 rfg.cpp -O2 -o rfg

pack: release
	tar -czvf rfg_v1.0.0_amd64.tar.gz rfg
