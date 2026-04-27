#PARA CRIAR A BUILD, esteja dentro da pasta do código
cmake -S . -B build
#Para compilar
cmake --build build
#Para rodar o codigo
./build/${PROJECT-NAME}
