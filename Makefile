agent: bfs.cpp dfs.cpp main.cpp ucs.cpp 
	@g++ bfs.cpp dfs.cpp main.cpp ucs.cpp -o agent
run: agent
	@./agent

