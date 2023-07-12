#include <iostream> 

class Primeira {
	public:
	Primeira() {
		std::cout << "Iniciando a primeira..." << "\n"; 
	}
	~Primeira() {
		std::cout << "Terminando a primeira..." << "\n"; 
	}
	void fmembro1() {
		std::cout << "fmembro da primeira" << "\n"; 	
	}
};

class Segunda {
	public: 
	
	virtual void f_membro_npode_ser_inst() = 0;
	
	Segunda() {
		std::cout << "Iniciando a Segunda..." << "\n"; 
	}
	~Segunda() {
		std::cout << "Terminando a Segunda..." << "\n"; 
	}
	void fmembro2() {
		std::cout << "fmembro da Segunda" << "\n"; 	
	}
};

class Terceira : public Primeira, public Segunda {
	public: 
	
	void f_membro_npode_ser_inst() {
		std::cout << "Imprimiu ..." << "\n"; 
	}
	
	Terceira() {
		std::cout << "Iniciando a Terceira..." << "\n"; 
	}
	~Terceira() {
		std::cout << "Terminando a Terceira..." << "\n"; 
	}
	void fmembro3() {
		std::cout << "fmembro da Terceira" << "\n"; 	
	}
};

int main(int argc, char** argv) {
	Terceira ter; 
	ter.fmembro2(); 
	ter.f_membro_npode_ser_inst();
	return 0; 
}
