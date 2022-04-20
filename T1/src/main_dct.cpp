#include <iostream>

#include "FileInterpreter.h"

using namespace std;

/*
    TODO:
    -->interface!
	-->Comentar o código direitinho!
	-->TABULAR CORRETAMENTE: 3 <<ESPAÇOS>> DE IDENTAÇÃO!
*/

int main() {

    FileInterpreter fi;
    try {
        vector<SampleCollection> *vi = fi.readFile("D:\in.txt");
        for(int n = 0; n < (int)vi->size(); n++) {
            vi->at(n).printAll();
        }
        delete vi;
    } catch (exception &e) {
        cout << "Erro: " << e.what() << endl;
    }

	system("pause");

    return 0;
}
